#include "gtest/gtest.h"

#include "../blist.h"
#include "../libsrc/utilmsg.h"

std::string ProgName = "blist_tests";

TEST(blist_test, Params)
{
  blist_params params{};

  EXPECT_EQ(params.DEF_TAB_SIZE, params.tab_size);
}
