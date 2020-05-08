// Keeping track of memory allocation
// http://stackoverflow.com/q/29820626/3093378 (question)
// http://stackoverflow.com/a/29821408/3093378 (my answer)

#include <iostream>
#include <map>

std::map<void*, std::size_t> memory; // globally allocated memory map
struct tag {}; // tag for placement new's so we don't overload the global ones

void* operator new(std::size_t size, const tag&) {
    void* addr = malloc(size);
    memory[addr] = size;
    return addr;
}

void* operator new[](std::size_t size, const tag&) // for arrays
{
    return operator new(size, tag());
}

void operator delete(void* p) noexcept {
    memory.erase(p);
    free(p);
}

void operator delete[](void* p) noexcept // for arrays
{
    operator delete(p);
}

void display_memory() {
    std::cout << "Allocated heap memory: " << std::endl;
    for (auto&& elem : memory) {
        std::cout << "\tADDR: " << elem.first << " "
                  << "SIZE: " << elem.second << std::endl;
    }
}

bool is_allocated(void* p) { return (memory.find(p) != memory.end()); }

int main() {
    int* p = new (tag()) int[10];
    char* c = new (tag()) char;

    // test if p is allocated
    std::cout << std::boolalpha << "Allocated: " << is_allocated(p)
              << std::endl;

    // display the allocated memory
    display_memory();

    // remove p
    delete[] p;

    // test again if p is allocated
    std::cout << std::boolalpha << "Allocated: " << is_allocated(p)
              << std::endl;

    display_memory();

    // remove c
    delete c;

    display_memory();
}
