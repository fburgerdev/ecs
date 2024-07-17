#pragma once
#include "common.hpp"

namespace ECS {
    // UUID
    using UUID = uint64;
    // generateUUID
    UUID generateUUID();

    // UUIDObject
    class UUIDObject {
    public:
        // constructor
        UUIDObject(UUID uuid)
            : m_uuid(uuid) {}
        UUIDObject(const UUIDObject&) = delete;
        UUIDObject(UUIDObject&& other)
            : m_uuid(other.m_uuid) {
            other.m_uuid = 0;
        }
        // get
        UUID getUUID() const {
            return m_uuid;
        }
    private:
        // UUID
        UUID m_uuid;
    };
}