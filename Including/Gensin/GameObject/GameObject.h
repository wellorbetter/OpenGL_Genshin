#pragma once
#include <GLFW/glfw3.h>
class GameObject {
public:
	virtual void Update(GLFWwindow* window) = 0;
	virtual void Awake() = 0;
	virtual void Start() = 0;

	virtual void Destroy() = 0;
};
