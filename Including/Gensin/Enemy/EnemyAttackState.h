#pragma once
#include "EnemyState.h"
class EnemyAttackState:public EnemyState
{
public:
	float delayTime = 1.5f, coolDown = 1.0f;
	bool isDelaying = false;
	bool isCoolDown = false;
	void Update(GLFWwindow* window, float deltaTime) override;
	void Enter() override;
	EnemyAttackState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName) :EnemyState(_enemy, _stateMachine, _stateName)
	{
		// 用一个Timer也行 多写点逻辑吧
		Timer = delayTime;
	}
};