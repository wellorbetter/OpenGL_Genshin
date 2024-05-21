#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Player;
class PlayerStateMachine;

class PlayerState {
public:
	virtual void Enter();
	virtual void Exit();

	// 一般在某个状态的时候检查输入 切换状态
	virtual void Update(GLFWwindow* window) = 0;
protected:
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