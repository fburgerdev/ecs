#pragma once
#include "uuid.hpp"
#include "logging.hpp"

namespace ECS {
    // TComponent
    template<typename Memory>
    class TComponent : public UUIDObject {
    public:
        // constructor
        TComponent(UUID uuid)
            : UUIDObject(uuid) {}
        // destructor
        virtual ~TComponent() = default;

        // events
        // :: onCreate
        virtual void onCreate() {
            LOG_TRACE("Component onCreate: {} ", getUUID());
        }
        // :: onDestroy
        virtual void onDestroy() {
            LOG_TRACE("Component onDestroy: {} ", getUUID());
        }
    };
}