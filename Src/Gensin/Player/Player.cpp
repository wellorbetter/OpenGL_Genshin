#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Enemy/EnemyManager.h"

std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// ��ʼ������ setAnimֱ����
	// ����ĳЩ״̬ ���ض���
	modelPath = "Animation/Babala/";
	this->collider = new Collider();
	this->stateMachine = new PlayerStateMachine();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->moveState = new PlayerMoveState(this, this->stateMachine, "Move");
	this->jumpState = new PlayerJumpState(this, this->stateMachine, "Jump");
	this->attackState = new PlayerAttackState(this, this->stateMachine, "Attack");
}

void Player::Start()
{
	this->position = glm::vec3(0.0, 0.0, 1.0f);
	// ��ʼ����״̬��Ⱦ
	this->stateMachine->InitialState(this->idleState);
	// �趨�ƶ��ٶ�
	glm::vec3 speed = glm::vec3(2.0f, 2.0f, 2.0f);
	this->setSpeed(speed);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	// �˳���Ϸ

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Player::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);
	this->cinemachine->switchTimer -= deltaTime;
	// ������ƶ� ֻ���ϵ��ӽǿ����ƶ�

	// ����������ģ���Ϊÿ�ε�update�ǳ��ǳ��̣������deltaTime��һ����С����
	// ���Կ����Ұ�����c������update�Ѿ�ִ���˺ü�����
	// �����л������Ҫһ������ʱ�� ����1��

	// �л����
	if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) && this->cinemachine->switchTimer < 0)
	{
		cinemachine->SwitchCamera();
		this->cinemachine->switchTimer = this->cinemachine->switchTime;
	}
	// ������ϵ��ӽǽ�ɫ��׼��
	if (this->cinemachine->activeCameraIndex == 2)
	{
		stateMachine->ChangeState(this->idleState);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(RIGHT, deltaTime);
		// ͬʱ��׼���и���
		//printf("%lf %lf %lf\n", this->getDirection().x, this->getDirection().y, this->getDirection().z);
		return;
	}

	// ״̬�ĸ���
	stateMachine->currentState->Update(window, deltaTime);
	
	this->collider->UpdateCollider(this->position);
	//this->collider->RenderCollider();
}

Player::Player(Cinemachine* _cinemachine):Entity()
{
	this->cinemachine = _cinemachine;
	// �õ�����ĵ�һ�˳Ƶ�λ�� �Լ����� ͬʱ�޸�����ײ���λ��

	// ���λ����Ҫ����һ����ƫ��������Ϊ�������λ�ú�ʵ�ʵ�λ�ò�һ�����Ҽ���һ��backOffset
	/*glm::vec3 newPositon = this->cinemachine->virtualCameras[1].camera->Position - this->cinemachine->virtualCameras[1].backOffset;
	this->setPosition(newPositon);*/
	this->setDirection(this->cinemachine->virtualCameras[1].camera->Front);
}

void Player::Damage()
{
	__super::Damage();
	// ���˾���һ��������Ч��Ȼ��׹�������
	// �׹����model�Ĳ��ʱ�ɰ�ɫ��Ȼ���ٱ����
	// ���������̫�øģ����ˣ��͸����Ч֮��
}


// �����ӵ�
void Player::fireBullet(float len)
{
	// ������player������
	glm::vec3 direction = this->cinemachine->virtualCameras[1].camera->Front;
	direction.y = 0;
	bullets.push_back(new Bullet(this, this->getPosition(), direction, 1.5f));
}

// �����ӵ�λ��
void Player::updateBullets(float deltaTime)
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		// ����deltatime���ٶ��������ӵ�λ��
		(*it)->Update(deltaTime);

		// ����ӵ��Ƿ񳬳������룬ɾ���ӵ�
		if (glm::length((*it)->getPosition() - this->getPosition()) > maxBulletDistance)
		{
			delete* it;
			it = bullets.erase(it);
		}
		else
		{// �����ײ
			bool isCollision = false;
			for (Enemy* enemy : EnemyManager::getInstance().getEnemies())
			{
				if (!enemy || !enemy->isAlive || !enemy->collider) continue;
				if ((*it)->collider->collisionCheck(enemy->collider))
				{
					enemy->Damage(); // �Ե�������˺�
					// ��̫��c++ ָ��destroyдһ��bug �ܲ�����
					// �ÿ�д��Main������
					delete* it;
					*it = nullptr;
					isCollision = true;
					it = bullets.erase(it);
					break;
				}
			}
			if (isCollision) continue;
			++it;
		}
	}
}