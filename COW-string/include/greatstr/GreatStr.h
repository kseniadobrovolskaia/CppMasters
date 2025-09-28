#ifndef GREAT_STR_H
#define GREAT_STR_H

#include <cassert>
#include <iostream>

template <typename CharT, typename Traits = std::char_traits<CharT>>
class GreatStr {

  struct GreatStrBuf {
    CharT *Data;
    size_t Size;
    size_t Capacity;
    mutable int RefCount = 0;

    static const size_t CIN_LIMIT = 1000;

    int refs() const { return RefCount; }
    void incRefs() const { ++RefCount; };
    void decRefs() const { --RefCount; };
    void reserve(size_t NewCapacity) {
      if (NewCapacity <= Capacity)
        return;

      CharT *NewData = new CharT[](NewCapacity);
      Traits::copy(NewData, Data, Size + 1);
      delete[] Data;
      Data = NewData;
      Capacity = NewCapacity;
    }

    GreatStrBuf() {
      Size = 0;
      Capacity = 1;
      Data = new CharT[](Capacity);
      Data[0] = Traits::to_char_type(0);
    }
    GreatStrBuf(const GreatStrBuf &Rhs) {
      Size = Rhs.Size;
      Capacity = Size + 1;
      Data = new CharT[](Capacity);
      Traits::copy(Data, Rhs.Data, Size + 1);
    }
    GreatStrBuf(GreatStrBuf &&Rhs)
        : Data(Rhs.Data), Size(Rhs.Size), Capacity(Rhs.Capacity) {
      Rhs.Size = 0;
      Rhs.Capacity = 0;
      Rhs.Data = nullptr;
    }
    GreatStrBuf(const CharT *Rhs) {
      Size = Traits::length(Rhs);
      Capacity = Size + 1;
      Data = new CharT[](Capacity);
      Traits::copy(Data, Rhs, Size);
      Data[Size] = Traits::to_char_type(0);
    }
    ~GreatStrBuf() {
      assert(RefCount == -1);
      delete[] Data;
    }

    GreatStrBuf &operator=(const GreatStrBuf &Rhs) {
      if (this == &Rhs)
        return *this;
      Size = Rhs.Size;
      if (Rhs.Size + 1 > Capacity) {
        assert(RefCount == -1);
        delete[] Data;
        Capacity = Rhs.Size + 1;
        Data = new CharT[](Capacity);
      }
      Traits::copy(Data, Rhs.Data, Size + 1);
      return *this;
    }
    GreatStrBuf &operator=(GreatStrBuf &&Rhs) {
      if (this == &Rhs)
        return *this;
      assert(RefCount == -1);
      delete[] Data;
      Size = Rhs.Size;
      Capacity = Rhs.Capacity;
      Data = Rhs.Data;
      Rhs.Size = 0;
      Rhs.Capacity = 0;
      Rhs.Data = nullptr;
      return *this;
    }
    GreatStrBuf &operator=(const CharT *S) {
      Size = Traits::length(S);
      if (Size + 1 > Capacity) {
        delete[] Data;
        Capacity = Size + 1;
        Data = new CharT[](Capacity);
      }
      Traits::copy(Data, S, Size);
      Data[Size] = Traits::to_char_type(0);
      return *this;
    }

    CharT &operator[](int Idx) {
      assert(Idx < (int)Size);
      return Data[Idx];
    }
    const CharT &operator[](int Idx) const {
      assert(Idx < (int)Size);
      return Data[Idx];
    }

    friend bool operator<(const GreatStrBuf &Lhs, const GreatStrBuf &Rhs) {
      if (Lhs.Size != Rhs.Size)
        return Lhs.Size < Rhs.Size;
      return Traits::compare(Lhs.Data, Rhs.Data, Lhs.Size) < 0;
    }
    friend bool operator>(const GreatStrBuf &Lhs, const GreatStrBuf &Rhs) {
      return Rhs < Lhs;
    }
    friend bool operator==(const GreatStrBuf &Lhs, const GreatStrBuf &Rhs) {
      return !(Lhs < Rhs) && !(Rhs < Lhs);
    }
    friend std::istream &operator>>(std::istream &Is, GreatStrBuf &S) {
      CharT Tmp[CIN_LIMIT];
      Is.get(Tmp, CIN_LIMIT);
      if (Is)
        S = Tmp;
      while (Is && Is.get() != Traits::eof())
        continue;
      return Is;
    }
    friend std::ostream &operator<<(std::ostream &Os, const GreatStrBuf &S) {
      Os << S.Data;
      return Os;
    }
  };

private:
  GreatStrBuf *Str;

  GreatStr(GreatStrBuf *Rhs) : Str(Rhs){};

public:
  GreatStr() : Str(new GreatStrBuf){};
  GreatStr(const GreatStr &Rhs) : Str(Rhs.Str) { Str->incRefs(); };
  GreatStr(GreatStr &&Rhs) {
    Str = Rhs.Str;
    Rhs.Str = new GreatStrBuf;
  }
  GreatStr(const CharT *Rhs) : Str(new GreatStrBuf(Rhs)){};
  ~GreatStr() {
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
  }

  GreatStr &operator=(const GreatStr &Rhs) {
    if (this == &Rhs || Rhs.Str == Str)
      return *this;
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Rhs.Str->incRefs();
    Str = Rhs.Str;
    return *this;
  };
  GreatStr &operator=(GreatStr &&Rhs) {
    if (this == &Rhs)
      return *this;
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Str = Rhs.Str;
    Rhs.Str = new GreatStrBuf;
    return *this;
  };
  GreatStr &operator=(const CharT *Rhs) {
    if ((Str->Size == Traits::length(Rhs)) &&
        !Traits::compare(Rhs, Str->Data, Str->Size))
      return *this;
    Str->decRefs();
    if (Str->refs() == -1)
      delete Str;
    Str = new GreatStrBuf(Rhs);
    return *this;
  };

  size_t size() const { return Str->Size; }
  int refs() const { return Str->refs(); }
  bool empty() const { return Str->Size == 0; }
  const CharT *c_str() const { return Str->Data; }
  void reserve(size_t NewCapacity) { Str->reserve(NewCapacity); }

  CharT &operator[](int Idx) {
    if (Str->refs() > 0) {
      GreatStrBuf *Tmp = new GreatStrBuf(*Str);
      Str->decRefs();
      if (Str->refs() == -1)
        delete Str;
      Str = Tmp;
    }
    return Str->operator[](Idx);
  };
  const CharT &operator[](int Idx) const { return Str->operator[](Idx); };

  friend bool operator==(const GreatStr &Lhs, const GreatStr &Rhs) {
    return *(Lhs.Str) == *(Rhs.Str);
  }
  friend bool operator<(const GreatStr &Lhs, const GreatStr &Rhs) {
    return *(Lhs.Str) < *(Rhs.Str);
  }
  friend bool operator>(const GreatStr &Lhs, const GreatStr &Rhs) {
    return *(Lhs.Str) > *(Rhs.Str);
  }
  friend std::ostream &operator<<(std::ostream &Os, const GreatStr &S) {
    Os << *(S.Str);
    return Os;
  }
  friend std::istream &operator>>(std::istream &Is, GreatStr &S) {
    Is >> *(S.Str);
    return Is;
  }
  friend GreatStr operator+(const GreatStr &Lhs, const GreatStr &Rhs) {
    GreatStrBuf *Tmp = new GreatStrBuf;
    Tmp->Size = Lhs.size() + Rhs.size();
    Tmp->Capacity = Tmp->Size + 1;
    Tmp->reserve(Tmp->Capacity);
    Traits::copy(Tmp->Data, Lhs.c_str(), Lhs.size());
    Traits::copy(Tmp->Data + Lhs.size(), Rhs.c_str(), Rhs.size());
    Tmp->Data[Tmp->Size] = Traits::to_char_type(0);
    return GreatStr(Tmp);
  }
};

using GreatCharStr = GreatStr<char>;

#endif // GREAT_STR_H
