#ifndef MESH_H
#define MESH_H

#include <vector>

namespace Crystal {

    class Mesh {
    public: 
        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void Draw();

    private:
        unsigned int VAO, VBO, EBO;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

}
#endif