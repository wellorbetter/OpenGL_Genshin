# OpenGL_Genshin

Opengl做一个原神贴膜的无尽跑酷游戏，感觉可能类似于c++小恐龙那种，但是会带一些骨骼动画，opengl确实难，但是还好有https://learnopengl-cn.github.io/上面的现成的代码(大部分框架都是基于learningopengl的代码写的)



##### Day1：

1. 写出了virtualCamera 第一人称、第三人称和上帝视角，就是拿到角色的位置之后，把camera的位置强制放在这个位置的前面一点就是第一人称，后面的上面就是第三人称，加一个可以自由移动的就是上帝视角

2. 模型obj拿的[WhizZest/learnOpenGL: openGL learning code (github.com)](https://github.com/WhizZest/learnOpenGL)上面的芭芭拉，不太懂pmx怎么转obj。动画用https://www.mixamo.com/，上传obj下载对应的简易动画即可

3. 写了一个简易的方形地图，可能后续得换一个长条的，加点障碍物什么的

4. 大概写了一些状态机的骨架