// load_libsvm.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <array>
#include <map>
#include <typeinfo>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/program_options.hpp>

using namespace std;

int main() {
	ifstream infile;
	infile.open("data.txt"); //读入文件
	if (!infile) {
		cout << "can not open file" << endl;
	}
	vector <int> train_labels;              //定义动态数据 存放labels
	vector<vector<float> > train_data;      //定义二维动态数据 存放train_data
	string s;								//定义行

	while (getline(infile, s)) {			//按行读入
		//cout << s << endl;
		vector<float> featValue;			//创建每行的temp数组
		vector<string> strs;
		boost::split(strs, s, boost::is_any_of(" "));			//按" "切分字符串
		train_labels.push_back(atoi(strs[0].c_str()));			//第一个位置转为int后存入train_labels
		map<int, float> tmp;									//key为int, value为float的字典
		for (size_t i = 1; i < strs.size(); i++) {				//从i=1开始，后面为特征
			vector<string> strs1;
			boost::split(strs1, strs[i], boost::is_any_of(":"));		//按":"切分  1:0.5
			//cout << typeid(strs1[0]).name();
			int key = atoi(strs1[0].c_str());					//第一个位置转化为int存入字典key
			float val = atof(strs1[1].c_str());					//第二个位置转化为float存入字典value
			tmp[key] = val;										//键值对字典
		}

		/* 打印字典
		for (map<string, string>::iterator it = tmp.begin(); it != tmp.end(); it++)
		{
		// map的迭代器，可以用 first 访问std::pair的第一个成员(Type1)，second 访问第二个成员 (Type2)
		cout << it->first << ":" << it->second << endl;
		}
		*/
		for (int i = 1; i < 340; i++) { // 6是总共有多少列特征
			/* int to string 
			stringstream ss;
			ss << i;
			string a = ss.str();
			*/
			std::map<int, float>::const_iterator iter = tmp.find(i);		
			if (iter != tmp.end())										//遍历字典
			{
				featValue.push_back(iter->second);						//如果找到key，将value存入每行的temp数组
			}
			else
			{
				featValue.push_back(0);									//否则将这个位置存入0
			}
		}
		train_data.push_back(featValue);								//每行遍历结束后，将每行的temp数组 featValue 存入train_data
	}

	/*
		如果对测试集一行一行的输入，那么就不需要外面大的train_data了，只要每行的featValue就可以，
		将featValue用xgboost的API（可以用XGDMatrixCreateFromMat）转为xgb所需的就可以了吧
	*/

	// 打印查看
	
	for (size_t i = 0; i < train_data.size(); i++) {
		for (size_t j = 0; j < train_data[i].size(); j++)
		{
			cout << train_data[i][j] << "\t";
		}
		cout << endl;
	}
	//for (size_t i = 0; i < train_labels.size(); i++) {
	//	cout << train_labels[i] << endl;
	//}
	
	cout << train_data.size() << endl;


	system("pause");
}



