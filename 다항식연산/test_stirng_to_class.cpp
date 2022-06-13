#include <iostream>
#include <string>
#include <cstdlib>
#define PLUS '+'
#define MINUS '-'
#define MULTI '*'

using namespace std;

class CTerm
{
	int coef, order;
	char vari, oper;
	
public:
	void input(string term);
	void show();
};


void print_error();

void main()
{
	string prb;

	cout<<"프로토 타입"<<endl;
	cout<<"+3x^2*3x^5-4x^3="<<endl;

	cin>>prb;

	char *pr = new char[prb.length()+1];
	strcpy(pr, prb.c_str());

	int opt_cnt=0;

	for(int i=0; i<prb.length(); i++)
	{
		if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI))
			opt_cnt++;
	}

	CTerm *terms = new CTerm[opt_cnt];

	int start=0, j=0;
	do
	{
		int count=0, i;

		for(i=1; i<prb.length(); i++)
		{
			if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI)||(*(pr+i)=='='))
				break;
			else
				count++;
		}
		
		string temp = prb.substr(start, count+1);

		(terms+j)->input(temp);

		start=i;
		pr+=i;
		j++;

		//cout<<start<<" "<<*pr<<" "<<j<<endl;

	}while(*pr!='=');

	for(int i=0; i<opt_cnt; i++)
		(terms+i)->show();

}

void CTerm::input(string term)
{
	//cout<<"input"<<endl;

	char *temp = new char[term.length()+1];

	strcpy(temp, term.c_str());

	oper = *temp;
	//cout<<"oper"<<endl;

	coef = 0;

	int i=1;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm+=*(temp+i);
			coef = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}
	//cout<<"coef"<<endl;

	vari = *(temp+i);
	//cout<<"vari"<<endl;

	order = 0;
	
	if(*(temp+i+1)!='^')
		print_error();
	
	i+=2;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm+=*(temp+i);
			order = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}
	//cout<<"order"<<endl;

	delete[] temp;
}

void CTerm::show()
{
	cout<<oper<<" "<<coef<<" "<<vari<<" "<<order<<endl;
}

void print_error()
{
	cout<<"입력에 잘못된 부분이 있습니다."<<endl;
	exit(1);
}