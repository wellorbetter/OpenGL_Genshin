#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gl/GL.h>

class GameObject {
public:
	virtual void Update(GLFWwindow* window) = 0;
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Destroy() = 0;
};

// AABB碰撞器 左下角和右上角
class Collider {
public:
	glm::vec3 leftDown, rightUp, colliderCenter;
	float boxLength = 1;
	bool collisionCheck(Collider* other);
	//virtual void collisionOnTrigger(Collider* other) = 0;
	Collider() {
		this->colliderCenter = glm::vec3(0, 0, 0);
		this->leftDown = glm::vec3(-boxLength / 2, -boxLength / 2, -boxLength / 2);
		this->rightUp = glm::vec3(boxLength / 2, boxLength / 2, boxLength / 2);
	}
    void UpdateCollider(glm::vec3 center) {
        this->colliderCenter = center;
        this->leftDown = glm::vec3(center.x - boxLength / 2, center.y - boxLength / 2, center.z - boxLength / 2);
        this->rightUp = glm::vec3(center.x + boxLength / 2, center.y + boxLength / 2, center.z + boxLength / 2);
    }
	void RenderCollider() {
		// 用左下、右上和边长，完全可以确定一个立方体
        // 顶点坐标
        glm::vec3 vertices[] = {
            glm::vec3(leftDown.x, leftDown.y, leftDown.z),
            glm::vec3(rightUp.x, leftDown.y, leftDown.z),
            glm::vec3(rightUp.x, rightUp.y, leftDown.z),
            glm::vec3(leftDown.x, rightUp.y, leftDown.z),

            glm::vec3(leftDown.x, leftDown.y, rightUp.z),
            glm::vec3(rightUp.x, leftDown.y, rightUp.z),
            glm::vec3(rightUp.x, rightUp.y, rightUp.z),
            glm::vec3(leftDown.x, rightUp.y, rightUp.z)
        };

        // 线框索引
        unsigned int indices[] = {
            0, 1, 1, 2, 2, 3, 3, 0,   // 底面
            4, 5, 5, 6, 6, 7, 7, 4,   // 顶面
            0, 4, 1, 5, 2, 6, 3, 7    // 垂直线框
        };

        // 创建顶点缓冲对象 (VBO) 和顶点数组对象 (VAO)
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // 设置顶点位置属性
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 绘制线框
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_LINES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
};