#include <gtest/gtest.h>
#include <glm/glm.hpp>

#include <Engine/ECS/ComponentPool.h>
#include <Engine/ECS/Components.h>

using namespace MyEngine;

class ComponentPoolTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        componentPool = new ComponentPool(sizeof(TransformComponent));
    }

    void TearDown() override
    {
        delete componentPool;
    }

    ComponentPool* componentPool;
};

TEST_F(ComponentPoolTest, AddAndGet)
{
    ComponentId index;

    // Add a TransformComponent
    void* mem1 = componentPool->Add(index);
    TransformComponent* transform1 = new (mem1) TransformComponent();
    transform1->position = glm::vec3(1.0f);

    // Ensure the index is correct
    ASSERT_EQ(index, 0);

    // Add another TransformComponent
    void* mem2 = componentPool->Add(index);
    TransformComponent* transform2 = new (mem2) TransformComponent();
    transform2->position = glm::vec3(1.0f);

    // Ensure the index is correct
    ASSERT_EQ(index, 1);

    // Get the first component and verify
    void* getMem1 = componentPool->Get(0);
    TransformComponent* pTransform1 = static_cast<TransformComponent*>(getMem1);
    ASSERT_EQ(mem1, getMem1);
    ASSERT_EQ(pTransform1->position, transform1->position);

    // Get the second component and verify
    void* getMem2 = componentPool->Get(1);
    TransformComponent* pTransform2 = static_cast<TransformComponent*>(getMem2);
    ASSERT_EQ(mem2, getMem2);
    ASSERT_EQ(pTransform2->position, transform2->position);
}

TEST_F(ComponentPoolTest, Remove)
{
    ComponentId index;

    // Add a TransformComponent
    void* mem1 = componentPool->Add(index);
    TransformComponent* transform1 = new (mem1) TransformComponent();
    transform1->position = glm::vec3(1.0f);

    // Add another TransformComponent
    void* mem2 = componentPool->Add(index);
    TransformComponent* transform2 = new (mem2) TransformComponent();
    transform2->position = glm::vec3(1.0f);

    ComponentId indexReplaced;
    componentPool->Remove(0, indexReplaced);

    ASSERT_EQ(componentPool->Size(), 1);

    // Check last component was moved to the first place
    ASSERT_EQ(indexReplaced, componentPool->Size());

    void* getMem2 = componentPool->Get(0);
    ASSERT_EQ(mem1, getMem2);

    // Verify moved component is correct
    TransformComponent* pTransform2 = static_cast<TransformComponent*>(mem1);
    ASSERT_EQ(pTransform2->position, transform2->position);
}

TEST_F(ComponentPoolTest, RemoveInvalidIndex)
{
    ComponentId index;
    void* mem1 = componentPool->Add(index);
    void* mem2 = componentPool->Add(index);

    componentPool->Remove(2, index);

    ASSERT_EQ(componentPool->Size(), 2);

    // Check that invalid index didn't change the pool
    void* getMem1 = componentPool->Get(0);
    void* getMem2 = componentPool->Get(1);
    ASSERT_EQ(mem1, getMem1);
    ASSERT_EQ(mem2, getMem2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}