#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <map>
#include <filesystem>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "animation.h"
#include "bone.h"
#include <iostream>

class Animator
{
public:
    // 所有的动画
    static std::map<string, Animation*> animations;
    static std::map<string, Model*> models;

    static void Init()
    {
        vector<string> path = { "Animation/Babala", "Animation/WeirdQiuqiuren" };
        // 读取所有的动画 Animation 目录下所有的文件夹
        for (auto& p : path)
            InitAnimation(p);
    }

    static void InitAnimation(string path)
    {
        std::filesystem::path animationPath(path);

        if (std::filesystem::exists(animationPath) && std::filesystem::is_directory(animationPath))
        {
            for (const auto& entry : std::filesystem::directory_iterator(animationPath))
            {
                if (entry.is_directory())
                {
                    std::string path = entry.path().string();
                    std::string name = entry.path().filename().string();

                    // 替换路径中的反斜杠为正斜杠
                    std::replace(path.begin(), path.end(), '\\', '/');

                    // 加载模型
                    std::string modelPath = path + "/" + name + ".dae";
                    // 加载动画
                    Model* model = new Model(modelPath);
                    Animation* animation = new Animation(modelPath, model);
                    models[modelPath] = model;
                    animations[modelPath] = animation;
                }
            }
        }
        else
        {
            std::cout << "Animation folder not found" << std::endl;
        }
    }


    Animator(Animation* animation)
    {
        m_CurrentTime = 0.0f;
        m_CurrentAnimation = animation;

        m_FinalBoneMatrices.reserve(100);

        for (int i = 0; i < 100; i++)
            m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
    }

    void UpdateAnimation(float dt)
    {
        m_DeltaTime = dt;
        if (m_CurrentAnimation)
        {
            m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
            m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
            CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
        }
    }

    void PlayAnimation(Animation* pAnimation)
    {
        m_CurrentAnimation = pAnimation;
        m_CurrentTime = 0.0f;
    }

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
    {
        std::string nodeName = node->name;
        glm::mat4 nodeTransform = node->transformation;

        Bone* bone = m_CurrentAnimation->FindBone(nodeName);

        if (bone)
        {
            bone->Update(m_CurrentTime);
            nodeTransform = bone->GetLocalTransform();
        }

        glm::mat4 globalTransformation = parentTransform * nodeTransform;

        auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
        if (boneInfoMap.find(nodeName) != boneInfoMap.end())
        {
            int index = boneInfoMap[nodeName].id;
            glm::mat4 offset = boneInfoMap[nodeName].offset;
            m_FinalBoneMatrices[index] = globalTransformation * offset;
        }

        for (int i = 0; i < node->childrenCount; i++)
            CalculateBoneTransform(&node->children[i], globalTransformation);
    }

    std::vector<glm::mat4> GetFinalBoneMatrices()
    {
        return m_FinalBoneMatrices;
    }

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    Animation* m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
};
