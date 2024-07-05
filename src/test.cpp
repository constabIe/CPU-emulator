#include <string>
#include <stdexcept>

#include "stack.hpp"
#include "utils.hpp"
#include "gtest/gtest.h"

using namespace stack_;

TEST(Rule_of_five, default_constructor)
{
    EXPECT_NO_THROW(Stack<std::string> stack_1 {});
}

TEST(Rule_of_five, copy_constructor)
{
    Stack<std::string> stack_1 {};

    EXPECT_NO_THROW(Stack<std::string> stack_2 {stack_1});
}

TEST(Rule_of_five, move_constructor)
{
    EXPECT_NO_THROW(Stack<std::string> stack_2 { Stack<std::string> {} });
}

TEST(Rule_of_five, destructor)
{
    Stack<std::string> stack_1 {};
    stack_1.push(std::string { "23" });

    EXPECT_EQ(0, 0);
}


TEST(Rule_of_five, copy_assignment)
{
    std::cout << 8;
    Stack<std::string> stack_1 {};
    Stack<std::string> stack_2 {};

    EXPECT_NO_THROW(stack_2 = stack_1);
}

TEST(Rule_of_five, move_assignment)
{
    Stack<std::string> stack_1 {};

    EXPECT_NO_THROW(stack_1 = Stack<std::string> {});
}

TEST(Elements_access, top)
{
    Stack<std::string> stack_1 {};
    stack_1.push(std::string { "23" });

    EXPECT_EQ(stack_1.top(), std::string { "23" });
}

TEST(Getters, size)
{
    Stack<std::string> stack_1 {};

    EXPECT_EQ(stack_1.size(), (size_t) 0);
}

TEST(Getters, capacity)
{
    Stack<std::string> stack_1 {};

    EXPECT_EQ(stack_1.capacity(), (size_t) 2);
}

TEST(Methods, push_copy)
{
    Stack<std::string> stack_1 {};
    std::string str { "slaaaay" };

    EXPECT_NO_THROW(stack_1.push(str));
}

TEST(Methods, push_move)
{
    Stack<std::string> stack_1 {};

    EXPECT_NO_THROW(stack_1.push(std::string { "slaaaay" }));
}

TEST(Methods, pop)
{
    Stack<std::string> stack_1 {};
    stack_1.push(std::string { "iii" });
    stack_1.pop();

    EXPECT_NO_THROW(stack_1.pop());
}

int main(int argc, char **argv) {
    std::cout << BYELLOW << "Testing " << BCYAN << "include/stack.hpp" << RESET << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}