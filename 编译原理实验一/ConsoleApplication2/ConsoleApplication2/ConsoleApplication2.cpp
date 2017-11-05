#include"stdafx.h"
#include<iostream>
#include<string>
#include <iomanip>
#include"stdio.h"
using namespace std;
string iT[20];                           //iT是标识符
string cT[20];                             //cT是字符
string sT[20];                           //sT是字符串
string CT[20];                           //CT是常数
string KT[20] = { "int","main","void","if","else","char" };        //KT是关键字
string PT[20] = { ">=", "<=", "==", "=", ">", "<", "+", "-", "*", "/", "{", "}", ",", ";","(", ")"};    //PT是界符
char ch[20];                     //用于存放读入的字符
int token[100];                //用于存放token序列
string str;
int k = 0,tokeni=0, state,g=0;
int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
int Ischar(char c)                       //判断接收的字符是否是字母
{
	if ((c <= 'z'&&c >= 'a') || (c <= 'Z'&&c >= 'A'))
		return(1);
	else
		return(0);
}
int Isnumber(char c)              //判断接受的字符是否是数字
{
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
int change(int state, char c)         //状态转换函数
{
	int s, z;
	g = 0;
	s = Isnumber(c);
	z = Ischar(c);
	if (state == 1 && (c == '\n' || c == ' ' || c == '\r'))
	{
		return state;
	}
	/* 判断关键字和标识符 */
	if (state == 1 && z == 1)
	{
		state = 2;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 2 && (s == 1 || z == 1))
	{
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 2 && s == 0 && z == 0)
	{
		ch[k] = '\0';
		str = ch;
		int i, p = 0;
		for (i = 0; i<20; i++)
		{
			if (str == KT[i])
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
		{
			cout << str << "  关键字  " <<"<0"<<i+4<<">"<< endl;
			token[tokeni] = i + 4; tokeni++;
		}
		else
		{
			for (i = 0; i<20; i++)
			{
				if (str == iT[i])
				{
					p = 1;
					break;
				}
			}
			if (p == 1)
			{
				cout << str << " 标识符 " << "<00>" << endl;
			}
			else
			{
				iT[q1] = str;
				cout << str << " 标识符 " <<"<00>"<< endl;
				q1++;
			}
			token[tokeni] = 0; tokeni++;
		}
		g = 1;                          //标志位置为1；
		state = 1;
		k = 0;
		return state;
	}

	/* 判断常数 */
	/* 判断整数 */
	if (state == 1 && s == 1)
	{
		state = 3;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 3 && s == 1)
	{
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 3 && s == 0)
	{
		ch[k] = '\0';
		str = ch;
		int i, p = 0;
		for (i = 0; i<20; i++)
		{
			if (CT[i] == str)
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
			cout << str << " 常数 " <<"<03>"<< endl;
		else
		{
			CT[q2] = str;
			q2++;
			cout << str << " 常数 " <<"<03>"<< endl;
		}
		token[tokeni] = 3; tokeni++;
		k = 0;
		state = 1;
		g = 1;
		return state;
	}
	/* 判断小数 */
	if (state == 3 && c == '.')
	{
		state = 8;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 8 && s == 1)
	{
		state = 7;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 7 && s == 1)
	{
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 7 && s == 0)
	{
		ch[k] = '\0';
		str = ch;
		int i, p;
		for (i = 0; i<20; i++)
		{
			if (CT[i] == str)
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
			cout << str << " 常数 " <<"<03>"<< endl;
		else
		{
			CT[q2] = str;
			q2++;
			cout << str << " 常数 " <<"<03>"<< endl;
		}
		token[tokeni] = 3; tokeni++;
		g = 1;
		state = 1;
		k = 0;
		return state;
	}
	/* 判断字符 */
	if (state == 1 && c == '\'')
	{
		state = 9;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 9 && z == 1)
	{
		state = 10;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 10 && c == '\'')
	{
		state = 16;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 16)
	{
		ch[k] = '\0';
		string str;
		str = ch;
		int i, p = 0;
		for (i = 0; i<20; i++)
		{
			if (str == cT[i])
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
			cout << str << " 字符 " <<"<01>"<< endl;
		else
		{
			cT[q3] = str;
			q3++;
			cout << str << " 字符 " <<"<01>"<< endl;
		}
		token[tokeni] = 1; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* 判断字符串 */
	if (state == 1 && c == '\"')
	{
		state = 11;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 11 && z == 1)
	{
		state = 12;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 12 && z == 1)
	{
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 12 && c == '\"')
	{
		state = 17;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 17)
	{
		ch[k] = '\0';
		str = ch;
		int i, p=0;
		for (i = 0; i<20; i++)
		{
			if (sT[i] == str)
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
		{
			cout << str << " 字符串 " <<"<02>"<< endl;
		}
		else
		{
			sT[q4] = str;
			q4++;
			cout << str << " 字符串 " <<"<02>"<< endl;
		}
		token[tokeni] = 2; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* 判断界符 */
	/* 判断>=和> */
	if (state == 1 && c == '>')
	{
		state = 4;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 4 && c == '=')
	{
		state = 13;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 4 && (c != '='))
	{
		ch[k] = '\0';
		string str;
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	if (state == 13)
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* 判断<=和< */
	if (state == 1 && c == '<')
	{
		state = 5;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 5 && c == '=')
	{
		state = 14;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 5 && c != '=')
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	if (state == 14)
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* 判断==和= */
	if (state == 1 && c == '=')
	{
		state = 6;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 6 && c == '=')
	{
		state = 15;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 6 && c != '=')
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	if (state == 15)
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i<20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* 判断界符---------- "(" ")" "{" "}" "[" "]" "," ";" "*" "+" "/" "-" ----------*/
	if (state == 1 && (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == '*' || c == '+' || c == '-' || c == '/'))
	{
		state = 18;
		ch[k] = c;
		k++;
		return state;
	}
	if (state == 18)
	{
		ch[k] = '\0';
		str = ch;
		int i;
		for (i = 0; i < 20; i++)
		{
			if (PT[i] == str)
				break;
		}
		cout << str << " 界符 " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		k = 0;
		g = 1;
		return state;
	}
	else
		cout << "err" << endl;
		return 0;
}
int main(void)
{
	int j;
	state = 1;
	char c;
	FILE* fp = NULL;
	fp = fopen("text.txt", "r");
	while ((c = fgetc(fp)) != EOF)
	{
		state = change(state, c);
		if (g == 1)
		{
			state = change(state, c);
		}
	}
	fclose(fp);
    cout << "token序列：" << endl;
	for (j = 0; j < tokeni; j++)
	{
		cout.fill('0');
		cout << "<" << setw(2) << token[j] << ">";
	}
	system("pause");
	return 0;
}












