#pragma once
#include "../Entity/Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"
#include "../../Utils/Cinemachine.h"

class Bullet;

// �����
// �����Ӧ�����ж�Ӧ��״̬����
class Player :public Entity {
public:
	PlayerIdleState* idleState;
	PlayerStateMachine* stateMachine;
	PlayerMoveState* moveState;
	PlayerJumpState* jumpState;
	PlayerAttackState* attackState;
    Collider* collider;

	Player(Cinemachine* _cinemachine);

	bool isMoving = false;

	void Awake() override;
	void Start() override;
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime);
	void Damage() override;
	// ��Ҫ��һ����һ�˳��ӽǵķ���λ��

    void fireBullet(float len);
    void updateBullets(float deltaTime);
    float maxBulletDistance = 15.0f; // �����ӵ���������

	Cinemachine* cinemachine;
    std::vector<Bullet*> bullets;
    
};

class Bullet{
public:
    Bullet(Player* player, glm::vec3 startPosition, glm::vec3 direction, float speed)
        : player(player), position(startPosition), direction(glm::normalize(direction)), speed(speed)
    {
        collider = new Collider();
        model = new Model("Resources/Model/Bullet/Bullet.dae");
        animation = new Animation("Resources/Model/Bullet/Bullet.dae", model);
        animator = new Animator(animation);
    }

    void Update(float deltaTime)
    {
        position += direction * speed * deltaTime;
        this->collider->UpdateCollider(this->position);
    }

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getDirection() const { return direction; }
    Collider* collider;
    Player* player;
    Model* model;
    Animation* animation;
    Animator* animator;
private:
    glm::vec3 position;
    glm::vec3 direction;
    float speed;
};