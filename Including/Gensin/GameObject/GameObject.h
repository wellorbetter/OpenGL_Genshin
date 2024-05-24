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
};

// AABB��ײ�� ���½Ǻ����Ͻ�
class Collider {
public:
	glm::vec3 leftDown, rightUp, colliderCenter;
	float boxLength = 0.25;
	bool collisionCheck(Collider* other);
	Collider() {}
    void UpdateCollider(glm::vec3 center) {
        this->colliderCenter = center;
		// ����̫���ˣ�����һ�¸߶�
        this->leftDown = glm::vec3(center.x - boxLength / 2, center.y - boxLength / 2, center.z - boxLength / 2);
        this->rightUp = glm::vec3(center.x + boxLength / 2, center.y + boxLength / 2, center.z + boxLength / 2);
    }
	void RenderUnitCube(const glm::vec3& center) {
		float halfSize = boxLength / 2;
		glm::vec3 vertices[] = {
			// ǰ��
			center + glm::vec3(-halfSize, -halfSize,  halfSize),
			center + glm::vec3(halfSize, -halfSize,  halfSize),
			center + glm::vec3(halfSize,  halfSize,  halfSize),
			center + glm::vec3(-halfSize,  halfSize,  halfSize),

			// ����
			center + glm::vec3(-halfSize, -halfSize, -halfSize),
			center + glm::vec3(halfSize, -halfSize, -halfSize),
			center + glm::vec3(halfSize,  halfSize, -halfSize),
			center + glm::vec3(-halfSize,  halfSize, -halfSize)
		};

		unsigned int indices[] = {
			// ǰ��
			0, 1, 2, 2, 3, 0,
			// ����
			4, 5, 6, 6, 7, 4,
			// ����
			0, 3, 7, 7, 4, 0,
			// ����
			1, 5, 6, 6, 2, 1,
			// ����
			3, 2, 6, 6, 7, 3,
			// ����
			0, 1, 5, 5, 4, 0
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// Clean up
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void RenderCollider() {
		RenderUnitCube(this->colliderCenter);
	}


};