#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Including/Gensin/Ground/Ground.h"
#include "../Including/Gensin/Player/Player.h"
#include "../Including/Gensin/Enemy/Enemy.h"
#include "../Including/Gensin/Enemy/EnemyManager.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void DrawPlayer(Shader& playerShader, glm::mat4& projection, glm::mat4& view, Player* player, Shader& groundShader);
void DrawEnemy(Shader& enemyShader, glm::mat4& projection, glm::mat4& view, Enemy* enemy);
void DrawBullet(Shader& bulletShader, glm::mat4& projection, glm::mat4& view, Bullet* bullet);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// 创建 Ground 对象
Ground* ground;

// 创建 Cinemachine 对象
Cinemachine* cinemachine;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    Shader playerShader("Resources/Shaders/anim_model.vs", "Resources/Shaders/anim_model.fs");
    Shader enemyShader("Resources/Shaders/anim_model.vs", "Resources/Shaders/anim_model.fs");
    Shader bulletShader("Resources/Shaders/anim_model.vs", "Resources/Shaders/anim_model.fs");

    Shader groundShader("Resources/Shaders/ground.vs", "Resources/Shaders/ground.fs");
    // load models
    /*Model ourModel("Animation/Babala/Idle/Idle.dae");
    Animation danceAnimation("Animation/Babala/Idle/Idle.dae", &ourModel);
    Animator animator(&danceAnimation);*/
    // 创建 Cinemachine 对象
    cinemachine = new Cinemachine(&camera);
    Player* player = new Player(cinemachine);
    Animator::Init();
    player->Awake();
    player->Start();
    
    Enemy* enemy = new Enemy(player);
    enemy->Awake();
    enemy->Start();

    EnemyManager::getInstance().addEnemy(enemy);

    // printf("%lf %lf %lf\n", enemy->position.x, enemy->position.y, enemy->position.z);

    // 创建地面对象
    ground = new Ground("Resources/Textures/Ground.jpg");

    float enemyGenerateTime = 15.0f;
    float enemyGenerateTimer = enemyGenerateTime;
    int enemyCountLimit = 3;
    int enemyCount = 1;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 只有当没满的时候才会生成敌人
        if (enemyCount < enemyCountLimit)
        {
            enemyGenerateTimer -= deltaTime;
        }

        if (enemyCount < enemyCountLimit && enemyGenerateTimer < 0)
        {
            enemyCount++;
            enemyGenerateTimer = enemyGenerateTime;
			Enemy* newEnemy = new Enemy(player);
			newEnemy->Awake();
			newEnemy->Start();
			EnemyManager::getInstance().addEnemy(newEnemy);
            printf("生成了新敌人\n");
		}
        // 清除缓冲区
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        // 设置视图和投影矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        DrawPlayer(playerShader, projection, view, player, groundShader);
        // 更新玩家状态
        player->Update(window, deltaTime);
        player->animator->UpdateAnimation(deltaTime);

        for (Enemy* enemy: EnemyManager::getInstance().getEnemies())
        {
            if (enemy && !enemy->isAlive)
            {
                EnemyManager::getInstance().removeEnemy(enemy);
                delete enemy;
                enemy = nullptr;
                enemyCount--;
            }
        }

        for (Enemy* enemy : EnemyManager::getInstance().getEnemies())
        {
            if (enemy)
            {
                DrawEnemy(enemyShader, projection, view, enemy);
                enemy->Update(window, deltaTime);
                enemy->animator->UpdateAnimation(deltaTime);
            }
        }

        for (auto bullet : player->bullets)
        {
            if (bullet && bullet->collider)
            {
                DrawBullet(bulletShader, projection, view, bullet);
                player->updateBullets(deltaTime);
            }
        }

        // 交换缓冲区并处理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    delete ground;
    delete cinemachine;
    return 0;
}

void DrawPlayer(Shader& playerShader, glm::mat4& projection, glm::mat4& view, Player* player, Shader& groundShader)
{
    // 启用着色器
    playerShader.use();
    playerShader.setMat4("projection", projection);
    playerShader.setMat4("view", view);

    // 获取骨骼矩阵并设置到着色器
    auto transforms = player->animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i)
    {
        playerShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
    }

    // 渲染模型
    // 创建模型矩阵并更新位置和旋转
    glm::vec3 characterPosition = player->getPosition();
    glm::vec3 playerDirection = player->getDirection();
    glm::vec3 initialDirection = glm::vec3(0.0, 0.0f, -1.0f); // 初始朝向

    // 计算旋转四元数
    glm::quat rotationQuat = glm::rotation(initialDirection, playerDirection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, characterPosition);
    // 翻转坐标系
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = model * glm::toMat4(rotationQuat); // 应用四元数旋转
    model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    playerShader.setMat4("model", model);

    // 绘制player模型
    player->model->Draw(playerShader);
    // 渲染地面
    ground->Draw(groundShader, view, projection);
    // 更新相机位置
    cinemachine->Update(characterPosition, deltaTime);
}

void DrawEnemy(Shader& enemyShader, glm::mat4& projection, glm::mat4& view, Enemy* enemy)
{
    enemyShader.use();
    enemyShader.setMat4("projection", projection);
    enemyShader.setMat4("view", view);
    // 绘制敌人
    auto transforms = enemy->animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i)
    {
        enemyShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
    }

    glm::vec3 enemyPosition = enemy->getPosition();
    glm::vec3 enemyDirection = enemy->getDirection();
    glm::vec3 enemyInitialDirection = glm::vec3(0.0, 0.0f, 1.0f); // 初始朝向

    // 计算旋转四元数
    glm::quat enemyRotationQuat = glm::rotation(enemyInitialDirection, enemyDirection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, enemyPosition);
    // 翻转坐标系 这个不用，因为它正好需要面对player 抵消了
    //model  = glm::rotate(model , glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = model * glm::toMat4(enemyRotationQuat); // 应用四元数旋转
    model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
    enemyShader.setMat4("model", model);
    // 绘制敌人模型
    enemy->model->Draw(enemyShader);
}

void DrawBullet(Shader& bulletShader, glm::mat4& projection, glm::mat4& view, Bullet* bullet)
{
    bulletShader.use();
    bulletShader.setMat4("projection", projection);
    bulletShader.setMat4("view", view);
    // 绘制敌人
    auto transforms = bullet->animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i)
    {
        bulletShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
    }

    glm::vec3 bulletPosition = bullet->getPosition();
    glm::vec3 bulletDirection = bullet->getDirection();
    glm::vec3 bulletInitialDirection = glm::vec3(0.0, 0.0f, 1.0f); // 初始朝向

    // 计算旋转四元数
    glm::quat bulletRotationQuat = glm::rotation(bulletInitialDirection, bulletDirection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, bulletPosition);
    model = model * glm::toMat4(bulletRotationQuat); // 应用四元数旋转
    model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
    bulletShader.setMat4("model", model);
    
    // 绘制敌人模型
    bullet->model->Draw(bulletShader);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cinemachine->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cinemachine->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cinemachine->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cinemachine->SwitchCamera(); // 切换相机
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
