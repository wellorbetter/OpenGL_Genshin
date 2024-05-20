#pragma once

#include "PlayerState.h"

class PlayerStateMachine {
public:
	PlayerState* currentState;

	// 第一次进入的时候触发
	void InitialState(PlayerState* state);
	void ChangeState(PlayerState* state);
};