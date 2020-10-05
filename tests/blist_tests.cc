#if defined(__clang__)
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "cert-err58-cpp"
#endif

#include "gtest/gtest.h"

#include "../src/blist.h"

TEST(blist_tests, Params)
{
  blist_params params{};

  EXPECT_EQ(params.DEF_TAB_SIZE, params.tab_size);
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
