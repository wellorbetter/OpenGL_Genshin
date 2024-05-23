#pragma once
#include "Enemy.h"

class EnemyManager
{
public:
    // ��ȡ����ʵ��
    static EnemyManager& getInstance()
    {
        static EnemyManager instance;
        return instance;
    }

    // ���ÿ�������͸�ֵ������
    EnemyManager(const EnemyManager&) = delete;
    void operator=(const EnemyManager&) = delete;

    // ��ӵ���
    void addEnemy(Enemy* enemy)
    {
        enemies.push_back(enemy);
    }

    // �Ƴ�����
    void removeEnemy(Enemy* enemy)
    {
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
    }

    // ��ȡ���е���
    std::vector<Enemy*> getEnemies() const
    {
        return enemies;
    }

private:
    // ˽�й��캯��
    EnemyManager() = default;

    // �����б�
    std::vector<Enemy*> enemies;
};