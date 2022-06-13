#include <iostream>
#include <string>

using namespace std;

void main()
{
	string prb;

	cout<<"ÇÁ·ÎÅä Å¸ÀÔ"<<endl;
	cout<<"3x^2+(3x^5-4x^3)="<<endl;

	cin>>prb;

	if((prb.find('(') >= 0)&&(prb.find(')') <= prb.length()))				//°ýÈ£ À¯¹«
	{
		if(prb.substr(prb.find('(')-1, 1) == "*")						//°ýÈ£ ¾Õ °ö¼À±âÈ£
		{
			int count=0;

			for(int i=prb.find('(')-2; i>=0; i--)
			{
				count++;
				if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))
					break;
			}
			string mid = prb.substr(prb.find('(') - count, prb.find(')') - prb.find('(') + count + 1);

			cout<<(prb.find('(')-count)<<" "<<mid<<endl;

		}
		else if(prb.substr(prb.find(')')+1, 1) == "*")					//°ýÈ£ µÚ °ö¼À±âÈ£
		{
			int count=0;

			for(int i=prb.find(')')+2; i<prb.length(); i++)
			{
				count++;
				if((prb.substr(i, 1)=="+")||(prb.substr(i, 1)=="-")||(prb.substr(i, 1)=="*"))
					break;
			}
			string mid = prb.substr(prb.find('('), prb.find(')') - prb.find('(') + count + 1);

			cout<<(prb.find(')')+count)<<" "<<mid<<endl;
		}
		else
		{
			string mid = prb.substr(prb.find('(')+1, prb.find(')') - prb.find('(') - 1);
		
			cout<<prb.find('(')<<" "<<mid<<endl;
		}
	}
	else
		cout<<prb.find('(')<<" "<<"not exist ()"<<endl;


}