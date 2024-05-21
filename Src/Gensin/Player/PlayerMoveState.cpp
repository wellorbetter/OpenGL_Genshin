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
	// �ȿ������Բ��ý���Ծ
	// ��Ϊ�����Ȼ�����ĳһ��״̬��Ҫô�ƶ�Ҫôidle
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		nowState->stateMachine->ChangeState(nowState->player->jumpState);
	}
	MoveDirection moveDirection = state->getMoveDirection(window);
	if (moveDirection != MoveDirection::NONE)
	{
		// �ƶ�ֻ���ڵ����ƶ����������ʱ���ٶ�ֻ����xyƽ���
		// �ܺã�����ˣ�ԭ�����z�����泯�ҵ�
		// y�������µ�  x�������ҵ�
		// ��·��ƽ����xzƽ��
		state->player->isMoving = true;

		// �޸ĳ��� ��Ϊ���ݵ�һ�˳Ƶĳ������޸ĵĻ��������ӽǾͻ���bug
		changeDir(state->player, moveDirection);
		glm::vec3 newVelocity = state->player->getDirection() * state->player->getSpeed();
		state->player->setVelocity(newVelocity, "2D");

		printf("%lf %lf %lf\n", state->player->getPosition().x, state->player->getPosition().y, state->player->getPosition().z);
		
		// λ�õĸ��� ���ﲻ�� * this->getDirection() ��Ϊ�ٶȰ����˷���֮ǰ�˹���
		glm::vec3 newPosition = deltaTime * state->player->getVelocity() + state->player->getPosition();
		state->player->setPosition(newPosition);

		switch (moveDirection)
		{
			// ������Լ����Լ�
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
	} // û���ƶ�
	else
	{
		state->player->isMoving = false;
		state->stateMachine->ChangeState(state->player->idleState);

	}
}