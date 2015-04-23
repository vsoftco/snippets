// A toy garbage collector for PODs using RAII

#include <iostream>
#include <iomanip>
#include <map>

class GC
{
    // globally allocated memory map
    static std::map<void*, std::pair<std::size_t, bool>> memory;

public:
    struct collect_t {}; // tag for placement new
    static void display_memory();
    static void clear_memory();
    ~GC();
    friend void* operator new(std::size_t size, const GC::collect_t&,
                              bool is_array);
    friend void operator delete(void *p, const GC::collect_t&) noexcept;
};
std::map<void*, std::pair<std::size_t, bool>> GC::memory;

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

    GC::display_memory();
}

void GC::display_memory()
{
    std::cout << "Allocated: " << std::endl;
    for (auto && elem : memory)
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

GC::~GC()
{
    clear_memory();
    display_memory();
}

void GC::clear_memory()
{
    for (auto && elem : memory)
    {
        if (elem.second.second) // non-array
            operator delete(elem.first, GC::collect_t{});
        else
            operator delete[](elem.first, GC::collect_t{});
    }
    memory.clear();
}

void* operator new(std::size_t size, const GC::collect_t&, bool is_array)
{
    void* addr = ::operator new(size);
    GC::memory[addr] = std::make_pair(size, is_array);
    return addr;
}

void* operator new[](std::size_t size, const GC::collect_t&)
{
    return operator new(size, GC::collect_t{}, true);
}

void operator delete(void *p, const GC::collect_t&) noexcept
{
    GC::memory.erase(p); // should call ::operator delete, no recursion
    ::operator delete(p);
}

void operator delete[](void *p, const GC::collect_t&) noexcept
{
    operator delete(p, GC::collect_t{});
}
