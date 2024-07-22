#include "Mesh.h"

#include <GL/glew.h>

namespace Crystal {

    Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
        this->vertices = vertices;
        this->indices = indices;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        this->transform_updated = true;
        this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        this->position = glm::vec2(0.0f, 0.0f);
        this->scale = glm::vec2(1.0f, 1.0f);
        this->rotation = 0.0f;
        this->model = glm::mat4(1.0f);
    }

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Mesh::Draw(Shader& shader) {

        if (transform_updated) {
            UpdateTransforms();
        }

        /* Set model matrix in vertex shader */
        shader.SetMatrix4("model", this->model);
        shader.SetVector4("color", this->color);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::UpdateTransforms() {
        this->model = glm::mat4(1.0f);
        this->model = glm::translate(this->model, glm::vec3(this->position, 0.0f));
        this->model = glm::rotate(this->model, glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        this->model = glm::scale(this->model, glm::vec3(this->scale, 1.0f));
        this->transform_updated = false;
    }

    void Mesh::SetPosition(const glm::vec2& position) {
        this->transform_updated = true;
        this->position = position;
    }

    void Mesh::SetScale(const glm::vec2& scale) {
        this->transform_updated = true;
        this->scale = scale;
    }

    void Mesh::SetRotation(float angle) {
        this->transform_updated = true;
        this->rotation = angle;
    }

    void Mesh::SetColor(float r, float g, float b, float a = 1) {
        this->color = glm::vec4(r, g, b, a);
    }

    glm::vec2 Mesh::GetPosition() {
        return this->position;
    }

    glm::vec2 Mesh::GetScale() {
        return this->scale;
    }

    float Mesh::GetRotation() {
        return this->rotation;
    }

}