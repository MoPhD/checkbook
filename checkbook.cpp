//Requires infile.txt in the following format:
//Check Number	Amount	Cashed(Y/N)
//Sample:
//4 88.23 Y
//2 102.34 n
//3 78.23 N
//1 12.34 y
//5 22.10 N

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Checkbook
{
public:
	Checkbook();
	int getNum();
	void setNum(int newnum);
	double getAmount();
	void setAmount(double newamount);
	bool getCashed();
	void setCashed(char newcashed);
	friend bool operator<(const Checkbook &c1, const Checkbook &c2);
	
	
private:
	int num;
	double amount;
	char cashed;
};
int main()
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	double oldbalance=0, deposit=0, sum=0, uncashed=0;
	cout << "Please enter your bank balance: " <<endl;
	cin >> oldbalance;
	cout << "Your bank balance is: " << oldbalance << endl;
	cout << "Please enter deposits, enter -1 when finished: " <<endl;
	while (deposit != -1)
	{
		cin >> deposit;
		sum += deposit;
	}
	cout << "Your deposits total is: " << sum+1 << endl;
	int numLines = 0;
	ifstream in("infile.txt");
	string unused;
	while (getline(in, unused))
	++numLines;
	in.close();
	Checkbook *mocheck;
	mocheck = new Checkbook[numLines];
	ifstream checkStream("infile.txt");
	string next;
	int tempnum;
	double tempamount;
	char tempcashed;
	checkStream >> tempnum;
	checkStream >> tempamount;
	checkStream >> tempcashed;
	mocheck[0].setNum(tempnum);
	mocheck[0].setAmount(tempamount);
	mocheck[0].setCashed(tempcashed);
	while(getline(checkStream, next))
	{
		for (int i = 1; i < numLines; i++)
		{
			int tempnum;
			double tempamount;
			char tempcashed;
			checkStream >> tempnum;
			checkStream >> tempamount;
			checkStream >> tempcashed;
			mocheck[i].setNum(tempnum);
			mocheck[i].setAmount(tempamount);
			mocheck[i].setCashed(tempcashed);
		}
	}
	for (int i = 0; i < numLines; i++)
	{
		for (int j = 1; j < numLines; j++)
		{
			if (mocheck[i].getNum() > mocheck[j].getNum())
			{
				Checkbook temp = mocheck[i];
				//int temp2 = mocheck[j].getNum();
				mocheck[i] = mocheck[j];
				mocheck[j] = temp;
			}
		}
	}

	
		
	cout << "These are the checks that were cashed: " << endl;
	for (int i = numLines-1; i >= 0; i--)
	{
		
		if (mocheck[i].getCashed()==true)
		{
			
			cout << "Check Number: " << mocheck[i].getNum() << endl;
			cout << "Check amount: " << mocheck[i].getAmount() << endl;
			//cout << "Check cashed:" << mocheck[i].getCashed() << endl;
			cout << endl;
		}
	}
	cout << "These are the checks that were not cashed: " << endl;
	for (int j = numLines - 1; j >= 0; j--)
	{
		
		if (mocheck[j].getCashed() == false)
		{
			
			cout << "Check Number: " << mocheck[j].getNum() << endl;
			cout << "Check amount: " << mocheck[j].getAmount() << endl;
			//cout << "Check cashed:" << mocheck[j].getCashed() << endl;
			cout << endl;
				uncashed+= mocheck[j].getAmount();
		}
	}
	cout << "The total of uncashed checks is: " << uncashed << endl;
	cout << "Your true balance is: " << oldbalance - uncashed + sum+1<< endl;
	return 0;
}
Checkbook::Checkbook()
{

}

bool operator< (const Checkbook &c1, const Checkbook &c2)
{
	return c1.num < c2.num;
}
void Checkbook::setNum(int newnum)
{
	num = newnum;

}
void Checkbook::setAmount(double newamount)
{
	amount = newamount;

}
void Checkbook::setCashed(char newcashed)
{
	cashed = newcashed;

}
int Checkbook::getNum()
{
	return num;
}
double Checkbook::getAmount()
{
	return amount;
}
bool Checkbook::getCashed()
{
	if (cashed=='Y' || cashed=='y')
	return true;
	else return false;
}
