// A toy garbage collector for PODs using RAII

#include <iostream>
#include <iomanip>
#include <map>

class GC
{
    // globally allocated _memory map
    static std::map<void*, std::pair<std::size_t, bool>> _memory;
public:
    struct collect_t {}; // tag for placement new
    static void display_memory();
    static void clear_memory();
    static bool is_managed(void* p);
    static void remove(void *p);
    static std::pair<std::size_t, bool> get(void* p);
    ~GC();
    friend void* operator new(std::size_t size, const GC::collect_t&,
                              bool is_array);
    friend void operator delete(void *p, const GC::collect_t&) noexcept;
};
std::map<void*, std::pair<std::size_t, bool>> GC::_memory;

void* operator new(std::size_t size, const GC::collect_t&,
                   bool is_array = false);
void* operator new[](std::size_t size, const GC::collect_t&);
void operator delete(void *p, const GC::collect_t&) noexcept;
void operator delete[](void *p, const GC::collect_t&) noexcept;

int main()
{
    GC gc; // RAII

    // use the garbage collector
    char *c = new(GC::collect_t{}) char;
    int *p = new(GC::collect_t{}) int[1024]; // true size: sizeof(int)*100 + y

    // don't use the garbace collector
    int *tmp = new int;

    std::cout << std::boolalpha << GC::is_managed(c) << std::endl;
    std::cout << std::boolalpha << GC::is_managed(p) << std::endl;
    std::cout << std::boolalpha << GC::is_managed(tmp) << std::endl;

    GC::display_memory();

    GC::remove(c);
    GC::display_memory();
    std::cout << std::boolalpha << GC::is_managed(c) << std::endl;
    std::cout << std::boolalpha << GC::is_managed(p) << std::endl;
    std::cout << std::boolalpha << GC::is_managed(tmp) << std::endl;

    delete tmp;
}

void GC::display_memory()
{
    std::cout << "Allocated: " << std::endl;
    for (auto && elem : _memory)
    {
        std::cout  << std::setfill('.')
                   << "\tADDR: "  << std::setw(8)
                   << elem.first
                   << "\tSIZE: " << std::setw(8) << std::right
                   << elem.second.first
                   << "\tARRAY: " << std::setw(8) << std::boolalpha
                   << elem.second.second << std::endl;
    }
}

void GC::clear_memory()
{
    for (auto && elem : _memory)
    {
        if (elem.second.second) // non-array
            operator delete(elem.first, GC::collect_t{});
        else
            operator delete[](elem.first, GC::collect_t{});
    }
    _memory.clear();
}

GC::~GC()
{
    clear_memory();
    display_memory();
}

bool GC::is_managed(void* p)
{
    return _memory.find(p) != _memory.end();
}

void GC::remove(void *p)
{
    _memory.erase(p);
}

std::pair<std::size_t, bool> GC::get(void* p)
{
    if (is_managed(p))
        return _memory[p];
    else
        return std::make_pair(0, false);
}

void* operator new(std::size_t size, const GC::collect_t&, bool is_array)
{
    void* addr = ::operator new(size);
    GC::_memory[addr] = std::make_pair(size, is_array);
    return addr;
}

void* operator new[](std::size_t size, const GC::collect_t&)
{
    return operator new(size, GC::collect_t{}, true);
}

void operator delete(void *p, const GC::collect_t&) noexcept
{
    GC::_memory.erase(p); // should call ::operator delete, no recursion
    ::operator delete(p);
}

void operator delete[](void *p, const GC::collect_t&) noexcept
{
    operator delete(p, GC::collect_t{});
}
