#include <gtest/gtest.h>

#include <Engine/Utils/BiMap.hpp>

using namespace MyEngine;

class BiMapTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        myBiMap.Add("entity1", "component1");
        myBiMap.Add("entity2", "component2");
    }

    void TearDown() override
    {
        myBiMap.Clear();
    }

    BiMap<std::string, std::string> myBiMap;
};

TEST_F(BiMapTest, AddingAndGettingMappings) {
    std::string valueOut;
    myBiMap.GetByKey("entity1", valueOut);
    EXPECT_EQ(valueOut, "component1");

    std::string keyOut;
    myBiMap.GetByValue("component2", keyOut);
    EXPECT_EQ(keyOut, "entity2");
}

TEST_F(BiMapTest, RemovingMappings) {
    myBiMap.RemoveByKey("entity1");

    std::string valueOut;
    myBiMap.GetByKey("entity1", valueOut);
    EXPECT_EQ(valueOut, "");

    std::string keyOut;
    myBiMap.GetByValue("component2", keyOut);
    EXPECT_EQ(keyOut, "entity2");
}

TEST_F(BiMapTest, RemovingMappingsByValue) {
    myBiMap.RemoveByValue("component2");

    std::string valueOut;
    myBiMap.GetByKey("entity1", valueOut);
    EXPECT_EQ(valueOut, "component1");

    std::string keyOut;
    myBiMap.GetByValue("component2", keyOut);
    EXPECT_EQ(keyOut, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
