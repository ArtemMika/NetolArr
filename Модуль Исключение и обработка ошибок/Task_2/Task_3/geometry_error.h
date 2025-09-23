#pragma once
#include <stdexcept>
#include <string>

class GeometryError : public std::domain_error 
{
public:
    explicit GeometryError(const std::string& message) : std::domain_error(message) {}
};