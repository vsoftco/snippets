// Enforcing dimensional unit correctness via template metaprogramming, take 1

#include <iostream>

//internally for everything use SI units.
//mass in kilograms,
//time in seconds
//length in meters

template <int M, int L, int T>
class Unit;

template <int M, int L, int T>
const Unit<M, L, T> operator+(const Unit<M, L, T>&, const Unit<M, L, T>&);

template <int M, int L, int T>
const Unit<M, L, T> operator-(const Unit<M, L, T>&, const Unit<M, L, T>&);

template<int M, int L, int T>
class Unit {
public:
    Unit(double val = 0.0) : value(val) {}
    Unit& operator+=(const Unit& rhs) {
        value += rhs.value;
        return *this;
    }
    Unit& operator-=(const Unit& rhs) {
        value -= rhs.value;
        return *this;
    }
    double getValue() const {
        return value;
    }
private:
    double value;
};

template <int M, int L, int T>
const Unit<M, L, T> operator+(const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return Unit<M, L, T>(lhs) += rhs;
}
template <int M, int L, int T>
const Unit<M, L, T> operator-(const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return Unit<M, L, T>(lhs) -= rhs;
}
template <int M1, int L1, int T1, int M2, int L2, int T2>
const Unit < M1 + M2, L1 + L2, T1 + T2 > operator*(const Unit<M1, L1, T1>& lhs, const Unit<M2, L2, T2>& rhs)
{
    return Unit < M1 + M2, L1 + L2, T1 + T2 > (lhs.getValue() * rhs.getValue());
}
template <int M, int L, int T>
const Unit<M, L, T> operator*(const double& lhs, const Unit<M, L, T>& rhs)
{
    return Unit<M, L, T>(lhs * rhs.getValue());
}

template <int M1, int L1, int T1, int M2, int L2, int T2>
const Unit < M1 - M2, L1 - L2, T1 - T2 > operator/(const Unit<M1, L1, T1>& lhs, const Unit<M2, L2, T2>& rhs)
{
    return Unit < M1 - M2, L1 - L2, T1 - T2 > (lhs.getValue() / rhs.getValue());
}

template <int M, int L, int T>
bool operator==(const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return (lhs.getValue() == rhs.getValue());
}
template <int M, int L, int T>
bool operator<=(const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return lhs.getValue() <= rhs.getValue();
}
template <int M, int L, int T>
bool operator>=(const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return lhs.getValue() >= rhs.getValue();
}
template <int M, int L, int T>
bool operator< (const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return lhs.getValue() < rhs.getValue();
}
template <int M, int L, int T>
bool operator> (const Unit<M, L, T>& lhs, const Unit<M, L, T>& rhs)
{
    return lhs.getValue() > rhs.getValue();
}

typedef Unit<1, 0, 0> Mass;
typedef Unit<0, 1, 0> Length;
typedef Unit<0, 0, 1> Time;

//length units - verify the constants
const Length meter = 1.0;
const Length centimeter = 0.01;
const Length feet = 0.3048 * meter;
const Length mile = 5280 * feet;

//time units
const Time second = 1.0;

//mass units
const Mass kilogram = 1.0;

//Can have more constants for all other units in terms of meter, second and kilogram
//feet,yard,inches,micrometer,hour,minute,grams,pounds, etc etc etc....

int main()
{
    Length distanceinCMs = 100000;
    Length distanceinFeets = distanceinCMs * centimeter / feet;
    std::cout << "distanceinCMs = " << distanceinCMs.getValue() << std::endl;
    std::cout << "distanceinFeets = " << distanceinFeets.getValue() << std::endl;
    //get in terms of miles and feets
    double total_in_miles = (distanceinCMs * centimeter / mile).getValue();
    double total_in_feets = (distanceinCMs * centimeter / feet).getValue();

    std::cout << "above distance = " << static_cast<int>(total_in_miles)
              << " miles and " << static_cast<int>(total_in_feets)
              << " feet (approx.)" << std::endl;

    std::cout << (meter * second + meter * meter * second / meter).getValue();
//  std::cout << (meter + second).getValue(); // Error at compile time!
}
