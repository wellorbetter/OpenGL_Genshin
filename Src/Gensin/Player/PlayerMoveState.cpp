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
	
}


void PlayerMoveState::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);
	
	moveUpdate(this, this, window, deltaTime);
}

void changeDir(Player* player, MoveDirection moveDirection)
{
	glm::vec3 newDirection;
	switch (moveDirection)
	{
	case MoveDirection::FRONT:
		newDirection = (glm::vec3(0, 0, -1));
		break;
	case MoveDirection::BACK:
		newDirection = (glm::vec3(0, 0, 1));
		break;
	case MoveDirection::LEFT:
		newDirection = (glm::vec3(-1, 0, 0));
		break;
	case MoveDirection::RIGHT:
		newDirection = (glm::vec3(1, 0, 0));
		break;
	}
	player->setDirection(newDirection);
}

void moveUpdate(PlayerState* nowState,PlayerMoveState* state, GLFWwindow* window, float deltaTime)
{
	// 先看看可以不用进跳跃
	// 因为后面必然会进入某一个状态，要么移动要么idle
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		nowState->stateMachine->ChangeState(nowState->player->jumpState);
	}
	MoveDirection moveDirection = state->getMoveDirection(window);
	if (moveDirection != MoveDirection::NONE)
	{
		// 移动只能在地上移动，所以这个时候速度只能是xy平面的
		// 很好，搞错了，原来这个z轴是面朝我的
		// y轴是上下的  x轴是左右的
		// 走路的平面是xz平面
		state->player->isMoving = true;

		// 修改朝向 因为根据第一人称的朝向来修改的话，其他视角就会有bug
		changeDir(state->player, moveDirection);
		glm::vec3 newVelocity = state->player->getDirection() * state->player->getSpeed();
		state->player->setVelocity(newVelocity, "2D");

		printf("%lf %lf %lf\n", state->player->getPosition().x, state->player->getPosition().y, state->player->getPosition().z);
		
		// 位置的更新 这里不用 * this->getDirection() 因为速度包括了方向，之前乘过了
		glm::vec3 newPosition = deltaTime * state->player->getVelocity() + state->player->getPosition();
		state->player->setPosition(newPosition);

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