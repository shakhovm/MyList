#include <gtest/gtest.h>
#include "my_list.h"
#include <vector>

class ListFixture : public :: testing::Test{



};


TEST_F(ListFixture, init)
{
    MyList<int> lst1;
    std::vector<int> v;
    for(int i = 0; i < 5; ++i)
    {

        lst1.push_back(i);
        v.push_back(i);


    }

    EXPECT_EQ(lst1.size(), 5);
    EXPECT_EQ(lst1.front(), 0);
    EXPECT_EQ(lst1.back(), 4);
    MyList<int> lst2(v.begin(), v.end());
    EXPECT_EQ(lst1 == lst2, true);
    lst1.pop_front();
    lst1.pop_back();
    EXPECT_EQ(lst1.front(), 1);
    EXPECT_EQ(lst1.back(), 3);
    lst1.clear();
    EXPECT_EQ(lst1.size(), 0);

    lst1.push_back(2);
    EXPECT_EQ(lst1.size(), 1);
    EXPECT_EQ(lst1.front(), 2);

    auto newList = new MyList<int>;
    for (int i = 0; i < 10; ++i) {
        newList->push_back(i);
    }

    delete newList;
}

TEST_F(ListFixture, insert_erase)
{
    std::vector<std::string> v = {"1", "2", "3"};
    MyList<std::string> lst1 = {"example", "simple", "111"};
    lst1.insert(lst1.begin() + 1, "09");
    EXPECT_EQ(lst1.size(), 4);
    EXPECT_EQ(lst1[1], "09");
    lst1.insert(lst1.end(), "9");
    EXPECT_EQ(lst1.back(), "9");

    lst1.erase(lst1.begin() + 1);
    EXPECT_EQ(lst1[1], "simple");
    lst1.insert(lst1.begin(), v.begin(), v.end());
    EXPECT_EQ(lst1.front(), "1");
    lst1.erase(lst1.begin() + 1, lst1.end() - 1);
    EXPECT_EQ(lst1.front(), "1");
    EXPECT_EQ(lst1.back(), "9");
    EXPECT_EQ(lst1[1], "9");
    EXPECT_EQ(lst1.size(), 2);
    lst1.erase(lst1.begin(), lst1.end());
    EXPECT_EQ(lst1.empty(), true);

}
//
TEST_F(ListFixture, emplace)
{
    struct X
    {
        int x;
        int y;

        X(int x = 0, int y = 0): x(x), y(y) {}
        ~X(){ x = 0; y = 0;}

    };
    std::vector<int> v = {1, 2, 3, 4, 5};
    MyList<X> lst;
    for(int i = 0; i < 10; ++i)
    {
        lst.emplace_back(i, i);
    }
    EXPECT_EQ(lst[1].x, 1);
    EXPECT_EQ(lst[1].y, 1);

    lst.emplace(lst.begin() + 3, 100, 120);
    EXPECT_EQ(lst[3].x, 100);
    EXPECT_EQ(lst[3].y, 120);
}

TEST_F(ListFixture, comparing)
{
    MyList<int> lst1;
    MyList<int> lst2;
    for (int i = 0; i < 10; ++i) {
        lst1.push_back(i);
        lst2.push_back(i);
    }
    EXPECT_EQ(lst1, lst2);
    EXPECT_LE(lst1, lst2);

    lst2.pop_back();

    EXPECT_GT(lst1, lst2);
    EXPECT_GE(lst1, lst2);
    EXPECT_LE(lst2, lst1);
    EXPECT_LT(lst2, lst1);

    lst2.pop_back();
    lst2.push_back(10);

    EXPECT_GT(lst2, lst1);
    EXPECT_NE(lst1, lst2);
}