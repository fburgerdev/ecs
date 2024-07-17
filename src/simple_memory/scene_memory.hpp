#pragma once
#include "base_map.hpp"
#include "entity.hpp"
#include "script.hpp"

namespace ECS {
    // SimpleSceneMemory
    class SimpleSceneMemory {
    public:
        // constructor
        SimpleSceneMemory() = default;

        // alias
        // :: View
        template<typename T>
        using View = SimpleView<T>;
        // :: Entity, Component, Script
        using Entity = TEntity<SimpleSceneMemory>;
        using Component = TComponent<SimpleSceneMemory>;
        using Script = TScript<SimpleSceneMemory>;
        // :: EntityView, ComponentView, ScriptView
        using EntityView = View<Entity>;
        using ComponentView = View<Component>;
        using ScriptView = View<Script>;

        // entity
        // :: create
        auto createEntity(UUID uuid) {
            return m_entities.create(uuid, uuid, this);
        }
        auto createEntity() {
            return createEntity(generateUUID());
        }
        // :: destroy
        void destroyEntity(UUID uuid) {
            m_entities.destroy(uuid);
        }
        // :: get
        auto getEntity(UUID uuid) {
            return m_entities.get(uuid);
        }
        auto getEntity(UUID uuid) const {
            return m_entities.get(uuid);
        }
        // :: has
        bool hasEntity(UUID uuid) const {
            return m_entities.has(uuid);
        }

        // component
        // :: isScript
        template<typename T>
        static constexpr bool isScript() {
            return std::is_base_of_v<Script, T>;
        }
        // :: create
        template<typename T, typename... TArgs>
        auto createComponent(UUID entityUUID, UUID componentUUID, TArgs&&... args) {
            if constexpr (isScript<T>()) {
                return m_scripts.create<T>(entityUUID, componentUUID, forward<TArgs>(args)...);
            }
            else {
                return m_components.create<T>(entityUUID, componentUUID, forward<TArgs>(args)...);
            }
        }
        template<typename T, typename... TArgs>
        auto createComponent(UUID entityUUID, TArgs&&... args) {
            return createComponent(entityUUID, generateUUID(), forward<TArgs>(args)...);
        }
        // :: destroy
        template<typename T>
        void destroyComponent(UUID uuid) {
            if constexpr (isScript<T>()) {
                m_scripts.destroy<T>(uuid);
            }
            else {
                m_components.destroy<T>(uuid);
            }
        }
        void destroyComponent(UUID uuid, address typeHash) {
            if (m_scripts.has(uuid, typeHash)) {
                m_scripts.destroy(uuid, typeHash);
            }
            else {
                m_components.destroy(uuid, typeHash);
            }
        }
        // :: get
        template<typename T>
        auto getComponent(UUID uuid) {
            if constexpr (isScript<T>()) {
                return m_scripts.get<T>(uuid);
            }
            else {
                return m_components.get<T>(uuid);
            }
        }
        template<typename T>
        auto getComponent(UUID uuid) const {
            if constexpr (isScript<T>()) {
                return m_scripts.get<T>(uuid);
            }
            else {
                return m_components.get<T>(uuid);
            }
        }
        SimpleView<Component> getComponent(UUID uuid, address typeHash) {
            if (m_scripts.has(uuid, typeHash)) {
                return m_scripts.getBase(uuid, typeHash);
            }
            else {
                return m_components.getBase(uuid, typeHash);
            }
        }
        // :: has
        template<typename T>
        bool hasComponent(UUID uuid) const {
            if constexpr (isScript<T>()) {
                return m_scripts.has<T>(uuid);
            }
            else {
                return m_components.has<T>(uuid);
            }
        }
        bool hasComponent(UUID uuid, address typeHash) const {
            return m_scripts.has(uuid, typeHash) || m_components.has(uuid, typeHash);
        }

        // forEach
        // :: entity
        void forEachEntity(function<void(View<Entity>)> func) {
            m_entities.forEach(func);
        }
        // :: component
        void forEachComponent(function<void(View<Entity>, View<Component>)> func) {
            m_components.forEach([&](UUID entityUUID, View<Component> component) {
                func(getEntity(entityUUID), component);
            });
        }
        // :: script
        void forEachScript(function<void(View<Entity>, View<Script>)> func) {
            m_scripts.forEach([&](UUID entityUUID, View<Script> script) {
                func(getEntity(entityUUID), script);
            });
        }
        // :: entity + component or script
        template<typename T>
        void forEach(function<void(View<Entity>, View<T>)> func) {
            if constexpr (isScript<T>()) {
                m_scripts.forEach<T>([&](UUID entityUUID, View<T> component) {
                    func(getEntity(entityUUID), component);
                });
            }
            else {
                m_components.forEach<T>([&](UUID entityUUID, View<T> component) {
                    func(getEntity(entityUUID), component);
                });
            }
        }
    private:
        // entity, component and script map
        DerivedMap<Entity> m_entities;
        BaseMap<Component> m_components;
        BaseMap<Script> m_scripts;
    };
    // component
    // :: create
    template<typename T, typename... TArgs>
    auto createComponentMemory(SimpleSceneMemory* memory, UUID entityUUID, UUID uuid, TArgs&&... args) {
        return memory->createComponent<T>(entityUUID, uuid, forward<TArgs>(args)...);
    }
    template<typename T, typename... TArgs>
    auto createScriptMemory(SimpleSceneMemory* memory, UUID entityUUID, UUID uuid, TArgs&&... args) {
        return memory->createComponent<T>(entityUUID, uuid, memory->getEntity(entityUUID), forward<TArgs>(args)...);
    }
    // :: destroy
    template<typename T>
    void destroyComponentMemory(SimpleSceneMemory* memory, UUID uuid) {
        memory->destroyComponent<T>(uuid);
    }
    // :: get
    template<typename T>
    auto getComponentMemory(SimpleSceneMemory* memory, UUID uuid) {
        return memory->getComponent<T>(uuid);
    }
    template<typename T>
    auto getComponentMemory(const SimpleSceneMemory* memory, UUID uuid) {
        return memory->getComponent<T>(uuid);
    }
    // :: has
    template<typename T>
    bool hasComponentMemory(const SimpleSceneMemory* memory, UUID uuid) {
        return memory->hasComponent<T>(uuid);
    }
}