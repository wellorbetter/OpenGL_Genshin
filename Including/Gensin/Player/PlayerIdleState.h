#pragma once

#include "PlayerState.h"

class PlayerIdleState :public PlayerState {
public:
	void Update(GLFWwindow* window) override;
	PlayerIdleState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName) :PlayerState(_player, _stateMachine, _stateName) {}

private:
};