#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
#include <iomanip>

// ---- Разделяемые данные ----
std::atomic<int> queue_count{ 0 };     // текущий размер очереди
std::atomic<int> total_added{ 0 };    // сколько клиентов всего пришло
std::atomic<int> total_served{ 0 };    // сколько клиентов обслужено

// Глобальный параметр — модель упорядочения памяти
std::memory_order mem_order = std::memory_order_seq_cst;

// Мьютекс только для вывода в консоль (к счётчикам отношения не имеет)
#include <mutex>
std::mutex cout_mutex;

// ---- Вспомогательные функции ----
std::string order_name(std::memory_order mo) {
    switch (mo) {
    case std::memory_order_relaxed:  return "relaxed";
    case std::memory_order_acquire:  return "acquire";
    case std::memory_order_release:  return "release";
    case std::memory_order_acq_rel:   return "acq_rel";
    case std::memory_order_seq_cst:   return "seq_cst";
    default:                          return "unknown";
    }
}

void log(const std::string& who, const std::string& action) {
    std::lock_guard<std::mutex> lk(cout_mutex);
    std::cout << "[" << who << "] " << action
        << " | queue: " << queue_count.load(std::memory_order_relaxed)
        << " | added: " << total_added.load(std::memory_order_relaxed)
        << " | served: " << total_served.load(std::memory_order_relaxed)
        << std::endl;
}

// ---- Поток «Клиент» ----
// Раз в секунду увеличивает счётчик на 1, но не более max_clients раз
void client_thread(int max_clients) {
    for (int i = 0; i < max_clients; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Атомарное увеличение на 1
        queue_count.fetch_add(1, mem_order);
        total_added.fetch_add(1, mem_order);

        log("Client ", "arrived (#" + std::to_string(i + 1) + ")");
    }
}

// ---- Поток «Операционист» ----
// Раз в 2 секунды уменьшает счётчик на 1, работает до последнего клиента
void operator_thread(int max_clients) {
    while (total_served.load(mem_order) < max_clients) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Атомарное уменьшение на 1 только если очередь не пуста.
        // Используем compare_exchange, чтобы гарантировать атомарность
        // проверки «> 0» и декремента.
        int expected = queue_count.load(mem_order);
        while (expected > 0 &&
            !queue_count.compare_exchange_weak(
                expected,           // ожидаемое значение
                expected - 1,       // желаемое новое значение
                mem_order,          // упорядочение при успехе
                std::memory_order_relaxed)) {  // при неудаче
            // Если CAS не сработал, expected обновлён на актуальное значение.
            // Цикл повторится с новым expected.
        }

        if (expected > 0) {
            // Успешно забрали клиента из очереди
            total_served.fetch_add(1, mem_order);
            log("Operator", "served a client");
        }
        else {
            log("Operator", "no clients, waiting...");
        }
    }
}

// ---- Запуск одной симуляции ----
void run_simulation(int max_clients, std::memory_order order) {
    // Сброс счётчиков
    queue_count.store(0, std::memory_order_relaxed);
    total_added.store(0, std::memory_order_relaxed);
    total_served.store(0, std::memory_order_relaxed);
    mem_order = order;

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  Max clients: " << max_clients
        << " | Memory order: " << order_name(order) << std::endl;
    std::cout << "  Client: +1 every 1s | Operator: -1 every 2s" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::thread t_client(client_thread, max_clients);
    std::thread t_operator(operator_thread, max_clients);

    t_client.join();
    t_operator.join();

    std::cout << "\n  Total added:  "
        << total_added.load(std::memory_order_relaxed) << std::endl;
    std::cout << "  Total served: "
        << total_served.load(std::memory_order_relaxed) << std::endl;
    std::cout << "  Queue left:   "
        << queue_count.load(std::memory_order_relaxed) << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

// ---- main ----
int main(int argc, char* argv[]) {
    int max_clients = 5;
    if (argc > 1) {
        max_clients = std::stoi(argv[1]);
    }

    // Проверяем три режима упорядочения памяти
    run_simulation(max_clients, std::memory_order_seq_cst);
    run_simulation(max_clients, std::memory_order_acq_rel);
    run_simulation(max_clients, std::memory_order_relaxed);

    return 0;
}