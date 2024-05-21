# OpenGL_Genshin

Opengl做一个原神贴膜的无尽跑酷游戏，感觉可能类似于c++小恐龙那种，但是会带一些骨骼动画，opengl确实难，但是还好有https://learnopengl-cn.github.io/上面的现成的代码(大部分框架都是基于learningopengl的代码写的)



##### Day1：

1. 写出了virtualCamera 第一人称、第三人称和上帝视角，就是拿到角色的位置之后，把camera的位置强制放在这个位置的前面一点就是第一人称，后面的上面就是第三人称，加一个可以自由移动的就是上帝视角

2. 模型obj拿的[WhizZest/learnOpenGL: openGL learning code (github.com)](https://github.com/WhizZest/learnOpenGL)上面的芭芭拉，不太懂pmx怎么转obj。动画用https://www.mixamo.com/，上传obj下载对应的简易动画即可

3. 写了一个简易的方形地图，可能后续得换一个长条的，加点障碍物什么的

4. 大概写了一些状态机的骨架

##### Day2:

1. 写状态机写了一堆，指针引过来引过去的，出来爆一堆前向引用的错，小修了一会儿(好久没用指针了，记不清了)
2. 人物动作全部都提前渲染好，免得切动作的时候卡顿，所有的动画都static存到了Animator里面，又是指针，报了一大堆的错。查半天，有时候这个编译器找不对错在了哪里，有时候是static变量忘了声明，但是爆的错是glm库里面没有什么什么成员变量？很奇怪，还好还好，今天把最基础的调出来了。可以init进入IdleState。
3. 准备抽象出Input类以供State进行Update里面的判断
4. 准备研究如何进行碰撞检测，添加障碍物以及伤害等诸多问题

##### Day3:

1. 可以前后左右移动，然后可以跳跃，但是我感觉应该写一个根据人称视角的角度进行位移，而不是限定死
2. 完成移动跳跃状态机，移动状态机包含前后左右四个subState
3. 准备写AABB Collider，完善地图