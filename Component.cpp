#include "Component.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "Libs/glm/glm.hpp"

namespace Crystal {
    int Component::next_id = 0;

    Component::Component(std::shared_ptr<Component> parent, float size_x, float size_y, float position_x, float position_y, bool relative = true) {
        this->id = next_id++;
        this->parent = parent;
        this->size_x = size_x;
        this->size_y = size_y;
        this->is_visible = true;

        this->rectangle = std::make_unique<Rectangle>(size_x, size_y, position_x, position_y); 

        if (relative) {
            this->relative_x = position_x;
            this->relative_y = position_y;
            
            if (parent != nullptr) {
                this->absolute_x = parent->GetAbsoluteX() + position_x;
                this->absolute_y = parent->GetAbsoluteY() + position_y;
            } else {
                this->absolute_x = position_x;
                this->absolute_y = position_y;
            }

        } else {
            this->absolute_x = position_x;
            this->absolute_y = position_y;

            if (parent != nullptr) {
                this->relative_x = position_x - parent->GetAbsoluteX();
                this->relative_y = position_y - parent->GetAbsoluteY();
            } else {
                this->relative_x = position_x;
                this->relative_y = position_y;
            }
        }

        /* Set transforms for mesh */
        this->rectangle->SetPosition(glm::vec2(this->absolute_x, this->absolute_y));
        this->rectangle->SetScale(glm::vec2(this->size_x, this->size_y));
    }

    void Component::Update(float x, float y, bool is_left_click) {
        this->mouse_x = x;
        this->mouse_y = y;

        if (!this->is_clicked && IsMouseClicked(x, y, is_left_click)) {
            this->is_clicked = true;
            HandleEvent(EventType::MOUSE_CLICK);
        } else {
            this->is_clicked = false;
        }

        if (IsMouseReleased(x, y, is_left_click, this->prev_left_click)) {
            HandleEvent(EventType::MOUSE_RELEASE);
        }

        if (!this->is_hovered && IsMouseHovered(x, y)) {
            this->is_hovered = true;
            HandleEvent(EventType::MOUSE_HOVER);
        } else {
            this->is_hovered = false;
        }

        if (IsMouseExited(x, y, this->prev_mouse_x, this->prev_mouse_y)) {
            HandleEvent(EventType::MOUSE_HOVER_EXIT);
        }

        /* Update all children of this component */
        for (auto child : this->children) {
            child->Update(x, y, is_left_click);
        }

        this->prev_mouse_x = x;
        this->prev_mouse_y = y;
    }

    void Component::Render(Shader& shader) {

        this->rectangle->Draw(shader);

        if (this->is_visible) {
            for (auto child : this->children) {
                child->Render(shader);
            }
        }
    }

    void Component::HandleEvent(Component::EventType event) {
        switch (event) {
            case Component::EventType::MOUSE_CLICK:
                OnMouseClick();
                break;
            case Component::EventType::MOUSE_RELEASE:
                OnMouseRelease();
                break;
            case Component::EventType::MOUSE_HOVER:
                OnMouseHover();
                break;
            case Component::EventType::MOUSE_HOVER_EXIT:
                OnMouseHoverExit();
                break;
            case Component::EventType::NO_EVENT:
                break;
        }
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
        parent->RemoveChild(child);
        
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

    void Component::SetParent(std::shared_ptr<Component> parent) {
        /* Make sure the parent is not the same component as the cild */
        if (parent.get() == this) {
            throw std::invalid_argument("Parent cannot be the same as the child.");
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
        if (parent != nullptr) {
            this->relative_x = x - parent->GetAbsoluteX();
            this->relative_y = y - parent->GetAbsoluteY();
        } else {
            this->relative_x = x;
            this->relative_y = y;
        }
    }

    void Component::SetRelativePosition(float x, float y) {
        this->relative_x = x;
        this->relative_y = y;
        if (parent != nullptr) {
            this->absolute_x = parent->GetAbsoluteX() + x;
            this->absolute_y = parent->GetAbsoluteY() + y;
        } else {
            this->absolute_x = x;
            this->absolute_y = y;
        }
    }

    bool Component::IsMouseClicked(float x, float y, bool is_left_click) {
        if (is_left_click && IsPointInside(x, y)) {
            return true;
        }
        return false;
    }

    bool Component::IsMouseReleased(float x, float y, bool is_left_click, bool prev_left_click) {
        if (prev_left_click && !is_left_click && IsPointInside(x, y)) {
            return true;
        }
        return false; 
    }

    bool Component::IsMouseHovered(float x, float y) {
        if (IsPointInside(x, y)) {
            return true;
        }
        return false;
    }

    bool Component::IsMouseExited(float x, float y, float prev_x, float prev_y) {
        if (IsPointInside(prev_x, prev_y) && !IsPointInside(x, y)) {
            return true;
        }
        return false;
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
