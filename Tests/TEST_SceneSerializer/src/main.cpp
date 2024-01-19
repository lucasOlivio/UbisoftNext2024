#include <gtest/gtest.h>
#include <Engine/ECS/SceneSerializer.h>
#include <Engine/ECS/Components.h>
#include <Engine/Utils/Files.h>

using namespace MyEngine;

class SceneSerializerTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_pScene = new Scene();
        m_pSerializer = new SceneSerializer(m_pScene);
    }

    void TearDown() override {
        delete m_pSerializer;
        delete m_pScene;
    }

    Scene* m_pScene;
    SceneSerializer* m_pSerializer;
};

TEST_F(SceneSerializerTest, SerializeTest) {
    const std::string filepath = "test_scene.json";

    // Composing scene
    Entity entity = m_pScene->CreateEntity();

    TagComponent* tagComponent = m_pScene->AddComponent<TagComponent>(entity);
    tagComponent->name = "test";

    TransformComponent* transformComponent = m_pScene->AddComponent<TransformComponent>(entity);
    transformComponent->position = glm::vec3(1.1f, 2.2f, 3.3f);
    transformComponent->orientation = glm::quat(1.1f, 2.2f, 3.3f, 4.4f);
    transformComponent->scale = 4.2f;

    MovementComponent* movementComponent = m_pScene->AddComponent<MovementComponent>(entity);
    movementComponent->velocity = glm::vec3(1.1f, 2.2f, 3.3f);
    movementComponent->acceleration = glm::vec3(1.1f, 2.2f, 3.3f);

    Entity entity2 = m_pScene->CreateEntity();

    TagComponent* tagComponent2 = m_pScene->AddComponent<TagComponent>(entity2);
    tagComponent2->name = "test2";

    TransformComponent* transformComponent2 = m_pScene->AddComponent<TransformComponent>(entity2);
    transformComponent2->position = glm::vec3(5.1f, 6.2f, 7.3f);
    transformComponent2->orientation = glm::quat(8.1f, 9.2f, 7.3f, 6.4f);
    transformComponent2->scale = 22.2f;

    // Perform serialization
    bool result = m_pSerializer->Serialize(filepath);

    // Check if serialization was successful
    EXPECT_TRUE(result);

    bool fileExists = FileExists(filepath);
    EXPECT_TRUE(fileExists);
}

TEST_F(SceneSerializerTest, DeserializeTest) {
    const std::string filepath = "test_scene.json";

    // Perform deserialization
    bool result = m_pSerializer->Deserialize(filepath);

    // Check if deserialization was successful
    EXPECT_TRUE(result);

    // Check if scene is constructed right
    EntityManager* pEntityManager = m_pScene->GetEntitymanager();
    EXPECT_EQ(pEntityManager->Size(), 3); // 1 more for the singleton components

    ComponentType tag = m_pScene->GetComponentType<TagComponent>();
    ComponentType transform = m_pScene->GetComponentType<TransformComponent>();
    ComponentType movement = m_pScene->GetComponentType<MovementComponent>();
    EXPECT_TRUE(pEntityManager->HasComponent(1, tag));
    EXPECT_TRUE(pEntityManager->HasComponent(1, transform));
    EXPECT_TRUE(pEntityManager->HasComponent(1, movement));

    EXPECT_TRUE(pEntityManager->HasComponent(2, tag));
    EXPECT_TRUE(pEntityManager->HasComponent(2, transform));
    EXPECT_FALSE(pEntityManager->HasComponent(2, movement));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
