// Understanding placement new and delete

#include <iostream>

struct Foo
{
    static void* operator new(std::size_t size, void* p)
    {
        std::cout << R"(Calling placement "operator new" for size )" << size << '\n';
        return ::operator new(size, p);
    }

    // dangerous to use for stack-allocated arrays
    static void operator delete(void* p)
    {
        std::cout << R"(Calling custom "operator delete")" << std::endl;
        // set the memory to -1
        for (std::size_t i = 0; i < 8; ++i)
            ((char*)p)[i] = 0;
        // release the memory
        ::operator delete(p); // don't do this for stack-allocated arrays!
    }
    Foo()
    {
        std::cout << "Foo::Foo()" << std::endl;
    }
    ~Foo()
    {
        std::cout << "~Foo::Foo()" << std::endl;
    }
    double dummy{10};
};

void disp_buf(void* buf, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
        std::cout << std::hex << std::showbase << std::uppercase
                  << (int)((char*)buf)[i] << " ";
    std::cout << std::dec;
    std::cout << std::endl;
}

int main()
{
    // heap allocation
    std::cout << "HEAP ALLOCATION" << std::endl;
    char* buf_heap = new char[128] {};
    disp_buf(buf_heap, 8);

    Foo* pFoo_heap = new(buf_heap) Foo; // placement allocation
    disp_buf(buf_heap, 8);

    // this automatically calls the destructor then operator delete
    // but it is not the best practice, especially for stack-allocated buffers
    // it is actually wrong, see
    // http://stackoverflow.com/q/29709491/3093378
    // it happens to work because pFoo_heap == buf_heap
    // but doesn't work otherwise
    delete pFoo_heap; // WRONG WRONG WRONG, call ~Foo() then delete[] buf_heap
    disp_buf(buf_heap, 8);

    // stack allocation
    std::cout << std::endl << "STACK ALLOCATION" << std::endl;
    char buf_stack[128] {};
    disp_buf(buf_stack, 8);

    Foo* pFoo_stack = new(buf_stack) Foo; // placement allocation
    disp_buf(buf_stack, 8);

    // this automatically calls the destructor then operator delete
    // but it is not the best practice, especially for stack-allocated buffers
    // delete pFoo_heap; // this will most likely cause a crash
    pFoo_stack->~Foo(); // explicitly call the destructor
    // operator delete is not called anymore, the memory is on stack
    // so it is automatically released
    disp_buf(buf_stack, 8);
}
