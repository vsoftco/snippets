// Policy-based design with traits that ca be enabled at compile time

#include <tuple>
#include <type_traits>

// Define our traits
struct Foo {
    void has_foo() {}
};
struct Bar {
    void has_bar() {}
};

// This is not a trait
struct Car {};

#ifdef DISABLE_CUSTOM_TRAITS // we don't allow users custom traits
// Define a type list with the enabled traits
using EnabledTraits = std::tuple<Foo, Bar>; // add your own here
#endif

// Next define utility functions to check if a type is present in a tuple

// Check if a type is present in the tuple
template <typename T, typename Tuple>
struct IsTypeInTuple;

// Base case: type is not present in an empty tuple
template <typename T>
struct IsTypeInTuple<T, std::tuple<>> : std::false_type {};

// Recursive case: check the first type in the tuple
template <typename T, typename... Ts>
struct IsTypeInTuple<T, std::tuple<T, Ts...>> : std::true_type {};

// Recursive case: check the rest of the tuple
template <typename T, typename U, typename... Ts>
struct IsTypeInTuple<T, std::tuple<U, Ts...>>
    : IsTypeInTuple<T, std::tuple<Ts...>> {};

// Restrict the trait list to Foo and Bar
template <typename... Ts>
struct TraitList : public Ts... {
#ifdef DISABLE_CUSTOM_TRAITS
    static_assert(std::disjunction<IsTypeInTuple<Ts, EnabledTraits>...>::value,
                  "Type is not in the EnabledTraits list");
#endif
};

// Detect if a type is a trait list
template <typename>
struct IsTraitList : std::false_type {};

template <typename... Ts>
struct IsTraitList<TraitList<Ts...>> : std::true_type {};

template <typename T, typename... Ts>
struct X : public T {
    // enforce T to be a TraitList
    static_assert(IsTraitList<T>::value, "T is not a TraitList<...>");
};

int main() {
    X<TraitList<Foo, Bar>, int, double> x1;
    X<TraitList<Foo>> x2;

    X<TraitList<Car>> x3; // Car is not in the enabled trait list
    // X<Car> x4;         // expects a trait list, doesn't compile
}
