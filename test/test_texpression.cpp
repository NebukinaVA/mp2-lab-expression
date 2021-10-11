#include "texpression.h"
#include <string>
#include <gtest.h>

using namespace std;
/**/
TEST(TExpression, can_checkkkkkkkkkkkkkkkkkkkkkkk)
{
	ASSERT_NO_THROW(TExpression exp);
}

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
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("(5*6-7)/10")); 
}

TEST(TExpression, can_check_if_correct_10)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("10*5+-7//*"));
}

TEST(TExpression, can_check_if_correct_11) 
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("55+"));
}

TEST(TExpression, can_check_if_correct_12) 
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression(")5*5("));
}

TEST(TExpression, can_check_if_correct_13)
{
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("(525*6-17)/112*5-100"));
}

TEST(TExpression, can_check_if_has_letters)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("a*b"));
}

TEST(TExpression, can_check_if_correct_with_float_1)
{
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("5.15+2*0.005"));
}

TEST(TExpression, can_check_if_correct_with_float_2)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("515.+2*0.005"));
}
TEST(TExpression, can_check_if_correct_with_float_3)
{
	TExpression exp;
	ASSERT_ANY_THROW(exp.SetExpression("5.02.66+2*0.005"));
}

TEST(TExpression, can_check_if_correct_with_float_4)
{
	TExpression exp;
	ASSERT_NO_THROW(exp.SetExpression("5..02+2*0.005"));
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
	EXPECT_EQ(exp.GetPostfix(), "5;5;+");

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

TEST(TExpression, can_transfer_to_postfix_5)
{
	TExpression exp("15*4+(6+2)");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "15;4;*6;2;++");
}

TEST(TExpression, can_transfer_to_postfix_with_float_1)
{
	TExpression exp("5.5+5.5");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "5.5;5.5;+"); 
}

TEST(TExpression, can_transfer_to_postfix_with_float_2)
{
	TExpression exp("1.5*4+(6.6+2)");
	exp.ToPostfix();
	EXPECT_EQ(exp.GetPostfix(), "1.5;4;*6.6;2;++");
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
	TExpression exp("15*4+(6+2)");  // 15;4;*6;2;++
	EXPECT_EQ(exp.Calculate(), 68);
}

TEST(TExpression, can_calculate_2)
{
	TExpression exp("5+5");
	EXPECT_EQ(exp.Calculate(), 10);
}

TEST(TExpression, can_calculate_3)
{
	TExpression exp("(8+2*5)/(1+3*2-4)");
	EXPECT_EQ(exp.Calculate(), 6);
}

TEST(TExpression, can_calculate_4)
{
	TExpression exp("(6+10-4)/(1+1*2)+1");
	EXPECT_EQ(exp.Calculate(), 5);
}

TEST(TExpression, can_calculate_5)
{
	TExpression exp("(6+10-4)/10");
	EXPECT_EQ(exp.Calculate(), (6.0 + 10.0 - 4.0) / 10.0);
}

TEST(TExpression, can_calculate_with_float_1)
{
	TExpression exp("5.5+5.5");
	EXPECT_EQ(exp.Calculate(), 11.0);
}

TEST(TExpression, throws_when_division_by_zero)
{
	TExpression exp("(6+10-4)/(6-2*3)");
	ASSERT_ANY_THROW(exp.Calculate());
}

