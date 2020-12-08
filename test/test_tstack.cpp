#include "tstack.h"

#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> s(MAX_STACK_SIZE + 1));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_check_if_stack_is_empty)
{
	TStack<int> s;
	EXPECT_EQ(1, s.IsEmpty());
}

TEST(TStack, can_push)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.Push(1));
}

TEST(TStack, can_pop)
{
	TStack<int> s;
	s.Push(1);
	ASSERT_NO_THROW(s.Pop());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, can_clear_stack)
{
	TStack<int> s;
	s.Push(1);
	s.Clear();
	EXPECT_EQ(1, s.IsEmpty());
}

TEST(TStack, can_check_if_stack_is_full)
{
	TStack<int> s(3);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	EXPECT_EQ(1, s.IsFull());
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s1;
	TStack<int> s2(s1);
	EXPECT_EQ(s1, s2);
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> s1;
	TStack<int> s2(s1);
	s2.Push(1);
	EXPECT_NE(s1, s2);
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s1;
	TStack<int> s2(s1);
	s1 = s1;
	EXPECT_EQ(s1, s2);
}

TEST(TStack, can_assingn_stacks_of_equal_size)
{
	TStack<int> s1(5), s2(5);
	s2.Push(2);
	s1 = s2;
	EXPECT_EQ(s1, s2);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	TStack<int> s1(5), s2(10);
	s2 = s1;
	EXPECT_EQ(s1, s2);
}

TEST(TStack, can_repack_stack)
{
	TStack<int> s(3);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	ASSERT_NO_THROW(s.Push(4));
}