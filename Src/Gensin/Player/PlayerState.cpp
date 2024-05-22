#include "../../../Including/Gensin/Player/PlayerState.h"
#include "../../../Including/Gensin/Player/Player.h"

PlayerState::PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName)
{
	player = _player;
	stateMachine = _stateMachine;
	stateName = _stateName;
	attackCDTimer = attackCDTime;
}

void PlayerState::Update(GLFWwindow* window)
{
	
}

void PlayerState::Update(GLFWwindow* window, float deltaTime)
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
MoveDirection PlayerState::getMoveDirection(GLFWwindow* window)
{
	MoveDirection moveDirection = MoveDirection::NONE;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		moveDirection = MoveDirection::FRONT;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		moveDirection = MoveDirection::BACK;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		moveDirection = MoveDirection::LEFT;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		moveDirection = MoveDirection::RIGHT;
	}
	return moveDirection;

}