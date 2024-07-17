#include "ecs.hpp"

using Scene = ECS::Scene<ECS::SimpleSceneMemory>;
using Entity = ECS::TEntity<ECS::SimpleSceneMemory>;
using Component = ECS::TComponent<ECS::SimpleSceneMemory>;
using Script = ECS::TScript<ECS::SimpleSceneMemory>;
template<typename T>
using View = ECS::SimpleView<T>;

class TestComponent : public Component {
public:
    TestComponent(ECS::UUID uuid, int value)
        : Component(uuid), value(value) {}

    int value;
};
class TestScript : public Script {
public:
    using Script::Script;

    void onCreate() override {
        LOG_TRACE("TestScript onCreate: {}", getUUID());
    }
    void onDestroy() override {
        LOG_TRACE("TestScript onDestroy: {}", getUUID());
    }
    void onUpdate(float deltaTime) override {
        LOG_TRACE("TestScript onUpdate: {}", getUUID());
    }
};
int main() {
    Scene scene;
    auto child1 = scene.getRoot()->createChild("Child1");
    auto child2 = scene.getRoot()->createChild("Child2");

    scene.getRoot()->addComponent<Component>();

    child1->addComponent<TestComponent>(42);
    child1->addComponent<Component>();

    child2->addComponent<Script>();
    child2->addComponent<TestScript>();
    child2->addComponent<Component>();
    

    scene.forEachScript(
        [&](View<Entity> entity, View<Script> script) {
            LOG_INFO("Script {} attached on {}", script->getUUID(), entity->tag);
            script->onUpdate(1.0F);
        }
    );
    scene.forEach<TestComponent>(
        [&](View<Entity> entity, View<TestComponent> component) {
            LOG_INFO("Entity {} with TestComponent {}", entity->tag, component->value);
        }
    );
    return 0;
}