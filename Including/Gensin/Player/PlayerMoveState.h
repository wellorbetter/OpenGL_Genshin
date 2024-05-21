#pragma once
#include "PlayerState.h"
class PlayerMoveState: public PlayerState
{
public:
	void Update(GLFWwindow* window) override;
	PlayerMoveState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName) :PlayerState(_player, _stateMachine, _stateName) {}
};