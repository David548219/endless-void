// Copyright 2018 David Oganesian david548219@gmail.com

#include <gtest/gtest.h>

#include "main.hpp"

TEST(SampleCategory, SampleName) {
  EXPECT_EQ(foo(4), 4);
  EXPECT_NE(foo(1), 0);
}