#include "../../../Including/Gensin/Enemy/EnemyStateMachine.h"

void EnemyStateMachine::InitialState(EnemyState* _newState)
{
	currentState = _newState;
	currentState->Enter();
}

void EnemyStateMachine::ChangeState(EnemyState* _newState)
{
	currentState->Exit();
	currentState = _newState;
	currentState->Enter();
}
