#pragma once

#include <string>
#include "Player.h"
#include "PlayerStateMachine.h"

class PlayerState {
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
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
	PlayerState(Player* _player, PlayerStateMachine* _stateMachine, string _stateName);
};