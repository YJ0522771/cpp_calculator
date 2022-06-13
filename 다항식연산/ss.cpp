#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;

#define MAX  50


//사칙연산을 위한 class

template<typename T>

class Stack
{
public:

	 struct list
	{
		 list() {};
  
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

  T cehckTop()
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

 class Calcul
{
public:

  Calcul(char* formula) 
 {
  
  size = 0;
  
  while (*formula++ != '\0')
  size++;
  size++;
  formula -= size;

  char* middle_formula = new char[size];
  
  memcpy(middle_formula, formula, size);

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
    while (mstack.cehckTop() != '(')
    {
     *reverse_formula++ = ' ';
     *reverse_formula++ = mstack.pop();
    }
    if (mstack.cehckTop() == '(')
     mstack.pop();
    middle_trimformula++;
   }
   else if (*middle_trimformula == '*' || *middle_trimformula == '/' || *middle_trimformula == '+' || *middle_trimformula == '-')
   {
    *reverse_formula++ = ' ';
    if (!mstack.isEmpty())
    {
     while ((compareOperation(mstack.cehckTop())) >= (compareOperation(*middle_trimformula)))
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
    printf("\n잘못된 입력방식입니다. 다시 입력해주세요.\n");
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
  
  cout<<"\n\n★★★계산결과값 = "<<m_operand.pop()<<"★★★"<<endl;
 
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

// 미적분을 위한 class
class dcalcul{
private :
int n; //n차식
int i,j;//배열
double a;
double b;
double c;
double d;
public:
	void adegree( );//1차식 미분 함수
	void bdegree( );//2차식 미분 함수
	void cdegree( );//3차식 미분 함수
	void ddiscreminent( );//1,2,3차 식 판별식 함수
	double result[2][21];//(0~20 까지 배열)
};//미분 관련 class

void dcalcul::ddiscreminent() //1,2,3,차식 판별식
{ cout<<"1,2,3차 식 중 몇 차식을 미분하고 싶으십니까?"<<endl;
  cin>>n;//n은 차수
  switch(n){
case 1: // 차수가 1이라면
	  adegree();//1차식 미분 함수
	  break;
case 2:// 차수가 2이라면
	  bdegree();//2차식 미분 함수
	  break;
case 3:// 차수가 3이라면
	  cdegree( );//3차식 미분 함수
	  break;
default:
	cout<<"계산 불가 (3차식까지 가능 합니다.)"<<endl;
	ddiscreminent();//다시 1,2,3 차식 판별식으로 되돌아가 가기 위해 삽입
  }
} // switch 문 사용해서 판별식 만듬

void dcalcul::adegree() //1차식
{
	cout<<"f(x)=ax+b이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	
	cout<<"\n★★f'(x)="<<a<<"입니다.★★"<<endl;

	
}


void dcalcul::bdegree() //2차식
{
	cout<<"f(x)=ax^2+bx+c이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	cout<<"계수c를 입력하시오"<<endl;
	cin>>c;
	double e=a*2; 
	cout<<"\n★★f'(x)="<<e<<"x + "<<b<<"입니다.★★"<<endl;
	
}
void dcalcul::cdegree()//3차식 미분
{
	cout<<"f(x)=ax^3+bx^2+cx+d이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	cout<<"계수c를 입력하시오"<<endl;
	cin>>c;
	cout<<"계수d를 입력하시오"<<endl;
	cin>>d;
	double e=3*a;
	double f=2*b;
	cout<<"\n★★f'(x)="<<e<<"x^2 + "<<f<<"x + "<<c<<"입니다.★★"<<endl;
	
}

class icalcul{
private :
int n;//1,2,3 차식을 나타냄
int i,j; //i는 행 i는 열을 나타냄
double a;//계수
double b;//계수
double c;//계수
double d;//계수
public:
	void edegree( );//1차식 적분
	void fdegree( );//2차식 적분
	void gdegree( );//3차식 적분
	void idiscreminent( );//1,2,3차 적분 판별
	double result[2][21];
};//적분 관련 class

void icalcul::idiscreminent()//1,2,3차 적분 판별
{ cout<<"1,2,3차 식 중 몇 차식을 적분하고 싶으싶니까?"<<endl;
  cin>>n;
  switch(n){ //n은 차수
case 1://차수가 1이라면
	  edegree();//1차식 적분
	  break;
case 2://차수가 2이라면
	  fdegree();//2차식 적분
	  break;
case 3:// 차수가 3이라면
	  gdegree( );//3차식 적분
	  break;
default:
	cout<<"계산 불가 (3차식까지 가능 합니다.)"<<endl;
	idiscreminent();//다시 1,2,3 차식 판별식으로 되돌아가 가기 위해 삽입
  }
  }

void icalcul::edegree()//1차식 적분
{
	cout<<"f(x)=ax+b이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	double e = a/2;
	cout<<"\n★★∫f(x)dx="<<e<<"x^2 + "<<b<<"x  "<<"입니다.★★"<<endl;// C 상수는 없는 것으로 만들었습니다.

}


void icalcul::fdegree()//2차식 적분
{
	cout<<"f(x)=ax^2+bx+c이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	cout<<"계수c를 입력하시오"<<endl;
	cin>>c;
	double e=a/3;
	double f=b/2;
	cout<<"\n★★∫f(x)dx="<<e<<"x^3 + "<<f<<"x^2 + "<<c<<"x  입니다.★★"<<endl;// C 상수는 없는 것으로 만들었습니다.

}
void icalcul::gdegree()//3차식 적분
{
	cout<<"f(x)=ax^3+bx^2+cx+d이라는 방정식이 있습니다"<<"\n"<<"계수 a를 입력하시오:"<<endl;
    cin>> a;
	cout<<"계수b를 입력하시오"<<endl;
	cin>>b;
	cout<<"계수c를 입력하시오"<<endl;
	cin>>c;
	cout<<"계수d를 입력하시오"<<endl;
	cin>>d;
	double e=a/4;
	double f=b/3;
	double g=c/2;
    cout<<"\n★★∫f(x)dx = "<<e<<"x^4 + "<<f<<"x^3 + "<<g<<"x^2 + "<<d<<"x 입니다.★★"<<endl;// C 상수는 없는 것으로 만들었습니다. 
	
 
	
	
}

class question : public dcalcul, public icalcul{
public:
 void discrem() //미분인지 적분 판별식
{  int u;
 cout<< "\n1,2,3차 다항식 미분 적분을 할 수있습니다."<<"\n"<< "미분을 원하시면 1을 적분을 원하시면 2를 눌러 주세요"<<endl;
  cin>>u;
	 switch(u){
    case 1:
	ddiscreminent();//미분 n차항 판별식으로
	 break;
   case 2:
	idiscreminent();//적분 n차항 판별식으로
	break;
    default:
	cout<<"계산 불가"<<endl;
    discrem();// 다시 미분 적분 선택하는 함수로 되돌아 가기 위해 삽입
	 }
 }
};



 
 void main()
{
 int select;
  
 

 cout<<"이 프로그램은 공학용계산기입니다."<<endl;
 cout<<"기능은 괄호가 포함된 사칙연산과 미적분을 할 수 있습니다."<<endl;

 for(int i=0 ; i<MAX ; i++)
 {
 cout<<"\n★사칙연산을 하시려면 1을 미적분계산을 하시려면 2를 입력하세요.★"<<endl;
 cout<<"종료를 원하시면 3을 입력하세요."<<endl<<endl;
 
 cout<<"입력 : ";
 cin>>select;
 cin.ignore();


 if(select == 1)
 { 	 
 char* formula = new char[500];
 char c;
 int index;
 //while (1)
// {
 
  index = 0;
  cout<<"\n사칙연산 프로그래밍입니다.";
  cout<<"\n수식을 입력하세요. \n";
  cout<<"사칙연산 (+,-,*,/) 및 () 괄호 계산 가능"<<endl;
  cout<<"종료를 원하시면 q를 입력하세요."<<endl;
  cout<<"수식입력 : ";

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

//  }
 delete[] formula;
 }



 else if(select == 2)
 {
	cout<<"\n미적분 프로그래밍입니다."<<endl;
	question getdis;// 판별식 클레스 정의
	getdis.discrem();
	 
 }



 else if(select = 3)
	 break;
 }
 }