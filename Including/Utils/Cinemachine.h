#pragma once

#include "camera.h"
#include <vector>
#include <glm/glm.hpp>

class VirtualCamera {
public:
    glm::vec3 offset;
    Camera* camera;
    bool isFreeCamera; // �Ƿ�Ϊ����������ϵ��ӽǣ�
    

    VirtualCamera(Camera* cam, const glm::vec3& offset, bool isFree = false)
        : camera(cam), offset(offset), isFreeCamera(isFree) {}

    void UpdatePosition(const glm::vec3& targetPosition) {
        if (!isFreeCamera) {
            camera->Position = targetPosition + offset;
            camera->updateCameraVectors();
        }
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        if (isFreeCamera) {
            camera->ProcessKeyboard(direction, deltaTime);
        }
    }
};

class Cinemachine {
public:
    std::vector<VirtualCamera> virtualCameras;
    int activeCameraIndex;
    float switchTime;
    float switchTimer;

    Cinemachine(Camera* cam) {
        activeCameraIndex = 1;
        switchTime = 1.0f;
        switchTimer = switchTime;
        // Ĭ�����һ�������˳������һ����һ�˳����
        // 0 1 2 ---- 3 1 ��
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 2.0f))); // �����˳�
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, .15f, 0.0f))); // ��һ�˳�
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 0.0f, 0.0f), true)); // �ϵ��ӽ�
    }

    void AddVirtualCamera(const VirtualCamera& vc) {
        virtualCameras.push_back(vc);
    }

    void SwitchCamera() {
        activeCameraIndex++;
        activeCameraIndex %= 3;
        std::cout << activeCameraIndex << std::endl;
        switch (activeCameraIndex)
        {
        case 0:
            std::cout << "�����˳�" << std::endl;
			break;
        case 1:
            std::cout << "��һ�˳�" << std::endl;
            break;
        case 2:
            std::cout << "�ϵ��ӽ�" << std::endl;
            break;
        }

    }

    void Update(const glm::vec3& targetPosition) {
        virtualCameras[activeCameraIndex].UpdatePosition(targetPosition);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
    }
};
