#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

#include "Shapes.h"

/* 
Every UI element is a component. Components can have children and parent components.
*/

namespace Crystal {

    class Component {
    public:
        Component(Component* parent, float size_x, float size_y, float position_x, float position_y, bool relative = true);
        ~Component();

        void AddChild(Component* child);
        void RemoveChild(Component* child);

        void SetParent(Component* parent);
        Component* GetParent();

        std::vector<Component*> GetChildren();

        void SetSize(float x, float y);
        void SetAbsolutePosition(float x, float y);
        void SetRelativePosition(float x, float y);

        float GetAbsoluteX();
        float GetAbsoluteY();
        float GetRelativeX();
        float GetRelativeY();
        float GetSizeX();
        float GetSizeY();

        virtual void Update() = 0;
        virtual void Render() = 0;

    private:
        Component* parent;
        Mesh* mesh;

        std::vector<Component*> children;

        /* 
        Position of the component. Absoulte psoition is relative to upper left side of the window
        relative position is relative to the parent component.
        */
        float absolute_x, absolute_y;
        float relative_x, relative_y;

        float size_x, size_y;
    };

}

#endif