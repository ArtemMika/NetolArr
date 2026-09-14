#include "task_1.h"
#include <iostream>
#include <cassert>

int main() 
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string expected = "SELECT name, phone FROM students WHERE id=42 AND name=John;";
    std::string result = query_builder.BuildQuery();

    assert(result == expected);

    std::cout << "Query built successfully:\n" << result << "\n";

    SqlSelectQueryBuilder builder2;
    builder2.AddFrom("users").AddWhere("active", "1");
    std::cout << "SELECT * example:\n" << builder2.BuildQuery() << "\n";

    return 0;
}