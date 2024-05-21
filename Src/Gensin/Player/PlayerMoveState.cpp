#include "../../../Including/Gensin/Player/PlayerMoveState.h"
#include "../../../Including/Gensin/Player/Player.h"

PlayerMoveState::PlayerMoveState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName) 
	:PlayerState(_player, _stateMachine, _stateName)
{
	frontState = new PlayerFrontMoveState(_player, _stateMachine, this, "Front");
	backState = new PlayerBackMoveState(_player, _stateMachine, this, "Back");
	leftState = new PlayerLeftMoveState(_player, _stateMachine, this, "Left");
	rightState = new PlayerRightMoveState(_player, _stateMachine, this, "Right");

}
void PlayerMoveState::Enter()
{
	player->setAnimation("Front", true);
}

void PlayerMoveState::Update(GLFWwindow* window)
{
	// 在移动
	MoveDirection moveDirection = this->getMoveDirection(window);
	if (moveDirection != MoveDirection::NONE)
	{
		player->isMoving = true;
		player->stateMachine->ChangeState(this->frontState);
	} // 没有移动
	else
	{
		player->isMoving = false;
		stateMachine->ChangeState(player->idleState);
	}
}

void moveUpdate(PlayerState* nowState,PlayerMoveState* state, GLFWwindow* window)
{
	MoveDirection moveDirection = state->getMoveDirection(window);
	if (moveDirection != MoveDirection::NONE)
	{
		state->player->isMoving = true;
		switch (moveDirection)
		{
			// 不会从自己到自己
		case MoveDirection::FRONT:
			if (nowState->stateName != "Front")
				state->stateMachine->ChangeState(state->frontState);
			break;
		case MoveDirection::BACK:
			if (nowState->stateName != "Back")
				state->stateMachine->ChangeState(state->backState);
			break;
		case MoveDirection::LEFT:
			if (nowState->stateName != "Left")
				state->stateMachine->ChangeState(state->leftState);
			break;
		case MoveDirection::RIGHT:
			if (nowState->stateName != "Right")
				state->stateMachine->ChangeState(state->rightState);
			break;
		}
	} // 没有移动
	else
	{
		state->player->isMoving = false;
		state->stateMachine->ChangeState(state->player->idleState);

	}
}