#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <memory>

#include "Shapes.h"

/* 
Every UI element is a component. Components can have children and parent components.
*/

namespace Crystal {

    class Component : public std::enable_shared_from_this<Component> {
    public:
        /* Event handler */
        enum class EventType {
            MOUSE_CLICK,
            MOUSE_RELEASE,
            MOUSE_HOVER,
            MOUSE_HOVER_EXIT
        };

        Component(std::weak_ptr<Component> parent, float size_x, float size_y, float position_x, float position_y, bool relative = true);
        virtual ~Component() = default;
        
        void EventHandler(EventType event, float x, float y);
        bool IsPointInside(float x, float y);
        void RemoveChild(std::shared_ptr<Component> child);
        void SetParent(std::weak_ptr<Component> parent);
        std::weak_ptr<Component> GetParent();
        std::vector<std::shared_ptr<Component>> GetChildren();
        void SetSize(float x, float y);
        void SetAbsolutePosition(float x, float y);
        void SetRelativePosition(float x, float y);
        void SetVisibility(bool is_visible);
        float GetAbsoluteX();
        float GetAbsoluteY();
        float GetRelativeX();
        float GetRelativeY();
        float GetSizeX();
        float GetSizeY();
        virtual void Update() = 0;
        virtual void Render() = 0;

        /* Template functions */
        template<typename T, typename... Args>
        std::weak_ptr<T> AddChild(Args&&... args);

        /* Add an already existing child component */
        template<typename T>
        std::weak_ptr<T> AddChild(std::shared_ptr<T> child);

        /* Events */
        virtual void OnMouseClick() = 0;
        virtual void OnMouseRelease() = 0;
        virtual void OnMouseHover() = 0;
        virtual void OnMouseHoverExit() = 0;

    private:
        static int next_id;
        unsigned int id;
        std::weak_ptr<Component> parent;
        std::unique_ptr<Mesh> mesh;
        std::vector<std::shared_ptr<Component>> children;
        
        float absolute_x, absolute_y;
        float relative_x, relative_y;
        float size_x, size_y;
        bool is_visible;
    };

}

#endif