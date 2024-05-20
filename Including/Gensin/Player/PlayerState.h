#pragma once


#include <string>
class Player;
class PlayerStateMachine;

class PlayerState {
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	// һ����ĳ��״̬��ʱ�������� �л�״̬
	virtual void Update() = 0;
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