#include <iostream>
#include <string>
#define PLUS '+'
#define MINUS '-'
#define MULTI '*'

using namespace std;

class CTerm
{
	int coef, order;
	char vari, oper;
	
public:
	//void input(string term);
	void show();
	
	CTerm(char p, int c, char v, int o):coef(c), order(o), vari(v), oper(p) {}
	CTerm() {}

	int get_coef() 
	{	return coef;	}
	int get_order()
	{	return order;	}
	char get_oper()
	{	return oper;	}

	void minus_to_plus();
	void plus_to_minus();
	void mul_to_plus(CTerm *other);
	bool cmp_oper_to(CTerm other);
	bool cmp_order_to(CTerm other);
	bool exist_mul();
	bool exist_oper();

	void add_coef(CTerm other)
	{	coef+=other.coef;	}
	void add_order(CTerm other)
	{	order+=other.order;	}
	void mul_coef(CTerm other)
	{	coef*=other.coef;	}
	void setNULL()
	{	oper=NULL;	}
	
	CTerm & operator =(CTerm &T);
	

};

int count_real_terms(CTerm *tms, int size);
CTerm * sort(CTerm *tms, int size);
CTerm * multiple(CTerm *terms, int &size);
CTerm * addition(CTerm *terms, int &size);
void show_poly(CTerm *st, int size);

void main()
{
	CTerm st[]={CTerm('+',3,'x',2), CTerm('*',7,'x',4), CTerm('-',4,'x',2), CTerm('-',3,'x',6),CTerm('+',3,'x',3)};

	int size=5;

	for(int i=0; i<size; i++)
		st[i].minus_to_plus();

	CTerm *pr = multiple(st,size);
	//cout<<"mul"<<endl;

	pr = addition(pr, size);
	//cout<<"add"<<endl;

	//show_poly(pr, size);

	pr = sort(pr, size);
	//cout<<"sort"<<endl;

	show_poly(pr, size);
	
}

void CTerm::minus_to_plus()
{
	if(oper==MINUS)
	{
		oper=PLUS;
		coef*=(-1);
	}
}

void CTerm::plus_to_minus()
{
	if(coef<0)
	{
		coef=abs(coef);
		oper=MINUS;
	}
}

void CTerm::mul_to_plus(CTerm *other)
{
	oper=PLUS;
	(*other).setNULL();
}

bool CTerm::cmp_oper_to(CTerm other)
{
	if(oper==other.oper)
		return true;
	else
		return false;
}

bool CTerm::cmp_order_to(CTerm other)
{
	if(order==other.order)
		return true;
	else
		return false;
}

bool CTerm::exist_mul()
{
	if(oper==MULTI)
		return true;
	else
		return false;
}

CTerm& CTerm::operator=(CTerm &T)
{
	oper=T.oper;
	coef=T.coef;
	vari=T.vari;
	order=T.order;

	return *this;
}

bool CTerm::exist_oper()
{
	if((oper==PLUS)||(oper==MINUS)||(oper==MULTI))
		return true;
	else
		return false;
}

void CTerm::show()
{
	cout<<oper<<" "<<coef<<" "<<vari<<" "<<order<<endl;
}

int count_real_terms(CTerm *tms, int size)
{
	int count=0;

	for(int i=0; i<size; i++)
		if((tms+i)->exist_oper())
			count++;

	return count;
}

CTerm * sort(CTerm *tms, int size)
{
	int terms = count_real_terms(tms, size), j=0;
	//cout<<"count"<<endl;
	
	CTerm *res = new CTerm[terms];
	//cout<<"new"<<endl;
	
	for(int i=0; i<size; i++)
	{
		if((tms+i)->exist_oper())
		{
			*(res+j) = *(tms+i);
			j++;
		}
	}

	//cout<<"이동"<<endl;

	for(int i=0; i<terms; i++)
		for(j=i; j<terms; j++)
			if((res+i)->get_order() < (res+j)->get_order())
			{
				CTerm temp = *(res+i);
				*(res+i) = *(res+j);
				*(res+j) = temp;
			}
	//cout<<"정렬"<<endl;

	//delete[] tms;

	//tms = res;

	return res;
}

CTerm * multiple(CTerm *terms, int &size)
{
	int count=0;

	for(int i=0; i<size; i++)
		if((terms+i)->exist_mul())
		{
			(terms+i)->mul_coef(*(terms+(i-1)));
			(terms+i)->add_order(*(terms+(i-1)));
			(terms+i)->mul_to_plus(terms+(i-1));
			
			count++;
		}

	CTerm *res = new CTerm[size-count];

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())
		{
			*(res+j) = *(terms+i);
			j++;
		}

	//delete[] terms;
	
	//terms = res;
	size-=count;

	return res;
}

CTerm * addition(CTerm *terms, int &size)
{
	int count=0;

	for(int i=0; i<size; i++)
	{
		if((terms+i)->get_oper() == NULL)
			break;
		for(int j=i+1; j<size; j++)
		{
			if((terms+j)->get_oper() == NULL)
				break;
			if((terms+i)->cmp_order_to(*(terms+j)))
			{
				(terms+i)->add_coef(*(terms+j));
				(terms+j)->setNULL();

				count++;
			}
		}
	}

	CTerm *res = new CTerm[size-count];

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())
		{
			*(res+j) = *(terms+i);
			j++;
		}

	//delete[] terms;
	
	//terms = res;
	size-=count;

	return res;
}

void show_poly(CTerm *st, int size)
{
	for(int i=0; i<size; i++)
		if(st[i].exist_oper())
			st[i].show();
}