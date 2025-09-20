#include <cstddef>


class GreatStr {
  char *Data;
  size_t Size;
  size_t Capacity;

public:
  GreatStr() : Data(nullptr), Size(0), Capacity(0) {};
  size_t size() const { return Size; }

};
