#pragma once

#include "EnemyState.h"

class EnemyIdleState :public EnemyState {
public:
	float IdleTime = 1.5f;
	void Update(GLFWwindow* window, float deltaTime) override;
	void Enter() override;
	EnemyIdleState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName) :EnemyState(_enemy, _stateMachine, _stateName) 
	{
		Timer = IdleTime;
	}

private:
};