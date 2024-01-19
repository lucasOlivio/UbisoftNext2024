#include <gtest/gtest.h>

#include <Engine/ECS/EntityManager.h>

using namespace MyEngine;

class EntityManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        entityManager.AddEntity(EntityMask(0x01));
    }

    void TearDown() override
    {
        entityManager = EntityManager(); // Reset the entityManager for a clean state
    }

    EntityManager entityManager;
};

TEST_F(EntityManagerTest, AddEntityIncreasesSize)
{
    Entity addedEntity = entityManager.AddEntity(EntityMask(0x02));
    ASSERT_EQ(entityManager.Size(), 2);
}

TEST_F(EntityManagerTest, RemoveEntityDecreasesSize)
{
    Entity addedEntity = entityManager.AddEntity(EntityMask(0x02));
    entityManager.RemoveEntity(addedEntity);
    ASSERT_EQ(entityManager.Size(), 1);
}

TEST_F(EntityManagerTest, RemoveEntityRemovesMask)
{
    Entity addedEntity = entityManager.AddEntity(EntityMask(0x02));
    entityManager.RemoveEntity(addedEntity);
    ASSERT_EQ(entityManager.GetMask(addedEntity), EntityMask(0));
}

TEST_F(EntityManagerTest, SetMaskUpdatesMask)
{
    Entity addedEntity = entityManager.AddEntity(EntityMask(0x02));
    entityManager.SetMask(addedEntity, EntityMask(0x04));
    ASSERT_EQ(entityManager.GetMask(addedEntity), EntityMask(0x04));
}

TEST_F(EntityManagerTest, GetMaskReturnsCorrectMask)
{
    Entity addedEntity = entityManager.AddEntity(EntityMask(0x02));
    ASSERT_EQ(entityManager.GetMask(addedEntity), EntityMask(0x02));
}

TEST_F(EntityManagerTest, SizeReturnsCorrectSize)
{
    entityManager.AddEntity(EntityMask(0x02));
    ASSERT_EQ(entityManager.Size(), 2);
}

TEST_F(EntityManagerTest, SizeReturnsZeroForEmptyManager)
{
    entityManager.RemoveEntity(1);
    ASSERT_EQ(entityManager.Size(), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
