//operation_number.cpp���������������йصĺ���
#include "operation.h"
#include "common.h"
#include <string>
#include <cctype>

using std::string;
using std::isdigit;

//operation_number_without������һ����
#define part1 exit=false;
#define part2 auto e{i+1} , s{i-1}; //�ж�һ���������ʽ��ͷβ
//��Ϊunsigned��signed���໥ת������ʹ��s<str.length()��Ϊ����
#define part3 for(;s < str.length();--s){if(IsOperator(str[s])) break;}
#define part4 for(;e < str.length();++e){if(e == i+1) continue; if(IsOperator(str[e])) break;}
#define part5 if(GetTypeOf(str.substr(s,i-s))!="number") throw "����number����δ֪�������ͣ�";
#define part6 if(GetTypeOf(str.substr(i+1,e-i-1))!="number") throw "����number����δ֪�������ͣ�";
#define part7 Number_Type but1{ StrToNum(str.substr(s,i-s)) };	//�������ʽ�еĵ�һ����
#define part8 Number_Type but2{ StrToNum(str.substr(i+1,e-i-1)) };	//�������ʽ�еĵڶ�����
#define part part1 part2 part3 part4 part5 part6 part7 part8
//-----------------------------------

typedef double Number_Type;	//�ļ��������������е���������

int CharToInt(char);	//��char����ת����int��
static bool IsOperator(char);	//�ж������ַ��Ƿ�Ϊ�����
string NumToStr(Number_Type);	//��Number_Type��ת����string��
Number_Type StrToNum(string);	//��string��ת����Number_Type��
string operation_number_without(string);	//��ɲ������ŵ�����������

int CharToInt(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}

bool IsOperator(char c){
	if(c == '+') return true;
	if(c == '-') return true;
	if(c == '*') return true;
	if(c == '/') return true;
	return false;
}

string NumToStr(Number_Type v){
	char but[100];
	sprintf(but,"%f",v);
	string str{but};
	//����ַ����Ļ���
	for(auto itr{ str.end()-1 };itr != str.begin();--itr){
		if(isdigit(*itr) && *itr != '0') break;
		if(*itr == '0'){*itr = ' '; continue;}
		if(*itr == '.'){*itr = ' '; break;}
	}
	str = DeleteBlank(str);
	if(!IsOperator(str[0])) str = "+" + str;
	return str;
}

Number_Type StrToNum(string str){
	Number_Type v{0};
	bool IsPoint{false};	//�ж��Ƿ���С��
	bool IsNegative{false};	//�ж��Ƿ��Ǹ���
	float location_point{0};	//С��λ*10
	for(auto e : str){
		if(e == '-') IsNegative = true;
		else if(e == '.'){IsPoint = true; location_point = 10;}
		else if(isdigit(e)){
			if(IsNegative){
				if(IsPoint){
					if(e != '0') v = v - CharToInt(e) / location_point;
					location_point *= 10;
				}
				else{
					v = v * 10 - CharToInt(e);
				}
			}
			else{
				if(IsPoint){
					if(e != '0') v = v + CharToInt(e) / location_point;
					location_point *= 10;
				}
				else{
					v = v * 10 + CharToInt(e);
				}
			}
		}
	}
	return v;
}

string operation_number_without(string str){
	//��ⲿ��
	if((IsOperator(str[0])&&str[0]!='-'&&str[0]!='+')||
			(IsOperator(str[str.length()-1])))
		throw "����number�����������˫Ŀ�Դ���";
	//----------
	str = "+" + str; str = str + "+";
	do{			//�˳���������
		auto length{str.length()};
		bool exit{true};
		for(decltype(str.length()) i{0};i < length;++i){
			if(str[i] == '*'){
				part 
				str = str.substr(0,s) + NumToStr(but1 * but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 * but2).length();
				length = str.length();
			}
			else if(str[i] == '/'){
				part
				if(but2 == 0) throw "����number����������Ϊ�㣡";
				str = str.substr(0,s) + NumToStr(but1 / but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 / but2).length();
				length = str.length();
			}
		}
	}while(!exit);
	do{			//�Ӽ���������
		auto length{(int)str.length()};
		bool exit{true};
		for(decltype(str.length()) i{0};i < length;++i){
			if(str[i] == '+'){
				if(IsOperator(str[i-1])) continue;
				if(i == 0 || i ==length - 1) continue;
				part
				str = str.substr(0,s) + NumToStr(but1 + but2) + str.substr(e,length-e);
				if(str[0] != '+'){str = "+" + str; ++i;}
				if(str[str.length()-1] != '+') str = str + "+";
				i = s + NumToStr(but1 + but2).length()-1;
				length = str.length();
			}
			else if(str[i] == '-'){
				if(IsOperator(str[i-1])) continue;
				part
				str = str.substr(0,s) + NumToStr(but1 - but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 - but2).length();
				length = str.length();
			}
		}
	}while(!exit);
	for(auto itr{str.begin()};itr != str.end();++itr){
		if(*itr == '+') *itr = ' ';
	}
	str = DeleteBlank(str);
	return str;
}

string operation_number(string str){
	//��ⲿ��
	for(auto itr{str.begin()};itr != str.end();++itr){
		if(IsOperator(*itr) && (IsOperator(*(itr-1)) || IsOperator(*(itr+1))))
			throw "����number����������ظ����֣�";
	}
	//--------
	while(1){
		if(str.find_first_of('(') == string::npos) break;
		auto location_L{str.find_first_of('(')};		//�����ŵ�λ��
		decltype(location_L) location_R{ location_L + 1 };					//�����ŵ�λ��
		unsigned int Num_L{0},Num_R{0};		//�����б��ʽӵ�е�������������������
		for(;location_R < str.length();++location_R){
			if(str[location_R] == '(') Num_L++;
			else if(str[location_R] == ')') Num_R++;
			if(Num_L < Num_R) break;
		}
	    //���õݹ���������б��ʽ��ֵ
		string but{ operation_number(str.substr(location_L+1,location_R-location_L-1)) };
		str = str.substr(0,location_L) + but + str.substr(location_R+1,str.length()-location_R-1);
	}
	return operation_number_without(str);
}
