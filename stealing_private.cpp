// Stealing private members, code snippet from:
// http://bloglitb.blogspot.de/2011/12/access-to-private-members-safer.html
// See also: http://stackoverflow.com/q/424104/3093378

#include <iostream>

template<typename Tag, typename Tag::type M>
struct Rob {
    friend typename Tag::type get(Tag) {
        return M;
    }
};

// use
struct A {
    A(int a): a(a) { }
private:
    int a;
};

// tag used to access A::a
struct A_f {
    typedef int A::*type;
    friend type get(A_f);
};

template struct Rob<A_f, &A::a>;

int main()
{
    A a(42);
    std::cout << "proof: " << a.*get(A_f()) << std::endl;
}
