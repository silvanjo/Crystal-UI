#include "Component.h"

namespace Crystal {

    Component::Component(Component* parent, float size_x, float size_y, float position_x, float position_y, bool relative) {
        this->parent = parent;

        this->size_x = size_x;
        this->size_y = size_y;

        if (relative) {
            this->relative_x = position_x;
            this->relative_y = position_y;
            this->absolute_x = parent->GetAbsoluteX() + position_x;
            this->absolute_y = parent->GetAbsoluteY() + position_y;
        } else {
            this->absolute_x = position_x;
            this->absolute_y = position_y;
            this->relative_x = position_x - this->parent->GetAbsoluteX();
            this->relative_y = position_y - this->parent->GetAbsoluteY();
            }
    }

    Component::~Component() {
        delete mesh;
    }

    void Component::AddChild(Component* child) {
        this->children.push_back(child);
    }

    void Component::RemoveChild(Component* child) {
        for (int i = 0; i < this->children.size(); i++) {
            if (this->children[i] == child) {
                this->children.erase(this->children.begin() + i);
                break;
            }
        }
    }

    void Component::SetParent(Component* parent) {
            this->parent = parent;
    }

    Component* Component::GetParent() {
            return this->parent;
    }

    std::vector<Component*> Component::GetChildren() {
            return this->children;
    }

    void Component::SetSize(float x, float y) {
        this->size_x = x;
        this->size_y = y;
    }

    void Component::SetAbsolutePosition(float x, float y) {
        this->absolute_x = x;
        this->absolute_y = y;
        this->relative_x = x - this->parent->GetAbsoluteX();
        this->relative_y = y - this->parent->GetAbsoluteY();
    }

    void Component::SetRelativePosition(float x, float y) {
        this->relative_x = x;
        this->relative_y = y;
        this->absolute_x = this->parent->GetAbsoluteX() + x;
        this->absolute_y = this->parent->GetAbsoluteY() + y;
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
