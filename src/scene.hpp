#pragma once
#include "scene_memory.hpp"

namespace ECS {
    // Scene
    template<SceneMemory Memory>
    class Scene {
    public:
        // alias
        // :: View
        template<typename T>
        using View = typename Memory::View<T>;
        // :: Entity, Component, Script
        using Entity = Memory::Entity;
        using Component = Memory::Component;
        using Script = Memory::Script;
        // :: EntityView, ComponentView, ScriptView
        using EntityView = View<Entity>;
        using ComponentView = View<Component>;
        using ScriptView = View<Script>;

        // constructor
        Scene() {
            m_root = m_memory.createEntity();
            m_root->tag = "ROOT";
        }
        // destructor
        ~Scene() {
            m_memory.destroyEntity(m_root->getUUID());
        }

        // root
        // :: getRoot
        auto getRoot() {
            return m_root;
        }

        // forEach
        // :: entity
        void forEachEntity(function<void(View<Entity>)> func) {
            m_memory.forEachEntity(func);
        }
        // :: component
        void forEachComponent(function<void(View<Entity>, View<Component>)> func) {
            m_memory.forEachComponent(func);
        }
        // :: script
        void forEachScript(function<void(View<Entity>, View<Script>)> func) {
            m_memory.forEachScript(func);
        }
        // :: entity + component or script
        template<typename T>
        void forEach(function<void(View<Entity>, View<T>)> func) {
            m_memory.forEach(func);
        }
    private:
        // memory
        Memory::EntityView m_root;
        Memory m_memory;
    };
}