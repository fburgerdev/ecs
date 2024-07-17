#pragma once
#include "view.hpp"

namespace ECS {
    // IDerivedMap
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
    // DerivedMap
    template<typename V, typename B = V>
    class DerivedMap : public IDerivedMap<B> {
    public:
        // create
        template<typename... TArgs>
        auto create(UUID key, TArgs&&... args) {
            m_map.try_emplace(key, forward<TArgs>(args)...);
            return get(key);
        }
        // destroy
        virtual void destroy(UUID uuid) override {
            m_map.erase(uuid);
        }
        // get
        auto get(UUID uuid) {
            return SimpleView<V>(&m_map.at(uuid));
        }
        auto get(UUID uuid) const {
            return SimpleView<const V>(&m_map.at(uuid));
        }
        // getBase
        virtual SimpleView<B> getBase(UUID uuid) override {
            return { static_cast<B*>(&m_map.at(uuid)) };
        }
        virtual SimpleView<const B> getBase(UUID uuid) const override {
            return { static_cast<const B*>(&m_map.at(uuid)) };
        }
        // has
        virtual bool has(UUID uuid) const override {
            return m_map.contains(uuid);
        }

        // forEach
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
        // map
        Map<UUID, V> m_map;
    };
}