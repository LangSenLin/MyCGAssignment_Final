#ifndef  GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <string>
#include <vector>

/*
 *   类名称：Grammar
 *   类功能：L-system分形树语法生成类
 */
using namespace std;
class Grammar {
public:
	string w;
	Grammar();
	~Grammar();
	void Iteration();
	string getResult();
private:
	
	string result;
	vector<string> generations;
	string search(char c);
	int level;
};


#endif // ! GRAMMAR_H

