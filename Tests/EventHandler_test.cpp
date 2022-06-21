#include <iostream>
#include <gtest/gtest.h>
#include "../Source/EventHandler.hpp"

class EventHandlerTest : public ::testing::Test
{
};

static int magicNumber = 0;

struct MockEventArgs 
{
    int magicNumber;
};

class MockSender
{
public:
    void MockMemberFunction(const MockEventArgs& args) 
    {
        ::magicNumber = args.magicNumber;
    }
};

TEST_F(EventHandlerTest, Works)
{
    MockSender *sender = new MockSender();
    auto handler = EventHandler<const MockEventArgs&>();
    handler.Bind<MockSender, &MockSender::MockMemberFunction>(sender);

    MockEventArgs eventArgs;
    eventArgs.magicNumber = 10;
    handler(eventArgs);

    EXPECT_EQ(10, ::magicNumber);
}