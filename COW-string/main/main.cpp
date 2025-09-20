#include "greatstr/GreatStr.h"

#include <iostream>

int main(int Argc, char **Argv) {
  try {
    const GreatStr FirstStr;
    std::cout << "Size first string: " << FirstStr.size() << "\n";
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}
