#include <iostream>
#include <string>
#include <type_traits>

template <typename T1, typename T2>
auto test(T1 a, T2 b) -> decltype(a + b) {
  return a + b;
}



int main() {

  int a {3};
  int b {3};
  std::cout << test<int, int>(a, b) << std::endl;

  std::string c = "this";
  std::string d = " worked";
  std::cout << test<std::string, std::string>(c, d) << std::endl;
  return 1;
}
