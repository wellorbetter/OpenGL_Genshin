#pragma once
#ifndef GROUND_H
#define GROUND_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

class Ground
{
public:
    Ground(const char* texturePath);
    ~Ground();

    void Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;

    void loadTexture(const char* texturePath);
    void setupGround();
};

#endif
