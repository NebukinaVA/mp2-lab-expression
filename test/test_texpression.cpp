#include "texpression.h"
#include <string>
#include <gtest.h>

using namespace std;

TEST(TExpression, can_check_if_correct_1)
{
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("6+7"));
}

TEST(TExpression, can_check_if_correct_2)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("5+(6-8))"));
}

TEST(TExpression, can_check_if_correct_3)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("5*+6"));
}

TEST(TExpression, can_check_if_correct_4)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("5+(a-b)"));
}

TEST(TExpression, can_check_if_correct_5)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("6/56-7+([[0)"));
}

TEST(TExpression, can_check_if_correct_6)
{
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("6 + 7"));
}

TEST(TExpression, can_check_if_correct_7)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression(""));
}

TEST(TExpression, can_check_if_correct_8)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("                  "));
}

TEST(TExpression, can_check_if_correct_9)
{
//	ASSERT_NO_THROW(TExpression exp("(5*6-7)/10"));
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("(5*6-7)/10"));
}

TEST(TExpression, can_check_if_has_letters)
{
	TExpression exp;
	EXPECT_TRUE(exp.HasLetters("a*b"));
}

TEST(TExpression, can_check_if_no_letters)
{
	TExpression exp;
	EXPECT_FALSE(exp.HasLetters("5-70"));
}

TEST(TExpression, can_transfer_to_postfix_1)
{
	TExpression exp("5+3+1");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "5;3;+1;+"); 
}

TEST(TExpression, can_transfer_to_postfix_2)
{
	TExpression exp("5+5");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "5;5;+"); //5;5;+

}

TEST(TExpression, can_transfer_to_postfix_3)
{
	TExpression exp("55+5");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "55;5;+");
}

TEST(TExpression, can_transfer_to_postfix_4)
{
	TExpression exp("5*(4+1)");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "5;4;1;+*");
}

TEST(TExpression, can_transfer_to_postfix_different_expressions)
{
	TExpression exp;
	exp.ToPostfix();
	std::string str = exp.GetPostfix();
	exp.SetExpression("(5*6-7)/10");
	exp.ToPostfix();
	EXPECT_NE(exp.GetPostfix(), str);
}

TEST(TExpression, can_calculate_1)
{
	TExpression exp("15*4+(6+2)");
	EXPECT_EQ(exp.Calculate(), 68);
}

TEST(TExpression, can_calculate_2)
{
	TExpression exp("5+5");
	EXPECT_EQ(exp.Calculate(), 10);
}

