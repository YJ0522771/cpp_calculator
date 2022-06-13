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
	
	cout<<"프로토 타입"<<endl;
	cout<<"3x^2(3x^5-4x^3)9x^5="<<endl;

	//cin>>prb;

	
	char *pr = new char[prb.length()+1];					//비교 연산에 사용하기 위한 char 포인터
	strcpy(pr, prb.c_str());

	cout<<"변경 전 : "<<prb<<endl;

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
	
	cout<<"변경 후 : "<<prb<<endl;
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
		if(*(pr+i)==')')
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

	//if((n>=0)&&(m<=prb.length()))		
	//{
		if(change=='y')					//앞의 과정에서 string 식의 변화가 생겼을 경우 char 포인터를 다시 할당받음
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

		if(('0'<= *(pr+n-1))&&('9'>=*(pr+n-1)))					//괄호 앞에 곱셈기호가 생략 되었을 때
		{
			prb.insert(n, "*");
			change = 'y';
		}
		
		if(change=='y')					//(함수처리 하려니까 자꾸 끝나면서 반납되는 거 같은 현상이 생겨서 걍 다 집어넣음)
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

		if(('0'<= *(pr+n+1))&&('9'>=*(pr+n+1)))				//괄호 내부 첫 항에 덧셈 기호 생략 되었을 때
		{
			prb.insert(n+1, "+");
			change = 'y';
		}
		
		if(change=='y')					//(얘도)
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


		if((('0'<=*(pr+m+1))&&('9'>=*(pr+m+1)))||(*(pr+m+1)=='('))				//괄호 뒤에 곱셈기호가 생략 되었을 때
		{
			prb.insert(m+1, "*");
			change = 'y';
		}

		cout<<pr<<endl;//
	//}
}