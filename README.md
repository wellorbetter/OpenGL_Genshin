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

##### Day4:

1. 感觉添加地形还是有点麻烦，地图也不好做，感觉还是做平面RPG好一点，完成player攻击，添加cd和后摇，攻击的时候不准跑
2. 写了AABB Collider，但是还没有限制碰撞和具体的碰撞逻辑，写了人物攻击发射子弹，同样没完善子弹和其他collider碰撞
3. 添加Enemy，Idle、Move和Attack，具体逻辑没写，目前只会Idle，应当会在Front一定角度和范围内感知player，然后朝着player走过去，一定角度和范围内会进行攻击，待完善
4. 换一个敌人模型，考虑pmx转obj

##### Day5:
1. 完成Enemy的Idle、Move和Attack逻辑
2. Player可以攻击，完成子弹Bullet的发射和模型展示
3. 完成AABB碰撞Collider，但是存在bug，这个框在Idle的时候是在player身上，但是一旦move，就不对了（enemy同理，或许bug在move上）
4. 完成bullet对enemy的碰撞检测，使用EnemyManager单例模式对Enemy进行管理，可以同时产生多个enemy
5. enemy受到攻击三次就会消失(但是还是碰撞框的问题，没找到bug，就可能一直打不到enemy)