#pragma once
#include "Enemy.h"

class EnemyManager
{
public:
    // 获取单例实例
    static EnemyManager& getInstance()
    {
        static EnemyManager instance;
        return instance;
    }

    // 禁用拷贝构造和赋值操作符
    EnemyManager(const EnemyManager&) = delete;
    void operator=(const EnemyManager&) = delete;

    // 添加敌人
    void addEnemy(Enemy* enemy)
    {
        enemies.push_back(enemy);
    }

    // 移除敌人
    void removeEnemy(Enemy* enemy)
    {
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
    }

    // 获取所有敌人
    std::vector<Enemy*> getEnemies() const
    {
        return enemies;
    }

private:
    // 私有构造函数
    EnemyManager() = default;

    // 敌人列表
    std::vector<Enemy*> enemies;
};