// Disabling rvalue binding to const references

struct X {};

// we intend to use this function only with lvalues
void f(const X&) {}

// a non-const rvalue factory
X get_rvalue_X()
{
    return {};
}

// a const-rvalue factory
const X get_const_rvalue_X()
{
    return {};
}

// below we need the const X&& as otherwise the output of the function
// const X get_const_rvalue_X() will bind to void f(const X&) since 
// the latter is a better match than simply void f(X&&) commented below
void f(const X&&) = delete; // need const!
// void f(X&&) = delete; // this is not enough!

int main()
{
    f(get_rvalue_X());

    // remove const from void f(const X&&) and the line below will compile
    f(get_const_rvalue_X());
}
