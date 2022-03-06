#include "LSystem.h"
#include "MyRotate.h"
/*
 *函数名称：LSystem()
 *函数功能：初始化在将文法翻译成三维信息的一些基本参数
                包括：1、初始旋转角度dx、dy、dz
                     2、树枝长度length、
                     3、树枝半径radius、
                     4、树叶长度leafLength、
                     5、树叶半径leafRadius
                     6、长度迭代因子lengthFactor
                     7、半径迭代因子radiusFactor
                     8、树枝、树叶数量numTrunks,numLeafs
                     9、字符串格式的树result

 *传递参数：none
 * 返回值： none
 */
LSystem::LSystem() {
	dx = dz = 35.0f;
	dy = 30.0f;
	length = 20.0;
	radius = 3.0f;
	leafRadius = 3.0f;
	leafLength = 0.2;
	lengthFactor = 0.7;
	radiusFactor = 0.6;
	numTrunks = numLeafs = 0;
	result = grammar.getResult();
}

LSystem::~LSystem() {
	result.clear();
}

/*
 *函数名称：generateFractal()
 *函数功能：将文法翻译成三维信息并存储这些信息
            通俗的说：通过文法，让树从主干开始“生长”，第一级枝干、第二级枝干、……第level级枝干，最后长出叶子。
                    翻译方法：
                            1、初始化当前状态（初始状态）
                            2、取出文法中的一个字符
                                1、'F‘：代表树干
                                2、'+‘：代表绕x轴顺时针环绕
                                3、'-‘：代表绕x轴逆时针环绕
                                4、'*‘：代表绕y轴顺时针环绕
                                5、'/‘：代表绕y轴逆时针环绕
                                6、'!‘：代表绕z轴顺时针环绕
                                7、'@‘：代表绕z轴逆时针环绕
                                8、'[‘：入栈操作，表示进入下一级枝干
                                9、']‘：出栈操作，表示返回上一级枝干
                               10、'L'：代表叶子
 *传递参数：none
 * 返回值：none
 */
void LSystem::generateFractal() {
	trunks.clear();
	leafs.clear();
	curState.pos = glm::vec3(0, 0, 0);
	curState.dir = glm::vec3(0, 1, 0);
	curState.length = length;
	curState.level = 1;
	curState.radius = radius;
	//状态栈
    //压入当前的状态，进入下一级枝干，将枝干按照因子系数进行缩小缩小
    //当出栈时代表返回上一级枝干的起点进行其他下一级枝干或继续返回上一级枝干
	stack<State> stacks;


	for (int i = 0; i < result.size(); i++) {
		char c = result[i];
		Trunk tmp;
		//树干
		if (c == 'F') {
			tmp.start = curState.pos;
			curState.pos += curState.dir * (float)curState.length;
			tmp.end = curState.pos;
			tmp.radius = curState.radius;
			trunks.push_back(tmp);
			continue;
		}
		//绕X轴转dx角度
		else if (c == '+') {
			curState.dir = MyRotate::RotateX(curState.dir, dx);
			continue;
		}
		//绕X轴转-dx角度
		else if (c == '-') {
			curState.dir = MyRotate::RotateX(curState.dir, -dx);
			continue;
		}
		//绕X轴转dy角度
		else if (c == '*') {
			curState.dir = MyRotate::RotateY(curState.dir, dy);
			continue;
		}
		//绕X轴转-dy角度
		else if (c == '/') {
			curState.dir = MyRotate::RotateY(curState.dir, -dy);
			continue;
		}
		//绕X轴转dz角度
		else if (c == '!') {
			curState.dir = MyRotate::RotateZ(curState.dir, dz);
			continue;
		}
		//绕X轴转-dz角度
		else if (c == '@') {
			curState.dir = MyRotate::RotateZ(curState.dir, -dz);
			continue;
		}
		//将当前的状态压入栈中保存
		//将当前的长度和体积按比例减小
		else if (c == '[') {
			stacks.push(curState);
			curState.length *= lengthFactor;
			curState.radius *= radiusFactor;
			continue;
		}
		//出栈
		else if (c == ']') {
			curState = stacks.top();
			stacks.pop();
			continue;
		}
		//叶子节点
		else if (c == 'L') {
			Trunk t = trunks[trunks.size() - 1];
			Leaf l;
			l.dir = t.end - t.start;
			l.dir = glm::normalize(l.dir);
			l.pos = t.end;
			l.end.x = l.pos.x + l.dir.x * leafLength;
			l.end.y = l.pos.y + l.dir.y * leafLength;
			l.end.z = l.pos.z + l.dir.z * leafLength;
			leafs.push_back(l);
		}
		else {
			//do nothing
		}
	}
}