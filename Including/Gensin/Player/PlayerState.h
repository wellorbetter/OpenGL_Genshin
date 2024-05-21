#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Player;
class PlayerStateMachine;

class PlayerState {
public:
	virtual void Enter();
	virtual void Exit();

	// һ����ĳ��״̬��ʱ�������� �л�״̬
	virtual void Update(GLFWwindow* window) = 0;
protected:
	// ״̬�� 
	// ������Animation\babala\stateName
	// �����ҵ���Ӧ��ģ���ļ�
	std::string stateName;

	// ״̬���ֵ�player
	Player* player;

	// ��Ӧ��״̬�� ������Ȼ������player���ʣ�����Ϊ�˼���ǰ׺�����Ǽ���
	PlayerStateMachine* stateMachine;

	// ��ʼ�����캯��
	PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName);
};