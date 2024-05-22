#pragma once
#include "EnemyState.h"

class EnemyMoveState:public EnemyState
{
	// ���������PlayerMoveState�ͼ򵥶��ˣ�ֻ��һ���ƶ�״̬
	// ֱͦͦ������Player����
public:
	void Update(GLFWwindow* window, float deltaTime) override;
	EnemyMoveState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName)
		:EnemyState(_enemy, _stateMachine, _stateName)
	{
	}
};