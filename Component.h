#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <memory>

#include "Shader.h"
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
            MOUSE_HOVER_EXIT,
            NO_EVENT
        };

        Component(std::shared_ptr<Component> parent, float size_x, float size_y, float position_x, float position_y, bool relative);
        virtual ~Component() = default;

        /* Don't allow copies from this class for now */
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
        
        void HandleEvent(EventType event);
        bool IsPointInside(float x, float y);
        void RemoveChild(std::shared_ptr<Component> child);
        void SetParent(std::shared_ptr<Component> parent);
        std::weak_ptr<Component> GetParent();
        std::vector<std::shared_ptr<Component>> GetChildren();
        void SetSize(float x, float y);
        void SetAbsolutePosition(float x, float y);
        void SetRelativePosition(float x, float y);
        void SetVisibility(bool is_visible);
        void SetColor(float r, float g, float b, float a);
        float GetAbsoluteX();
        float GetAbsoluteY();
        float GetRelativeX();
        float GetRelativeY();
        float GetSizeX();
        float GetSizeY();
        virtual void Update(float x, float y, bool is_left_click);
        virtual void Render(Shader& shader);

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

        bool IsMouseClicked(float x, float y, bool is_left_click);
        bool IsMouseReleased(float x, float y, bool is_left_click, bool prev_left_click);
        bool IsMouseHovered(float x, float y);
        bool IsMouseExited(float x, float y, float prev_x, float prev_y);

    private:
        static int next_id;
        unsigned int id;
        std::shared_ptr<Component> parent;
        std::unique_ptr<Rectangle> rectangle;
        std::vector<std::shared_ptr<Component>> children;
        
        float absolute_x, absolute_y;
        float relative_x, relative_y;
        float size_x, size_y;
        bool is_visible;
        float mouse_x, mouse_y, prev_mouse_x, prev_mouse_y, prev_left_click;
        bool is_hovered, is_clicked;
    };

}

#endif