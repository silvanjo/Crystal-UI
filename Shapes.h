#ifndef SHAPES_H
#define SHAPES_H

#include "Mesh.h"

namespace Crystal {

    class Rectangle : public Mesh {
    public:
        Rectangle() : Mesh({
            0.5f,  0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f,
            -0.5f,  0.5f
            }, {
                0, 1, 3,
                1, 2, 3
            }) {}
    };

}

#endif