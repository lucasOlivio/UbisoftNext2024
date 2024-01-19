#include <gtest/gtest.h>
#include <glm/glm.hpp>

#include <Engine/ECS/Scene.h>
#include <Engine/ECS/Components.h>

using namespace MyEngine;

class SceneTest : public ::testing::Test {
protected:
    void SetUp() override {
        scene = new Scene();
    }

    void TearDown() override {
        delete scene;
    }

    Scene* scene;
};

TEST_F(SceneTest, CreateEntity) {
    Entity entity = scene->CreateEntity();

    // Expect the entity ID to be greater than -1
    EXPECT_GT(entity, -1);
}

TEST_F(SceneTest, AddGetComponent) {
    Entity entity = scene->CreateEntity();

    // Add a component
    TransformComponent* transformComponent = scene->AddComponent<TransformComponent>(entity);
    ASSERT_NE(transformComponent, nullptr);

    // Retrieve the component
    TransformComponent* retrievedComponent = scene->Get<TransformComponent>(entity);
    ASSERT_EQ(transformComponent, retrievedComponent);

    // Modify the component and check if the changes are reflected
    retrievedComponent->position = glm::vec3(1.0f, 2.0f, 3.0f);

    TransformComponent* updatedComponent = scene->Get<TransformComponent>(entity);
    ASSERT_EQ(updatedComponent->position, retrievedComponent->position);
}

TEST_F(SceneTest, DestroyEntity) {
    Entity entity = scene->CreateEntity();

    // Add a component
    TransformComponent* transformComponent = scene->AddComponent<TransformComponent>(entity);
    ASSERT_NE(transformComponent, nullptr);

    // Remove the entity and destroy from scene
    scene->RemoveEntity(entity);

    scene->DestroyEntities();

    // Try to retrieve the component after removal, should be nullptr
    TransformComponent* retrievedComponent = scene->Get<TransformComponent>(entity);
    ASSERT_EQ(retrievedComponent, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}