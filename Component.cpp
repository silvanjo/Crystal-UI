#include "Component.h"

#include <algorithm>
#include <stdexcept>

namespace Crystal {
    int Component::next_id = 0;

    Component::Component(std::weak_ptr<Component> parent, float size_x, float size_y, float position_x, float position_y, bool relative) {
        this->id = next_id++;

        this->parent = parent;

        this->size_x = size_x;
        this->size_y = size_y;

        if (relative) {
            this->relative_x = position_x;
            this->relative_y = position_y;
            
            if (auto p = parent.lock()) {
                this->absolute_x = p->GetAbsoluteX() + position_x;
                this->absolute_y = p->GetAbsoluteY() + position_y;
            } else {
                this->absolute_x = position_x;
                this->absolute_y = position_y;
            }

        } else {
            this->absolute_x = position_x;
            this->absolute_y = position_y;
            
            if (auto p = parent.lock()) {
                this->relative_x = position_x - p->GetAbsoluteX();
                this->relative_y = position_y - p->GetAbsoluteY();
            } else {
                this->relative_x = position_x;
                this->relative_y = position_y;
            }
        }
    }

    void EventHandler(Component::EventType event, float x, float y) {
        /* TODO: Implement event handling */
    }

    bool Component::IsPointInside(float x, float y) {
        return x >= this->absolute_x && x <= this->absolute_x + this->size_x && y >= this->absolute_y && y <= this->absolute_y + this->size_y;
    }

    template<typename T, typename... Args>
    std::weak_ptr<T> Component::AddChild(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        
        auto child = std::make_shared<T>(std::forward<Args>(args)...);
        child->SetParent(this->shared_from_this());
        this->children.push_back(child);
        return child;
    }

    template<typename T>
    std::weak_ptr<T> Component::AddChild(std::shared_ptr<T> child) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

        if (!child) {
            throw std::invalid_argument("Child cannot be null.");
        }

        /* If the provided child already has a parent, we remove that connection and instead this component as the new parent. */
        if (auto p = child->GetParent().lock()) {
            p->RemoveChild(child);
        }
        
        /* This this as the new parent */
        child->SetParent(this->shared_from_this());

        this->children.push_back(child);
    }

    void Component::RemoveChild(std::shared_ptr<Component> child) {
        auto iterator = std::find(this->children.begin(), this->children.end(), child); 

        if (iterator != this->children.end()) {
            this->children.erase(iterator);
        }
    }

    void Component::SetParent(std::weak_ptr<Component> parent) {
        /* Make sure the parent is not the same component as the cild */
        if (auto p = parent.lock()) {
            if (p.get() == this) {
                throw std::invalid_argument("Parent cannot be the same as the child.");
            }
        }

        this->parent = parent;
    }

    std::weak_ptr<Component> Component::GetParent() {
            return this->parent;
    }

    std::vector<std::shared_ptr<Component>> Component::GetChildren() {
            return this->children;
    }

    void Component::SetSize(float x, float y) {
        this->size_x = x;
        this->size_y = y;
    }

    void Component::SetAbsolutePosition(float x, float y) {
        this->absolute_x = x;
        this->absolute_y = y;
        if (auto p = parent.lock()) {
            this->relative_x = x - p->GetAbsoluteX();
            this->relative_y = y - p->GetAbsoluteY();
        } else {
            this->relative_x = x;
            this->relative_y = y;
        }
    }

    void Component::SetRelativePosition(float x, float y) {
        this->relative_x = x;
        this->relative_y = y;
        if (auto p = parent.lock()) {
            this->absolute_x = p->GetAbsoluteX() + x;
            this->absolute_y = p->GetAbsoluteY() + y;
        } else {
            this->absolute_x = x;
            this->absolute_y = y;
        }
    }

    void Component::SetVisibility(bool is_visible) {
        this->is_visible = is_visible;
    }

    float Component::GetAbsoluteX() {
        return this->absolute_x;
    }

    float Component::GetAbsoluteY() {
        return this->absolute_y;
    }

    float Component::GetRelativeX() {
        return this->relative_x;
    }

    float Component::GetRelativeY() {
        return this->relative_y;
    }

    float Component::GetSizeX() {
        return this->size_x;
    }

    float Component::GetSizeY() {
        return this->size_y;
    }

}
