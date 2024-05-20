#include "../../../Including/Gensin/Player/PlayerStateMachine.h"

void PlayerStateMachine::InitialState(PlayerState* _newState)
{
	currentState = _newState;
	currentState->Enter();
}

void PlayerStateMachine::ChangeState(PlayerState* _newState)
{
	currentState->Exit();
	currentState = _newState;
	currentState->Enter();
}
