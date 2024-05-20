#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"

void PlayerIdelState::Enter()
{
	player->setAnimation("Idle", true);
}

void PlayerIdelState::Exit()
{
	player->setAnimation("Idle", false);
}