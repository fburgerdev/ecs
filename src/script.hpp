#pragma once
#include "component.hpp"

namespace ECS {
    // TScript
    template<typename Memory>
    class TScript : public TComponent<Memory> {
    public:
        // constructor
        TScript(UUID uuid, typename Memory::EntityView entity)
            : TComponent<Memory>(uuid), entity(entity) {}
        // destructor
        virtual ~TScript() = default;

        // events
        // :: onCreate
        virtual void onCreate() override {
            LOG_TRACE("Script onCreate: {} ", UUIDObject::getUUID());
        }
        // :: onDestroy
        virtual void onDestroy() override {
            LOG_TRACE("Script onDestroy: {} ", UUIDObject::getUUID());
        }
        // :: onUpdate
        virtual void onUpdate(float deltaTime) {
            LOG_TRACE("Script onUpdate: {} ", UUIDObject::getUUID());
        }

        // entity
        typename Memory::EntityView entity;
    };
}