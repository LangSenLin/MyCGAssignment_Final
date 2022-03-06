
#include "Grammar.h"
/*
 *函数名称：
 *函数功能：
 *传递参数：
 * 返回值：
 */
Grammar::Grammar() {
	w = "F[@/L][*@L][+%L]";
	level = 6;//迭代层数，建议在3~6之间，过小则生成的树简单，过大则电脑带不动
    //文法字符解释
	//F是树干
	//+ - 绕x轴转动dx -dx
	//* / 绕y轴转动dy -dy
	//! @ 绕z轴转动dz -dz
	generations.push_back("F[+@L][/*!L][!-L]");
	generations.push_back("F[*@L][*-L][@/-L]");
	generations.push_back("F[/-L][+@L][-!L]");
	generations.push_back("F[*+L][-*L][/!L]");
}

/*
 *函数名称：getResult()
 *函数功能：调用Iteration()生成一个L-system分形树的文法并返回该文法
 *传递参数：none
 * 返回值：string result-文法
 */
string Grammar::getResult() {
	Iteration();
	return result;
}

Grammar::~Grammar() {
	generations.clear();
}

/*
 * 函数名称：Iteration()
 * 函数功能：对原始文法进行迭代
 *                  迭代规则：在level下对字符“L”进行替换，随机使用替换文法generations[4]其中一个
 * 传递参数：none
 * 返回值  ：none
 */

void Grammar::Iteration() {
	srand(time(NULL));
	result = w;
	for (int i = 0; i < level; i++) {
		string tmp = "";
		for (int j = 0; j < result.size(); j++) {
			tmp += search(result[j]);
		}
		result = tmp;
	}
}

/*
 * 函数名称：search()
 * 函数功能：随机替换一个叶节点的文法
 * 传递参数：char c:文法中的一个字符
 * 返回值  ：原字符c/叶子节点被替换的字符串
 */
string Grammar::search(char c) {
	if (c == 'L') {
		//替换
		int index = rand() % generations.size();
		return generations[index];
	}
	else {
		//不替换
		string tmp(1, c);
		return tmp;
	}
}

