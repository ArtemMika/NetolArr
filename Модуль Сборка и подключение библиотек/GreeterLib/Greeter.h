#ifndef GREETER_H
#define GREETER_H

#include <string>

namespace GreeterLibrary 
{
    class Greeter 
    {
    public:
        std::string greet(const std::string& name);
    };
}

#endif // GREETER_H