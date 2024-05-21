#pragma once
#include "PlayerState.h"

class PlayerJumpState:public PlayerState
{
public:
	// 上升时间、下降时间
	float upTime = 0.5, downTime = 0.5;
	float upTimer, downTimer;
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime) override;
	PlayerJumpState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName) :PlayerState(_player, _stateMachine, _stateName) 
	{
		upTimer = upTime;
		downTimer = downTime;
	}
};