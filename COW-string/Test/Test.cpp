#include <gtest/gtest.h>
#include <greatstr/GreatStr.h>

TEST(GreatCharStr, DefaultConstructor) {
  GreatCharStr S;
  EXPECT_EQ(0, S.size());
  EXPECT_STREQ("", S.c_str());
}

TEST(GreatCharStr, CopyConstructor) {
  GreatCharStr Original("Hello");
  GreatCharStr Copy(Original);
  EXPECT_EQ(Original.size(), Copy.size());
  EXPECT_STREQ(Original.c_str(), Copy.c_str());
}

TEST(GreatCharStr, MoveConstructor) {
  GreatCharStr Original("Hello");
  GreatCharStr Moved(std::move(Original));
  EXPECT_EQ(5, Moved.size());
  EXPECT_STREQ("Hello", Moved.c_str());
  EXPECT_EQ(0, Original.size());
  EXPECT_TRUE(Original.empty());
}

TEST(GreatCharStr, FromCString) {
  const char *CS = "Test";
  GreatCharStr S(CS);
  EXPECT_EQ(4, S.size());
  EXPECT_STREQ(CS, S.c_str());
}

TEST(GreatCharStr, CopyAssignment) {
  GreatCharStr Original("Hello");
  GreatCharStr Copy;
  Copy = Original;
  EXPECT_EQ(Original.size(), Copy.size());
  EXPECT_STREQ(Original.c_str(), Copy.c_str());
}

TEST(GreatCharStr, MoveAssignment) {
  GreatCharStr Original("Hello");
  GreatCharStr Moved;
  Moved = std::move(Original);
  EXPECT_EQ(5, Moved.size());
  EXPECT_STREQ("Hello", Moved.c_str());
  EXPECT_EQ(0, Original.size());
  EXPECT_TRUE(Original.empty());
}

TEST(GreatCharStr, CStringAssignment) {
  const char *CS = "Test";
  GreatCharStr S;
  S = CS;
  EXPECT_EQ(4, S.size());
  EXPECT_STREQ(CS, S.c_str());
}

TEST(GreatCharStr, EqualityOperator) {
  GreatCharStr S1("Hello");
  GreatCharStr S2("Hello");
  GreatCharStr S3("World");
  EXPECT_TRUE(S1 == S2);
  EXPECT_FALSE(S1 == S3);
}

TEST(GreatCharStr, LessThanOperator) {
  GreatCharStr S1("Apple");
  GreatCharStr S2("Banana");
  EXPECT_TRUE(S1 < S2);
  EXPECT_FALSE(S2 < S1);
}

TEST(GreatCharStr, LessThanOperator2) {
  GreatCharStr S1("Apple");
  GreatCharStr S2("Applf");
  EXPECT_TRUE(S1 < S2);
  EXPECT_FALSE(S2 < S1);
}

TEST(GreatCharStr, GreaterThanOperator) {
  GreatCharStr S1("Banana");
  GreatCharStr S2("Apple");
  EXPECT_TRUE(S1 > S2);
  EXPECT_FALSE(S2 > S1);
}

TEST(GreatCharStr, ConcatenationOperator) {
  GreatCharStr S1("Hello");
  GreatCharStr S2(" World");
  GreatCharStr Result = S1 + S2;
  EXPECT_EQ(11, Result.size());
  EXPECT_STREQ("Hello World", Result.c_str());
}

TEST(GreatCharStr, IndexOperator) {
  GreatCharStr S("Hello");
  EXPECT_EQ('H', S[0]);
  EXPECT_EQ('e', S[1]);
  S[0] = 'h';
  EXPECT_STREQ("hello", S.c_str());
}

TEST(GreatCharStr, COWIndexOperator) {
  GreatCharStr First("Hello");
  auto Second = First;
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(1, Second.refs());
  Second[0] = 'h';
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());
}

TEST(GreatCharStr, ConstIndexOperator) {
  const GreatCharStr S("Hello");
  EXPECT_EQ('H', S[0]);
  EXPECT_EQ('e', S[1]);
}

TEST(GreatCharStr, InputOperator) {
  GreatCharStr S;
  EXPECT_TRUE(S.empty());
  std::istringstream Is("Test\nInput");
  Is >> S;
  EXPECT_STREQ("Test", S.c_str());
}

TEST(GreatCharStr, OutputOperator) {
  GreatCharStr S("Hello");
  std::ostringstream Os;
  Os << S;
  EXPECT_STREQ("Hello", Os.str().c_str());
}

TEST(GreatCharStr, SizeMethod) {
  GreatCharStr S("SizeEqlTen");
  EXPECT_EQ(10, S.size());
}

TEST(GreatCharStr, EmptyMethod) {
  GreatCharStr S;
  EXPECT_TRUE(S.empty());
}

TEST(GreatCharStr, CStrMethod) {
  GreatCharStr S("Test");
  EXPECT_STREQ("Test", S.c_str());
}

TEST(GreatCharStr, refsMethodCopy) {
  GreatCharStr First("First");
  EXPECT_EQ(0, First.refs());
  GreatCharStr Second(First);
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(1, Second.refs());
  EXPECT_STREQ(First.c_str(), Second.c_str());
  GreatCharStr Third(Second);
  EXPECT_EQ(2, First.refs());
  EXPECT_EQ(2, Second.refs());
  EXPECT_EQ(2, Third.refs());
  EXPECT_STREQ(First.c_str(), Third.c_str());
}

TEST(GreatCharStr, refsMethodMove) {
  GreatCharStr First("First");
  EXPECT_EQ(0, First.refs());
  GreatCharStr Second(std::move(First));
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());
}

TEST(GreatCharStr, refsMethodEqualityOperatorCopy) {
  GreatCharStr First("First");
  GreatCharStr Second = First;
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(1, Second.refs());

  GreatCharStr Third("Third");
  First = Third;
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(0, Second.refs());
  EXPECT_EQ(1, Third.refs());
}

TEST(GreatCharStr, refsMethodEqualityOperatorStr) {
  GreatCharStr First("First");
  GreatCharStr Second = std::move(First);
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());

  First = "Third";
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());
}

TEST(GreatCharStr, refsMethodEqualityOperatorMove) {
  GreatCharStr First("First");
  GreatCharStr Second = First;
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(1, Second.refs());

  First = std::move(Second);
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());
  EXPECT_TRUE(Second.empty());
}

TEST(GreatCharStr, reserveMethod) {
  GreatCharStr S("First");
  auto Data = S.c_str();
  S.reserve(100);
  EXPECT_EQ(0, Data == S.c_str());
  EXPECT_STREQ("First", S.c_str());
  auto OldData = S.c_str();
  S = "LongerThanFirst";
  EXPECT_STREQ("LongerThanFirst", S.c_str());
  EXPECT_EQ(OldData, S.c_str());
}

TEST(GreatCharStr, reserveMethod2) {
  GreatCharStr S("First");
  auto Data = S.c_str();
  S.reserve(5);
  EXPECT_EQ(1, Data == S.c_str());
  auto OldData = S.c_str();
  S = "Less";
  EXPECT_STREQ("Less", S.c_str());
  EXPECT_EQ(OldData, S.c_str());
}

TEST(GreatCharStr, reserveMethodCOW) {
  GreatCharStr First("First");
  GreatCharStr Second = First;
  EXPECT_EQ(1, Second.refs());
  First.reserve(100);
  EXPECT_EQ(1, First.refs());
  EXPECT_EQ(1, Second.refs());
  First = "Second";
  EXPECT_EQ(0, First.refs());
  EXPECT_EQ(0, Second.refs());
}
