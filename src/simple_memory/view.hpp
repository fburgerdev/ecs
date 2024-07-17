#pragma once
#include "common.hpp"

namespace ECS {
    // SimpleView
    template<typename T>
    class SimpleView {
    public:
        // constructor
        SimpleView() = default;
        SimpleView(T* ptr)
            : m_ptr(ptr) {}
        template<typename U>
        SimpleView(const SimpleView<U>& other)
            : m_ptr(static_cast<T*>(other.m_ptr)){}

        // operator->
        auto* operator->() const {
            return m_ptr;
        } 
        // validate
        // :: isValid
        bool isValid() const {
            return m_ptr != nullptr;
        }
        // :: bool()
        explicit operator bool() const {
            return isValid();
        }
        // operator<=>
        auto operator<=>(const SimpleView<T>&) const = default;

        // friend
        template<typename U>
        friend class SimpleView;
    private:
        // pointer
        T* m_ptr = nullptr;
    };
}