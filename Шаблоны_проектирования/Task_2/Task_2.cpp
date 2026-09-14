#include "task_2.h"
#include <iostream>
#include <cassert>

int main()
{
    SqlSelectQueryBuilder query_builder;

    query_builder.AddColumns({ "name", "phone", "email" });

    query_builder.AddFrom("students");

    query_builder.AddWhere("id", "42");

    query_builder.AddWhere({ {"name", "John"}, {"age", "20"} });

    std::string result = query_builder.BuildQuery();
    std::string expected = "SELECT name, phone, email FROM students WHERE id=42 AND name=John AND age=20;";

    assert(result.find("SELECT name, phone, email") != std::string::npos);
    assert(result.find("FROM students") != std::string::npos);
    assert(result.find("id=42") != std::string::npos);
    assert(result.find("name=John") != std::string::npos);
    assert(result.find("age=20") != std::string::npos);
    assert(result.back() == ';');
    std::cout << result << "\n";

    return 0;
}