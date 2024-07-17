#pragma once
#include "transform.hpp"
#include "component.hpp"
#include "script.hpp"
#include "scene_memory.hpp"

namespace ECS {
    // TEntity
    template<typename Memory>
    class TEntity : public UUIDObject {
    public:
        // constructor
        TEntity(UUID uuid, Memory* memory)
            : UUIDObject(uuid), m_memory(memory) {}
        // destructor
        ~TEntity() {
            LOG_TRACE("~Entity: {}", tag);
            for (auto componentUUID : m_components) {
                m_memory->getComponent(getUUID(), componentUUID)->onDestroy();
                m_memory->destroyComponent(getUUID(), componentUUID);
            }
            for (auto childUUID : m_children) {
                m_memory->destroyEntity(childUUID);
            }
        }

        // children
        // :: create
        auto createChild(const string& tag) {
            auto child = m_memory->createEntity();
            child->m_parent = getUUID();
            m_children.insert(child->getUUID());

            child->tag = tag;
            return child;
        }
        // :: destroy
        void destroyChild(View auto entity) {
            m_memory->destroyEntity(entity->getUUID());
            m_children.erase(entity->getUUID());
        }
        // :: has
        void hasChild(View auto entity) {
            return m_children.contains(entity->getUUID());
        }
        // :: children
        auto children() {
            Set<typename Memory::EntityView> out;
            for (UUID childUUID : m_children) {
                out.insert(m_memory->getEntity(childUUID));
            }
            return out;
        }

        // component
        // :: add
        template<typename T, typename... TArgs>
        auto addComponent(TArgs&&... args) {
            m_components.insert(typeid(T).hash_code());
            if constexpr (std::is_base_of_v<typename Memory::Script, T>) {
                auto component = createScriptMemory<T>(m_memory, getUUID(), generateUUID(), forward<TArgs>(args)...);
                component->onCreate();
                return component;
            }
            else {
                auto component = createComponentMemory<T>(m_memory, getUUID(), generateUUID(), forward<TArgs>(args)...);
                component->onCreate();
                return component;
            }
        }
        // :: remove
        template<typename T>
        void removeComponent() {
            getComponent<T>()->onDestroy();
            destroyComponentMemory<T>(m_memory, getUUID());
            m_components.erase(typeid(T).hash_code());
        }
        // :: get
        template<typename T>
        auto getComponent() {
            return getComponentMemory<T>(m_memory, getUUID());
        }
        template<typename T>
        auto getComponent() const {
            return destroyComponentMemory<T>(m_memory, getUUID());
        }
        // :: has
        template<typename T>
        bool hasComponent() const {
            return hasComponentMemory<T>(m_memory, getUUID());
        }

        // tag
        string tag = "Entity";
        // transform
        Transform transform;
    private:
        // parent / children
        UUID m_parent;
        Set<UUID> m_children;
        // components
        Set<address> m_components;
        // memory
        Memory* m_memory = nullptr;
    };
}