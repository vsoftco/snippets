// A toy garbage collector for PODs

#include <iostream>
#include <map>

std::map<void*, std::size_t> memory; // globally allocated memory map
struct collect_t {} collect; // tag for placement new

void* operator new(std::size_t size, const collect_t&)
{
    void* addr = malloc(size);
    memory[addr] = size;
    return addr;
}

void* operator new[](std::size_t size, const collect_t&)
{
    return operator new(size, collect);
}

void operator delete(void *p, const collect_t&) noexcept
{
    memory.erase(p); // should call ::operator delete, no recursion
    free(p);
}

void operator delete[](void *p, const collect_t&) noexcept
{
    operator delete(p, collect);
}

void display_memory()
{
    std::cout << "Allocated heap memory: " << std::endl;
    for (auto && elem : memory)
    {
        std::cout << "\tADDR: " << elem.first << " "
                  << "SIZE: "  << elem.second << std::endl;
    }
}

void clear()
{
    for (auto && elem : memory)
        free(elem.first); // is this safe for arrays?
    memory.clear();
}

int main()
{
    // use the garbage collector
    char *c = new(collect) char;
    int *p = new(collect) int[1024]; // true size: sizeof(int)*100 + y

    display_memory();
    clear();
    display_memory();
}
