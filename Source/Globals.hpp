#ifndef Globals_hpp
#define Globals_hpp

#include <cstdint>
#include <iostream>
#include <map>

constexpr uint_fast32_t WINDOW          = 0x01;
constexpr uint_fast32_t WINDOW_WIDTH    = 0x02;
constexpr uint_fast32_t WINDOW_HEIGHT   = 0x03;
constexpr uint_fast32_t FULLSCREEN      = 0x04;
constexpr uint_fast32_t REFRESH_RATE    = 0x05;
constexpr uint_fast32_t PUBLISHER       = 0x06;

class GlobalsKeyNotFound : public std::exception 
{
};

template <typename T>
class Globals
{
public:
    Globals(Globals const&) = delete;
    Globals& operator=(Globals const&) = delete;
    
    static Globals& Instance()
    {
        static Globals instance;
        return instance;
    }

    Globals& Set(const uint_fast32_t& key, T value)
    {
        _globals.insert_or_assign(key, value);
        return Instance();
    }

    T Get(const uint_fast32_t& key)
    {
        auto iterator = _globals.find(key);
        if (iterator != _globals.end())
            return static_cast<T>(iterator->second);

        throw GlobalsKeyNotFound();
    }

private:
    std::map<uint_fast32_t, T> _globals;
    Globals() {}
};

#endif