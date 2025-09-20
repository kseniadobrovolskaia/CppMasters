#include <gtest/gtest.h>
#include <greatstr/GreatStr.h>

TEST(greatstr, 1) {
  const GreatStr Str;
  auto Size = Str.size();
  EXPECT_EQ(0, Size);
}
