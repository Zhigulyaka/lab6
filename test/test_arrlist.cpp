#include "ArrList.h"
#include <../gtest/gtest.h>


TEST(ArrList, can_create_list_size_one)
{
	ASSERT_NO_THROW(ArrList<int> l(1));
}

TEST(ArrList, cant_create_list_with_negative_length)
{
	ASSERT_ANY_THROW(ArrList<int> l(-1));
}

TEST(ArrList, can_assign_list_to_itself)
{
	ArrList<int> l1(3);
	l1.InsFirst(5);
	l1.InsLast(6);
	ASSERT_NO_THROW(l1=l1);
}

TEST(ArrList, can_assign_list_to_equal_size)
{
	ArrList<int> l1(3);
	ArrList<int> l2(3);
	l1.InsFirst(5);
	l1.InsLast(6);
	ASSERT_NO_THROW(l2 = l1);
}

TEST(ArrList, can_assign_list_to_non_equal_size)
{
	ArrList<int> l1(3);
	ArrList<int> l2(6);
	l1.InsFirst(5);
	l1.InsLast(6);
	ASSERT_NO_THROW(l2 = l1);
}


TEST(ArrList, can_copy_list)
{
	ArrList<int> l1(2);
	ASSERT_NO_THROW(ArrList<int> l2(l1));
}

TEST(ArrList, can_insert_first_element)
{
	ArrList<int> l1(2);
	ASSERT_NO_THROW(l1.InsFirst(5));
}

TEST(ArrList, can_insert_last_element)
{
	ArrList<int> l1(2);
	l1.InsFirst(5);
	ASSERT_NO_THROW(l1.InsLast(6));
}

TEST(ArrList, can_insert_middle_element)
{
	ArrList<int> l1(3);
	l1.InsFirst(5);
	l1.InsLast(6);
	ArrListIterator<int> a(l1,1);
	ASSERT_NO_THROW(l1.Ins(a,7));
}

TEST(ArrList, can_get_first_element)
{
	ArrList<int> l1(2);
	l1.InsFirst(5);
	EXPECT_EQ(l1.GetFirst(), 5);
}

TEST(ArrList, can_get_last_element)
{
	ArrList<int> l1(2);
	l1.InsLast(6);
	EXPECT_EQ(l1.GetLast(), 6);
}

TEST(ArrList, can_get_middle_element)
{
	ArrList<int> l1(3);
	l1.InsFirst(5);
	l1.InsLast(6);
	l1.InsLast(7);
	EXPECT_EQ(l1.GetMiddle(7), 2);

}
TEST(ArrList, can_delete_first_element)
{
	ArrList<int> l1(2);
	l1.InsFirst(5);
	ASSERT_NO_THROW(l1.DelFirst());
}


TEST(ArrList, can_delete_last_element)
{
	ArrList<int> l1(2);
	l1.InsLast(5);
	ASSERT_NO_THROW(l1.DelLast());
}

TEST(ArrList, can_delete_middle_element)
{
	ArrList<int> l1(3);
	l1.InsFirst(5);
	l1.InsLast(6);
    ArrListIterator<int> a(l1, 1);
	l1.Ins(a, 7);
	
	ASSERT_NO_THROW(l1.Del(a));
}
