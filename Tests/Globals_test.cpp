#include <gtest/gtest.h>
#include "../Source/Globals.hpp"

class GlobalsTest : public ::testing::Test
{
};

TEST_F(GlobalsTest, AllowsSettingAndRetrievingValues)
{
    Globals<int>::Instance().Set(0x01, 0);
    Globals<int>::Instance().Set(0x02, 10);
    Globals<int>::Instance().Set(0x03, 20);

    EXPECT_EQ(0, Globals<int>::Instance().Get(0x01));
    EXPECT_EQ(10, Globals<int>::Instance().Get(0x02));
    EXPECT_EQ(20, Globals<int>::Instance().Get(0x03));
}

TEST_F(GlobalsTest, AllowsSettingAndRetrievingValuesForMultipleTypes)
{
    Globals<int>::Instance().Set(0x01, 1);
    Globals<bool>::Instance().Set(0x02, true);
    Globals<float>::Instance().Set(0x03, 3.14f);

    EXPECT_EQ(1, Globals<int>::Instance().Get(0x01));
    EXPECT_EQ(true, Globals<bool>::Instance().Get(0x02));
    EXPECT_NEAR(3.14f, Globals<float>::Instance().Get(0x03), 1e-3);
}

TEST_F(GlobalsTest, ReplacesValueIfKeyExists)
{
    Globals<int>::Instance().Set(0x01, 1);
    Globals<int>::Instance().Set(0x01, 100);

    EXPECT_EQ(100, Globals<int>::Instance().Get(0x01));
}