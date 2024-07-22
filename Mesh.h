#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Shader.h"
#include "Libs/glm/glm.hpp"
#include "Libs/glm/gtc/matrix_transform.hpp"
#include "Libs/glm/gtc/type_ptr.hpp"

namespace Crystal {

    class Mesh {
    public: 
        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void SetPosition(const glm::vec2& position);
        void SetScale(const glm::vec2& scale);
        void SetRotation(float angle);
        void SetColor(float r, float g, float b, float a);
        glm::vec2 GetPosition();
        glm::vec2 GetScale();
        float GetRotation();
        void UpdateTransforms();
        void Draw(Shader& shader);

    private:
        unsigned int VAO, VBO, EBO;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        /* This variable indicates if the transforms need to be recalculated. */
        bool transform_updated;
        /* Transforms */
        glm::mat4 model;
        glm::vec4 color;
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
    };

}
#endif