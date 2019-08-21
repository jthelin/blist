#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gtest/gtest.h"

#include "../blist.h"
#include "../libsrc/proginfo.h"

std::string ProgInfo::Name = "blist_tests";

TEST(blist_tests, Params) {
  blist_params params{};

  EXPECT_EQ(params.DEF_TAB_SIZE, params.tab_size);
}

#pragma clang diagnostic pop
