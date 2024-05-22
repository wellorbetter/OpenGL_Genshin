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

void changeDirBasedOnCamera(Player* player, Camera* camera, MoveDirection moveDirection)
{
    glm::vec3 newDirection;
    switch (moveDirection)
    {
    case MoveDirection::FRONT:
        newDirection = camera->Front;
        break;
    case MoveDirection::BACK:
        newDirection = -camera->Front;
        break;
    case MoveDirection::LEFT:
        newDirection = -camera->Right;
        break;
    case MoveDirection::RIGHT:
        newDirection = camera->Right;
        break;
    default:
        newDirection = player->getDirection();
        break;
    }
    newDirection = glm::normalize(glm::vec3(newDirection.x, 0.0f, newDirection.z));
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
        state->player->isMoving = true;

        // 根据相机视角修改玩家朝向
        changeDirBasedOnCamera(state->player, state->player->cinemachine->virtualCameras[1].camera, moveDirection);

        glm::vec3 newVelocity = state->player->getDirection() * state->player->getSpeed();
        state->player->setVelocity(newVelocity, "2D");

        glm::vec3 newPosition = deltaTime * state->player->getVelocity() + state->player->getPosition();
        state->player->setPosition(newPosition);

        // 更新状态
        if (moveDirection == MoveDirection::FRONT && nowState->stateName != "Front")
        {
            state->stateMachine->ChangeState(state->frontState);
        }
        else if (moveDirection == MoveDirection::BACK && nowState->stateName != "Back")
        {
            state->stateMachine->ChangeState(state->backState);
        }
        else if (moveDirection == MoveDirection::LEFT && nowState->stateName != "Left")
        {
            state->stateMachine->ChangeState(state->leftState);
        }
        else if (moveDirection == MoveDirection::RIGHT && nowState->stateName != "Right")
        {
            state->stateMachine->ChangeState(state->rightState);
        }
    }
    else
    {
        state->player->isMoving = false;
        state->stateMachine->ChangeState(state->player->idleState);
    }
}