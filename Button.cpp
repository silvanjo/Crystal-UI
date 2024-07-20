#include "Button.h"

#include <iostream>

namespace Crystal {

    Button::Button(std::shared_ptr<Component> parent, float siye_x, float siye_y, float position_x, float position_y, bool relative = true) 
        : Component(parent, siye_x, siye_y, position_x, position_y, relative) {

    }

    Button::~Button() {
    }

    void Button::OnMouseClick() {
        std::cout << "Button clicked" << std::endl;
    }

    void Button::OnMouseRelease() {
        std::cout << "Button released" << std::endl;
    }

    void Button::OnMouseHover() {
        std::cout << "Button hovered" << std::endl;
    }

    void Button::OnMouseHoverExit() {
        std::cout << "Button hover exit" << std::endl;
    }

}