// Simulation of virtual function calls via function pointers

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>

class Base {
    typedef std::map<std::string, void (Base::*)(void)> HASH_PFN;
    typedef std::map<std::string, void (Base::*)(void)>::iterator HASH_PFN_ITER;
    typedef std::map<std::string, void (Base::*)(void)>::const_iterator
        HASH_PFN_CITER;
    HASH_PFN _vtable; // hash pointer table
  protected:
    template <typename T> // marks it as "virtual" (adds it to _vtable)
    void markv(std::string vname, void (T::*vfunc)(void)) {
        _vtable[vname] = static_cast<void (Base::*)()>(vfunc);
    }

  public:
    Base() {
        // construct the "virtual table" for Base
        markv("_virtual_func", &Base::_virtual_func);
        markv("_virtual_another", &Base::_virtual_another);
    }

    // calls the "virtual" function
    void callv(const std::string& vname) {
        for (HASH_PFN_CITER it = _vtable.cbegin(); it != _vtable.cend(); ++it)
            if (it->first == vname) {
                (this->*it->second)();
                return;
            }

        throw std::runtime_error("Function is not in vtable!");
    }

    // define "virtual" functions here
    void _virtual_func() {
        std::cout << "Calling Base::_virtual_func()" << std::endl;
    }
    void _virtual_another() {
        std::cout << "Calling Base::_virtual_another()" << std::endl;
    }
};

class Derived : public Base {
  public:
    Derived() {
        // construct the "virtual table" for Derived
        markv("_virtual_func", &Derived::_virtual_func);
        markv("_virtual_another", &Derived::_virtual_another);
    }

    // override "virtual" functions here
    void _virtual_func() {
        std::cout << "Calling Derived::_virtual_func()" << std::endl;
    }
    void _virtual_another() {
        std::cout << "Calling Derived::_virtual_another()" << std::endl;
    }
};

class DerivedDerived : public Derived {
  public:
    DerivedDerived() {
        // construct the "virtual table" for DerivedDerived
        markv("_virtual_func", &DerivedDerived::_virtual_func);
        markv("_virtual_another", &DerivedDerived::_virtual_another);
    }

    // override "virtual" functions here
    void _virtual_func() {
        std::cout << "Calling DerivedDerived::_virtual_func()" << std::endl;
    }
    void _virtual_another() {
        std::cout << "Calling DerivedDerived::_virtual_another()" << std::endl;
    }
};

int main() {
    // now the magic happens
    std::unique_ptr<Base> p(new Base);
    std::unique_ptr<Base> q(new Derived);
    std::unique_ptr<Base> r(new DerivedDerived);
    std::unique_ptr<Derived> s(new Derived);

    // simulates a virtual function call
    // using the table of function pointers

    p->callv("_virtual_func");    // calls it in Base
    q->callv("_virtual_func");    // calls it in Derived
    q->callv("_virtual_another"); // calls it in Derived
    r->callv("_virtual_func");    // calls it in DerivedDerived
    r->callv("_virtual_another"); // this is not marked virtual

    // now call directly from Derived, non-virtual behaviour

    q->_virtual_func();
    q->_virtual_another();

    s->_virtual_func();
}
