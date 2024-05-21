#include "../../../Including/Gensin/Player/PlayerState.h"
#include "../../../Including/Gensin/Player/Player.h"

PlayerState::PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName)
{
	player = _player;
	stateMachine = _stateMachine;
	stateName = _stateName;
}

void PlayerState::Update(GLFWwindow* window)
{
	
}
void PlayerState::Enter()
{
	player->setAnimation(this->stateName, true);
}

void PlayerState::Exit()
{
	player->setAnimation(this->stateName, false);
}
