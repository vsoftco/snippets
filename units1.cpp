// Enforcing dimensional unit correctness via template metaprogramming, take 1

#include <iostream>

template <int m, // exponent for mass
          int d, // exponent for distance
          int t> // exponent for time
class Units {
public:
  explicit Units(double initVal = 0) : val(initVal) {}
  double value() const { return val; }
  double &value() { return val; }
  Units<m, d, t> &operator*=(double rhs) {
    val *= rhs;
    return *this;
  }

private:
  double val;
};

template <int m, int d, int t>
const Units<m, d, t> operator+(const Units<m, d, t> &lhs,
                               const Units<m, d, t> &rhs) {
  Units<m, d, t> result(lhs);
  return result += rhs;
}
template <int m, int d, int t>
const Units<m, d, t> operator*(double lhs, const Units<m, d, t> &rhs) {
  Units<m, d, t> result(rhs);
  return result *= lhs;
}
template <int m, int d, int t>
const Units<m, d, t> operator*(const Units<m, d, t> &lhs, double rhs) {
  Units<m, d, t> result(lhs);
  return result *= rhs;
}

typedef Units<1, 0, 0> Mass;
typedef Units<0, 1, 0> Distance;
typedef Units<0, 0, 1> Time;

// Fundamental constants
const Mass kg(1);
const Distance meter(1);
const Time sec(1);

Mass my_mass(74 * kg);

int main() {
  Units<1, 0, 0> mass(10);
  Units<1, 0, 0> another_mass(2);
  Units<0, 0, 1> time(.1);

  std::cout << "mass: " << mass.value() << std::endl;
  std::cout << "time: " << time.value() << std::endl;
  std::cout << "another_mass: " << another_mass.value() << std::endl;
  std::cout << "sum of masses: " << mass.value() + another_mass.value()
            << std::endl;

  mass = another_mass;
  std::cout << "my mass is: " << my_mass.value() << " Kilograms." << std::endl;

  //  mass = time; // error!!!
}
