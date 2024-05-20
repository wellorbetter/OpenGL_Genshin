#include "../../../Including/Gensin/Player/PlayerState.h"

PlayerState::PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName)
{
	player = _player;
	stateMachine = _stateMachine;
	stateName = _stateName;
}