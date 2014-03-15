#include <math.h>
#include <string>
#include <sstream>
#include "Stack.h"
#define OPSIZE 8
SeqStack<float> OPND;
SeqStack<char> OPTR;
unsigned char Prior[8][8] =
{ // 运算符优先级表 
 //     '+' '-' '*' '/' '(' ')' '#' '^' 
 /*'+'*/'>','>','<','<','<','>','>','<', 
 /*'-'*/'>','>','<','<','<','>','>','<', 
 /*'*'*/'>','>','>','>','<','>','>','<', 
 /*'/'*/'>','>','>','>','<','>','>','<', 
 /*'('*/'<','<','<','<','<','=',' ','<', 
 /*')'*/'>','>','>','>',' ','>','>','>', 
 /*'#'*/'<','<','<','<','<',' ','=','<', 
 /*'^'*/'>','>','>','>','<','>','>','>' 
}; 

char OPSET[OPSIZE]={'+','-','*','/','(',')','#','^'}; //操作符集合

float Operate(float a,char theta, float b)//计算函数Operate
{
	switch(theta)
	{
		case '+': return a+b; 
		case '-': return a-b; 
		case '*': return a*b; 
		case '/': return a/b; 
		case '^': return pow(a,b);
		default : return 0; 
	} 
} 

int ReturnOpOrd(char op,char * SET){
	for(int i=0;i<OPSIZE;i++){
		if(op==SET[i]){
			return i;
		}
	}
	return -1;
}

char precede(char Aop, char Bop)
{ 
 return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)]; 
} 

float EvaluateExpression(string exp){
	OPTR.Push('#');
	char top;
	int i=0;
	size_t idx = 0;
	string str[100];
	while((idx = exp.find_first_of("()+-*/^#", idx)) != string::npos){
		exp.insert(idx," ");
		exp.insert(idx+2," ");
		idx+=2;
	}
	istringstream iss(exp);
	while (iss>>str[i++])
	{
	}
	i=0;
	while (str[i]!="#"|| OPTR.GetTop()!='#')
	{
		if(ReturnOpOrd(str[i].c_str()[0],OPSET)==-1){
			OPND.Push(atof(str[i].c_str()));
			i++;
		}
		else{
			top=OPTR.GetTop();
			switch (precede(top,str[i].c_str()[0]))
			{
			case '<':
				OPTR.Push(str[i].c_str()[0]);i++;
				break;
			case '=':
				OPTR.Pop();i++;
				break;
			case '>':
				char theta;
				float a,b;
				theta = OPTR.Pop();
				b=OPND.Pop();a=OPND.Pop();
				OPND.Push(Operate(a,theta,b));
				break;
			}
		}
	}
	return OPND.GetTop();
}
int main(int argc,char **argv){
	string str="1.12+2+33^2#";
	printf("%.3f",EvaluateExpression(str));
}