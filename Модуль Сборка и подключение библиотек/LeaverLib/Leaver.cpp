#include "Leaver.h"
#include <string>

namespace LeaverLibrary 
{
    std::string Leaver::leave(const std::string& name) 
    {
        return "До свидания, " + name + "!";
    }
}