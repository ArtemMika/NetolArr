#pragma once
#include <string>
#include <vector>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    // Добавление колонки
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    // Установка таблицы (перезаписывает предыдущую)
    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    // Добавление условия WHERE (ключ = значение)
    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) {
        where_conditions_.emplace_back(key, value);
        return *this;
    }

    // Построение запроса
    std::string BuildQuery() const {
        if (table_.empty()) {
            return ""; // Или выбросить исключение: "Table not specified"
        }

        std::ostringstream query;

        // SELECT часть
        query << "SELECT ";
        if (columns_.empty()) {
            query << "*";
        }
        else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                query << columns_[i];
                if (i != columns_.size() - 1) {
                    query << ", ";
                }
            }
        }

        // FROM часть
        query << " FROM " << table_;

        // WHERE часть
        if (!where_conditions_.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < where_conditions_.size(); ++i) {
                const auto& [key, value] = where_conditions_[i];
                query << key << "=" << value;
                if (i != where_conditions_.size() - 1) {
                    query << " AND ";
                }
            }
        }

        query << ";";
        return query.str();
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::vector<std::pair<std::string, std::string>> where_conditions_;
};