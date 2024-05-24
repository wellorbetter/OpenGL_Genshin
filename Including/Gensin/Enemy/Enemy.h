#pragma once
#include "../Entity/Entity.h"
#include "EnemyAttackState.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyStateMachine.h"

class Player;

class Enemy : public Entity {
public:
    EnemyMoveState* moveState;
    EnemyAttackState* attackState;
    EnemyStateMachine* stateMachine;
    EnemyIdleState* idleState;
    Player* player;
    Collider* collider;
    // 构造函数
    Enemy(Player* _player);

    // 覆盖父类的方法
    void Awake() override;
    void Start() override;
    void Update(GLFWwindow* window, float deltaTime);
    void Damage() override;
};
