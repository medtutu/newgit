#include"stdafx.h"
#include<iostream>
#include<string>
#include <iomanip>
#include"stdio.h"
using namespace std;
string iT[20];                           //iT�Ǳ�ʶ��
string cT[20];                             //cT���ַ�
string sT[20];                           //sT���ַ���
string CT[20];                           //CT�ǳ���
string KT[20] = { "int","main","void","if","else","char" };        //KT�ǹؼ���
string PT[20] = { ">=", "<=", "==", "=", ">", "<", "+", "-", "*", "/", "{", "}", ",", ";","(", ")"};    //PT�ǽ��
char ch[20];                     //���ڴ�Ŷ�����ַ�
int token[100];                //���ڴ��token����
string str;
int k = 0,tokeni=0, state,g=0;
int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
int Ischar(char c)                       //�жϽ��յ��ַ��Ƿ�����ĸ
{
	if ((c <= 'z'&&c >= 'a') || (c <= 'Z'&&c >= 'A'))
		return(1);
	else
		return(0);
}
int Isnumber(char c)              //�жϽ��ܵ��ַ��Ƿ�������
{
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
int change(int state, char c)         //״̬ת������
{
	int s, z;
	g = 0;
	s = Isnumber(c);
	z = Ischar(c);
	if (state == 1 && (c == '\n' || c == ' ' || c == '\r'))
	{
		return state;
	}
	/* �жϹؼ��ֺͱ�ʶ�� */
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
			cout << str << "  �ؼ���  " <<"<0"<<i+4<<">"<< endl;
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
				cout << str << " ��ʶ�� " << "<00>" << endl;
			}
			else
			{
				iT[q1] = str;
				cout << str << " ��ʶ�� " <<"<00>"<< endl;
				q1++;
			}
			token[tokeni] = 0; tokeni++;
		}
		g = 1;                          //��־λ��Ϊ1��
		state = 1;
		k = 0;
		return state;
	}

	/* �жϳ��� */
	/* �ж����� */
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
			cout << str << " ���� " <<"<03>"<< endl;
		else
		{
			CT[q2] = str;
			q2++;
			cout << str << " ���� " <<"<03>"<< endl;
		}
		token[tokeni] = 3; tokeni++;
		k = 0;
		state = 1;
		g = 1;
		return state;
	}
	/* �ж�С�� */
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
			cout << str << " ���� " <<"<03>"<< endl;
		else
		{
			CT[q2] = str;
			q2++;
			cout << str << " ���� " <<"<03>"<< endl;
		}
		token[tokeni] = 3; tokeni++;
		g = 1;
		state = 1;
		k = 0;
		return state;
	}
	/* �ж��ַ� */
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
			cout << str << " �ַ� " <<"<01>"<< endl;
		else
		{
			cT[q3] = str;
			q3++;
			cout << str << " �ַ� " <<"<01>"<< endl;
		}
		token[tokeni] = 1; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* �ж��ַ��� */
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
			cout << str << " �ַ��� " <<"<02>"<< endl;
		}
		else
		{
			sT[q4] = str;
			q4++;
			cout << str << " �ַ��� " <<"<02>"<< endl;
		}
		token[tokeni] = 2; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* �жϽ�� */
	/* �ж�>=��> */
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* �ж�<=��< */
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* �ж�==��= */
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
		token[tokeni] = i + 10; tokeni++;
		state = 1;
		g = 1;
		k = 0;
		return state;
	}
	/* �жϽ��---------- "(" ")" "{" "}" "[" "]" "," ";" "*" "+" "/" "-" ----------*/
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
		cout << str << " ��� " <<"<"<<i+10<<">"<< endl;
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
    cout << "token���У�" << endl;
	for (j = 0; j < tokeni; j++)
	{
		cout.fill('0');
		cout << "<" << setw(2) << token[j] << ">";
	}
	system("pause");
	return 0;
}












