#include "skiplist.h"

#include "gtest/gtest.h"

//finger tests
TEST(skiplist_finger_tests, basic_insert_finger_test)
{
    skiplist sk(10);
    sk.enable_finger();

    auto insert_ret = sk.insert(1, 10);
    ASSERT_EQ(true, insert_ret);

    auto search_ret = sk.search(1);
    ASSERT_EQ(true, search_ret.first);
    ASSERT_EQ(10, search_ret.second);

    insert_ret = sk.insert(2, 15);
    ASSERT_EQ(true, insert_ret);

    search_ret = sk.search(2);
    ASSERT_EQ(true, search_ret.first);
    ASSERT_EQ(15, search_ret.second);

    insert_ret = sk.insert(2, 20);
    ASSERT_EQ(false, insert_ret);

    search_ret = sk.search(2);
    ASSERT_EQ(true, search_ret.first);
    ASSERT_EQ(20, search_ret.second);
}

TEST(skiplist_finger_tests, basic_erase_finger_test)
{
    skiplist sk(10);
    sk.enable_finger();

    auto insert_ret = sk.insert(1, 10);
    ASSERT_EQ(true, insert_ret);

    auto search_ret = sk.search(1);
    ASSERT_EQ(true, search_ret.first);
    ASSERT_EQ(10, search_ret.second);

    auto erase_ret = sk.erase(1);
    ASSERT_EQ(true, erase_ret);

    search_ret = sk.search(1);
    ASSERT_EQ(false, search_ret.first);

    erase_ret = sk.erase(1);
    ASSERT_EQ(false, erase_ret);
}

TEST(skiplist_finger_tests, cap_finger_test)
{
    skiplist sk(10);
    sk.enable_finger();

    for (int i = 0 ;i < 10; i++) {
        auto insert_ret = sk.insert(i, i*10);
        ASSERT_EQ(true, insert_ret);
    }

    auto insert_ret = sk.insert(10, 100);
    ASSERT_EQ(false, insert_ret);
}

TEST(skiplist_finger_tests, many_insert_finger_test)
{
    skiplist sk(100);
    sk.enable_finger();

    for (int i = 0 ;i < 100; i++) {
        auto insert_ret = sk.insert(i, i*10);
        ASSERT_EQ(true, insert_ret);
    }

    for (int i = 0 ;i < 100; i++) {
        auto search_ret = sk.search(i);
        ASSERT_EQ(true, search_ret.first);
        ASSERT_EQ(i*10, search_ret.second);
    }
}

TEST(skiplist_finger_tests, many_erase_finger_test)
{
    skiplist sk(100);
    sk.enable_finger();
    
    for (int i = 0 ;i < 100; i++) {
        auto insert_ret = sk.insert(i, i*10);
        ASSERT_EQ(true, insert_ret);
    }

    for (int i = 0 ;i < 100; i++) {
        auto search_ret = sk.search(i);
        ASSERT_EQ(true, search_ret.first);
        ASSERT_EQ(i*10, search_ret.second);
    }

    for (int i = 0 ;i < 50; i++) {
        auto erase_ret = sk.erase(i);
        ASSERT_EQ(true, erase_ret);
    }

    for (int i = 0 ;i < 50; i++) {
        auto search_ret = sk.search(i);
        ASSERT_EQ(false, search_ret.first);
    }

    for (int i = 50 ;i < 100; i++) {
        auto search_ret = sk.search(i);
        ASSERT_EQ(true, search_ret.first);
        ASSERT_EQ(i*10, search_ret.second);
    }

}