#pragma once
#include "PlayerState.h"

class PlayerAttackState : public PlayerState
{
public:
	float delayTime = 1.5f, delayTimer;
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime) override;
	void Enter() override;
	PlayerAttackState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName) :PlayerState(_player, _stateMachine, _stateName) 
	{
		attackCDTimer = attackCDTime;
		delayTimer = delayTime;
	}
};