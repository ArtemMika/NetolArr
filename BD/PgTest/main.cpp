#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <libpq-fe.h>

#ifdef _WIN32
#include <windows.h>
#endif

// --- Структура данных клиента в C++ ---
struct Client {
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

// --- Класс управления клиентами (строго по заданию) ---
class ClientManager {
public:
    explicit ClientManager(const std::string& conninfo)
        : conninfo_(conninfo), conn_(nullptr) {
    }

    ~ClientManager() {
        if (conn_) PQfinish(conn_);
    }

    // 1. Создать структуру БД (таблицы)
    bool createSchema() {
        PGconn* tmp = PQconnectdb(conninfo_.c_str());
        if (!tmp || PQstatus(tmp) != CONNECTION_OK) {
            std::cerr << "Ошибка подключения для createSchema: " << PQerrorMessage(tmp) << "\n";
            if (tmp) PQfinish(tmp);
            return false;
        }

        const char* sqlClients =
            "CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY,"
            "first_name VARCHAR(100) NOT NULL,"
            "last_name  VARCHAR(100) NOT NULL,"
            "email      VARCHAR(255) UNIQUE NOT NULL);";

        PGresult* res = PQexec(tmp, sqlClients);
        if (PQresultStatus(res) != PGRES_COMMAND_OK &&
            PQresultStatus(res) != PGRES_EMPTY_QUERY) {
            std::cerr << "Ошибка создания clients: " << PQresultErrorMessage(res) << "\n";
            PQclear(res); PQfinish(tmp); return false;
        }
        PQclear(res);

        const char* sqlPhones =
            "CREATE TABLE IF NOT EXISTS client_phones ("
            "id SERIAL PRIMARY KEY,"
            "client_id INTEGER NOT NULL REFERENCES clients(id) ON DELETE CASCADE,"
            "phone      VARCHAR(50) NOT NULL);";

        res = PQexec(tmp, sqlPhones);
        if (PQresultStatus(res) != PGRES_COMMAND_OK &&
            PQresultStatus(res) != PGRES_EMPTY_QUERY) {
            std::cerr << "Ошибка создания client_phones: " << PQresultErrorMessage(res) << "\n";
            PQclear(res); PQfinish(tmp); return false;
        }
        PQclear(res);
        PQfinish(tmp);
        return true;
    }

    // Вспомогательный: открыть соединение (нужно для остальных методов)
    bool connect() {
        conn_ = PQconnectdb(conninfo_.c_str());
        if (!conn_ || PQstatus(conn_) != CONNECTION_OK) {
            std::cerr << "Ошибка подключения: " << PQerrorMessage(conn_) << "\n";
            if (conn_) { PQfinish(conn_); conn_ = nullptr; }
            return false;
        }
        return true;
    }

    // 2. Добавить нового клиента
    int addClient(const std::string& first_name, const std::string& last_name,
        const std::string& email) {
        if (!conn_) return -1;

        const char* sql =
            "INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING id;";
        const char* values[3] = { first_name.c_str(), last_name.c_str(), email.c_str() };
        int lengths[3] = { static_cast<int>(first_name.size()),
                          static_cast<int>(last_name.size()),
                          static_cast<int>(email.size()) };
        int formats[3] = { 0, 0, 0 };

        PGresult* res = PQexecParams(conn_, sql, 3, nullptr, values, lengths, formats, 1);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Ошибка добавления клиента: " << PQresultErrorMessage(res) << "\n";
            PQclear(res); return -1;
        }

        int id = std::stoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        return id;
    }

    // 3. Добавить телефон для существующего клиента
    bool addPhone(int client_id, const std::string& phone) {
        if (!conn_) return false;

        const char* sql = "INSERT INTO client_phones (client_id, phone) VALUES ($1, $2);";
        std::string idStr = std::to_string(client_id);
        const char* values[2] = { idStr.c_str(), phone.c_str() };
        int lengths[2] = { static_cast<int>(idStr.size()), static_cast<int>(phone.size()) };
        int formats[2] = { 0, 0 };

        PGresult* res = PQexecParams(conn_, sql, 2, nullptr, values, lengths, formats, 0);
        bool ok = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!ok) std::cerr << "Ошибка добавления телефона: " << PQresultErrorMessage(res) << "\n";
        PQclear(res);
        return ok;
    }

    // 4. Изменить данные о клиенте
    bool updateClient(int client_id, const std::string& first_name,
        const std::string& last_name, const std::string& email) {
        if (!conn_) return false;

        const char* sql =
            "UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4;";
        std::string idStr = std::to_string(client_id);
        const char* values[4] = { first_name.c_str(), last_name.c_str(),
                                 email.c_str(), idStr.c_str() };
        int lengths[4] = { static_cast<int>(first_name.size()),
                          static_cast<int>(last_name.size()),
                          static_cast<int>(email.size()),
                          static_cast<int>(idStr.size()) };
        int formats[4] = { 0, 0, 0, 0 };

        PGresult* res = PQexecParams(conn_, sql, 4, nullptr, values, lengths, formats, 0);
        bool ok = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!ok) std::cerr << "Ошибка обновления клиента: " << PQresultErrorMessage(res) << "\n";
        PQclear(res);
        return ok;
    }

    // 5. Удалить телефон у существующего клиента
    bool removePhone(int client_id, const std::string& phone) {
        if (!conn_) return false;

        const char* sql = "DELETE FROM client_phones WHERE client_id = $1 AND phone = $2;";
        std::string idStr = std::to_string(client_id);
        const char* values[2] = { idStr.c_str(), phone.c_str() };
        int lengths[2] = { static_cast<int>(idStr.size()), static_cast<int>(phone.size()) };
        int formats[2] = { 0, 0 };

        PGresult* res = PQexecParams(conn_, sql, 2, nullptr, values, lengths, formats, 0);
        bool ok = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!ok) std::cerr << "Ошибка удаления телефона: " << PQresultErrorMessage(res) << "\n";
        PQclear(res);
        return ok;
    }

    // 6. Удалить существующего клиента
    bool deleteClient(int client_id) {
        if (!conn_) return false;

        const char* sql = "DELETE FROM clients WHERE id = $1;";
        std::string idStr = std::to_string(client_id);
        const char* values[1] = { idStr.c_str() };
        int lengths[1] = { static_cast<int>(idStr.size()) };
        int formats[1] = { 0 };

        PGresult* res = PQexecParams(conn_, sql, 1, nullptr, values, lengths, formats, 0);
        bool ok = (PQresultStatus(res) == PGRES_COMMAND_OK);
        if (!ok) std::cerr << "Ошибка удаления клиента: " << PQresultErrorMessage(res) << "\n";
        PQclear(res);
        return ok;
    }

    // 7. Найти клиента по имени, фамилии, email или телефону
    std::vector<Client> findClients(const std::string& first_name_like,
        const std::string& last_name_like,
        const std::string& email_like,
        const std::string& phone_like) {
        std::vector<Client> result;
        if (!conn_) return result;

        // Сначала ищем клиентов по полям в clients
        std::ostringstream sql;
        sql << "SELECT id, first_name, last_name, email FROM clients WHERE 1=1";
        std::vector<std::string> params;
        int paramIndex = 1;

        if (!first_name_like.empty()) {
            sql << " AND first_name ILIKE $" << paramIndex;
            params.push_back("%" + first_name_like + "%");
            paramIndex++;
        }
        if (!last_name_like.empty()) {
            sql << " AND last_name ILIKE $" << paramIndex;
            params.push_back("%" + last_name_like + "%");
            paramIndex++;
        }
        if (!email_like.empty()) {
            sql << " AND email ILIKE $" << paramIndex;
            params.push_back("%" + email_like + "%");
            paramIndex++;
        }

        std::vector<const char*> valuesPtr(params.size());
        std::vector<int> lengths(params.size());
        for (size_t i = 0; i < params.size(); ++i) {
            valuesPtr[i] = params[i].c_str();
            lengths[i] = static_cast<int>(params[i].size());
        }

        PGresult* resClients = PQexecParams(conn_, sql.str().c_str(), static_cast<int>(params.size()),
            nullptr, params.empty() ? nullptr : valuesPtr.data(),
            params.empty() ? nullptr : lengths.data(), nullptr, 0);

        if (PQresultStatus(resClients) != PGRES_TUPLES_OK) {
            std::cerr << "Ошибка поиска клиентов: " << PQresultErrorMessage(resClients) << "\n";
            PQclear(resClients);
            return result;
        }

        int rows = PQntuples(resClients);
        for (int i = 0; i < rows; ++i) {
            Client c;
            c.id = std::stoi(PQgetvalue(resClients, i, 0));
            c.first_name = PQgetvalue(resClients, i, 1);
            c.last_name = PQgetvalue(resClients, i, 2);
            c.email = PQgetvalue(resClients, i, 3);

            // Подтягиваем телефоны для этого клиента
            const char* phoneSql = "SELECT phone FROM client_phones WHERE client_id = $1";
            std::string idStr = std::to_string(c.id);
            const char* pValues[1] = { idStr.c_str() };
            int pLengths[1] = { static_cast<int>(idStr.size()) };
            PGresult* resPhones = PQexecParams(conn_, phoneSql, 1, nullptr, pValues, pLengths, nullptr, 0);
            if (PQresultStatus(resPhones) == PGRES_TUPLES_OK) {
                int pRows = PQntuples(resPhones);
                for (int j = 0; j < pRows; ++j) {
                    c.phones.push_back(PQgetvalue(resPhones, j, 0));
                }
            }
            PQclear(resPhones);
            result.push_back(c);
        }
        PQclear(resClients);

        // Если задан фильтр по телефону — дополнительно отфильтруем
        if (!phone_like.empty()) {
            std::vector<Client> filtered;
            for (const auto& c : result) {
                for (const auto& p : c.phones) {
                    if (p.find(phone_like) != std::string::npos) {
                        filtered.push_back(c);
                        break;
                    }
                }
            }
            return filtered;
        }

        return result;
    }

private:
    std::string conninfo_;
    PGconn* conn_ = nullptr;
};

// --- Демонстрация работы (main) ---
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    const std::string conninfo = "host=localhost user=postgres dbname=postgres password=786826 port=5432";

    ClientManager manager(conninfo);

    if (!manager.connect()) 
    {
        std::cerr << "Не удалось подключиться к БД.\n";
        return 1;
    }

    // 1. Создать схему БД
    if (!manager.createSchema()) 
    {
        std::cerr << "Не удалось создать схему БД.\n";
        return 1;
    }
    std::cout << "Схема БД готова.\n";

    // 2. Добавить новых клиентов
    int id1 = manager.addClient("Иван", "Петров", "ivan.petrov@example.com");
    if (id1 == -1) 
    {
        std::cerr << "Ошибка добавления клиента 1.\n";
        return 1;
    }
    std::cout << "Добавлен клиент id=" << id1 << "\n";

    int id2 = manager.addClient("Анна", "Сидорова", "anna.sidorova@example.com");
    if (id2 == -1) {
        std::cerr << "Ошибка добавления клиента 2.\n";
        return 1;
    }
    std::cout << "Добавлен клиент id=" << id2 << "\n";

    // 3. Добавить телефоны (у Ивана несколько, у Анны пока нет)
    manager.addPhone(id1, "+79991112233");
    manager.addPhone(id1, "+79994445566");
    std::cout << "Телефоны добавлены.\n";

    // 4. Обновить данные клиента
    manager.updateClient(id1, "Иван", "Петров-Новый", "ivan.new@example.com");
    std::cout << "Данные клиента id=" << id1 << " обновлены.\n";

    // 5. Удалить один телефон
    manager.removePhone(id1, "+79991112233");
    std::cout << "Один телефон удалён у клиента id=" << id1 << ".\n";

    // 6. Поиск по email
    auto foundByEmail = manager.findClients("", "", "ivan.new", "");
    std::cout << "Найдено по email: " << foundByEmail.size() << "\n";
    for (const auto& c : foundByEmail) {
        std::cout << "  id=" << c.id << ", " << c.first_name << " " << c.last_name
            << ", email=" << c.email << "\n";
        std::cout << "    Телефоны: ";
        if (c.phones.empty()) 
        {
            std::cout << "(нет)";
        }
        else {
            for (const auto& p : c.phones) 
            {
                std::cout << p << " ";
            }
        }
        std::cout << "\n";
    }

    // Поиск по телефону
    auto foundByPhone = manager.findClients("", "", "", "+79994445566");
    std::cout << "Найдено по телефону: " << foundByPhone.size() << "\n";
    for (const auto& c : foundByPhone)
    {
        std::cout << "  Клиент: " << c.first_name << " " << c.last_name
            << " (id=" << c.id << ")\n";
    }

    // 7. Удалить существующего клиента (Анну)
    bool deletedClient = manager.deleteClient(id2);
    if (deletedClient)
    {
        std::cout << "Клиент id=" << id2 << " удалён.\n";
    }
    else {
        std::cerr << "Ошибка удаления клиента.\n";
    }

    // Проверка: ищем Анну после удаления — должно быть 0
    auto checkAnna = manager.findClients("Анна", "", "", "");
    std::cout << "После удаления поиск по имени 'Анна' нашёл клиентов: "
        << checkAnna.size() << " (должно быть 0)\n";

    // Ещё одна проверка: у Ивана остался только один телефон
    auto checkIvan = manager.findClients("Иван", "", "", "");
    if (!checkIvan.empty()) {
        const auto& c = checkIvan[0];
        std::cout << "У клиента " << c.first_name << " осталось телефонов: "
            << c.phones.size() << "\n";
        std::cout << "Список телефонов: ";
        for (const auto& p : c.phones)
        {
            std::cout << p << " ";
        }
        std::cout << "\n";
    }

    return 0;
}