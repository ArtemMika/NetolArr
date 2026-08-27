#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

int main() 
{
    const int maxClients = 10;

    // счётчик клиентов в очереди
    int clientsInQueue = 0;

    // Мьютекс для защиты доступа к общей переменной
    std::mutex queueMutex;

    // Флаг для остановки потока клиента, лимит
    std::atomic<bool> clientGeneratorRunning{ true };

    // Поток 1
    auto clientThreadFunc = [&]() {
        while (clientGeneratorRunning.load())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Блокируем мьютекс
            std::lock_guard<std::mutex> lock(queueMutex);
            if (clientsInQueue < maxClients) 
            {
                ++clientsInQueue;
                std::cout << "[Клиент] Пришёл новый клиент. В очереди: "
                    << clientsInQueue << "\n";
            }
            else
            {
                std::cout << "[Клиент] Лимит очереди достигнут ("
                    << maxClients << "). Новые клиенты не принимаются.\n";

                clientGeneratorRunning.store(false);
            }
        }
        };

    // Поток 2
    auto operatorThreadFunc = [&]() 
        {
        while (true) 
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));

            std::lock_guard<std::mutex> lock(queueMutex);

            if (clientsInQueue > 0) 
            {
                --clientsInQueue;
                std::cout << "[Операционист] Клиент обслужен. В очереди: "
                    << clientsInQueue << "\n";
            }
            else {
                std::cout << "[Операционист] Очередь пуста. Работа завершена.\n";
                break; //клиентов больше нет
            }
        }
        };

    // Запуск потоков
    std::thread clientThread(clientThreadFunc);
    std::thread operatorThread(operatorThreadFunc);

    //завершения обоих потоков
    clientThread.join();
    operatorThread.join();

    std::cout << "Имитация очереди завершена.\n";
    return 0;
}