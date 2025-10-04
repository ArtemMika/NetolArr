#include "Greeter.h"
#include <string>

// Исправляем опечатку в названии namespace
namespace GreeterLibrary
{
    std::string Greeter::greet(const std::string& name) 
    {
        return "Здравствуйте, " + name + "!";
    }
}