#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Admin
{
	public:
	int t_no,fseat,sseat,date,ffare,sfare,fseatb,sseatb;
	string b_pt,d_pt,t_name;
	Admin()
	{
		fseatb = 0;
		sseatb = 0;
		t_no=0;
		fseat=0;
		sseat=0;
		date=0;
		ffare=0;
		sfare=0;
	}
	void input();              //take details
	void show();                //show details of 1 train
	void display();                  //show details of each train                        

};

void Admin::input()
{
	cout<<"Train Number : "<<endl;
	cin>>t_no;
	cout<<"Train Name : "<<endl;
	cin>>t_name;
	cout<<"Boarding Point : "<<endl;
	cin>>b_pt;
	cout<<"Destination Point : "<<endl;
	cin>>d_pt;
	cout<<"Date of Journey : "<<endl;
	cin>>date;
	cout<<"No. of seats in first class : "<<endl;
	cin>>fseat;
	cout<<"No. of seats in second class : "<<endl;
	cin>>sseat;
	cout<<"Fare of first class seat : "<<endl;
	cin>>ffare;
	cout<<"Fare of second class seat : "<<endl;
	cin>>sfare;
}

void Admin::show()
{
	cout<<"Train Number :"<<t_no<<endl;
	cout<<"Train Name :"<<t_name<<endl<<endl;
	cout<<"Boarding Point :"<<b_pt<<endl;
	cout<<"Destination Point :"<<d_pt<<endl;
	cout<<"Date :"<<date<<endl<<endl;
	cout<<"Total seats in first class :"<<fseat<<endl;
	cout<<"Total seats in second class :"<<sseat<<endl<<endl;
	cout<<"Remaining seats in first class :"<<(fseat-fseatb)<<endl;
	cout<<"Remaining seats in second class :"<<(sseat-sseatb)<<endl;
}

void Admin::display()
{
	cout<<t_no<<"\t"<<t_name<<"\t"<<b_pt<<"\t"<<d_pt<<"\t"<<(fseat-fseatb)<<"\t"<<(sseat-sseatb)<<endl;
}


void addTrain()
{
	Admin a;
	ofstream f;
	f.open("train.txt",ios::app);
	a.input();
	f<<a.t_no<<" "<<a.t_name<<" "<<a.b_pt<<" "<<a.d_pt<<" "<<a.date<<" "<<a.fseat<<" "<<a.sseat<<" "<<a.ffare<<" "<<a.sfare<<endl;
	// f.write((char*)&a, sizeof(a));
	cout<<"Train added successfully "<<endl<<endl;
	f.close();
}

void showTrainNo()
{
	ifstream f;
	Admin a;
	int t_no1,chk=0;
	cout<<"Enter train no. to display details  "<<endl;
	cin>>t_no1;
	f.open("train.txt");
	if(f.fail())
		cout<<"Can't open file "<<endl;
	else
	{
		while(!f.eof())
		{
			f>>a.t_no>>a.t_name>>a.b_pt>>a.d_pt>>a.date>>a.fseat>>a.sseat>>a.ffare>>a.sfare;
			if(a.t_no==t_no1)
			{
				a.show();
				chk=1;
				break;
			}
		}
		if(chk==0)            //chk is a flag to check the bus whether found or not
			cout<<"Train not found "<<endl;
	}
	f.close();
}

void showTrains()
{
	ifstream f;
	Admin a;
	f.open("train.txt",ios::in);
	while(!f.eof())
	{
		f>>a.t_no>>a.t_name>>a.b_pt>>a.d_pt>>a.date>>a.fseat>>a.sseat>>a.ffare>>a.sfare;
		// f.read((char *)&a , sizeof(a));
		a.display();
	}
	f.close();

	cout<<"Press enter to continue "<<endl;
	
}

void deleteTrain()
{
	int t_no1;
	fstream f;
	ofstream g;
	Admin a;
	int chk = 0;
	cout<<"Enter the train number to be deleted "<<endl;
	cin>>t_no1;
	f.open("train.txt",ios::in | ios::binary);
       if (!f)
       {
              cout << "File could not be open !! Press any Key...";
              return;
       }
       g.open("temp.txt",ios::out | ios::binary);
       f.seekg(0, ios::beg);
       while (f.read(reinterpret_cast<char *> (&a), sizeof(a)))
       {
              if (a.t_no!=t_no1)
              {
                     g.write(reinterpret_cast<char *> (&a), sizeof(a));
              }
       }
       f.close();
       g.close();
       remove("train.txt");
       rename("temp.txt", "train.txt");
}

int main()
{
	cout<<"---------------------------------RAILWAY RESERVATION----------------------------------------"<<endl;
	cout<<"--------------------------------------------------------------------------------------------"<<endl;
	cout<<"-----------------------------------MAINMENU-------------------------------------------------"<<endl<<endl;
	
	int ch;
	do
	{
		cout<<"1. Add new Train "<<endl;
		cout<<"2. Show selective Train "<<endl;
		cout<<"3. Show all Trains "<<endl;
		cout<<"4. Delete a train "<<endl;
		cout<<"5. Book tickets "<<endl;
		cout<<"6. Exit "<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:		addTrain();
						break;
				
			case 2:		showTrainNo();
						break;
				
			case 3:		showTrains();
						break;
				
			case 4:		deleteTrain();
						break;
		}
	}
	while(ch!=6);
	
	return 0;
}