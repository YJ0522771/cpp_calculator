#include <iostream>
#include <string>

using namespace std;

char * re_copy(char *pr, string prb);
char * check_change(char &code, char *pr, string prb);
void print_error();
int count_brk (char *pr);
int find(char *str, char c, int n);
void check_next_brk(char *pr, string &prb, int brk_n, char &change);

void main()
{
	string prb = "3x^2(3x^5-4x^3)9x^5(3x^2)=";
	
	cout<<"������ Ÿ��"<<endl;
	cout<<"3x^2(3x^5-4x^3)9x^5="<<endl;

	//cin>>prb;

	
	char *pr = new char[prb.length()+1];					//�� ���꿡 ����ϱ� ���� char ������
	strcpy(pr, prb.c_str());

	cout<<"���� �� : "<<prb<<endl;

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
	
	cout<<"���� �� : "<<prb<<endl;
}

char * re_copy(char *pr, string prb)
{
	delete[] pr;

	pr = new char[prb.length()+1];
	strcpy(pr, prb.c_str());

	//cout<<"recopy "<<ne<<endl;
	return pr;
}

char * check_change(char &code, char *pr, string prb)
{
	if(code=='y')
	{
		code='n';
		delete[] pr;

		pr = new char[prb.length()+1];
		strcpy(pr, prb.c_str());

		return pr;
	}
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
		if(*(pr+i)==')')
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

	//if((n>=0)&&(m<=prb.length()))		
	//{
		if(change=='y')					//���� �������� string ���� ��ȭ�� ������ ��� char �����͸� �ٽ� �Ҵ����
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());

			n = find(pr, '(', brk_n); 
			m = find(pr, ')', brk_n);
		}
		cout<<pr<<endl;//
		cout<<*(pr+n-1)<<" "<<*(pr+n+1)<<" "<<*(pr+m+1)<<endl;//

		if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//��ȣ �տ� ������ȣ�� ���� �Ǿ��� ��
		{
			prb.insert(n, "*");
			change = 'y';
		}
		
		if(change=='y')					//(�Լ�ó�� �Ϸ��ϱ� �ڲ� �����鼭 �ݳ��Ǵ� �� ���� ������ ���ܼ� �� �� �������)
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());

			n = find(pr, '(', brk_n); 
			m = find(pr, ')', brk_n);
		}

		cout<<pr<<endl;//
		cout<<*(pr+n+1)<<" "<<*(pr+m+1)<<endl;

		if(('0'<= *(pr+n+1))&&('9'>=*(pr+n+1)))				//��ȣ ���� ù �׿� ���� ��ȣ ���� �Ǿ��� ��
		{
			prb.insert(n+1, "+");
			change = 'y';
		}
		
		if(change=='y')					//(�굵)
		{
			change='n';
			delete[] pr;

			pr = new char[prb.length()+1];
			strcpy(pr, prb.c_str());

			n = find(pr, '(', brk_n); 
			m = find(pr, ')', brk_n);
		}
		
		cout<<pr<<endl;//
		cout<<*(pr+m+1)<<endl;


		if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//��ȣ �ڿ� ������ȣ�� ���� �Ǿ��� ��
		{
			prb.insert(m+1, "*");
			change = 'y';
		}

		cout<<pr<<endl;//
	//}
}