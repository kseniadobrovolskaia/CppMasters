#include "greatstr/GreatStr.h"

#include <iostream>

int main(int Argc, char **Argv) {
  try {
    GreatCharStr First("First");
    std::cout << "Size first string: " << First.size() << "\n";
    GreatCharStr Second = "Second";
    std::cout << "Size second string: " << Second.size()
              << ", second: " << Second << "\n";
    std::cout << "Size trird string: " << (First + Second).size()
              << ", third: " << First + Second << "\n";
    std::cerr << "Lhs = (" << "" << "), Rhs = (" << GreatCharStr().c_str()
              << ")\nGet first: ";
    std::cin >> First;
    std::cerr << "First new = " << First;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}
