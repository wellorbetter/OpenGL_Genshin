#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
public:
	virtual void Update(GLFWwindow* window) = 0;
	virtual void Awake() = 0;
	virtual void Start() = 0;

	virtual void Destroy() = 0;
};

// AABBÅö×²Æ÷ ×óÏÂ½ÇºÍÓÒÉÏ½Ç
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
};