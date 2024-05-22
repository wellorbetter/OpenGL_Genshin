#pragma once
#include "EnemyState.h"

class EnemyMoveState:public EnemyState
{
	// 这里相对于PlayerMoveState就简单多了，只有一个移动状态
	// 直挺挺的走向Player即可
public:
	void Update(GLFWwindow* window, float deltaTime) override;
	EnemyMoveState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName)
		:EnemyState(_enemy, _stateMachine, _stateName)
	{
	}
};