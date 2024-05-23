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

// AABB��ײ�� ���½Ǻ����Ͻ�
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
		// �����¡����Ϻͱ߳�����ȫ����ȷ��һ��������
        // ��������
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

        // �߿�����
        unsigned int indices[] = {
            0, 1, 1, 2, 2, 3, 3, 0,   // ����
            4, 5, 5, 6, 6, 7, 7, 4,   // ����
            0, 4, 1, 5, 2, 6, 3, 7    // ��ֱ�߿�
        };

        // �������㻺����� (VBO) �Ͷ���������� (VAO)
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // ���ö���λ������
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // �����߿�
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_LINES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
};