#pragma once
#include "PlayerState.h"

class PlayerJumpState:public PlayerState
{
public:
	// ����ʱ�䡢�½�ʱ��
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