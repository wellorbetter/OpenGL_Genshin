#pragma once

#include "PlayerState.h"

class PlayerIdelState:PlayerState {
public:
	void Enter() override;
	void Exit() override;

private:
};