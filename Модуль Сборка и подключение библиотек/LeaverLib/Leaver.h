#ifndef LEAVER_H
#define LEAVER_H
#include <string>

#ifdef LEAVERLIB_EXPORTS
#define LEAVERLIB_API __declspec(dllexport)
#else
#define LEAVERLIB_API __declspec(dllimport)
#endif

namespace LeaverLibrary 
{
    class LEAVERLIB_API Leaver 
    {
    public:
        std::string leave(const std::string& name);
    };
}

#endif // LEAVER_H