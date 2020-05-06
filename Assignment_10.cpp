//============================================================================
// Name        : Assignment10.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Student
{
    int roll;
    char name[20];
    int div;
    char address[50];
public:
    friend class fileop;

    Student()
    {
        roll=0;
        div=0;
    }
    void getdata();
    void displaydata();
    void getdata2(int x);
};
    void Student::getdata()
    {
        cout<<"Enter Roll: ";
        cin>>roll;
        if(roll == -1)
        {
            return;
        }
        cin.ignore(1);
        cout<<"Enter Name: ";
        cin.getline(name, 19);
        cout<<"Enter Div: ";
        cin>>div;
        cin.ignore(1);
        cout<<"Enter Address: ";
        cin.getline(address, 49);
        cout<<endl;
    }
    void Student::displaydata()
    {
        cout<<"\t\t\t\t-------------------------------------------"<<endl;
        cout<<"\t\t\t\t\tName: "<<name<<"\n\t\t\t\t\tDiv: "<<div<<"\t\tRoll No: "<<roll<<endl;
        cout<<"\t\t\t\t\tAddress:- "<<address<<endl;
        cout<<"\t\t\t\t-------------------------------------------"<<endl;
    }

    void Student::getdata2(int x)
    {
        roll=x;
        if(roll == -1)
        {
            return;
        }
        cin.ignore(1);
        cout<<"Enter Name: ";
        cin.getline(name, 19);
        cout<<"Enter Div: ";
        cin>>div;
        cin.ignore(1);
        cout<<"Enter Address: ";
        cin.getline(address, 49);
    }

class fileop
{
    fstream file;
public:
    void create();
    void append();
    void display();
    void search();
    void edit();
    void delentry();
};

void fileop::create()
{
    Student s;
    file.open("student.dat", ios::out);
    while(1)
    {
        s.getdata();
        if(s.roll == -1)
        {
            break;
        }
        file.write( (char *)&s, sizeof(s) );
    }
    file.close();
}

void fileop::append()
{
    Student s;
    file.open("student.dat", ios::app);
    s.getdata();
    file.write( (char *)&s, sizeof(s) );
    file.close();
}


void fileop::display()
{
    Student s;
    file.open("student.dat", ios::in);
    while(!file.eof())
    {
        file.read( (char *)&s, sizeof(s) );
        if(!file.eof())
        {
            s.displaydata();
        }
    }
    file.close();
}

void fileop::search()
{
    Student s;
    char retry;
    int sroll;
    int flag=0;
    cout<<" Enter Roll No: ";
    cin>>sroll;
    file.open( "student.dat", ios::in);
    while(!file.eof())
    {
        file.read( (char*)&s, sizeof(s) );
        if(!file.eof() && s.roll == sroll)
        {
            flag=1;
            retry='n';
            cout<<"\tStudent Details are:- \n";
            s.displaydata();
        }
    }
    if(flag!=1)
    {
        cout<<"\n\t\t\t\t[Error]  Data not found!\n\n";
    }
}


void fileop::edit()
{
    Student s;
    int eroll;
    int flag=0;
    fstream temp;
    cout<<"Enter Roll No: ";
    cin>>eroll;
    file.open( "student.dat", ios::in);
    temp.open( "temp.dat", ios::out);
    while(file.read( (char *)&s, sizeof(s)))
    {
        if(s.roll != eroll)
        {
            temp.write( (char *)&s, sizeof(s));
        }
        else if(s.roll == eroll)
        {
            flag=1;
            s.getdata2(eroll);
            temp.write( (char *)&s, sizeof(s));
        }
    }
    if(flag!=1)
    {
        cout<<"\n\t\t\t\t[Error]  Data not found!\n\n";
    }
    file.close();
    temp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");

}

void fileop::delentry()
{
    Student s;
    int droll;
    int flag=0;
    fstream temp;
    cout<<"Enter Roll No: ";
    cin>>droll;
    file.open( "student.dat", ios::in);
    temp.open( "temp.dat", ios::out);
    while(file.read( (char *)&s, sizeof(s)))
    {
        if(s.roll != droll)
        {
            temp.write( (char *)&s, sizeof(s));
        }
        else if(s.roll == droll)
        {
            flag=1;
        }
    }
    if(flag!=1)
    {
        cout<<"\n\t\t\t\t[Error]  Data not found!\n\n";
    }
    file.close();
    temp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
}



int main()
{
   
    int choice;
    char select;
    do{
         fileop f;
    cout<<"\t\t\t\t\t\t[MENU]\n\t\t\t\t\t1.Create\n\t\t\t\t\t2.Append\n\t\t\t\t\t3.Search\n\t\t\t\t\t4.Edit\n\t\t\t\t\t5.Delete\n\t\t\t\t\t6.Display\n\t\t\t\t\t  Enter Choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1: {
            cout<<"\t\t\t\t[Create]\n";
            f.create();
            cout<<"\t\t\t\t\t    [STUDENT DATABASE]\n";
            f.display();
            break;
        }
        case 2: {
            cout<<"\t\t\t\t[Append]\n";
            f.append();
            cout<<"\t\t\t\t\t    [STUDENT DATABASE]\n";
            f.display();
            break;
        }
        case 3: {
            cout<<"\t\t\t\t[Search]\n";
            f.search();
            break;
        }
        case 4: {
            cout<<"\t\t\t\t[Edit]\n";
            f.edit();
            cout<<"\t\t\t\t\t    [STUDENT DATABASE]\n";
            f.display();
            break;
        }
        case 5: {
            cout<<"\t\t\t\t[Delete]\n";
            f.delentry();
            cout<<"\t\t\t\t\t    [STUDENT DATABASE]\n";
            f.display();
            break;
        }
        case 6: {
            cout<<"\t\t\t\t[Display]\n";
            f.display();
            break;
        }
    }
    cout<<"Do you wish to continue? -> ";
    cin>>select;
    }while(select=='y');
    return 0;
}

