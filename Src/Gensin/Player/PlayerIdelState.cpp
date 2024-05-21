#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"




void PlayerIdleState::Update(GLFWwindow* window)
{
	// 检查输入
	// 按下wasd或者方向键 就表示移动了
	__super::Update(window);

	// 在移动
	if (this->getMoveDirection(window) != MoveDirection::NONE)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // 没有移动
	else
	{
		player->isMoving = false;
	}
}