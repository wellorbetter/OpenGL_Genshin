#pragma once

#include "PlayerState.h"

class PlayerStateMachine {
public:
	PlayerState* currentState;

	// ��һ�ν����ʱ�򴥷�
	void InitialState(PlayerState* state);
	void ChangeState(PlayerState* state);
};