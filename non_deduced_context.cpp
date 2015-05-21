// Non-deduced context in templates

template <typename T>
struct non_deduced_context
{
    using type = T;
};

template <typename T>
using non_deduced_context_t = typename non_deduced_context<T>::type;

template<typename T>
void f(T x) {} // can deduce the context

template<typename T>
void g(non_deduced_context_t<T> x) {} // cannot deduce the context

int main()
{
    int x = 0;
    f(x); // ok
    // g(x); // doesn't compile, cannot deduce the type of x
    g<int>(x); // compiles, explicit type deduction
}
