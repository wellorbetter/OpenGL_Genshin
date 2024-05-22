#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Player;
class PlayerStateMachine;

enum class MoveDirection
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	NONE
};

class PlayerState {
public:
	MoveDirection getMoveDirection(GLFWwindow* window);
	float attackCDTimer, attackCDTime = 0.5;
	virtual void Enter();
	virtual void Exit();

	// 一般在某个状态的时候检查输入 切换状态
	virtual void Update(GLFWwindow* window) = 0;
	// 本来没这么复杂，主要是写玩了发现忘了带参数deltaTime，懒得改了
	// 就多写了另一个函数调用原来这个
	virtual void Update(GLFWwindow* window, float deltaTime) = 0;
	// 状态名 
	// 可以在Animation\babala\stateName
	// 下面找到对应的模型文件
	std::string stateName;

	// 状态保持的player
	Player* player;

	// 对应的状态机 这里虽然可以用player访问，但是为了减少前缀，还是加上
	PlayerStateMachine* stateMachine;

	// 初始化构造函数
	PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName);
};