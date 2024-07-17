#pragma once
#include "derived_map.hpp"

namespace ECS {
    // BaseMap
    template<typename B>
    class BaseMap {
    public:
        // create
        template<typename T, typename... TArgs>
        auto create(UUID key, UUID uuid, TArgs&&... args) {
            return getMap<T>().create(key, uuid, forward<TArgs>(args)...);
        }
        // destroy
        template<typename T>
        void destroy(UUID uuid) {
            getMap<T>().destroy(uuid);
        }
        void destroy(UUID uuid, address typeHash) {
            m_map.at(typeHash)->destroy(uuid);
        }
        // get
        template<typename T>
        auto get(UUID uuid) {
            return getMap<T>().get(uuid);
        }
        template<typename T>
        auto get(UUID uuid) const {
            return getMap<T>().get(uuid);
        }
        // getBase
        auto getBase(UUID uuid, address typeHash) {
            return m_map.at(typeHash)->getBase(uuid);
        }
        auto getBase(UUID uuid, address typeHash) const {
            return m_map.at(typeHash)->getBase(uuid);
        }
        // has
        template<typename T>
        bool has(UUID uuid) const {
            return getMap<T>().has(uuid);
        }
        bool has(UUID uuid, address typeHash) const {
            return m_map.contains(typeHash) && m_map.at(typeHash)->has(uuid);
        }

        // forEach
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
        // getMap
        template<typename T>
        auto& getMap() {
            if (!m_map.contains(typeid(T).hash_code())) {
                m_map.emplace(typeid(T).hash_code(), static_cast<IDerivedMap<B>*>(new DerivedMap<T, B>()));
            }
            return *dynamic_cast<DerivedMap<T, B>*>(m_map.at(typeid(T).hash_code()).get());
        }
        // map
        Map<address, UniquePtr<IDerivedMap<B>>> m_map;
    };
}