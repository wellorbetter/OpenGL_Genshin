#pragma once

#include "EnemyState.h"

class EnemyStateMachine {
public:
	EnemyState* currentState;

	// 第一次进入的时候触发
	void InitialState(EnemyState* state);
	void ChangeState(EnemyState* state);
};