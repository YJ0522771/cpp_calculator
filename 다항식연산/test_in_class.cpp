#include <iostream>
using namespace std;

class Cvar
{
	int coef, order;
	char vari, oper;
	
	//Cvar *next;
public:
	int input(Cvar ob[10]);
	int cal(Cvar ob[10], Cvar res[10], int n);
	void print(Cvar res[10], int n);


};



void main()
{
	Cvar ob, term[10], result[10];
	int n;
	
	n = ob.input(term);

	int res_n = ob.cal(term, result, n);

	ob.print(result, res_n);


	
}

int Cvar::input(Cvar ob[10])
{
	for(int i=0; i<10; i++)
	{
		cin>>ob[i].coef>>ob[i].vari;
		cout<<"^";
		cin>>ob[i].order>>ob[i].oper;

		if(ob[i].oper=='=')
			return i;
	}


}
	
int Cvar::cal(Cvar ob[10], Cvar res[10], int n)
{
	int count=0;
	for(int i=0; i<=n; i++)
	{
		if(ob[i].coef!=0)
		{
			
			res[count].order = ob[i].order;
			res[count].coef = ob[i].coef;
			res[count].vari = ob[i].vari;
		
			for(int j=i+1; j<=n; j++)
			{
				if(ob[i].order==ob[j].order)
				{
					res[i].coef+=ob[j].coef;
					ob[j].coef = 0;
				}
			}
			count++;
		}
	}

	return count;
}

void Cvar::print(Cvar res[10], int n)
{
	for(int i=0; i<n; i++)
	{
		cout<<res[i].coef<<res[i].vari<<"^"<<res[i].order<<endl;
	}
}
		