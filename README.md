# 构建L-system分形树    

## 一、基本概念
### 1、L-system
&emsp;Lindenmayer系统，简称L系统，是由荷兰乌特勒支大学的生物学和植物学家，匈牙利裔的林登麦伊尔（Aristid Lindenmayer）于1968年提出的有关生长发展中的细胞交互作用的数学模型，尤其被广泛应用于植物生长过程的研究。       
&emsp;L-system是一系列不同形式的正规语法规则，多被用于植物生长过程建模，但是也被用于模拟各种生物体的形态。          
&emsp;L-system的自然递归规则导致自相似性，也因此使得分形一类形式可以很容易的使用L-system描述。植物模型和自然界的有机结构生成，非常相似并很容易被定义，因此通过增加递归的层数，可以缓慢生长并逐渐变得更复杂。L-system同样在制造人造生命领域。 L-system 语法与Chomsky语法非常相似，说到L-system通常指的是带参数的L-system，定义如下：      
&emsp;  G＝｛V,S,ω,P},        
&emsp;  V:变量符号集合         
&emsp;  S：常量符号集合        
&emsp;  ω：初始状态串        
&emsp;  P：产生式规则         
&emsp;自初始状态开始迭代套入L-system的文法规则，和正规文法所产生的语言不同处在于，L-system在一次迭代中可同时套用许多不同的文法规则。如果在一次迭代中只能够套用一个文法规则，产生出来的结果被称为语言而不是L-system。由此可知，L-system为正规文法所产生出的语言的子集合。       
           
#### 例子：Lindenmayer研究海藻生长模式时提出的最早的L-系统：           
&emsp;变量 : A B               
&emsp;常量 : 无        
&emsp;公理  : A        
&emsp;规则  : (A → AB), (B → A)          
&emsp;迭代过程：        
&emsp;&emsp;n = 0 : A          
&emsp;&emsp;n = 1 : AB         
&emsp;&emsp;n = 2 : ABA           
&emsp;&emsp;n = 3 : ABAAB        
&emsp;&emsp;n = 4 : ABAABABA         
&emsp;&emsp;n = 5 : ABAABABAABAAB        
&emsp;&emsp;n = 6 : ABAABABAABAABABAABABA       
&emsp;&emsp;n = 7 : ABAABABAABAABABAABABAABAABABAABAAB         
### 2、分形树
&emsp;该想法主要用递归思想来实现，看一个简单的例子：           
![](https://img-blog.csdnimg.cn/20190310014419492.gif)    
用我个人的理解来解释这个概念就是通过遵循一定的几何线条生成规则来生成的一棵树。

## 二、基本函数库
### 1、OpenGL       
&emsp;函数库OpenGL（Open Graphics Library）是一个跨编程语言、跨平台的编程图形程序接口，它将计算机的资源抽象称为一个个OpenGL的对象，对这些资源的操作抽象为一个个的OpenGL指令。           
### 2、Glut        
&emsp;GLUT，是指OpenGL Utility Toolkit，用于开发独立于窗口系统的OpenGL程序，即该库打包了很多的窗口操作，提供了独立于具体操作系统的API，让你快速的在OpenGL开发中完成窗口相关操作，如窗口显示、输入设备读取、多级级联菜单、多窗口管理等等便捷功能。         
### 3、glm        
&emsp;矩阵运算方法。GLM是OpenGL Mathematics的缩写。作为一个header only库，GLM只要包括了相应的头文件就可以使用它提供的类和函数。GLM是C++语言编写的，故不适用于C语言工程。        

#### 注：个人建议学习OpenGL可边参考[官方文档](https://learnopengl-cn.github.io/)，边看[傅老师的OpenGL教程](https://www.bilibili.com/video/BV11W411N7b9/?spm_id_from=333.788.recommend_more_video.0)，边动手实践。

## 三、实验记录
&emsp;出于电脑卡顿原因，卸载了VS2019的C++部分，故不能重现实验过程，但存有当时的实验记录文档，故此处直接对实验过程进行描述，附加截图帮助大家理解。
### 1、我的文法生成器（Grammar类）
&emsp;该类的功能就是生成一个字符串类型的文法。       
![image](https://user-images.githubusercontent.com/43472106/156921085-5583577c-b6f6-4e59-9a1b-c816e7d37692.png)         
&emsp;构建用例，查看生成结果          
![image](https://user-images.githubusercontent.com/43472106/156921065-0df7cbbc-25a3-4e81-a027-6f5ebc93f013.png)      
&emsp;执行结果：         
![image](https://user-images.githubusercontent.com/43472106/156921104-9166767a-c193-409d-8d74-782ec860d012.png)           
### 2、文法翻译（LSystem类）
该类的功能就是将字符串文法翻译为三维模型中树的节点信息，包含位置、方向、长度和半径，还包含迭代因子。        
![image](https://user-images.githubusercontent.com/43472106/156921200-0943c787-0d3c-415b-ba00-0ffa73d933a8.png)          
&emsp;其中的generateFractal()就是翻译过程，在构造函数中初始化主树干的三维信息，然后在此基础上进行迭代，最后的结果将存进Trunk数组和Leaf数组，这两个数组的内容最后会加工喂给OpenGL库函数来帮助我们生成一棵树。        
### 3、旋转工具（myRotate）         
&emsp;功能是帮助LSystem对符号“+”“-”“*”“/”“!”“@”进行解释，将三维信息做x/y/z轴的三维世界的旋转。是利用矩阵来实现的。         
![](https://pic3.zhimg.com/80/v2-ff7877954f6a4020f934df16ca109322_720w.jpg)      
&emsp;代码实现：         
![image](https://user-images.githubusercontent.com/43472106/156921539-e1683e26-4269-406b-9fdd-36a9d7a84d93.png)
![image](https://user-images.githubusercontent.com/43472106/156921543-6a63238c-fd31-4c8c-aecf-b939e9354231.png)

### 4、绘制树干、树叶
&emsp;这部分实现参考助教所给博客[opengl L系统 三维分形树（有纹理）](https://blog.csdn.net/qq_39019698/article/details/80376416?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_paycolumn_v3&utm_relevant_index=2)中画树干、树叶的方法进行实现。      
&emsp;实现效果如下图：         
&emsp;&emsp;迭代5次：        
![image](https://user-images.githubusercontent.com/43472106/156922090-dca69348-792b-4206-b069-86ce4075329e.png)       
![image](https://user-images.githubusercontent.com/43472106/156922092-0354973b-a668-43ce-9f22-9fa0fdef3946.png)              
&emsp;&emsp;迭代6次：        
![image](https://user-images.githubusercontent.com/43472106/156922102-d19b98d0-0f04-4662-acaa-ae5cce09158f.png)       
![image](https://user-images.githubusercontent.com/43472106/156922107-757c8025-b2ce-4f5b-8ac4-890b3ae1a9b2.png)        

#### 以上就是我在小组分工中所完成的全部任务，代码部分已给出，还未实现的部分包括纹理贴图、天空盒背景、局部光照明模型和人机交互模型。

## 四、实验总结
&emsp;前期开工比较慢，也有个人性格的原因，总之就是收集资料，了解实现过程，当心里有了实现的方法便开始coding。当时因为负责本次大作业的开工，写了两天两夜（不是不睡觉，是除了睡觉吃饭，别的时候都在打代码）。虽然网上有现成的代码，但是当自己从头开始到窗孔弹出了绘制树干、树叶的效果图的时候，那一份造出自己“蓝盒子”的心情真的是无法比拟的快乐和开心。所以这里也不贴出我的main函数代码啦，参考博客有较为全面的讲解，我也在我的源文件中给出了注释，相信可以给你一些思路，如果你想实现一棵L-system系统分形树。            
&emsp;最后贴出我们小组的最终实现效果ppt截图，以此纪念我们四人小组那段难忘的时光。       
![image](https://user-images.githubusercontent.com/43472106/156922780-4fedb4fe-a8a8-4bde-ba72-a89b24f56989.png)
![e1b344745b5299e4e34580749bd01a1](https://user-images.githubusercontent.com/43472106/156922579-a2ed7307-3f5b-4973-a5f4-fd141283d6fe.jpg)
![9f3446a3c7162db99071dd664b6f714](https://user-images.githubusercontent.com/43472106/156922587-6c1263f2-a09a-4a89-8440-dc207ae65cd7.jpg)

