#include "../ID.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include <set>


class test : public ::testing::Test {
};

class Thing1 {};
using Thing1ID = ID<uint32_t, Thing1>;

TEST(test, BasicTests) {
    Thing1ID t1id_0{342}; // create valid ID
    EXPECT_TRUE(t1id_0) << "operator bool() should return true for valid ID's";
    EXPECT_EQ(t1id_0.raw_value(), 342) << "raw_value is wrong after construction";

    Thing1ID t1id_1; // default ctor creates invalid ID
    EXPECT_FALSE(t1id_1) << "operator bool() should return false for invalid ID's";

    t1id_1 = t1id_0;
    EXPECT_EQ(t1id_0, t1id_1) << "assignment should create equal ID's";

    Thing1ID t1id_2{987};
    Thing1ID t1id_3; // create invalid rhs for assignment
    t1id_3 = std::move(t1id_2); // move should cause copy
    EXPECT_TRUE(t1id_2) << "rhs should be valid after move because it is really a copy";
    EXPECT_TRUE(t1id_3) << "lhs should be valid after assignment";
    EXPECT_EQ(t1id_2.raw_value(), 987) << "raw_value is wrong after assignment";
    EXPECT_EQ(t1id_3.raw_value(), 987) << "raw_value is wrong after assignment";
}

TEST(test, OrderedContainerTests) {
    std::set<Thing1ID> ids;
    Thing1ID id1{11};
    ids.insert(id1);
    ids.emplace(12);
    EXPECT_NE(ids.find(Thing1ID(12)), std::end(ids)) << "ID should be found in set";
    EXPECT_TRUE(ids.contains(id1)) << "ID should be contained in set";
    EXPECT_FALSE(ids.contains(Thing1ID(100))) << "ID should not be contained in set";
}

TEST(test, UnorderedContainerTests) {
    std::unordered_set<Thing1ID, Thing1ID::Hasher> idus;
    Thing1ID id1{11};
    idus.insert(id1);
    idus.emplace(12);
    EXPECT_NE(idus.find(Thing1ID(12)), std::end(idus)) << "ID should be found in set";
    EXPECT_TRUE(idus.contains(id1)) << "ID should be contained in set";
    EXPECT_FALSE(idus.contains(Thing1ID(100))) << "ID should not be contained in set";
}