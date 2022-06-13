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

	int get_coef()								//외부 함수에서 계수값을 읽어오는 함수
	{	return coef;	}						
	int get_order()								//외부 함수에서 차수값을 읽어오는 함수
	{	return order;	}
	char get_oper()								//외부 함수에서 연산자를 읽어오는 함수
	{	return oper;	}

	void minus_to_plus();						//연산자가 -인 항을 계산을 위해 계수를 음수, 연산자를 +로 바꾸는 함수
	void plus_to_minus();						//연산이 끝난식에서 음수 계수를 가지는 항을 계수를 양수, 연산자를 -바꾸는 함수
	void mul_to_plus(CTerm *other);				//항 끼리의 곱셈 뒤, 연산자를 *에서 +로 바꾸는 함수
	bool cmp_oper_to(CTerm other);				//두 개 항의 연산자가 같은지의 여부를 확인하는 함수
	bool cmp_order_to(CTerm other);				//두 개 항의 차수가 같은지의 여부를 확인하는 함수
	bool exist_mul();							//항에 곱셈 기호가 존재하는지 확인하는 함수
	bool exist_oper();							//항에 연산자가 존재하는지 확인하는 함수

	void add_coef(CTerm other)					//두 개 항의 계수는 더하는 함수
	{	coef+=other.coef;	}
	void add_order(CTerm other)					//두 개 항의 차수를 더하는 함수
	{	order+=other.order;	}
	void mul_coef(CTerm other)					//두 개 항의 계수를 곱하는 함수
	{	coef*=other.coef;	}
	void coef_mul_order()						//미분 시, 계수와 차수를 곱하는 함수
	{	coef*=order;	}
	double coef_div_order()						//적분 시, 계수를 차수로 나누는 함수
	{	return (double)coef/order;	}
	void order_one_minus()						//미분 시, 차수를 하나 줄이는 함수
	{	order--;	}
	void order_one_plus()						//적분 시, 차수를 하나 더하는 함수
	{	order++;	}
	void setNULL()								//연산이 끝난 항을 표시하기 위해 연산자를 비움
	{	oper=NULL;	}

	friend string cterm_to_string(CTerm *tms, int size);			//CTerm 객체로 표현된 항을 string으로 변환하는 함수

	CTerm & operator =(CTerm &T);									//객체 대입 연산자
};

int count_real_terms(CTerm *tms, int size);						//연산자가 NULL이 아닌 살아있는 항의 수를 셈
CTerm * sort(CTerm *tms, int size);								//차수에 따른 내림차순으로 정렬
CTerm * multiple(CTerm *terms, int &size);						//괄호가 없는 식의 곱셈
CTerm * addition(CTerm *terms, int &size);						//괄호, 곱셈 기호가 없는 식의 덧셈
void print_error();												//에러구문 출력
int count_brk (char *pr);										//식 내의 괄호의 수를 셈
int find(char *str, char c, int n);								//문자열에서 n번째 특정 문자의 위치를 반환
void check_next_brk(char *pr, string &prb, int brk_n, char &change);		//괄호 옆 곱셈기호나 내부 첫 항의 덧셈기호 생략을 확인
string tune_input(string prb);									//입력받은 식을 분석 가능한 구조로 변환
CTerm * string_to_cterm(string poly, int &size);				//string 식을 항 하나 당 CTerm 객체 하나로 표현 
CTerm * calculation_not_brk(CTerm *poly, int &size);			//괄호가 없는 식의 연산
string find_in_brk(string prb, int &n, int &m);					//괄호 내부식과 주변 곱셈항을 확인하고 연산하여 반환
void calculation();												//(메인 호출)전체적인 동작 함수
void print_result(CTerm *res, int size, string fn_name);		//결과를 화면에 출력
string multiple_poly(string mid, char code);					//다항식끼리의 곱셈
void insert_code(int &c);										//동작할 기능을 사용자로부터 입력받음
void differ(CTerm *poly, int size);								//미분
void integ(CTerm *poly, int size);								//적분

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

	if((prb.find('(') >= 0)&&(prb.find(')') <= prb.length()))				//괄호 유무
	{
		if(prb.substr(prb.find('(')-1, 1) == "*")						//괄호 앞 곱셈기호
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
		else if(prb.substr(prb.find(')')+1, 1) == "*")					//괄호 뒤 곱셈기호
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
	cout<<"입력에 잘못된 부분이 있습니다."<<endl;
	exit(1);
}

int count_brk (char *pr)				//괄호 갯수 반환
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

int find(char *str, char c, int n)			//str 문자열에서 n번째 c문자를 찾아 그 위치를 반환
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

void check_next_brk(char *pr, string &prb, int brk_n, char &change)					//괄호 옆, 생략된 곱셈기호 및 덧셈기호 삽입
{																					//brk_n번째 괄호에 대한
	int n = find(pr, '(', brk_n), m = find(pr, ')', brk_n);
	
	if(change=='y')					//앞의 과정에서 string 식의 변화가 생겼을 경우 char 포인터를 다시 할당받음
	{
		change='n';
		delete[] pr;

		pr = new char[prb.length()+1];
		strcpy(pr, prb.c_str());
		
		n = find(pr, '(', brk_n); 
		m = find(pr, ')', brk_n);
	}

	if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//괄호 앞에 곱셈기호가 생략 되었을 때
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

	if(('0'<= *(pr+n+1))&&('9'>=*(pr+n+1)))				//괄호 내부 첫 항에 덧셈 기호 생략 되었을 때
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

	if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//괄호 뒤에 곱셈기호가 생략 되었을 때
	{
		prb.insert(m+1, "*");
		change = 'y';
	}
}

string tune_input(string prb)
{
	char *pr = new char[prb.length()+1];					//비교 연산에 사용하기 위한 char 포인터
	strcpy(pr, prb.c_str());

	char change = 'n';

	if(('1'<=*pr)&&('9'>=*pr))						//식의 맨 앞에 생략된 + 삽입
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

	cout<<"$주의 사항$"<<endl;
	cout<<"()를 포함한 다항 함수의 연산을 합니다."<<endl;
	cout<<"입력 식에 포함 가능한 연산자는 +, -, * 입니다."<<endl;
	cout<<"변수는 어떤 알파벳을 써도 상관없으나 단일 변수 함수만 연산 가능합니다."<<endl;
	cout<<"입력된 다항 함수의 연산을 한 뒤에 미적분이 가능합니다."<<endl;
	cout<<"() 옆의 곱셈기호는 생략 가능합니다.(입력 여부 관계 없음)"<<endl;
	cout<<"() 중복(괄호 내부의 괄호)은 불가능하며 괄호는 반드시 소괄호를 사용해주세요."<<endl;
	cout<<"차수는 음수가 불가능합니다. 또한 1차항과 상수항도 반드시 변수와 차수를 입력해주세요."<<endl;
	cout<<"식의 형태에 커다란 제약은 없지만 되도록 예시에서 많이 벗어나는 입력은 자제해주세요."<<endl;
	cout<<"ex) 3x^2(2x^6+4x^3)+4x^3\n=> 6x^8+12x^5+4x^3"<<endl<<endl;

	cout<<"연산할 함수(or 다항식)을 입력해주세요."<<endl;
	
	cout<<"함수 입력 : ";
	cin>>fnt;

	ofstream fout("test.txt", ios::app);

	fout<<endl<<"입력 함수 : "<<fnt<<endl;

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

	print_result(result, len, "연산");

	while(1)
	{
		int code;

		insert_code(code);

		switch (code)
		{
		case 1: differ(result, len); cin.ignore(); break;
		case 2: integ(result, len); cin.ignore(); break;
		case 3: ; break;
		default: cout<<"잘못된 입력입니다. 다시 입력해주세요."<<endl; break;
		}
	}

}

void print_result(CTerm *res, int size, string fn_name)
{
	string result = cterm_to_string(res, size);

	if(result.substr(0,1)=="+")
		result.erase(0,1);

	cout<<fn_name<<" 결과 : "<<result<<endl;

	ofstream fout("test.txt", ios::app);

	fout<<fn_name<<" 결과 : "<<result<<endl;

	fout.close();
}

void insert_code(int &c)
{
	cout<<"연산 결과식의 미분을 원할 경우 1, 적분을 원할 경우 2, 초기 화면으로 돌아가려면 3을 입력\n=>";
	
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

	print_result(poly, size, "미분");
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

	cout<<"적분 결과 : ";
	for(int i=0; i<size; i++)
		(poly+i)->show(*(coef+i), i);
		
	cout<<endl;

	ofstream fout("test.txt", ios::app);

	fout<<"적분 결과 : ";

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