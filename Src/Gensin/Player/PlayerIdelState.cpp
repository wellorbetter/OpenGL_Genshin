#include "../../../Including/Gensin/Player/PlayerIdleState.h"

void PlayerIdelState::Enter()
{
	player->setAnimation("Idle", true);
}

void PlayerIdelState::Exit()
{

}