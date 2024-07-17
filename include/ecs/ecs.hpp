#pragma once
// #include "common.hpp" (HPPMERGE)
#include <ranges> 
#include <memory> 
#include <string> 
#include <string_view> 
#include <array> 
#include <vector> 
#include <stack> 
#include <queue> 
#include <deque> 
#include <unordered_set> 
#include <map> 
#include <set> 
#include <unordered_map> 
#include <functional> 
#include <optional> 
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <mutex> 
#include <shared_mutex> 
#include <atomic> 
namespace ECS {
    namespace stdr = std::ranges;
    using address = std::size_t;
    using uchar = unsigned char;
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    using uint = unsigned int;
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using string = std::string;
    using strview = std::string_view;
    template<typename T, address N>
    using Array = std::array<T, N>;
    template<typename T>
    using List = std::vector<T>;
    template<typename T>
    using Stack = std::stack<T>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename T>
    using Deque = std::deque<T>;
    template<typename T>
    using Set = std::set<T>;
    template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
    template<typename T>
    using HashSet = std::unordered_set<T>;
    template<typename Key, typename Value>
    using HashMap = std::unordered_map<Key, Value>;
    using std::forward;
    using std::move;
    template<class T, class... Args>
    auto makeUniquePtr(Args&&... args) {
        return std::make_unique<T>(forward(args)...);
    }
    template<class T, class... Args>
    auto makeSharedPtr(Args&&... args) {
        return std::make_shared<T>(forward(args)...);
    }
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;
    using std::function;
    template<typename T>
    using Opt = std::optional<T>;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    using strstream = std::stringstream;
    using std::mutex;
    using std::recursive_mutex;
    using std::shared_mutex;
    template<typename Mutex>
    using UniqueLock = std::unique_lock<Mutex>;
    template<typename Mutex>
    using SharedLock = std::shared_lock<Mutex>;
    using atomic_address = std::atomic_size_t;
    using atomic_int = std::atomic_int;
    using atomic_int8 = std::atomic_int8_t;
    using atomic_int16 = std::atomic_int16_t;
    using atomic_int32 = std::atomic_int32_t;
    using atomic_int64 = std::atomic_int64_t;
    using atomic_uint = std::atomic_uint;
    using atomic_uint8 = std::atomic_uint8_t;
    using atomic_uint16 = std::atomic_uint16_t;
    using atomic_uint32 = std::atomic_uint32_t;
    using atomic_uint64 = std::atomic_uint64_t;
}
// #include "uuid.hpp" (HPPMERGE)
namespace ECS {
    using UUID = uint64;
    UUID generateUUID();
    class UUIDObject {
    public:
        UUIDObject(UUID uuid)
            : m_uuid(uuid) {}
        UUIDObject(const UUIDObject&) = delete;
        UUIDObject(UUIDObject&& other)
            : m_uuid(other.m_uuid) {
            other.m_uuid = 0;
        }
        UUID getUUID() const {
            return m_uuid;
        }
    private:
        UUID m_uuid;
    };
}
// #include "logging.hpp" (HPPMERGE)
#if defined(BEAVER_LOGGING)
#include "beaver/beaver.hpp"
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#define ASSERT(...)
#define ASSERT_MSG(...)
#endif
// #include "component.hpp" (HPPMERGE)
namespace ECS {
    template<typename Memory>
    class TComponent : public UUIDObject {
    public:
        TComponent(UUID uuid)
            : UUIDObject(uuid) {}
        virtual ~TComponent() = default;
        virtual void onCreate() {
            LOG_TRACE("Component onCreate: {} ", getUUID());
        }
        virtual void onDestroy() {
            LOG_TRACE("Component onDestroy: {} ", getUUID());
        }
    };
}
// #include "script.hpp" (HPPMERGE)
namespace ECS {
    template<typename Memory>
    class TScript : public TComponent<Memory> {
    public:
        TScript(UUID uuid, typename Memory::EntityView entity)
            : TComponent<Memory>(uuid), entity(entity) {}
        virtual ~TScript() = default;
        virtual void onCreate() override {
            LOG_TRACE("Script onCreate: {} ", UUIDObject::getUUID());
        }
        virtual void onDestroy() override {
            LOG_TRACE("Script onDestroy: {} ", UUIDObject::getUUID());
        }
        virtual void onUpdate(float deltaTime) {
            LOG_TRACE("Script onUpdate: {} ", UUIDObject::getUUID());
        }
        typename Memory::EntityView entity;
    };
}
// #include "transform.hpp" (HPPMERGE)
#include "vecmath/vecmath.hpp"
namespace ECS {
    struct Transform {
        Transform() = default;
        Math::Vec3F position = Math::Vec3F(0);
        Math::Vec3F rotation = Math::Vec3F(0);
        Math::Vec3F scale = Math::Vec3F(1);
    };
}
// #include "view.hpp" (HPPMERGE)
#include <concepts>
namespace ECS {
    template<typename T>
    concept View = requires(T x) {
        { x.operator->() };
    };
}
// #include "scene_memory.hpp" (HPPMERGE)
namespace ECS {
    template<typename T>
    concept SceneMemory = requires(T x, UUID uuid) {
        { T() };
    };
}
// #include "entity.hpp" (HPPMERGE)
namespace ECS {
    template<typename Memory>
    class TEntity : public UUIDObject {
    public:
        TEntity(UUID uuid, Memory* memory)
            : UUIDObject(uuid), m_memory(memory) {}
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
        auto createChild(const string& tag) {
            auto child = m_memory->createEntity();
            child->m_parent = getUUID();
            m_children.insert(child->getUUID());
            child->tag = tag;
            return child;
        }
        void destroyChild(View auto entity) {
            m_memory->destroyEntity(entity->getUUID());
            m_children.erase(entity->getUUID());
        }
        void hasChild(View auto entity) {
            return m_children.contains(entity->getUUID());
        }
        auto children() {
            Set<typename Memory::EntityView> out;
            for (UUID childUUID : m_children) {
                out.insert(m_memory->getEntity(childUUID));
            }
            return out;
        }
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
        template<typename T>
        void removeComponent() {
            getComponent<T>()->onDestroy();
            destroyComponentMemory<T>(m_memory, getUUID());
            m_components.erase(typeid(T).hash_code());
        }
        template<typename T>
        auto getComponent() {
            return getComponentMemory<T>(m_memory, getUUID());
        }
        template<typename T>
        auto getComponent() const {
            return destroyComponentMemory<T>(m_memory, getUUID());
        }
        template<typename T>
        bool hasComponent() const {
            return hasComponentMemory<T>(m_memory, getUUID());
        }
        string tag = "Entity";
        Transform transform;
    private:
        UUID m_parent;
        Set<UUID> m_children;
        Set<address> m_components;
        Memory* m_memory = nullptr;
    };
}
// #include "scene.hpp" (HPPMERGE)
namespace ECS {
    template<SceneMemory Memory>
    class Scene {
    public:
        template<typename T>
        using View = typename Memory::View<T>;
        using Entity = Memory::Entity;
        using Component = Memory::Component;
        using Script = Memory::Script;
        using EntityView = View<Entity>;
        using ComponentView = View<Component>;
        using ScriptView = View<Script>;
        Scene() {
            m_root = m_memory.createEntity();
            m_root->tag = "ROOT";
        }
        ~Scene() {
            m_memory.destroyEntity(m_root->getUUID());
        }
        auto getRoot() {
            return m_root;
        }
        void forEachEntity(function<void(View<Entity>)> func) {
            m_memory.forEachEntity(func);
        }
        void forEachComponent(function<void(View<Entity>, View<Component>)> func) {
            m_memory.forEachComponent(func);
        }
        void forEachScript(function<void(View<Entity>, View<Script>)> func) {
            m_memory.forEachScript(func);
        }
        template<typename T>
        void forEach(function<void(View<Entity>, View<T>)> func) {
            m_memory.forEach(func);
        }
    private:
        Memory::EntityView m_root;
        Memory m_memory;
    };
}
// #include "view.hpp" (HPPMERGE)
namespace ECS {
    template<typename T>
    class SimpleView {
    public:
        SimpleView() = default;
        SimpleView(T* ptr)
            : m_ptr(ptr) {}
        template<typename U>
        SimpleView(const SimpleView<U>& other)
            : m_ptr(static_cast<T*>(other.m_ptr)){}
        auto* operator->() const {
            return m_ptr;
        } 
        bool isValid() const {
            return m_ptr != nullptr;
        }
        explicit operator bool() const {
            return isValid();
        }
        auto operator<=>(const SimpleView<T>&) const = default;
        template<typename U>
        friend class SimpleView;
    private:
        T* m_ptr = nullptr;
    };
}
// #include "derived_map.hpp" (HPPMERGE)
namespace ECS {
    template<typename B>
    class IDerivedMap {
    public:
        virtual ~IDerivedMap() = default;
        virtual void destroy(UUID uuid) = 0;
        virtual SimpleView<B> getBase(UUID uuid) = 0;
        virtual SimpleView<const B> getBase(UUID uuid) const = 0;
        virtual bool has(UUID uuid) const = 0;
        virtual void forEach(function<void(SimpleView<B>)>) = 0;
        virtual void forEach(function<void(UUID, SimpleView<B>)>) = 0;
    };
    template<typename V, typename B = V>
    class DerivedMap : public IDerivedMap<B> {
    public:
        template<typename... TArgs>
        auto create(UUID key, TArgs&&... args) {
            m_map.try_emplace(key, forward<TArgs>(args)...);
            return get(key);
        }
        virtual void destroy(UUID uuid) override {
            m_map.erase(uuid);
        }
        auto get(UUID uuid) {
            return SimpleView<V>(&m_map.at(uuid));
        }
        auto get(UUID uuid) const {
            return SimpleView<const V>(&m_map.at(uuid));
        }
        virtual SimpleView<B> getBase(UUID uuid) override {
            return { static_cast<B*>(&m_map.at(uuid)) };
        }
        virtual SimpleView<const B> getBase(UUID uuid) const override {
            return { static_cast<const B*>(&m_map.at(uuid)) };
        }
        virtual bool has(UUID uuid) const override {
            return m_map.contains(uuid);
        }
        virtual void forEach(function<void(SimpleView<B>)> func) override {
            for (auto& [key, value] : m_map) {
                func({ &value });
            }
        }
        virtual void forEach(function<void(UUID, SimpleView<B>)> func) override {
            for (auto& [key, value] : m_map) {
                func(key, { &value });
            }
        }
    private:
        Map<UUID, V> m_map;
    };
}
// #include "base_map.hpp" (HPPMERGE)
namespace ECS {
    template<typename B>
    class BaseMap {
    public:
        template<typename T, typename... TArgs>
        auto create(UUID key, UUID uuid, TArgs&&... args) {
            return getMap<T>().create(key, uuid, forward<TArgs>(args)...);
        }
        template<typename T>
        void destroy(UUID uuid) {
            getMap<T>().destroy(uuid);
        }
        void destroy(UUID uuid, address typeHash) {
            m_map.at(typeHash)->destroy(uuid);
        }
        template<typename T>
        auto get(UUID uuid) {
            return getMap<T>().get(uuid);
        }
        template<typename T>
        auto get(UUID uuid) const {
            return getMap<T>().get(uuid);
        }
        auto getBase(UUID uuid, address typeHash) {
            return m_map.at(typeHash)->getBase(uuid);
        }
        auto getBase(UUID uuid, address typeHash) const {
            return m_map.at(typeHash)->getBase(uuid);
        }
        template<typename T>
        bool has(UUID uuid) const {
            return getMap<T>().has(uuid);
        }
        bool has(UUID uuid, address typeHash) const {
            return m_map.contains(typeHash) && m_map.at(typeHash)->has(uuid);
        }
        template<typename T>
        void forEach(function<void(SimpleView<T>)> func) {
            getMap<T>().forEach(func);
        }
        template<typename T>
        void forEach(function<void(UUID, SimpleView<T>)> func) {
            getMap<T>().forEach(func);
        }
        void forEach(function<void(SimpleView<B>)> func) {
            for (auto& [hash, map] : m_map) {
                map->forEach(func);
            }
        }
        void forEach(function<void(UUID, SimpleView<B>)> func) {
            for (auto& [hash, map] : m_map) {
                map->forEach(func);
            }
        }
    private:
        template<typename T>
        auto& getMap() {
            if (!m_map.contains(typeid(T).hash_code())) {
                m_map.emplace(typeid(T).hash_code(), static_cast<IDerivedMap<B>*>(new DerivedMap<T, B>()));
            }
            return *dynamic_cast<DerivedMap<T, B>*>(m_map.at(typeid(T).hash_code()).get());
        }
        Map<address, UniquePtr<IDerivedMap<B>>> m_map;
    };
}
// #include "scene_memory.hpp" (HPPMERGE)
namespace ECS {
    class SimpleSceneMemory {
    public:
        SimpleSceneMemory() = default;
        template<typename T>
        using View = SimpleView<T>;
        using Entity = TEntity<SimpleSceneMemory>;
        using Component = TComponent<SimpleSceneMemory>;
        using Script = TScript<SimpleSceneMemory>;
        using EntityView = View<Entity>;
        using ComponentView = View<Component>;
        using ScriptView = View<Script>;
        auto createEntity(UUID uuid) {
            return m_entities.create(uuid, uuid, this);
        }
        auto createEntity() {
            return createEntity(generateUUID());
        }
        void destroyEntity(UUID uuid) {
            m_entities.destroy(uuid);
        }
        auto getEntity(UUID uuid) {
            return m_entities.get(uuid);
        }
        auto getEntity(UUID uuid) const {
            return m_entities.get(uuid);
        }
        bool hasEntity(UUID uuid) const {
            return m_entities.has(uuid);
        }
        template<typename T>
        static constexpr bool isScript() {
            return std::is_base_of_v<Script, T>;
        }
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
        void forEachEntity(function<void(View<Entity>)> func) {
            m_entities.forEach(func);
        }
        void forEachComponent(function<void(View<Entity>, View<Component>)> func) {
            m_components.forEach([&](UUID entityUUID, View<Component> component) {
                func(getEntity(entityUUID), component);
            });
        }
        void forEachScript(function<void(View<Entity>, View<Script>)> func) {
            m_scripts.forEach([&](UUID entityUUID, View<Script> script) {
                func(getEntity(entityUUID), script);
            });
        }
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
        DerivedMap<Entity> m_entities;
        BaseMap<Component> m_components;
        BaseMap<Script> m_scripts;
    };
    template<typename T, typename... TArgs>
    auto createComponentMemory(SimpleSceneMemory* memory, UUID entityUUID, UUID uuid, TArgs&&... args) {
        return memory->createComponent<T>(entityUUID, uuid, forward<TArgs>(args)...);
    }
    template<typename T, typename... TArgs>
    auto createScriptMemory(SimpleSceneMemory* memory, UUID entityUUID, UUID uuid, TArgs&&... args) {
        return memory->createComponent<T>(entityUUID, uuid, memory->getEntity(entityUUID), forward<TArgs>(args)...);
    }
    template<typename T>
    void destroyComponentMemory(SimpleSceneMemory* memory, UUID uuid) {
        memory->destroyComponent<T>(uuid);
    }
    template<typename T>
    auto getComponentMemory(SimpleSceneMemory* memory, UUID uuid) {
        return memory->getComponent<T>(uuid);
    }
    template<typename T>
    auto getComponentMemory(const SimpleSceneMemory* memory, UUID uuid) {
        return memory->getComponent<T>(uuid);
    }
    template<typename T>
    bool hasComponentMemory(const SimpleSceneMemory* memory, UUID uuid) {
        return memory->hasComponent<T>(uuid);
    }
}