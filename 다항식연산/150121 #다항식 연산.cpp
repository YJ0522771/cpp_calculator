#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
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
	void show(double coe, int term_num);
	void f_print(double coe, int i);

	int get_coef()								//�ܺ� �Լ����� ������� �о���� �Լ�
	{	return coef;	}						
	int get_order()								//�ܺ� �Լ����� �������� �о���� �Լ�
	{	return order;	}
	char get_oper()								//�ܺ� �Լ����� �����ڸ� �о���� �Լ�
	{	return oper;	}

	void minus_to_plus();						//�����ڰ� -�� ���� ����� ���� ����� ����, �����ڸ� +�� �ٲٴ� �Լ�
	void plus_to_minus();						//������ �����Ŀ��� ���� ����� ������ ���� ����� ���, �����ڸ� -�ٲٴ� �Լ�
	void mul_to_plus(CTerm *other);				//�� ������ ���� ��, �����ڸ� *���� +�� �ٲٴ� �Լ�
	bool cmp_oper_to(CTerm other);				//�� �� ���� �����ڰ� �������� ���θ� Ȯ���ϴ� �Լ�
	bool cmp_order_to(CTerm other);				//�� �� ���� ������ �������� ���θ� Ȯ���ϴ� �Լ�
	bool exist_mul();							//�׿� ���� ��ȣ�� �����ϴ��� Ȯ���ϴ� �Լ�
	bool exist_oper();							//�׿� �����ڰ� �����ϴ��� Ȯ���ϴ� �Լ�

	void add_coef(CTerm other)					//�� �� ���� ����� ���ϴ� �Լ�
	{	coef+=other.coef;	}
	void add_order(CTerm other)					//�� �� ���� ������ ���ϴ� �Լ�
	{	order+=other.order;	}
	void mul_coef(CTerm other)					//�� �� ���� ����� ���ϴ� �Լ�
	{	coef*=other.coef;	}
	void coef_mul_order()						//�̺� ��, ����� ������ ���ϴ� �Լ�
	{	coef*=order;	}
	double coef_div_order()						//���� ��, ����� ������ ������ �Լ�
	{	return (double)coef/order;	}
	void order_one_minus()						//�̺� ��, ������ �ϳ� ���̴� �Լ�
	{	order--;	}
	void order_one_plus()						//���� ��, ������ �ϳ� ���ϴ� �Լ�
	{	order++;	}
	void setNULL()								//������ ���� ���� ǥ���ϱ� ���� �����ڸ� ���
	{	oper=NULL;	}

	friend string cterm_to_string(CTerm *tms, int size);			//CTerm ��ü�� ǥ���� ���� string���� ��ȯ�ϴ� �Լ�

	CTerm & operator =(CTerm &T);									//��ü ���� ������
};

int count_real_terms(CTerm *tms, int size);						//�����ڰ� NULL�� �ƴ� ����ִ� ���� ���� ��
CTerm * sort(CTerm *tms, int size);								//������ ���� ������������ ����
CTerm * multiple(CTerm *terms, int &size);						//��ȣ�� ���� ���� ����
CTerm * addition(CTerm *terms, int &size);						//��ȣ, ���� ��ȣ�� ���� ���� ����
void print_error();												//�������� ���
int count_brk (char *pr);										//�� ���� ��ȣ�� ���� ��
int find(char *str, char c, int n);								//���ڿ����� n��° Ư�� ������ ��ġ�� ��ȯ
void check_next_brk(char *pr, string &prb, int brk_n, char &change);		//��ȣ �� ������ȣ�� ���� ù ���� ������ȣ ������ Ȯ��
string tune_input(string prb);									//�Է¹��� ���� �м� ������ ������ ��ȯ
CTerm * string_to_cterm(string poly, int &size);				//string ���� �� �ϳ� �� CTerm ��ü �ϳ��� ǥ�� 
CTerm * calculation_not_brk(CTerm *poly, int &size);			//��ȣ�� ���� ���� ����
string find_in_brk(string prb, int &n, int &m);					//��ȣ ���νİ� �ֺ� �������� Ȯ���ϰ� �����Ͽ� ��ȯ
void calculation();												//(���� ȣ��)��ü���� ���� �Լ�
void print_result(CTerm *res, int size, string fn_name);		//����� ȭ�鿡 ���
string multiple_poly(string mid, char code);					//���׽ĳ����� ����
void insert_code(int &c);										//������ ����� ����ڷκ��� �Է¹���
void differ(CTerm *poly, int size);								//�̺�
void integ(CTerm *poly, int size);								//����

void main()
{

	calculation();

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
	if((coef<0)&&(oper==PLUS))
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

void CTerm::show(double coe, int term_num)
{
	if((term_num==0)&&(oper=='+'))
		cout<<coe<<vari<<"^"<<order;
	else
		cout<<oper<<coe<<vari<<"^"<<order;
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
	
	CTerm *res = new CTerm[terms];
	
	for(int i=0; i<size; i++)
	{
		if((tms+i)->exist_oper())
		{
			*(res+j) = *(tms+i);
			j++;
		}
	}

	for(int i=0; i<terms; i++)
		for(j=i; j<terms; j++)
			if((res+i)->get_order() < (res+j)->get_order())
			{
				CTerm temp = *(res+i);
				*(res+i) = *(res+j);
				*(res+j) = temp;
			}
	
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

CTerm * calculation_not_brk(CTerm *poly, int &size)
{
	for(int i=0; i<size; i++)
		(poly+i)->minus_to_plus();

	CTerm *pr = multiple(poly,size);

	pr = addition(pr, size);

	pr = sort(pr, size);

	for(int i=0; i<size; i++)
		(pr+i)->plus_to_minus();

	return pr;
}

string find_in_brk(string prb, int &n, int &m)
{
	char code='x';

	if((prb.find('(') >= 0)&&(prb.find(')') <= prb.length()))				//��ȣ ����
	{
		if(prb.substr(prb.find('(')-1, 1) == "*")						//��ȣ �� ������ȣ
		{
			int count=0;

			if((prb.substr(prb.find('(')-2, 1) == ")"))
			{
				code='d';
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if(prb.substr(i, 1)=="(")
					{
						count++;
						break;
					}
				}
			}
			else
			{
				code='f';
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))
					{
						count++;
						break;
					}
				}
			}

			n=prb.find('(') - count;
			m=prb.find(')');
			string mid = prb.substr(n,m-n+1);

			mid=multiple_poly(mid, code);

			return mid;
		}
		else if(prb.substr(prb.find(')')+1, 1) == "*")					//��ȣ �� ������ȣ
		{
			int count=0;
			if(prb.substr(prb.find(')')+2, 1) == "(")
			{
				code='d';
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if(prb.substr(i, 1)==")")
					{
						count++;
						break;
					}
				}
			}
			else
			{
				code='b';
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))
						break;
				}
			}

			n=prb.find('(');
			m=prb.find(')') + count;
			string mid = prb.substr(n, m-n+1);

			mid=multiple_poly(mid, code);

			return mid;
		}
		else
		{
			n=prb.find('(');
			m=prb.find(')');

			string mid = prb.substr(n+1, m-n-1);
			code='n';

			int size=0;

			mid = cterm_to_string(calculation_not_brk(string_to_cterm(mid, size), size), size);
		
			return mid;
		}
	}
	else
		return "not";
}	

void print_error()
{
	cout<<"�Է¿� �߸��� �κ��� �ֽ��ϴ�."<<endl;
	exit(1);
}

int count_brk (char *pr)				//��ȣ ���� ��ȯ
{
	int cnt_open=0, cnt_close=0;

	for(int i=0; i<strlen(pr); i++)
	{
		if(*(pr+i)=='(')
			cnt_open++;
		else if(*(pr+i)==')')
			cnt_close++;
	}

	if(cnt_open==cnt_close)
		return cnt_open;
	else
		print_error();
}			

int find(char *str, char c, int n)			//str ���ڿ����� n��° c���ڸ� ã�� �� ��ġ�� ��ȯ
{
	int count=0;

	for(int i=0; i<strlen(str); i++)
	{
		if((*(str+i))==c)
			count++;
		if(count==n)
			return i;
	}
}

void check_next_brk(char *pr, string &prb, int brk_n, char &change)					//��ȣ ��, ������ ������ȣ �� ������ȣ ����
{																					//brk_n��° ��ȣ�� ����
	int n = find(pr, '(', brk_n), m = find(pr, ')', brk_n);
	
	if(change=='y')					//���� �������� string ���� ��ȭ�� ������ ��� char �����͸� �ٽ� �Ҵ����
	{
		change='n';
		delete[] pr;

		pr = new char[prb.length()+1];
		strcpy(pr, prb.c_str());
		
		n = find(pr, '(', brk_n); 
		m = find(pr, ')', brk_n);
	}

	if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//��ȣ �տ� ������ȣ�� ���� �Ǿ��� ��
	{
		prb.insert(n, "*");
		change = 'y';
	}
		
	if(change=='y')					
	{
		change='n';
		delete[] pr;

		pr = new char[prb.length()+1];
		strcpy(pr, prb.c_str());

		n = find(pr, '(', brk_n); 
		m = find(pr, ')', brk_n);
	}

	if(('0'<= *(pr+n+1))&&('9'>=*(pr+n+1)))				//��ȣ ���� ù �׿� ���� ��ȣ ���� �Ǿ��� ��
	{
		prb.insert(n+1, "+");
		change = 'y';
	}
		
	if(change=='y')					
	{
		change='n';
		delete[] pr;

		pr = new char[prb.length()+1];
		strcpy(pr, prb.c_str());

		n = find(pr, '(', brk_n); 
		m = find(pr, ')', brk_n);
	}

	if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//��ȣ �ڿ� ������ȣ�� ���� �Ǿ��� ��
	{
		prb.insert(m+1, "*");
		change = 'y';
	}
}

string tune_input(string prb)
{
	char *pr = new char[prb.length()+1];					//�� ���꿡 ����ϱ� ���� char ������
	strcpy(pr, prb.c_str());

	char change = 'n';

	if(('1'<=*pr)&&('9'>=*pr))						//���� �� �տ� ������ + ����
	{
		prb.insert(0, "+");
		change = 'y';
	}
	
	if(change=='y')
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());
		}

	int brk_cnt = count_brk(pr);

	if(brk_cnt>0)
		for(int i=0; i<brk_cnt; i++)
			check_next_brk(pr, prb, i+1, change);
	
	delete[] pr;
	
	return prb;
}

string multiple_poly(string mid, char code)
{
	string st1, st2;

	if(code=='f')
	{
		st1=mid.substr(0, mid.find('*'));

		int n=mid.find('('), m=mid.find(')');
		st2 = mid.substr(n+1, m-n-1);
	}
	else if(code=='b')
	{
		int n=mid.find('('), m=mid.find(')');
		st1 = mid.substr(n+1, m-n-1);

		st2=mid.substr(mid.find('*')+1, mid.length()-mid.find('*')-1);
	}
	else if(code=='d')
	{
		char *md=new char[mid.length()+1];
		strcpy(md, mid.c_str());
		
		int n=find(md, '(', 1), m=find(md, ')', 1);
		st1 = mid.substr(n+1, m-n-1);

		n=find(md, '(', 2);
		m=find(md, ')', 2);
		st2 = mid.substr(n+1, m-n-1);
	}

	int size1, size2;

	CTerm *poly1 = string_to_cterm(st1, size1);
	CTerm *poly2 = string_to_cterm(st2, size2);

	poly1=calculation_not_brk(poly1, size1);
	poly2=calculation_not_brk(poly2, size2);

	CTerm *res = new CTerm[size1*size2];

	for(int i=0; i<size1; i++)
		(poly1+i)->minus_to_plus();
	for(int i=0; i<size2; i++)
		(poly2+i)->minus_to_plus();

	int k=0;
	for(int i=0; i<size2; i++)
	{
		for(int j=0; j<size1; j++)
		{
			*(res+k)=*(poly2+i);
			(res+k)->mul_coef(*poly1);
			(res+k)->add_order(*poly1);
			k++;
		}
	}

	for(int i=0; i<size1*size2; i++)
		(res+i)->plus_to_minus();

	return cterm_to_string(res, size1*size2);	
}

CTerm * string_to_cterm(string poly, int &size)
{
	string prb=poly+'@';
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
			if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI)||(*(pr+i)=='@'))
				break;
			else
				count++;
		}
		
		string temp = prb.substr(start, count+1);

		(terms+j)->input(temp);

		start+=i;
		pr+=i;
		j++;

	}while(j!=opt_cnt);

	size=opt_cnt;

	return terms;
}

string cterm_to_string(CTerm *tms, int size)
{
	string res;

	for(int i=0; i<size; i++)
	{
		char *pt=new char[5];
		res+=(tms+i)->oper;

		_itoa((tms+i)->coef, pt, 10);
		res+=pt;

		res+=(tms+i)->vari;
		res+="^";

		_itoa((tms+i)->order, pt, 10);
		res+=pt;
	}

	return res;
}

void CTerm::input(string term)
{
	char *temp = new char[term.length()+1];

	strcpy(temp, term.c_str());

	oper = *temp;

	coef = 0;

	int i=1;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm=*(temp+i);

			if(coef!=0)
				coef = (coef*10)+atoi(tm.c_str());
			else
				coef = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}

	vari = *(temp+i);

	order = 0;
	
	if((*(temp+i+1)) !='^')
		print_error();
	
	
	i+=2;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm=*(temp+i);

			if(order!=0)
				order = (order*10)+atoi(tm.c_str());
			else
				order = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}

	delete[] temp;
}

void calculation()
{
	string fnt;

	cout<<"$���� ����$"<<endl;
	cout<<"()�� ������ ���� �Լ��� ������ �մϴ�."<<endl;
	cout<<"�Է� �Ŀ� ���� ������ �����ڴ� +, -, * �Դϴ�."<<endl;
	cout<<"������ � ���ĺ��� �ᵵ ��������� ���� ���� �Լ��� ���� �����մϴ�."<<endl;
	cout<<"�Էµ� ���� �Լ��� ������ �� �ڿ� �������� �����մϴ�."<<endl;
	cout<<"() ���� ������ȣ�� ���� �����մϴ�.(�Է� ���� ���� ����)"<<endl;
	cout<<"() �ߺ�(��ȣ ������ ��ȣ)�� �Ұ����ϸ� ��ȣ�� �ݵ�� �Ұ�ȣ�� ������ּ���."<<endl;
	cout<<"������ ������ �Ұ����մϴ�. ���� 1���װ� ����׵� �ݵ�� ������ ������ �Է����ּ���."<<endl;
	cout<<"���� ���¿� Ŀ�ٶ� ������ ������ �ǵ��� ���ÿ��� ���� ����� �Է��� �������ּ���."<<endl;
	cout<<"ex) 3x^2(2x^6+4x^3)+4x^3\n=> 6x^8+12x^5+4x^3"<<endl<<endl;

	cout<<"������ �Լ�(or ���׽�)�� �Է����ּ���."<<endl;
	
	cout<<"�Լ� �Է� : ";
	cin>>fnt;

	ofstream fout("test.txt", ios::app);

	fout<<endl<<"�Է� �Լ� : "<<fnt<<endl;

	fout.close();

	int start, end;

	string tun = tune_input(fnt);

	string mid = find_in_brk(tun, start, end);

	while(mid!="not")
	{
		tun.replace(start, end-start+1, mid);
		mid = find_in_brk(tun, start, end);
	}

	int len=0;

	for(int i=0; i<fnt.length(); i++)
		if((fnt.substr(i, 1) == "+")||(fnt.substr(i, 1) == "-")||(fnt.substr(i, 1) == "*"))
			len++;

	CTerm *result = new CTerm[len];
	result = calculation_not_brk(string_to_cterm(tun, len), len);

	print_result(result, len, "����");

	while(1)
	{
		int code;

		insert_code(code);

		switch (code)
		{
		case 1: differ(result, len); cin.ignore(); break;
		case 2: integ(result, len); cin.ignore(); break;
		case 3: ; break;
		default: cout<<"�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���."<<endl; break;
		}
	}

}

void print_result(CTerm *res, int size, string fn_name)
{
	string result = cterm_to_string(res, size);

	if(result.substr(0,1)=="+")
		result.erase(0,1);

	cout<<fn_name<<" ��� : "<<result<<endl;

	ofstream fout("test.txt", ios::app);

	fout<<fn_name<<" ��� : "<<result<<endl;

	fout.close();
}

void insert_code(int &c)
{
	cout<<"���� ������� �̺��� ���� ��� 1, ������ ���� ��� 2, �ʱ� ȭ������ ���ư����� 3�� �Է�\n=>";
	
	cin>>c;
}

void differ(CTerm *pol, int size)
{
	CTerm *poly = new CTerm[size];
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		(poly+i)->coef_mul_order();
		(poly+i)->order_one_minus();

		if((poly+i)->get_order()<0)
			size--;
	}

	print_result(poly, size, "�̺�");
}

void integ(CTerm *pol, int size)
{
	double *coef = new double[size];
	CTerm *poly = new CTerm[size];
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		*(coef+i) = (poly+i)->coef_div_order();
		(poly+i)->order_one_plus();
	}

	cout<<"���� ��� : ";
	for(int i=0; i<size; i++)
		(poly+i)->show(*(coef+i), i);
		
	cout<<endl;

	ofstream fout("test.txt", ios::app);

	fout<<"���� ��� : ";

	fout.close();

	for(int i=0; i<size; i++)
		(poly+i)->f_print(*(coef+i), i);

	fout.open("test.txt", ios::app);
	fout<<endl;
	fout.close();
}

void CTerm::f_print(double coe, int i)
{
	ofstream fout("test.txt", ios::app);

	if((i==0)&&(oper=='+'))
		fout<<coe<<vari<<"^"<<order;
	else
		fout<<oper<<coe<<vari<<"^"<<order;

	fout.close();
}