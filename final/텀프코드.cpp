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

//		<����>

//	2009037353 �� �� ��
//	2011104313 �� �� ��
//	2012104134 �� ȫ ��
//	2013020050 �� �� ��


//��Ģ������ ���� class

template<typename T> // ��� ���̶� �Է¹ޱ����� ���ø����� ���� ����

class Stack //���������� ���� stack�̶�� Ŭ���� ����
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

 class Calcul//������������ ���� Calcul�̶�� Ŭ��������
{
public:
  static int j; //���� ī��Ʈ�� ���� static���� ����

  Calcul(char* formula) 
 {
  
  size = 0;
  ofstream aout("4basic_operator.txt",ios::app);//������� ���Ͽ� �����ϱ� ���� ����

  while (*formula++ != '\0')
  size++;
  size++;
  formula -= size;

  char* middle_formula = new char[size];
  
  memcpy(middle_formula, formula, size);
  
  aout<<"================================================"<<endl;
  aout<<"("<<Calcul::j<<") "<<"���� = "<<middle_formula<<endl;

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
	cout<<"\n�߸��� �Է¹���Դϴ�. �ٽ� �Է����ּ���.\n";
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
  
  ofstream aout("4basic_operator.txt",ios::app);//������� ���Ͽ� �����ϱ� ���� ����

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
  
  time_t cur_time;
  struct tm* pTime;

  time(&cur_time);
  pTime = localtime(&cur_time);//����ð��� ����ϱ����� ��ɹ�

  double result = m_operand.pop();//������� ����ó���ϱ� ���� �ٽ� ����.
  
  
  cout<<"\n �� ������� = "<<result<<endl;
  aout<<" �� "<<"����� = "<<result<<endl<<endl;
  aout<<"���ð� = "<<asctime(pTime)<<endl;

  aout.close();
  Calcul::j++;//���°���� ī��Ʈ�ϱ� ���� 

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

int Calcul::j=1;//���������� 1�� �ʱ�ȭ�Ͽ� ����ó���� ���� ī��Ʈ

// �������� ���� class

class CTerm
{
	int coef, order;		//���, ����
	char vari, oper;		//����, ������	//�� ���� ���� �� ���� ��ҷ� ǥ��
	
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
void insert_code(char &c);										//������ ����� ����ڷκ��� �Է¹���
void differ(CTerm *poly, int size);								//�̺�
void integ(CTerm *poly, int size);								//����




 
 void main()
{
 char select;
  
 

 cout<<"�� ���α׷��� ���п�����Դϴ�."<<endl;
 cout<<"��ȣ�� ���Ե� ��Ģ����� �������� �� �� �ֽ��ϴ�."<<endl;

 while(true)
 {
	cout<<"=================================================================="<<endl;
	cout<<"\n�ڻ�Ģ������ �Ͻ÷��� 1��, �����а���� �Ͻ÷��� 2�� �Է��ϼ���.��"<<endl;
	cout<<"�����ݱ����� ������� ���÷��� 3�� �Է��ϼ���.��"<<endl;
	cout<<"��ȭ��û�Ҹ� ���Ͻø� c�� �Է��ϼ���.��"<<endl;
	cout<<"�����α׷� ���Ḧ ���Ͻø� q�� �Է��ϼ���.��"<<endl<<endl;
 
	cout<<"�Է� : ";
	cin>>select;
	cin.ignore();


	if(select == '1')
	{ 	 
		char* formula = new char[500];
		char c;
		int index;

		index = 0;
		cout<<"\n����Ģ���� �����Դϴ�.��";
		cout<<"\n������ �Է��ϼ���. \n";
		cout<<"��Ģ���� (+,-,*,/) �� () ��ȣ ��� ����"<<endl;
		cout<<"���α׷� ���Ḧ ���Ͻø� q�� �Է��ϼ���."<<endl;
		cout<<"\n�����Է� : ";

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
		pTime = localtime(&cur_time);//����ð��� ����ϱ����� ��ɹ�
	 
		cout<<"\n�������� �����Դϴ�.��"<<endl<<endl;
		
		calculation();

		fout<<"\n���ð� = "<<asctime(pTime)<<endl;

	}

	else if(select == '3')
	{
		int code;

		cout<<"�α׸� ����� ���� ����"<<endl;
		cout<<"1 : ��Ģ����, 2 : ������"<<endl;
		cout<<"�Է� : "; cin>>code;
		
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
			cout<<"�߸��� �Է� ����Դϴ�."<<endl;
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
	if(oper==MINUS)				//������ ���Ǹ� ���� ����� ������ ������ �������� �ٲ۴�
	{
		oper=PLUS;
		coef*=(-1);
	}
}

void CTerm::plus_to_minus()
{
	if((coef<0)&&(oper==PLUS))			//������ ���� �� ����� �����̸� ���������� �����ش�
	{
		coef=abs(coef);
		oper=MINUS;
	}
}

void CTerm::mul_to_plus(CTerm *other)
{
	oper=PLUS;							//�� ���� ���� ��, ����� ������ ���� �����ڸ� +��
	(*other).setNULL();					//������ �� ���� �����μ��� ����� �����ϴ� �ǹ̿��� �����ڸ� �����Ѵ�
}

bool CTerm::cmp_order_to(CTerm other)
{
	if(order==other.order)					//��� �� ���� ������ ������ true�� ��ȯ
		return true;						
	else
		return false;
}

bool CTerm::exist_mul()
{
	if(oper==MULTI)					//�ش� ���� ������ȣ�� ������ ������ true�� ��ȯ
		return true;
	else
		return false;
}

CTerm& CTerm::operator=(CTerm &T)		//CTerm ��ü������ ���Կ�����
{
	oper=T.oper;
	coef=T.coef;
	vari=T.vari;
	order=T.order;

	return *this;
}

bool CTerm::exist_oper()
{
	if((oper==PLUS)||(oper==MINUS)||(oper==MULTI))			//�� ���� ����� ����� �ϰ� �ִ�(�����ڰ� �����ϴ�) �������� ���θ� �Ǵ�
		return true;										//����� �� ����� �ϰ� ������ true�� ��ȯ
	else
		return false;
}

void CTerm::show(double coe, int term_num)					//������ ��� ����� �����ֱ� ���� �Լ�
{															
	if((term_num==0)&&(oper==PLUS))							//ù ���� �����ڰ� +�� ����
		cout<<coe<<vari<<"^"<<order;
	else
		cout<<oper<<coe<<vari<<"^"<<order;	
}

int count_real_terms(CTerm *tms, int size)					//����� ����� �ϰ� �ִ� ���� �� ������ ������ ��ȯ
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
	
	CTerm *res = new CTerm[terms];					//����� ��� ���� ���� ������ŭ CTerm �����Ϳ� �޸� �Ҵ�
	
	for(int i=0; i<size; i++)
	{
		if((tms+i)->exist_oper())					//��� ���� ���̸� ������ �޸𸮿� ����
		{
			*(res+j) = *(tms+i);
			j++;
		}
	}

	for(int i=0; i<terms; i++)									//������ ū ������� ����
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
		if((terms+i)->exist_mul())						// * �����ڸ� ���� ���� ã�� �� ���� �װ� ����
		{
			(terms+i)->mul_coef(*(terms+(i-1)));
			(terms+i)->add_order(*(terms+(i-1)));
			(terms+i)->mul_to_plus(terms+(i-1));
			
			count++;									//������ �� ����ŭ ��ü ���� �پ��Ƿ� �� ���� ī��Ʈ
		}

	CTerm *res = new CTerm[size-count];					//��� ����� �����ϱ� ���� ���� �׸�ŭ �޸� �Ҵ�

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())						//��� ������� ��� �ִ� CTerm ������ ����
		{
			*(res+j) = *(terms+i);
			j++;
		}

	size-=count;											//���� �� ������ ����

	return res;											//������� ��� ������ ��ȯ
}

CTerm * addition(CTerm *terms, int &size)
{
	int count=0;

	for(int i=0; i<size; i++)
	{
		if((terms+i)->get_oper() == NULL)				//��� ���� �ƴ� ���� �Ѿ���� ��츦 ����� �Ÿ���ġ
			break;
		for(int j=i+1; j<size; j++)
		{
			if((terms+j)->get_oper() == NULL)
				break;
			if((terms+i)->cmp_order_to(*(terms+j)))		//������ ������ Ȯ���ϸ� ���� ����
			{
				(terms+i)->add_coef(*(terms+j));			//����� ����
				(terms+j)->setNULL();					//����� ����� �� �ܿ� �ٸ� ���� ��� ����

				count++;								//����� Ƚ����ŭ ī��Ʈ
			}
		}
	}

	CTerm *res = new CTerm[size-count];					//��� �׸�ŭ �޸� �Ҵ�

	int j=0;
	for(int i=0; i<size; i++)
		if((terms+i)->exist_oper())
		{
			*(res+j) = *(terms+i);						//��� �׸��� ������ ������ ����
			j++;
		}

	size-=count;											//���� ���� ����

	return res;											//��� �׸� ��� ������ ��ȯ
}

CTerm * calculation_not_brk(CTerm *poly, int &size)			//��ȣ�� ���� ���׽� ���
{
	for(int i=0; i<size; i++)								//����� ���Ǹ� ���� ���� ���� ���� ���������� ��ȯ
		(poly+i)->minus_to_plus();

	CTerm *pr = multiple(poly,size);						//����� ���� �����͸� �����ϰ� ���� ��� ����

	pr = addition(pr, size);								//���� ����

	pr = sort(pr, size);									//���� ũ�� ������ ����

	for(int i=0; i<size; i++)								//���� �������� �ٽ� ���������� �ٲ�
		(pr+i)->plus_to_minus();

	return pr;												//��� ��ȯ
}

string find_in_brk(string prb, int &n, int &m)
{
	char code='x';														//��ȣ�� �־� ��Ƴ� ���� � ���������� �˷��ִ� code����
																		//��ȣ�� ���� ��� x
	if((prb.find('(') >= 0)&&(prb.find(')') <= prb.length()))			//��ȣ ���� Ȯ��
	{
		if(prb.substr(prb.find('(')-1, 1) == "*")						//��ȣ �� ������ȣ�� ã��
		{
			int count=0;

			if((prb.substr(prb.find('(')-2, 1) == ")"))					//������ȣ ���� �ִ� ���� �� �ٸ� ��ȣ�� ���
			{
				code='d';												//��ȣ�� �� ����� �ǹ��� double�� d
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if(prb.substr(i, 1)=="(")							//�� ��ȣ�� ������ �κ��� ã��
					{
						count++;
						break;
					}
				}
			}
			else														//���� ��ȣ ���� �ִ� ���� �ϳ��� ���� ���
			{
				code='f';												//�������� ��ȣ�� �տ� �ִٴ� �ǹ��� front�� f
				for(int i=prb.find('(')-2; i>=0; i--)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))	//�� ���� ������ ������ ã��
					{
						count++;
						break;
					}
				}
			}

			n=prb.find('(') - count;
			m=prb.find(')');
			string mid = prb.substr(n,m-n+1);							//ã�Ƴ� ��ȣ�� �� �� ���� �κ��� ����

			mid=multiple_poly(mid, code);								//�� ���� ����Ͽ� ��� ��ȯ

			return mid;
		}
		else if(prb.substr(prb.find(')')+1, 1) == "*")					//��ȣ �� ������ȣ
		{
			int count=0;
			if(prb.substr(prb.find(')')+2, 1) == "(")					//��ȣ �� ���� ��ȣ ���� �ִ� ���� �Ǵٸ� ��ȣ
			{
				code='d';												//��ȣ�� �� ������ �˸��� �ڵ�
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if(prb.substr(i, 1)==")")							//������ ��ġ�� ã��
					{
						count++;
						break;
					}
				}
			}
			else														//��ȣ �� ������ȣ ���� �ϳ��� ���� ���
			{
				code='b';												//���� ���� ��ȣ�� �ڿ� �ִ� �ǹ��� back�� b
				for(int i=prb.find(')')+2; i<prb.length(); i++)
				{
					count++;
					if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))	//���� ������ ������ ã��
						break;
				}
			}

			n=prb.find('(');
			m=prb.find(')') + count;
			string mid = prb.substr(n, m-n+1);

			mid=multiple_poly(mid, code);								//����Ͽ� ��ȯ

			return mid;
		}
		else															//��ȣ ���� ������ ���� ���
		{
			n=prb.find('(');
			m=prb.find(')');

			string mid = prb.substr(n+1, m-n-1);							//��ȣ ���� ����
			code='n';													//������ ���� �ǹ��� not�� n

			int size=0;

			mid = cterm_to_string(calculation_not_brk(string_to_cterm(mid, size), size), size);		//��ȣ ���� ���� �� ��ȯ
		
			return mid;
		}
	}
	else
		return "not";			//��ȣ�� ������ ���ڿ� not�� ��ȯ
}	

void print_error()									//�Է��� �߸��� ��� ����� �Բ� ���Է�
{
	cout<<"�Է¿� �߸��� �κ��� �ֽ��ϴ�."<<endl;
	return calculation();					
}

int count_brk (char *pr)					//��ȣ ���� ��ȯ
{
	int cnt_open=0, cnt_close=0;

	for(int i=0; i<strlen(pr); i++)
	{
		if(*(pr+i)=='(')					//������ ��ȣ�� ������ ī��Ʈ
			cnt_open++;
		else if(*(pr+i)==')')				//������ ��ȣ�� ������ ī��Ʈ
			cnt_close++;
	}

	if(cnt_open==cnt_close)
		return cnt_open;					//��ȣ ���� ��ȯ
	else									//������ ��ȣ�� ������ ��ȣ�� ������ ��ġ���� ���� ��� �Է��� �߸����� �˸�
		print_error();
}			

int find(char *str, char c, int n)			//str ���ڿ����� n��° c���ڸ� ã�� �� ��ġ�� ��ȯ
{
	int count=0;

	for(int i=0; i<strlen(str); i++)
	{
		if((*(str+i))==c)					//ã�� �ִ� ���ڰ� ��Ÿ�� ��� ī��Ʈ
			count++;
		if(count==n)						//�� Ƚ���� ã���ִ� n��°�� ��ġ�ϸ� ��ġ ��ȯ
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

	if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//��ȣ �տ� ���� ��ȣ�� ���� �Ǿ��� ��
	{
		prb.insert(n, "*");									//��ȣ �տ� ���� ��ȣ�� �߰��ϰ� ���� ��ȭ�Ͽ����� �˸�
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
		prb.insert(n+1, "+");							//���� ó�� �κп� ���� ��ȣ�� �߰��ϰ� ���� ��ȭ�Ͽ����� �˸�
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

	if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//��ȣ �ڿ� ���� ��ȣ�� ���� �Ǿ��� ��
	{
		prb.insert(m+1, "*");												//��ȣ �� ���� ��ȣ�� �߰��ϰ� ���� ��ȭ�Ͽ����� �˸�
		change = 'y';
	}
}

string tune_input(string prb)						//������ ���� �� �׿� ������, ���, ����, ���� ��θ� ���� �ִ� ���·� ��ȯ
{
	char *pr = new char[prb.length()+1];			//�� ���꿡 ����ϱ� ���� char ������
	strcpy(pr, prb.c_str());

	char change = 'n';

	if(('1'<=*pr)&&('9'>=*pr))						//���� �� �տ� ������ ���� ��ȣ�� �����ϰ� ���� ��ȭ�Ͽ����� �˸�
	{
		prb.insert(0, "+");
		change = 'y';
	}
	
	if(change=='y')									//���� ��ȭ�Ͽ��� ��� char �����͸� �ٽ� ����
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());
		}

	int brk_cnt = count_brk(pr);					//��ȣ�� ����

	if(brk_cnt>0)
		for(int i=0; i<brk_cnt; i++)				//(i+1)��° ��ȣ�� ���� ������ �����̳� ���� ��ȣ �߰�
			check_next_brk(pr, prb, i+1, change);
	
	delete[] pr;
	
	return prb;							//������ ����� ��ȯ
}

string multiple_poly(string mid, char code)			//�� ���׽��� ����
{
	string st1, st2;								//�� ���׽��� �����ϴ� string ���� ��

	if(code=='f')									//�� �ϳ��� ��ȣ�� �տ� ���� ���
	{
		st1=mid.substr(0, mid.find('*'));			//ó�� ���� ����

		int n=mid.find('('), m=mid.find(')');
		st2 = mid.substr(n+1, m-n-1);				//��ȣ ���� ���� ����
	}
	else if(code=='b')								//�� �ϳ��� ��ȣ �ڿ� ���� ���
	{
		int n=mid.find('('), m=mid.find(')');
		st1 = mid.substr(n+1, m-n-1);				//��ȣ ���� �� ����

		st2=mid.substr(mid.find('*')+1, mid.length()-mid.find('*')-1);		//������ �� ����
	}
	else if(code=='d')								//��ȣ�� �� ���� ���
	{
		char *md=new char[mid.length()+1];
		strcpy(md, mid.c_str());
		
		int n=find(md, '(', 1), m=find(md, ')', 1);		//��ȣ ���� ���� ���� ����
		st1 = mid.substr(n+1, m-n-1);

		n=find(md, '(', 2);
		m=find(md, ')', 2);
		st2 = mid.substr(n+1, m-n-1);
	}

	int size1, size2;

	CTerm *poly1 = string_to_cterm(st1, size1);			//������ ���� ���� CTerm ���� ��ȯ
	CTerm *poly2 = string_to_cterm(st2, size2);

	poly1=calculation_not_brk(poly1, size1);			//�� ���� ���� ���
	poly2=calculation_not_brk(poly2, size2);

	CTerm *res = new CTerm[size1*size2];				//���� ����� ������ CTerm �޸� �Ҵ�

	for(int i=0; i<size1; i++)							//���� ����� ��ȣ ����
		(poly1+i)->minus_to_plus();
	for(int i=0; i<size2; i++)
		(poly2+i)->minus_to_plus();

	int k=0;
	for(int i=0; i<size2; i++)
	{
		for(int j=0; j<size1; j++)						//���� ���� ����
		{
			*(res+k)=*(poly2+i);
			(res+k)->mul_coef(*poly1);					//����� ���ϰ� ������ ���ؼ� ���ο� �޸𸮿� �ϳ��� ����
			(res+k)->add_order(*poly1);
			k++;
		}
	}

	for(int i=0; i<size1*size2; i++)
		(res+i)->plus_to_minus();						//������ ����� ���¸� �ٽ� �ǵ���

	return cterm_to_string(res, size1*size2);			//����� string���� ��ȯ�Ͽ� ����
}

CTerm * string_to_cterm(string poly, int &size)					//string�� CTerm���� ��ȯ�ϴ� �Լ�
{
	string prb=poly+'@';										//���� ���� �˸������� ��ȣ @�� �߰�
	char *pr = new char[prb.length()+1];						//�� ������ ���Ǹ� ���� char ������ ����
	strcpy(pr, prb.c_str());

	int opt_cnt=0;

	for(int i=0; i<prb.length(); i++)
	{
		if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI))
			opt_cnt++;											//�������� ����(=���� ��)�� ī��Ʈ
	}

	CTerm *terms = new CTerm[opt_cnt];							//�����ϴ� ���� ����ŭ CTerm ������ �޸� �Ҵ�

	int start=0, j=0;
	do
	{
		int count=0, i;

		for(i=1; i<prb.length(); i++)
		{
			if((*(pr+i)==PLUS)||(*(pr+i)==MINUS)||(*(pr+i)==MULTI)||(*(pr+i)=='@'))		//�� �ϳ��� ũ�⸦ ����
				break;
			else
				count++;
		}
		
		string temp = prb.substr(start, count+1);				//ũ�⸦ ���� �� �ϳ��� �ӽ÷� ����

		(terms+j)->input(temp);									//CTerm�� ���·� ����

		start+=i;												//���� ���� ��� ���� ī��Ʈ�� �������� ��ȯ
		pr+=i;													//�������� ������ ��ȯ
		j++;													//��� ������ ��ȣ�� �������� ��ȯ

	}while(j!=opt_cnt);											//���� ����ŭ ������ �Ǿ����� �ݺ��� Ż��

	size=opt_cnt;												//���� �� ����

	delete[] pr;

	return terms;												//CTerm ������ ��ȯ
}

string cterm_to_string(CTerm *tms, int size)		//CTerm �����͸� string���� ��ȯ
{
	string res;

	for(int i=0; i<size; i++)						//���� ������ŭ �ݺ�
	{
		char *pt=new char[5];						//_itoa �Լ��� ����� char ����Ʈ
		res+=(tms+i)->oper;							//����� ������ �߰�

		_itoa((tms+i)->coef, pt, 10);
		res+=pt;									//��� �߰�

		res+=(tms+i)->vari;							//������ �ŵ����� ������ ^�߰�
		res+="^";

		_itoa((tms+i)->order, pt, 10);
		res+=pt;									//���� �߰�
	}

	return res;										//��� ��ȯ
}

void CTerm::input(string term)					//�ϳ��� ���� CTerm �����ͷ� ��ȯ
{
	char *temp = new char[term.length()+1];		//���Ǹ� ���� char ������

	strcpy(temp, term.c_str());

	oper = *temp;								//���� ù��° ���ڴ� �������̹Ƿ� oper�� ����

	coef = 0;									//����� 0���� �ʱ�ȭ

	int i=1;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))
		{
			tm=*(temp+i);

			if(coef!=0)									//����� �� �ڸ� �̻��� ��츦 ���� ��ġ
				coef = (coef*10)+atoi(tm.c_str());		//�ι�° ���ں��ʹ� ���� ���� 10�� ���� ���� ����
			else
				coef = atoi(tm.c_str());
		}
		else
			break;

		i++;
	}

	vari = *(temp+i);							//���� ����

	order = 0;									//������ �ʱ�ȭ
	
	if((*(temp+i+1)) !='^')						//������ ���� ���ڰ� �ŵ����� �����ڰ� �ƴ� ��� �Է��� �߸��Ǿ����� �˸�
		print_error();
	
	
	i+=2;
	while(1)
	{
		string tm;
		
		if((*(temp+i)>='0')&&(*(temp+i)<='9'))				//����� ���� ������ ���� ����
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

void calculation()						//���ο��� ȣ���ϱ� ���� ���� �Լ�
{
	string fnt;

	cout<<"������ ���ס�"<<endl;
	cout<<"�� ()�� ������ ���� �Լ��� ������ �մϴ�."<<endl;
	cout<<"�� �Է� �Ŀ� ���� ������ �����ڴ� +, -, * �Դϴ�."<<endl;
	cout<<"�� ������ � ���ĺ��� �ᵵ ��������� ���� ���� �Լ��� ���� �����մϴ�."<<endl;
	cout<<"�� �Էµ� ���� �Լ��� ������ �� �ڿ� �������� �����մϴ�."<<endl;
	cout<<"�� () ���� ������ȣ�� ���� �����մϴ�.(�Է� ���� ���� ����)"<<endl;
	cout<<"�� () �ߺ�(��ȣ ������ ��ȣ)�� �Ұ����ϸ� ��ȣ�� �ݵ�� �Ұ�ȣ�� ������ּ���."<<endl;
	cout<<"�� ������ ������ �Ұ����մϴ�. ���� 1���װ� ����׵� �ݵ�� ������ ������ �Է����ּ���. ex) 5x --> 5x^1"<<endl;
	cout<<"�� ���� ���¿� Ŀ�ٶ� ������ ������, �ǵ��� ���ÿ��� ���� ����� �Է��� �������ּ���."<<endl;
	cout<<"ex) 3x^2(2x^6+4x^3)+4x^3\n => 6x^8+12x^5+4x^3"<<endl<<endl;
	cout<<"ex) 3x^5 + 5\n => �̷������� ������� �Է¹����� ����."<<endl<<endl;
	cout<<"ex) 2x^-5\n => ���������� ������ ������ ������ ����."<<endl<<endl;
	
	cout<<"������ �Լ�(or ���׽�)�� �Է����ּ���."<<endl;
	
	cout<<"�Լ� �Է� : ";													//����� ���� �Է� ����
	cin>>fnt;
	
	ofstream fout("differentiation_integration.txt", ios::app);				//�Է� ���� ���� ���Ͽ� ����
	
	fout<<"===================================="<<endl;
	fout<<endl<<"�Է� �Լ� : "<<fnt<<endl;

	fout.close();

	int start, end;

	string tun = tune_input(fnt);							//�Է� �� ���� ����

	string mid = find_in_brk(tun, start, end);				//��ȣ�� ã�� ���� ���� �����Ͽ� ����� �ش� �κ��� ��ġ�� ����

	while(mid!="not")										//���� ��ȣ�� ����� mid�� not�� ���� ������ �ݺ�
	{
		tun.replace(start, end-start+1, mid);				//����� �ش� ��ġ�� ������
		mid = find_in_brk(tun, start, end);					//��ȣ �˻�
	}

	int len=0;

	for(int i=0; i<fnt.length(); i++)
		if((fnt.substr(i, 1) == "+")||(fnt.substr(i, 1) == "-")||(fnt.substr(i, 1) == "*"))
			len++;														//���� ���� ī��Ʈ

	CTerm *result = new CTerm[len];										//�� ������ ���� CTerm ������ �޸� �Ҵ�		
	result = calculation_not_brk(string_to_cterm(tun, len), len);		//���� CTerm���� �ٲٰ� �̸� �־� ���

	print_result(result, len, " �� ����");								//���� ����� ���

	while(1)
	{
		char code;

		insert_code(code);												//�� ������ ������ ����� �Է� ����

		switch (code)
		{
		case '1': differ(result, len); cin.ignore(); return;			//��� ���� �̺�
		case '2': integ(result, len); cin.ignore(); return;				//��� ���� ����
		case 'q': ; exit(1);

		default: cout<<"�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���."<<endl; break;	//�߸��� �Է¿� ���� ��� ����
		}
	}

	delete[] result;
}

void print_result(CTerm *res, int size, string fn_name)				//��� ��� �Լ�(����, �̺�)
{
	string result = cterm_to_string(res, size);						//����� string���� ��ȯ

	if(result.substr(0,1)=="+")										//�� ���� +�� ��� �̸� ����
		result.erase(0,1);

	cout<<endl<<fn_name<<" ��� : "<<result<<endl;

	ofstream fout("differentiation_integration.txt", ios::app);		//����� ���Ͽ� ��

	fout<<fn_name<<" ��� : "<<result<<endl;

	fout.close();
}

void insert_code(char &c)							//switch ������ �۵��� ��ɾ� �Է� �Լ�
{
	cout<<"\n���� ������� �̺��� ���� ��� 1, ������ ���� ��� 2�� �Է����ּ���."<<endl; 
	cout<<"���α׷��� �����ϰ� �����ø� q�� �Է����ּ���."<<endl<<endl;
	cout<<"�Է� : "; cin>>c;
}

void differ(CTerm *pol, int size)				//�̺� �Լ�
{
	CTerm *poly = new CTerm[size];				//���� ���� ���Ƿ� ������ ����
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		(poly+i)->coef_mul_order();				//������ ����� ���Ͽ� ����� ����
		(poly+i)->order_one_minus();				//������ �ϳ� ����

		if((poly+i)->get_order()<0)				//������� �̺��� ���(���� -1)
			size--;								//���� ����
	}

	print_result(poly, size, " �� �̺�");		//��� ���

	delete[] poly;
}

void integ(CTerm *pol, int size)				//���� �Լ�
{
	double *coef = new double[size];			//��� ������ ���� double ������ �޸�
	CTerm *poly = new CTerm[size];				//���� ���� ���Ƿ� ������ ����
	for(int i=0; i<size; i++)
		*(poly+i)=*(pol+i);

	for(int i=0; i<size; i++)
	{
		*(coef+i) = (poly+i)->coef_div_order();		//����� ������ ����
		(poly+i)->order_one_plus();					//������ �ϳ� ����
	}

	cout<<endl<<" �� ���� ��� : ";
	for(int i=0; i<size; i++)
		(poly+i)->show(*(coef+i), i);				//��� ���. ��, ����δ� ���� ����� �ƴ� ���� ���� double�� �����Ϳ� ������ ����� �ҷ���
		
	cout<<" + C(���л��)"<<endl;

	ofstream fout("differentiation_integration.txt", ios::app);		//����� ���Ͽ� ����

	fout<<" �� ���� ��� : ";

	fout.close();

	for(int i=0; i<size; i++)
		(poly+i)->f_print(*(coef+i), i);

	fout.open("differentiation_integration.txt", ios::app);
	fout<<" + C(���л��)"<<endl;
	fout.close();

	delete[] poly;
	delete[] coef;
}

void CTerm::f_print(double coe, int i)				//���� ����� ���Ͽ� ���� ���� �Լ�
{
	ofstream fout("differentiation_integration.txt", ios::app);

	if((i==0)&&(oper=='+'))							//ù ���ڰ� +�̸� �̸� ������� ����
		fout<<coe<<vari<<"^"<<order;
	else
		fout<<oper<<coe<<vari<<"^"<<order;

	fout.close();
}