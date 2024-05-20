#pragma once

#include "PlayerState.h"

class PlayerIdelState:public PlayerState {
public:
	void Enter() override;
	void Exit() override;

private:
};