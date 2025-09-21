#ifndef GREAT_STR_H
#define GREAT_STR_H

#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>

template <typename CharT1, typename Traits1, typename Allocator1>
class GreatStr;

template <typename CharT, typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class GreatStrBuf {
  CharT *Data;
  size_t Size;
  size_t Capacity;
  mutable int RefCount = 0;

  static const size_t MIN_CAPACITY = 100;
  static const size_t CIN_LIMIT = 100;

public:
  GreatStrBuf();
  GreatStrBuf(const GreatStrBuf &Rhs);
  GreatStrBuf(GreatStrBuf &&Rhs);
  GreatStrBuf(const CharT *Rhs);
  GreatStrBuf &operator=(const GreatStrBuf &Rhs);
  GreatStrBuf &operator=(GreatStrBuf &&Rhs);
  GreatStrBuf &operator=(const CharT *Rhs);
  ~GreatStrBuf();

  CharT &operator[](int Idx);
  const CharT &operator[](int Idx) const;
  int refs() const { return RefCount; }
  void incRefs() { ++RefCount; };
  void decRefs() { --RefCount; };

  template <typename CharT1>
  friend bool operator<(const GreatStrBuf<CharT1> &Lhs,
                        const GreatStrBuf<CharT1> &Rhs);
  template <typename CharT1>
  friend bool operator>(const GreatStrBuf<CharT1> &Lhs,
                        const GreatStrBuf<CharT1> &Rhs);
  template <typename CharT1>
  friend bool operator==(const GreatStrBuf<CharT1> &Lhs,
                         const GreatStrBuf<CharT1> &Rhs);
  template <typename CharT1>
  friend std::ostream &operator<<(std::ostream &Os,
                                  const GreatStrBuf<CharT1> &S);
  template <typename CharT1, typename Traits1>
  friend std::istream &operator>>(std::istream &Is,
                                  GreatStrBuf<CharT1, Traits1> &S);

  template <typename CharT1, typename Traits1, typename Allocator1>
  friend class GreatStr;

  template <typename CharT1, typename Traits1, typename Allocator1>
  friend GreatStr<CharT1, Traits1, Allocator1>
  operator+(const GreatStr<CharT1, Traits1, Allocator1> &Lhs,
            const GreatStr<CharT1, Traits1, Allocator1> &Rhs);
};

//------------------------------The big five---------------------------------
template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator>::GreatStrBuf() {
  Size = 0;
  Allocator Alloc;
  Data = Alloc.allocate(1);
  Data[0] = Traits::to_char_type(0);
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator>::GreatStrBuf(
    const GreatStrBuf<CharT, Traits, Allocator> &Rhs) {
  Size = Rhs.Size;
  Allocator Alloc;
  Data = Alloc.allocate(Size + 1);
  Traits::copy(Data, Rhs.Data, Size + 1);
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator>::GreatStrBuf(
    GreatStrBuf<CharT, Traits, Allocator> &&Rhs)
    : Data(Rhs.Data), Size(Rhs.Size) {
  Rhs.Data = nullptr;
  Rhs.Size = 0;
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator>::GreatStrBuf(const CharT *Rhs) {
  Size = Traits::length(Rhs);
  Allocator Alloc;
  Data = Alloc.allocate(Size + 1);
  Traits::copy(Data, Rhs, Size);
  Data[Size] = Traits::to_char_type(0);
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator>::~GreatStrBuf() {
  delete[] Data;
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator> &
GreatStrBuf<CharT, Traits, Allocator>::operator=(const GreatStrBuf &Rhs) {
  if (this == &Rhs)
    return *this;
  delete[] Data;
  Size = Rhs.Size;
  Allocator Alloc;
  Data = Alloc.allocate(Size + 1);
  Traits::copy(Data, Rhs.Data, Size + 1);
  return *this;
}

template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator> &
GreatStrBuf<CharT, Traits, Allocator>::operator=(GreatStrBuf &&Rhs) {
  if (this == &Rhs)
    return *this;
  delete[] Data;
  Size = Rhs.Size;
  Data = Rhs.Data;
  Rhs.Size = 0;
  Rhs.Data = nullptr;
  return *this;
}

//-----------------------------Overloaded operators--------------------------
template <typename CharT, typename Traits, typename Allocator>
GreatStrBuf<CharT, Traits, Allocator> &
GreatStrBuf<CharT, Traits, Allocator>::operator=(const CharT *S) {
  delete[] Data;
  Size = Traits::length(S);
  Allocator Alloc;
  Data = Alloc.allocate(Size + 1);
  Traits::copy(Data, S, Size);
  Data[Size] = Traits::to_char_type(0);
  return *this;
}

template <typename CharT, typename Traits, typename Allocator>
CharT &GreatStrBuf<CharT, Traits, Allocator>::operator[](int Idx) {
  assert(Idx < (int)Size);
  return Data[Idx];
}

template <typename CharT, typename Traits, typename Allocator>
const CharT &GreatStrBuf<CharT, Traits, Allocator>::operator[](int Idx) const {
  assert(Idx < (int)Size);
  return Data[Idx];
}

template <typename CharT>
std::ostream &operator<<(std::ostream &Os, const GreatStrBuf<CharT> &S) {
  Os << S.Data;
  return Os;
}

template <typename CharT>
bool operator<(const GreatStrBuf<CharT> &Lhs, const GreatStrBuf<CharT> &Rhs) {
  return (std::strcmp(Lhs.Data, Rhs.Data) < 0);
}

template <typename CharT>
bool operator>(const GreatStrBuf<CharT> &Lhs, const GreatStrBuf<CharT> &Rhs) {
  return Rhs < Lhs;
}

template <typename CharT>
bool operator==(const GreatStrBuf<CharT> &Lhs, const GreatStrBuf<CharT> &Rhs) {
  return (std::strcmp(Lhs.Data, Rhs.Data) == 0);
}

template <typename CharT, typename Traits>
std::istream &operator>>(std::istream &Is, GreatStrBuf<CharT, Traits> &S) {
  CharT Tmp[GreatStrBuf<CharT, Traits>::CIN_LIMIT];
  Is.get(Tmp, GreatStrBuf<CharT, Traits>::CIN_LIMIT);
  if (Is)
    S = Tmp;
  while (Is && Is.get() != Traits::eof())
    continue;
  return Is;
}

//---------------------------GreatStr class-------------------------------

template <typename CharT, typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class GreatStr {
  GreatStrBuf<CharT, Traits, Allocator> *Str;

  GreatStr(GreatStrBuf<CharT, Traits, Allocator> &&Rhs)
      : Str(new GreatStrBuf(std::move(Rhs))){};

public:
  GreatStr() : Str(new GreatStrBuf<CharT, Traits, Allocator>){};
  GreatStr(const GreatStr &Rhs) : Str(Rhs.Str) { Str->incRefs(); };
  GreatStr(GreatStr &&Rhs) {
    Str = Rhs.Str;
    Rhs.Str = new GreatStrBuf<CharT, Traits, Allocator>;
  }
  GreatStr(const CharT *Rhs) : Str(new GreatStrBuf(Rhs)){};
  GreatStr &operator=(const GreatStr &Rhs) {
    if (this == &Rhs)
      return *this;
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Rhs.Str->incRefs();
    Str = Rhs.Str;
    return *this;
  };

  GreatStr &operator=(GreatStr &&Rhs) {
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Str = Rhs.Str;
    Rhs.Str = new GreatStrBuf<CharT, Traits, Allocator>;
    return *this;
  };

  GreatStr &operator=(const CharT *Rhs) {
    if ((Str->Size == Traits::length(Rhs)) &&
        !Traits::compare(Rhs, Str->Data, Str->Size))
      return *this;
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Str = new GreatStrBuf<CharT>(Rhs);
    return *this;
  };

  ~GreatStr() {
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
  }

  size_t size() const { return Str->Size; }
  int refs() const { return Str->refs(); }
  bool empty() const { return Str->Size == 0; }
  const CharT *c_str() const { return Str->Data; }

  CharT &operator[](int Idx) {
    if (Str->refs() > 0) {
      Str->decRefs();
      auto Tmp = *Str;
      Str = new GreatStrBuf<CharT>(Tmp);
    }
    return Str->operator[](Idx);
  };

  const CharT &operator[](int Idx) const { return Str->operator[](Idx); };

  template <typename CharT1>
  friend bool operator<(const GreatStr<CharT1> &Lhs,
                        const GreatStr<CharT1> &Rhs);
  template <typename CharT1>
  friend bool operator>(const GreatStr<CharT1> &Lhs,
                        const GreatStr<CharT1> &Rhs);
  template <typename CharT1>
  friend bool operator==(const GreatStr<CharT1> &Lhs,
                         const GreatStr<CharT1> &Rhs);
  template <typename CharT1>
  friend std::ostream &operator<<(std::ostream &Os, const GreatStr<CharT1> &S);
  template <typename CharT1, typename Traits1>
  friend std::istream &operator>>(std::istream &Is,
                                  GreatStr<CharT1, Traits1> &S);
  template <typename CharT1, typename Traits1, typename Allocator1>
  friend GreatStr<CharT1, Traits1, Allocator1>
  operator+(const GreatStr<CharT1, Traits1, Allocator1> &Lhs,
            const GreatStr<CharT1, Traits1, Allocator1> &Rhs);
};

using GreatCharStr = GreatStr<char>;

template <typename CharT>
bool operator<(const GreatStr<CharT> &Lhs, const GreatStr<CharT> &Rhs) {
  return *(Lhs.Str) < *(Rhs.Str);
}
template <typename CharT>
bool operator>(const GreatStr<CharT> &Lhs, const GreatStr<CharT> &Rhs) {
  return *(Lhs.Str) > *(Rhs.Str);
}
template <typename CharT>
bool operator==(const GreatStr<CharT> &Lhs, const GreatStr<CharT> &Rhs) {
  return *(Lhs.Str) == *(Rhs.Str);
}
template <typename CharT>
std::ostream &operator<<(std::ostream &Os, const GreatStr<CharT> &S) {
  Os << *(S.Str);
  return Os;
}
template <typename CharT, typename Traits>
std::istream &operator>>(std::istream &Is, GreatStr<CharT, Traits> &S) {
  Is >> *(S.Str);
  return Is;
}
template <typename CharT, typename Traits, typename Allocator>
GreatStr<CharT, Traits, Allocator>
operator+(const GreatStr<CharT, Traits, Allocator> &Lhs1,
          const GreatStr<CharT, Traits, Allocator> &Rhs1) {

  GreatStrBuf<CharT> Tmp, Lhs = *(Lhs1.Str), Rhs = *(Rhs1.Str);
  Tmp.Size = Lhs.Size + Rhs.Size;
  Allocator Alloc;
  Tmp.Data = Alloc.allocate(Tmp.Size + 1);

  Traits::copy(Tmp.Data, Lhs.Data, Lhs.Size);
  Traits::copy(Tmp.Data + Lhs.Size, Rhs.Data, Rhs.Size + 1);

  return std::move(Tmp);
}

#endif // GREAT_STR_H
