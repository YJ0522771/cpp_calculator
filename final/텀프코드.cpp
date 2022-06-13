#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <process.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAX  100
#define PLUS '+'
#define MINUS '-'
#define MULTI '*'

//		<조원>

//	2009037353 장 성 규
//	2011104313 조 해 윤
//	2012104134 박 홍 휘
//	2013020050 조 유 진


//사칙연산을 위한 class

template<typename T> // 어떠한 값이라도 입력받기위해 템플릿으로 변수 선언

class Stack //후위연산을 위한 stack이라는 클래스 선언
{
public:

  struct list
 {
  list()
  {};
  
  list(T ele)
  {
   element = ele;
  }

   T element;
  list* next;

  };


  Stack()
 {
  head = NULL;
  tail = NULL;
  initstack();
 }

 ~Stack()
 {
  clear();
 }


  void initstack()
 {
  if (head != NULL)
   clear();

  head = new list();
  tail = new list();
  head->next = tail;
  tail->next = head;
 }

  T checkTop()
 {
  if (head->next == tail)
   return 0;

  list* temp = head->next;
  T etemp = temp->element;
  
  return etemp;

 }

  T pop()
 {
  if (head->next == tail)
   return 0;

  list* tpop = head->next;
  head->next = tpop->next;

  T temp = tpop->element;

  delete tpop;
  return temp;

  }

 void push(T ele)
 {
  list* tpush = new list(ele);
  list* temp = head->next;
  head->next = tpush;
  tpush->next = temp;
 }

 void clear()
 {
  while (head->next != tail)
  {
   list* temp = head->next;
   head->next = temp->next;
   delete temp;
  }

  delete head;
  delete tail;
 }

 int isEmpty()
 {
  if (head->next == tail)
   return 1;
  else
   return 0;
 }

 private:
 list* head;
 list* tail;

 };

 class Calcul//후위연산계산을 위한 Calcul이라는 클래스선언
{
public:
  static int j; //숫자 카운트를 위한 static변수 선언

  Calcul(char* formula) 
 {
  
  size = 0;
  ofstream aout("4basic_operator.txt",ios::app);//결과값을 파일에 저장하기 위해 선언

  while (*formula++ != '\0')
  size++;
  size++;
  formula -= size;

  char* middle_formula = new char[size];
  
  memcpy(middle_formula, formula, size);
  
  aout<<"================================================"<<endl;
  aout<<"("<<Calcul::j<<") "<<"계산식 = "<<middle_formula<<endl;

   change_Reverse_Poland(middle_formula);
 }

  char* remove_Space(const char* remove) 
 {
  const char* orgremove = remove;
  int operatorsize = 0;
  trim_size = 0;
  while (*remove != 0)
  {
   if (*remove != ' ')
   {
    trim_size++;
   }
  
   if (*remove == '+' || *remove == '/' || *remove == '*' || *remove == '-')
   {
    operatorsize++;
   }
   remove++;
  }
  char* trimchar = new char[trim_size + 1];
 
  while (*orgremove !=0)
  {
   if (*orgremove != ' ')
    *trimchar++ = *orgremove++;
   else
    orgremove++;
   
  }
  *trimchar = '\0';
  trimchar -= trim_size;
  int element = (operatorsize + operatorsize + 3);
   
  trim_size += element;
  return trimchar;
 }

  int compareOperation(char op)
 {
  if (op == '*' || op == '/')
   return 2;
  else if (op == '+' || op == '-')
   return 1;
  else if (op == '(' )
   return 0;
  else 
   return -1;
 }

  void change_Reverse_Poland(char* middle_formula)
 {
  char* middle_trimformula;
  middle_trimformula = remove_Space(middle_formula);
  reverse_formula = new char[trim_size];
  char* origin_offset = reverse_formula;
  delete[] middle_formula;

   Stack<char> mstack;

 
   while (*middle_trimformula != '\0' && trim_size > 0)
  {
   if (isdigit(*middle_trimformula)||*middle_trimformula == '.')
   {
    *reverse_formula++ = *middle_trimformula++;
   }
   else if (*middle_trimformula == '(')
   {
    mstack.push('(');
    middle_trimformula++;
   }
   else if (*middle_trimformula == ')')
   {
    while (mstack.checkTop() != '(')
    {
     *reverse_formula++ = ' ';
     *reverse_formula++ = mstack.pop();
    }
    if (mstack.checkTop() == '(')
     mstack.pop();
    middle_trimformula++;
   }
   else if (*middle_trimformula == '*' || *middle_trimformula == '/' || *middle_trimformula == '+' || *middle_trimformula == '-')
   {
    *reverse_formula++ = ' ';
    if (!mstack.isEmpty())
    {
     while ((compareOperation(mstack.checkTop())) >= (compareOperation(*middle_trimformula)))
     {
      *reverse_formula++ = mstack.pop();
      *reverse_formula++ = ' ';
     }
     mstack.push(*middle_trimformula);
     middle_trimformula++;
    }
    else
    {

      mstack.push(*middle_trimformula);
     middle_trimformula++;
    }

    }
   else
   {
    delete[] origin_offset;
	cout<<"\n잘못된 입력방식입니다. 다시 입력해주세요.\n";
    return;
   }

   }
  while (!mstack.isEmpty())
  {
   *reverse_formula++ = ' ';
   *reverse_formula++ = mstack.pop();
  }
  *reverse_formula++ = ' ';
  *reverse_formula = '\0';
  
  
  reverse_formula = origin_offset;
  int size = strlen(reverse_formula);
  
  
 // cout<<"\n후위연산 표기수식 \n%s"<<reverse_formula;
  calc_Reverse_Ploand(reverse_formula);
 
 }

  void calc_Reverse_Ploand(char* p_reverse_formula)
 {
  
  ofstream aout("4basic_operator.txt",ios::app);//결과값을 파일에 저장하기 위해 선언

  char* deletepointer = p_reverse_formula;
  double op;
  Stack<double> m_operand;
  
  while (*p_reverse_formula)
  {
   
   if (isdigit(*p_reverse_formula))
   {
    m_operand.push(atof(p_reverse_formula));
    p_reverse_formula = getOp(p_reverse_formula);
   }
   else if (*p_reverse_formula == '+')
   {
    m_operand.push(m_operand.pop() + m_operand.pop());
    p_reverse_formula = getOp(p_reverse_formula);
   }
   else if (*p_reverse_formula == '*')
   {
    m_operand.push(m_operand.pop() * m_operand.pop());
    p_reverse_formula = getOp(p_reverse_formula);
   }
   else if (*p_reverse_formula == '-')
   {
    op = m_operand.pop();
    m_operand.push(m_operand.pop() - op);
    p_reverse_formula = getOp(p_reverse_formula);

    }
   else if (*p_reverse_formula == '/')
   {
    
    op = m_operand.pop();
    if (op != 0)
     m_operand.push(m_operand.pop() / op);
    p_reverse_formula = getOp(p_reverse_formula);
   }
   else
   {
	cout<<"잘못된 입력방식입니다. 다시 입력해주세요. "<<endl;
    delete[] deletepointer;
    return;
   }
   
  }
  
  time_t cur_time;
  struct tm* pTime;

  time(&cur_time);
  pTime = localtime(&cur_time);//현재시간을 계산하기위한 명령문

  double result = m_operand.pop();//결과값을 파일처리하기 위해 다시 선언.
  
  
  cout<<"\n ☞ 계산결과값 = "<<result<<endl;
  aout<<" ☞ "<<"결과값 = "<<result<<endl<<endl;
  aout<<"계산시각 = "<<asctime(pTime)<<endl;

  aout.close();
  Calcul::j++;//몇번째인지 카운트하기 위해 

  delete[] deletepointer;
 }

  char* getOp(char* op)
 {
  
  while (*op++ != ' ');
  
  return op;
 }
private:
 int trim_size;
 unsigned int size;
 
 char* reverse_formula;
 
};

int Calcul::j=1;//정적변수를 1로 초기화하여 파일처리를 위해 카운트

// 미적분을 위한 class

class CTerm
{
	int coef, order;		//계수, 차수
	char vari, oper;		//변수, 연산자	//한 개의 항을 네 개의 요소로 표현
	
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
void insert_code(char &c);										//동작할 기능을 사용자로부터 입력받음
void differ(CTerm *poly, int size);								//미분
void integ(CTerm *poly, int size);								//적분




 
 void main()
{
 char select;
  
 

 cout<<"이 프로그램은 공학용계산기입니다."<<endl;
 cout<<"괄호가 포함된 사칙연산과 미적분을 할 수 있습니다."<<endl;

 while(true)
 {
	cout<<"=================================================================="<<endl;
	cout<<"\n★사칙연산을 하시려면 1을, 미적분계산을 하시려면 2를 입력하세요.★"<<endl;
	cout<<"★지금까지의 결과값을 보시려면 3을 입력하세요.★"<<endl;
	cout<<"★화면청소를 원하시면 c를 입력하세요.★"<<endl;
	cout<<"★프로그램 종료를 원하시면 q를 입력하세요.★"<<endl<<endl;
 
	cout<<"입력 : ";
	cin>>select;
	cin.ignore();


	if(select == '1')
	{ 	 
		char* formula = new char[500];
		char c;
		int index;

		index = 0;
		cout<<"\n『사칙연산 계산기입니다.』";
		cout<<"\n수식을 입력하세요. \n";
		cout<<"사칙연산 (+,-,*,/) 및 () 괄호 계산 가능"<<endl;
		cout<<"프로그램 종료를 원하시면 q를 입력하세요."<<endl;
		cout<<"\n수식입력 : ";

		while ((c = getchar()) != 10 && index<500)
		{
			if (c >= 0 && c < 10)
			{
				c += 48;
			}
			formula[index] = c;
			index++;

		}
 
		formula[index] = 0;
  

		if (*formula == 'q') 
		return;
  
		Calcul cl(formula);
		cl.~Calcul();
		

		delete[] formula;
	}



	else if(select == '2')
	{  
		ofstream fout("differentiation_integration.txt",ios::app);

		time_t cur_time;
		struct tm* pTime;

		time(&cur_time);
		pTime = localtime(&cur_time);//현재시간을 계산하기위한 명령문
	 
		cout<<"\n『미적분 계산기입니다.』"<<endl<<endl;
		
		calculation();

		fout<<"\n계산시각 = "<<asctime(pTime)<<endl;

	}

	else if(select == '3')
	{
		int code;

		cout<<"로그를 출력할 파일 선택"<<endl;
		cout<<"1 : 사칙연산, 2 : 미적분"<<endl;
		cout<<"입력 : "; cin>>code;
		
		if(code==1)
		{
			ifstream fin("4basic_operator.txt", ios::in);
			fin.seekg(0, ios::beg);

			char *st=new char[100];
			fin.getline(st, 100, '\n');

			while(!fin.eof())
			{
				cout<<st<<endl;
				fin.getline(st, 100, '\n');
			}
		}

		else if(code==2)
		{
			ifstream fin("differentiation_integration.txt", ios::in);
			fin.seekg(0, ios::beg);

			char *st=new char[100];
			fin.getline(st, 100, '\n');

			while(!fin.eof())
			{
				cout<<st<<endl;
				fin.getline(st, 100, '\n');
			}
		}

		else
		{
			cout<<"잘못된 입력 방식입니다."<<endl;
		}

	}



	else if(select == 'c')
	{
		system("cls");
	}

	else if(select = 'q')
		exit(1);
	
 }

}


 void CTerm::minus_to_plus()
{
	if(oper==MINUS)				//연산의 편의를 위해 양수의 뺄셈을 음수의 덧셈으로 바꾼다
	{
		oper=PLUS;
		coef*=(-1);
	}
}

void CTerm::plus_to_minus()
{
	if((coef<0)&&(oper==PLUS))			//연산이 끝난 후 계수가 음수이면 뺄셈항으로 고쳐준다
	{
		coef=abs(coef);
		oper=MINUS;
	}
}

void CTerm::mul_to_plus(CTerm *other)
{
	oper=PLUS;							//두 항의 곱셈 후, 결과를 저장한 항은 연산자를 +로
	(*other).setNULL();					//나머지 한 쪽은 항으로서의 기능을 정지하는 의미에서 연산자를 삭제한다
}

bool CTerm::cmp_order_to(CTerm other)
{
	if(order==other.order)					//어느 두 항의 차수가 같으면 true를 반환
		return true;						
	else
		return false;
}

bool CTerm::exist_mul()
{
	if(oper==MULTI)					//해당 항이 곱셈기호를 가지고 있으면 true를 반환
		return true;
	else
		return false;
}

CTerm& CTerm::operator=(CTerm &T)		//CTerm 객체끼리의 대입연산자
{
	oper=T.oper;
	coef=T.coef;
	vari=T.vari;
	order=T.order;

	return *this;
}

bool CTerm::exist_oper()
{
	if((oper==PLUS)||(oper==MINUS)||(oper==MULTI))			//이 항이 제대로 기능을 하고 있는(연산자가 존재하는) 항인지의 여부를 판단
		return true;										//제대로 된 기능을 하고 있으면 true를 반환
	else
		return false;
}

void CTerm::show(double coe, int term_num)					//적분의 계산 결과를 보여주기 위한 함수
{															
	if((term_num==0)&&(oper==PLUS))							//첫 항의 연산자가 +면 생략
		cout<<coe<<vari<<"^"<<order;
	else
		cout<<oper<<coe<<vari<<"^"<<order;	
}

int count_real_terms(CTerm *tms, int size)					//제대로 기능을 하고 있는 항이 몇 개인지 갯수를 반환
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
	
	CTerm *res = new CTerm[terms];					//제대로 기능 중인 항의 갯수만큼 CTerm 포인터에 메모리 할당
	
	for(int i=0; i<size; i++)
	{
		if((tms+i)->exist_oper())					//기능 중인 항이면 새로은 메모리에 대입
		{
			*(res+j) = *(tms+i);
			j++;
		}
	}

	for(int i=0; i<terms; i++)									//차수가 큰 순서대로 정렬
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
		if((terms+i)->exist_mul())						// * 연산자를 가진 항을 찾아 그 옆의 항과 곱셈
		{
			(terms+i)->mul_coef(*(terms+(i-1)));
			(terms+i)->add_order(*(terms+(i-1)));
			(terms+i)->mul_to_plus(terms+(i-1));
			
			count++;									//곱셈을 한 수만큼 전체 항이 줄어드므로 그 수를 카운트
		}

	CTerm *res = new CTerm[size-count];					//계산 결과를 저장하기 위해 남은 항만큼 메모리 할당

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())						//계산 결과만을 담고 있는 CTerm 포인터 생성
		{
			*(res+j) = *(terms+i);
			j++;
		}

	size-=count;											//식의 항 갯수를 수정

	return res;											//결과만이 담긴 포인터 반환
}

CTerm * addition(CTerm *terms, int &size)
{
	int count=0;

	for(int i=0; i<size; i++)
	{
		if((terms+i)->get_oper() == NULL)				//기능 중이 아닌 항이 넘어왔을 경우를 대비한 거름장치
			break;
		for(int j=i+1; j<size; j++)
		{
			if((terms+j)->get_oper() == NULL)
				break;
			if((terms+i)->cmp_order_to(*(terms+j)))		//차수가 같음을 확인하면 덧셈 연산
			{
				(terms+i)->add_coef(*(terms+j));			//계수를 더함
				(terms+j)->setNULL();					//결과가 저장된 항 외에 다른 항의 기능 정지

				count++;								//계산한 횟수만큼 카운트
			}
		}
	}

	CTerm *res = new CTerm[size-count];					//결과 항만큼 메모리 할당

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())
		{
			*(res+j) = *(terms+i);						//결과 항만을 저장한 포인터 생성
			j++;
		}

	size-=count;											//항의 갯수 수정

	return res;											//결과 항만 담긴 포인터 반환
}

CTerm * calculation_not_brk(CTerm *poly, int &size)			//괄호가 없는 다항식 계산
{
	for(int i=0; i<size; i++)								//계산의 편의를 위해 뺄셈 항을 음수 덧셈항으로 변환
		(poly+i)->minus_to_plus();

	CTerm *pr = multiple(poly,size);						//결과를 담을 포인터를 생성하고 곱셈 결과 저장

	pr = addition(pr, size);								//덧셈 연산

	pr = sort(pr, size);									//차수 크기 순으로 정렬

	for(int i=0; i<size; i++)								//음수 덧셈항을 다시 뺄셈항으로 바꿈
		(pr+i)->plus_to_minus();

	return pr;												//결과 반환
}

string find_in_brk(string prb, int &n, int &m)
{
	char code='x';														//괄호가 있어 잡아낸 식이 어떤 형태인지를 알려주는 code변수
																		//괄호가 없을 경우 x
	if((prb.find('(') >= 0)&&(prb.find(')') <= prb.length()))			//괄호 유무 확인
	{
		if(prb.substr(prb.find('(')-1, 1) == "*")						//괄호 앞 곱셈기호를 찾음
		{
			int count=0;

			if((prb.substr(prb.find('(')-2, 1) == ")"))					//곱셈기호 옆에 있는 것이 또 다른 괄호일 경우
			{
				code='d';												//괄호가 두 개라는 의미의 double의 d
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if(prb.substr(i, 1)=="(")							//옆 괄호의 닫히는 부분을 찾음
					{
						count++;
						break;
					}
				}
			}
			else														//곱셈 기호 옆에 있는 것이 하나의 항일 경우
			{
				code='f';												//곱셈항이 괄호의 앞에 있다는 의미의 front의 f
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))	//그 항이 끝나는 지점을 찾음
					{
						count++;
						break;
					}
				}
			}

			n=prb.find('(') - count;
			m=prb.find(')');
			string mid = prb.substr(n,m-n+1);							//찾아낸 괄호와 그 옆 곱셈 부분을 추출

			mid=multiple_poly(mid, code);								//이 둘을 계산하여 결과 반환

			return mid;
		}
		else if(prb.substr(prb.find(')')+1, 1) == "*")					//괄호 뒤 곱셈기호
		{
			int count=0;
			if(prb.substr(prb.find(')')+2, 1) == "(")					//괄호 위 곱셈 기호 옆에 있는 것이 또다른 괄호
			{
				code='d';												//괄호가 두 개임을 알리는 코드
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if(prb.substr(i, 1)==")")							//닫히는 위치를 찾음
					{
						count++;
						break;
					}
				}
			}
			else														//괄호 뒤 곱셈기호 옆에 하나의 항일 경우
			{
				code='b';												//곱셈 항이 괄호의 뒤에 있단 의미의 back의 b
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))	//항이 끝나는 지점을 찾음
						break;
				}
			}

			n=prb.find('(');
			m=prb.find(')') + count;
			string mid = prb.substr(n, m-n+1);

			mid=multiple_poly(mid, code);								//계산하여 반환

			return mid;
		}
		else															//괄호 옆에 곱셈이 없을 경우
		{
			n=prb.find('(');
			m=prb.find(')');

			string mid = prb.substr(n+1, m-n-1);							//괄호 내부 추출
			code='n';													//곱셈이 없단 의미의 not의 n

			int size=0;

			mid = cterm_to_string(calculation_not_brk(string_to_cterm(mid, size), size), size);		//괄호 내부 연산 후 반환
		
			return mid;
		}
	}
	else
		return "not";			//괄호가 없으면 문자열 not을 반환
}	

void print_error()									//입력이 잘못될 경우 경고문과 함께 재입력
{
	cout<<"입력에 잘못된 부분이 있습니다."<<endl;
	return calculation();					
}

int count_brk (char *pr)					//괄호 갯수 반환
{
	int cnt_open=0, cnt_close=0;

	for(int i=0; i<strlen(pr); i++)
	{
		if(*(pr+i)=='(')					//열리는 괄호의 갯수를 카운트
			cnt_open++;
		else if(*(pr+i)==')')				//닫히는 괄호의 갯수를 카운트
			cnt_close++;
	}

	if(cnt_open==cnt_close)
		return cnt_open;					//괄호 갯수 반환
	else									//닫히는 괄호와 열리는 괄호의 갯수가 일치하지 않을 경우 입력이 잘못됨을 알림
		print_error();
}			

int find(char *str, char c, int n)			//str 문자열에서 n번째 c문자를 찾아 그 위치를 반환
{
	int count=0;

	for(int i=0; i<strlen(str); i++)
	{
		if((*(str+i))==c)					//찾고 있는 문자가 나타날 경우 카운트
			count++;
		if(count==n)						//그 횟수가 찾고있는 n번째와 일치하면 위치 반환
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

	if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//괄호 앞에 곱셈 기호가 생략 되었을 때
	{
		prb.insert(n, "*");									//괄호 앞에 곱셈 기호를 추가하고 식이 변화하였음을 알림
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
		prb.insert(n+1, "+");							//내부 처음 부분에 덧셈 기호를 추가하고 식이 변화하였음을 알림
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

	if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//괄호 뒤에 곱셈 기호가 생략 되었을 때
	{
		prb.insert(m+1, "*");												//괄호 뒤 곱셈 기호를 추가하고 식이 변화하였음을 알림
		change = 'y';
	}
}

string tune_input(string prb)						//연산을 위해 한 항에 연산자, 계수, 변수, 차수 모두를 갖고 있는 형태로 변환
{
	char *pr = new char[prb.length()+1];			//비교 연산에 사용하기 위한 char 포인터
	strcpy(pr, prb.c_str());

	char change = 'n';

	if(('1'<=*pr)&&('9'>=*pr))						//식의 맨 앞에 생략된 덧셈 기호를 삽입하고 식이 변화하였음을 알림
	{
		prb.insert(0, "+");
		change = 'y';
	}
	
	if(change=='y')									//식이 변화하였을 경우 char 포인터를 다시 생성
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());
		}

	int brk_cnt = count_brk(pr);					//괄호의 갯수

	if(brk_cnt>0)
		for(int i=0; i<brk_cnt; i++)				//(i+1)번째 괄호의 옆에 생략된 곱셈이나 덧셈 기호 추가
			check_next_brk(pr, prb, i+1, change);
	
	delete[] pr;
	
	return prb;							//수정된 결과식 반환
}

string multiple_poly(string mid, char code)			//두 다항식의 곱셈
{
	string st1, st2;								//두 다항식을 저장하는 string 변수 둘

	if(code=='f')									//항 하나가 괄호의 앞에 있을 경우
	{
		st1=mid.substr(0, mid.find('*'));			//처음 항을 저장

		int n=mid.find('('), m=mid.find(')');
		st2 = mid.substr(n+1, m-n-1);				//괄호 내부 식을 저장
	}
	else if(code=='b')								//항 하나가 괄호 뒤에 있을 경우
	{
		int n=mid.find('('), m=mid.find(')');
		st1 = mid.substr(n+1, m-n-1);				//괄호 내부 식 저장

		st2=mid.substr(mid.find('*')+1, mid.length()-mid.find('*')-1);		//마지막 항 저장
	}
	else if(code=='d')								//괄호가 두 개일 경우
	{
		char *md=new char[mid.length()+1];
		strcpy(md, mid.c_str());
		
		int n=find(md, '(', 1), m=find(md, ')', 1);		//괄호 내부 식을 각각 저장
		st1 = mid.substr(n+1, m-n-1);

		n=find(md, '(', 2);
		m=find(md, ')', 2);
		st2 = mid.substr(n+1, m-n-1);
	}

	int size1, size2;

	CTerm *poly1 = string_to_cterm(st1, size1);			//저장한 식을 각각 CTerm 으로 변환
	CTerm *poly2 = string_to_cterm(st2, size2);

	poly1=calculation_not_brk(poly1, size1);			//두 식을 각각 계산
	poly2=calculation_not_brk(poly2, size2);

	CTerm *res = new CTerm[size1*size2];				//곱셈 결과를 저장할 CTerm 메모리 할당

	for(int i=0; i<size1; i++)							//식을 계수의 부호 조정
		(poly1+i)->minus_to_plus();
	for(int i=0; i<size2; i++)
		(poly2+i)->minus_to_plus();

	int k=0;
	for(int i=0; i<size2; i++)
	{
		for(int j=0; j<size1; j++)						//항을 각각 곱셈
		{
			*(res+k)=*(poly2+i);
			(res+k)->mul_coef(*poly1);					//계수를 곱하고 차수를 더해서 새로운 메모리에 하나씩 저장
			(res+k)->add_order(*poly1);
			k++;
		}
	}

	for(int i=0; i<size1*size2; i++)
		(res+i)->plus_to_minus();						//조정한 계수의 형태를 다시 되돌림

	return cterm_to_string(res, size1*size2);			//결과를 string으로 변환하여 리턴
}

CTerm * string_to_cterm(string poly, int &size)					//string을 CTerm으로 변환하는 함수
{
	string prb=poly+'@';										//식의 끝을 알리기위한 기호 @를 추가
	char *pr = new char[prb.length()+1];						//비교 연산의 편의를 위한 char 포인터 생성
	strcpy(pr, prb.c_str());

	int opt_cnt=0;

	for(int i=0; i<prb.length(); i++)
	{
		if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI))
			opt_cnt++;											//연산자의 갯수(=항의 수)를 카운트
	}

	CTerm *terms = new CTerm[opt_cnt];							//존재하는 항의 수만큼 CTerm 포인터 메모리 할당

	int start=0, j=0;
	do
	{
		int count=0, i;

		for(i=1; i<prb.length(); i++)
		{
			if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI)||(*(pr+i)=='@'))		//항 하나의 크기를 잡음
				break;
			else
				count++;
		}
		
		string temp = prb.substr(start, count+1);				//크기를 잡은 항 하나를 임시로 저장

		(terms+j)->input(temp);									//CTerm의 형태로 저장

		start+=i;												//다음 항을 잡기 위해 카운트의 시작점을 변환
		pr+=i;													//포인터의 시작점 변환
		j++;													//결과 저장의 번호를 다음으로 변환

	}while(j!=opt_cnt);											//항의 수만큼 저장이 되었으면 반복문 탈출

	size=opt_cnt;												//항의 수 저장

	delete[] pr;

	return terms;												//CTerm 포인터 반환
}

string cterm_to_string(CTerm *tms, int size)		//CTerm 포인터를 string으로 변환
{
	string res;

	for(int i=0; i<size; i++)						//항의 갯수만큼 반복
	{
		char *pt=new char[5];						//_itoa 함수에 사용할 char 포인트
		res+=(tms+i)->oper;							//결과에 연산자 추가

		_itoa((tms+i)->coef, pt, 10);
		res+=pt;									//계수 추가

		res+=(tms+i)->vari;							//변수와 거듭제곱 연산자 ^추가
		res+="^";

		_itoa((tms+i)->order, pt, 10);
		res+=pt;									//차수 추가
	}

	return res;										//결과 반환
}

void CTerm::input(string term)					//하나의 항을 CTerm 포인터로 변환
{
	char *temp = new char[term.length()+1];		//편의를 위한 char 포인터

	strcpy(temp, term.c_str());

	oper = *temp;								//항의 첫번째 문자는 연산자이므로 oper에 저장

	coef = 0;									//계수를 0으로 초기화

	int i=1;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm=*(temp+i);

			if(coef!=0)									//계수가 두 자리 이상을 경우를 위한 장치
				coef = (coef*10)+atoi(tm.c_str());		//두번째 숫자부터는 기존 수에 10을 곱한 다음 더함
			else
				coef = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}

	vari = *(temp+i);							//변수 저장

	order = 0;									//차수를 초기화
	
	if((*(temp+i+1)) !='^')						//변수의 다음 문자가 거듭제곱 연산자가 아닐 경우 입력이 잘못되었음을 알림
		print_error();
	
	
	i+=2;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))				//계수와 같은 원리로 차수 저장
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

void calculation()						//메인에서 호출하기 위한 종합 함수
{
	string fnt;

	cout<<"※주의 사항※"<<endl;
	cout<<"① ()를 포함한 다항 함수의 연산을 합니다."<<endl;
	cout<<"② 입력 식에 포함 가능한 연산자는 +, -, * 입니다."<<endl;
	cout<<"③ 변수는 어떤 알파벳을 써도 상관없으나 단일 변수 함수만 연산 가능합니다."<<endl;
	cout<<"④ 입력된 다항 함수의 연산을 한 뒤에 미적분이 가능합니다."<<endl;
	cout<<"⑤ () 옆의 곱셈기호는 생략 가능합니다.(입력 여부 관계 없음)"<<endl;
	cout<<"⑥ () 중복(괄호 내부의 괄호)은 불가능하며 괄호는 반드시 소괄호를 사용해주세요."<<endl;
	cout<<"⑦ 차수는 음수가 불가능합니다. 또한 1차항과 상수항도 반드시 변수와 차수를 입력해주세요. ex) 5x --> 5x^1"<<endl;
	cout<<"⑧ 식의 형태에 커다란 제약은 없지만, 되도록 예시에서 많이 벗어나는 입력은 자제해주세요."<<endl;
	cout<<"ex) 3x^2(2x^6+4x^3)+4x^3\n => 6x^8+12x^5+4x^3"<<endl<<endl;
	cout<<"ex) 3x^5 + 5\n => 이런식으로 상수항을 입력받을수 없음."<<endl<<endl;
	cout<<"ex) 2x^-5\n => 다음과같이 차수에 음수를 넣을수 없음."<<endl<<endl;
	
	cout<<"연산할 함수(or 다항식)을 입력해주세요."<<endl;
	
	cout<<"함수 입력 : ";													//계산할 식을 입력 받음
	cin>>fnt;
	
	ofstream fout("differentiation_integration.txt", ios::app);				//입력 받은 식을 파일에 쓰기
	
	fout<<"===================================="<<endl;
	fout<<endl<<"입력 함수 : "<<fnt<<endl;

	fout.close();

	int start, end;

	string tun = tune_input(fnt);							//입력 식 형태 조정

	string mid = find_in_brk(tun, start, end);				//괄호를 찾고 내부 식은 연산하여 결과와 해당 부분의 위치를 받음

	while(mid!="not")										//식의 괄호가 사라져 mid에 not을 받을 때까지 반복
	{
		tun.replace(start, end-start+1, mid);				//결과를 해당 위치에 덧씌움
		mid = find_in_brk(tun, start, end);					//괄호 검사
	}

	int len=0;

	for(int i=0; i<fnt.length(); i++)
		if((fnt.substr(i, 1) == "+")||(fnt.substr(i, 1) == "-")||(fnt.substr(i, 1) == "*"))
			len++;														//항의 갯수 카운트

	CTerm *result = new CTerm[len];										//항 저장을 위한 CTerm 포인터 메모리 할당		
	result = calculation_not_brk(string_to_cterm(tun, len), len);		//식을 CTerm으로 바꾸고 이를 넣어 계산

	print_result(result, len, " ☞ 연산");								//연산 결과를 출력

	while(1)
	{
		char code;

		insert_code(code);												//이 다음에 실행할 명령을 입력 받음

		switch (code)
		{
		case '1': differ(result, len); cin.ignore(); return;			//결과 식을 미분
		case '2': integ(result, len); cin.ignore(); return;				//결과 식을 적분
		case 'q': ; exit(1);

		default: cout<<"잘못된 입력입니다. 다시 입력해주세요."<<endl; break;	//잘못된 입력에 대한 경고 구문
		}
	}

	delete[] result;
}

void print_result(CTerm *res, int size, string fn_name)				//결과 출력 함수(연산, 미분)
{
	string result = cterm_to_string(res, size);						//결과를 string으로 변환

	if(result.substr(0,1)=="+")										//맨 앞이 +일 경우 이를 삭제
		result.erase(0,1);

	cout<<endl<<fn_name<<" 결과 : "<<result<<endl;

	ofstream fout("differentiation_integration.txt", ios::app);		//결과를 파일에 씀

	fout<<fn_name<<" 결과 : "<<result<<endl;

	fout.close();
}

void insert_code(char &c)							//switch 구문을 작동할 명령어 입력 함수
{
	cout<<"\n연산 결과식의 미분을 원할 경우 1, 적분을 원할 경우 2를 입력해주세요."<<endl; 
	cout<<"프로그램을 종료하고 싶으시면 q를 입력해주세요."<<endl<<endl;
	cout<<"입력 : "; cin>>c;
}

void differ(CTerm *pol, int size)				//미분 함수
{
	CTerm *poly = new CTerm[size];				//받은 식을 임의로 저장할 공간
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		(poly+i)->coef_mul_order();				//차수과 계수를 곱하여 계수에 대입
		(poly+i)->order_one_minus();				//차수를 하나 줄임

		if((poly+i)->get_order()<0)				//상수항을 미분한 경우(차수 -1)
			size--;								//항을 삭제
	}

	print_result(poly, size, " ☞ 미분");		//결과 출력

	delete[] poly;
}

void integ(CTerm *pol, int size)				//적분 함수
{
	double *coef = new double[size];			//계수 저장을 위한 double 포인터 메모리
	CTerm *poly = new CTerm[size];				//받은 식을 임의로 저장할 공간
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		*(coef+i) = (poly+i)->coef_div_order();		//계수를 차수로 나눔
		(poly+i)->order_one_plus();					//차수를 하나 줄임
	}

	cout<<endl<<" ☞ 적분 결과 : ";
	for(int i=0; i<size; i++)
		(poly+i)->show(*(coef+i), i);				//결과 출력. 단, 계수로는 기존 계수가 아닌 새로 만든 double형 포인터에 저장한 계수를 불러옴
		
	cout<<" + C(적분상수)"<<endl;

	ofstream fout("differentiation_integration.txt", ios::app);		//결과를 파일에 쓰기

	fout<<" ☞ 적분 결과 : ";

	fout.close();

	for(int i=0; i<size; i++)
		(poly+i)->f_print(*(coef+i), i);

	fout.open("differentiation_integration.txt", ios::app);
	fout<<" + C(적분상수)"<<endl;
	fout.close();

	delete[] poly;
	delete[] coef;
}

void CTerm::f_print(double coe, int i)				//적분 결과를 파일에 쓰기 위한 함수
{
	ofstream fout("differentiation_integration.txt", ios::app);

	if((i==0)&&(oper=='+'))							//첫 글자가 +이면 이를 출력하지 않음
		fout<<coe<<vari<<"^"<<order;
	else
		fout<<oper<<coe<<vari<<"^"<<order;

	fout.close();
}