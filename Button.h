#ifndef BUTTON_H
#define BUTTON_H

#include <memory>

#include "Component.h"

namespace Crystal {

    class Button : public Component {
    public:
        Button(std::shared_ptr<Component> parent, float siye_x, float siye_y, float position_x, float position_y, bool relative);
        ~Button();
        
        void OnMouseClick() override;
        void OnMouseRelease() override;
        void OnMouseHover() override;
        void OnMouseHoverExit() override;

    private:
    };

}

#endif