#pragma once

#include "EnemyState.h"

class EnemyStateMachine {
public:
	EnemyState* currentState;

	// ��һ�ν����ʱ�򴥷�
	void InitialState(EnemyState* state);
	void ChangeState(EnemyState* state);
};