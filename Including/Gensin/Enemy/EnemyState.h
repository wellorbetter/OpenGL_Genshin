#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Enemy;
class EnemyStateMachine;

class EnemyState {
public:
	float Timer; // 计时器 本来Player应该也要怎么写，但是写都写了，懒得改了
	virtual void Enter();
	virtual void Exit();

	virtual void Update(GLFWwindow* window, float deltaTime) = 0;
	std::string stateName;
	Enemy* enemy;
	EnemyStateMachine* stateMachine;

	EnemyState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName);
};