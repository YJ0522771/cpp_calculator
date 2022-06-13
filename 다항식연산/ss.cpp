#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;

#define MAX  50


//��Ģ������ ���� class

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
    printf("\n�߸��� �Է¹���Դϴ�. �ٽ� �Է����ּ���.\n");
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
  
  
 // cout<<"\n�������� ǥ����� \n%s"<<reverse_formula;
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
	cout<<"�߸��� �Է¹���Դϴ�. �ٽ� �Է����ּ���. "<<endl;
    delete[] deletepointer;
    return;
   }
   
  }
  
  cout<<"\n\n�ڡڡڰ������ = "<<m_operand.pop()<<"�ڡڡ�"<<endl;
 
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

// �������� ���� class
class dcalcul{
private :
int n; //n����
int i,j;//�迭
double a;
double b;
double c;
double d;
public:
	void adegree( );//1���� �̺� �Լ�
	void bdegree( );//2���� �̺� �Լ�
	void cdegree( );//3���� �̺� �Լ�
	void ddiscreminent( );//1,2,3�� �� �Ǻ��� �Լ�
	double result[2][21];//(0~20 ���� �迭)
};//�̺� ���� class

void dcalcul::ddiscreminent() //1,2,3,���� �Ǻ���
{ cout<<"1,2,3�� �� �� �� ������ �̺��ϰ� �����ʴϱ�?"<<endl;
  cin>>n;//n�� ����
  switch(n){
case 1: // ������ 1�̶��
	  adegree();//1���� �̺� �Լ�
	  break;
case 2:// ������ 2�̶��
	  bdegree();//2���� �̺� �Լ�
	  break;
case 3:// ������ 3�̶��
	  cdegree( );//3���� �̺� �Լ�
	  break;
default:
	cout<<"��� �Ұ� (3���ı��� ���� �մϴ�.)"<<endl;
	ddiscreminent();//�ٽ� 1,2,3 ���� �Ǻ������� �ǵ��ư� ���� ���� ����
  }
} // switch �� ����ؼ� �Ǻ��� ����

void dcalcul::adegree() //1����
{
	cout<<"f(x)=ax+b�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	
	cout<<"\n�ڡ�f'(x)="<<a<<"�Դϴ�.�ڡ�"<<endl;

	
}


void dcalcul::bdegree() //2����
{
	cout<<"f(x)=ax^2+bx+c�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	cout<<"���c�� �Է��Ͻÿ�"<<endl;
	cin>>c;
	double e=a*2; 
	cout<<"\n�ڡ�f'(x)="<<e<<"x + "<<b<<"�Դϴ�.�ڡ�"<<endl;
	
}
void dcalcul::cdegree()//3���� �̺�
{
	cout<<"f(x)=ax^3+bx^2+cx+d�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	cout<<"���c�� �Է��Ͻÿ�"<<endl;
	cin>>c;
	cout<<"���d�� �Է��Ͻÿ�"<<endl;
	cin>>d;
	double e=3*a;
	double f=2*b;
	cout<<"\n�ڡ�f'(x)="<<e<<"x^2 + "<<f<<"x + "<<c<<"�Դϴ�.�ڡ�"<<endl;
	
}

class icalcul{
private :
int n;//1,2,3 ������ ��Ÿ��
int i,j; //i�� �� i�� ���� ��Ÿ��
double a;//���
double b;//���
double c;//���
double d;//���
public:
	void edegree( );//1���� ����
	void fdegree( );//2���� ����
	void gdegree( );//3���� ����
	void idiscreminent( );//1,2,3�� ���� �Ǻ�
	double result[2][21];
};//���� ���� class

void icalcul::idiscreminent()//1,2,3�� ���� �Ǻ�
{ cout<<"1,2,3�� �� �� �� ������ �����ϰ� �����ʹϱ�?"<<endl;
  cin>>n;
  switch(n){ //n�� ����
case 1://������ 1�̶��
	  edegree();//1���� ����
	  break;
case 2://������ 2�̶��
	  fdegree();//2���� ����
	  break;
case 3:// ������ 3�̶��
	  gdegree( );//3���� ����
	  break;
default:
	cout<<"��� �Ұ� (3���ı��� ���� �մϴ�.)"<<endl;
	idiscreminent();//�ٽ� 1,2,3 ���� �Ǻ������� �ǵ��ư� ���� ���� ����
  }
  }

void icalcul::edegree()//1���� ����
{
	cout<<"f(x)=ax+b�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	double e = a/2;
	cout<<"\n�ڡڡ�f(x)dx="<<e<<"x^2 + "<<b<<"x  "<<"�Դϴ�.�ڡ�"<<endl;// C ����� ���� ������ ��������ϴ�.

}


void icalcul::fdegree()//2���� ����
{
	cout<<"f(x)=ax^2+bx+c�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	cout<<"���c�� �Է��Ͻÿ�"<<endl;
	cin>>c;
	double e=a/3;
	double f=b/2;
	cout<<"\n�ڡڡ�f(x)dx="<<e<<"x^3 + "<<f<<"x^2 + "<<c<<"x  �Դϴ�.�ڡ�"<<endl;// C ����� ���� ������ ��������ϴ�.

}
void icalcul::gdegree()//3���� ����
{
	cout<<"f(x)=ax^3+bx^2+cx+d�̶�� �������� �ֽ��ϴ�"<<"\n"<<"��� a�� �Է��Ͻÿ�:"<<endl;
    cin>> a;
	cout<<"���b�� �Է��Ͻÿ�"<<endl;
	cin>>b;
	cout<<"���c�� �Է��Ͻÿ�"<<endl;
	cin>>c;
	cout<<"���d�� �Է��Ͻÿ�"<<endl;
	cin>>d;
	double e=a/4;
	double f=b/3;
	double g=c/2;
    cout<<"\n�ڡڡ�f(x)dx = "<<e<<"x^4 + "<<f<<"x^3 + "<<g<<"x^2 + "<<d<<"x �Դϴ�.�ڡ�"<<endl;// C ����� ���� ������ ��������ϴ�. 
	
 
	
	
}

class question : public dcalcul, public icalcul{
public:
 void discrem() //�̺����� ���� �Ǻ���
{  int u;
 cout<< "\n1,2,3�� ���׽� �̺� ������ �� ���ֽ��ϴ�."<<"\n"<< "�̺��� ���Ͻø� 1�� ������ ���Ͻø� 2�� ���� �ּ���"<<endl;
  cin>>u;
	 switch(u){
    case 1:
	ddiscreminent();//�̺� n���� �Ǻ�������
	 break;
   case 2:
	idiscreminent();//���� n���� �Ǻ�������
	break;
    default:
	cout<<"��� �Ұ�"<<endl;
    discrem();// �ٽ� �̺� ���� �����ϴ� �Լ��� �ǵ��� ���� ���� ����
	 }
 }
};



 
 void main()
{
 int select;
  
 

 cout<<"�� ���α׷��� ���п�����Դϴ�."<<endl;
 cout<<"����� ��ȣ�� ���Ե� ��Ģ����� �������� �� �� �ֽ��ϴ�."<<endl;

 for(int i=0 ; i<MAX ; i++)
 {
 cout<<"\n�ڻ�Ģ������ �Ͻ÷��� 1�� �����а���� �Ͻ÷��� 2�� �Է��ϼ���.��"<<endl;
 cout<<"���Ḧ ���Ͻø� 3�� �Է��ϼ���."<<endl<<endl;
 
 cout<<"�Է� : ";
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
  cout<<"\n��Ģ���� ���α׷����Դϴ�.";
  cout<<"\n������ �Է��ϼ���. \n";
  cout<<"��Ģ���� (+,-,*,/) �� () ��ȣ ��� ����"<<endl;
  cout<<"���Ḧ ���Ͻø� q�� �Է��ϼ���."<<endl;
  cout<<"�����Է� : ";

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
	cout<<"\n������ ���α׷����Դϴ�."<<endl;
	question getdis;// �Ǻ��� Ŭ���� ����
	getdis.discrem();
	 
 }



 else if(select = 3)
	 break;
 }
 }