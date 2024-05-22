#include "../../../Including/Gensin/Player/PlayerAttackState.h"
#include "../../../Including/Gensin/Player/Player.h"

void PlayerAttackState::Enter()
{
	__super::Enter();
	// �������Ե����� ����zero�ٶ�
	// ��ȥ֮��ֱ�ӷ���һ���ӵ� Ȼ�󷢵���������λ����ȥ
	// Ҳ���ǵ�ǰ��һ�˳ƶ�Ӧ��Front����
	Camera* camera = player->cinemachine->virtualCameras[1].camera;
	// ��һ����Ч ����
	delayTimer = delayTime;
	std::cout << "Attack" << std::endl;
	player->fireBullet(10);
	// Ȼ���������Ҫ��cd�����ҵ��к�ҡ���ö�������
}

void PlayerAttackState::Update(GLFWwindow* window)
{
	// �������
	// ����wasd���߷���� �ͱ�ʾ�ƶ���
	__super::Update(window);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		stateMachine->ChangeState(player->jumpState);
	}

	// ���ƶ�
	if (this->getMoveDirection(window) != MoveDirection::NONE)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // û���ƶ�
	else
	{
		player->isMoving = false;
		stateMachine->ChangeState(player->idleState);
	}
}


void PlayerAttackState::Update(GLFWwindow* window, float deltaTime)
{
	// ���
	// ��ҡ
	delayTimer -= deltaTime;
	std::cout << "���ں�ҡ" << std::endl;
	if (delayTimer >= 0) return;

	attackCDTimer -= deltaTime;
	std::cout << "����CD" << std::endl;
	if (attackCDTimer < 0 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		attackCDTimer = attackCDTime;
		stateMachine->ChangeState(player->attackState);
	}
	this->Update(window);
}