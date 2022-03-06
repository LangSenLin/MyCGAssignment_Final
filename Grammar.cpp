
#include "Grammar.h"
/*
 *�������ƣ�
 *�������ܣ�
 *���ݲ�����
 * ����ֵ��
 */
Grammar::Grammar() {
	w = "F[@/L][*@L][+%L]";
	level = 6;//����������������3~6֮�䣬��С�����ɵ����򵥣���������Դ�����
    //�ķ��ַ�����
	//F������
	//+ - ��x��ת��dx -dx
	//* / ��y��ת��dy -dy
	//! @ ��z��ת��dz -dz
	generations.push_back("F[+@L][/*!L][!-L]");
	generations.push_back("F[*@L][*-L][@/-L]");
	generations.push_back("F[/-L][+@L][-!L]");
	generations.push_back("F[*+L][-*L][/!L]");
}

/*
 *�������ƣ�getResult()
 *�������ܣ�����Iteration()����һ��L-system���������ķ������ظ��ķ�
 *���ݲ�����none
 * ����ֵ��string result-�ķ�
 */
string Grammar::getResult() {
	Iteration();
	return result;
}

Grammar::~Grammar() {
	generations.clear();
}

/*
 * �������ƣ�Iteration()
 * �������ܣ���ԭʼ�ķ����е���
 *                  ����������level�¶��ַ���L�������滻�����ʹ���滻�ķ�generations[4]����һ��
 * ���ݲ�����none
 * ����ֵ  ��none
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
 * �������ƣ�search()
 * �������ܣ�����滻һ��Ҷ�ڵ���ķ�
 * ���ݲ�����char c:�ķ��е�һ���ַ�
 * ����ֵ  ��ԭ�ַ�c/Ҷ�ӽڵ㱻�滻���ַ���
 */
string Grammar::search(char c) {
	if (c == 'L') {
		//�滻
		int index = rand() % generations.size();
		return generations[index];
	}
	else {
		//���滻
		string tmp(1, c);
		return tmp;
	}
}

