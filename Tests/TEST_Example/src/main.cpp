#include <gtest/gtest.h>

#include "Engine/Core/Engine.h"

using namespace MyEngine;

class EngineCreationTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(EngineCreationTest, CreateEngineObject) {
    // Attempt to create an object of the Engine class
    ASSERT_NO_THROW(Engine());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}