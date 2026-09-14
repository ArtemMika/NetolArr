#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& col : columns) {
            columns_.push_back(col);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) {
        where_conditions_.emplace_back(key, value);
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [key, value] : kv) {
            where_conditions_.emplace_back(key, value);
        }
        return *this;
    }

    std::string BuildQuery() const {
        if (table_.empty()) {
            return "";
        }

        std::ostringstream query;

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

        query << " FROM " << table_;

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