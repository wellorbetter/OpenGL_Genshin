#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Player/Player.h"

void Enemy::Awake()
{
	modelPath = "Animation/WeirdQiuqiuren/";

    collider = new Collider();
    this->collider->boxLength = 0.1f;
	// ��ʼ��״̬��
	stateMachine = new EnemyStateMachine();
	// ��ʼ��״̬
	idleState = new EnemyIdleState(this, stateMachine, "Idle");
	moveState = new EnemyMoveState(this, stateMachine, "Move");
	attackState = new EnemyAttackState(this, stateMachine, "Attack");
}

void Enemy::Start()
{
	// ��ǰ��λ�õ�Ȼ���ܺ�player�غ�
    // ʹ�����������λ��
	this->position = glm::vec3(rand() % 10, 0.0f, rand() % 10);
    glm::vec3 speed = glm::vec3(1.0f, 1.0f, 1.0f);
    this->setSpeed(speed);
	stateMachine->InitialState(this->idleState);
}

void Enemy::Update(GLFWwindow* window, float deltaTime)
{
    // �����enemy��player�ķ�������
    glm::vec3 directionToPlayer = this->player->getPosition() - this->getPosition();
    directionToPlayer.y = 0; // ������y��

    // ������������Ƿ�Ϊ��
    if (glm::length(directionToPlayer) > 0.0001f) {
        glm::vec3 newDirection = glm::normalize(directionToPlayer);

        // ʹ�����Բ�ֵ��ƽ���������
        float smoothingFactor = 0.1f; // �������ֵ������ƽ���̶�
        glm::vec3 currentDirection = this->getDirection();
        glm::vec3 smoothedDirection = glm::mix(currentDirection, newDirection, smoothingFactor);

        // �ٴι淶���·���
        smoothedDirection = glm::normalize(smoothedDirection);

        // printf("%f %f %f\n", smoothedDirection.x, smoothedDirection.y, smoothedDirection.z);
        this->setDirection(smoothedDirection);
    }
    
    stateMachine->currentState->Update(window, deltaTime);
    this->collider->UpdateCollider(this->position);
    //this->collider->RenderCollider();
}



void Enemy::Damage()
{
	__super::Damage();
    // �������ֵΪ0��������
    std::cout << "Enemy HP: " << this->HP << std::endl;
    if (this->HP <= 0) {
        // ���ﲻ���this��ɾ�ˣ�ֻ�ǰ���������״̬��Ϊdestroyed
        isAlive = false;
	}
}


Enemy::Enemy(Player* _player)
{
	this->player = _player;
}