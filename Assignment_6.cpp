//============================================================================
// Name        : Assignment_6.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
#define max 26
using namespace std;

//Hashing
//search, edit
class entry
{
        string key;
        string value;
    public:
        friend class dictionary;
//	entry(string k , string v)
//{
//		key=k;
//		value=v;
//}
};


class dictionary
{
        entry e[max];
        int n;
        char empty;
        int collisions;

    public:
        dictionary()
        {
            collisions=0;
        }
        void getdict_WOR();
        void getdict_WR();
        void addword_WOR();
        void addword_WR();
        void display();
        int hashfunc(string key);
        int search();
        int find();
        void edit();
        void delword();
        void delfunc(string dw, int cindex);
        void delfunc2(string dw, int cindex);
};

void dictionary::getdict_WOR()
{
    string k, v;
    int i=0;
//	int collisions=0;
    int hashindex=0;
    while(1)
        {
            cout<<"Enter Key: ";
            cin>>k;
            if(k=="-1")
                {
                    break;
                }
            cout<<"Enter Val: ";
            cin>>v;
            hashindex=hashfunc(k);
            if(e[hashindex].key=="\0")
                {
                    e[hashindex].key=k;
                    e[hashindex].value=v;
//			e[hashindex]= new entry(k, v);
                }
            else
                {
                    collisions++;
                    i=hashindex;
                    while(e[i].key!="\0")
                        {
                            i++;

                        }
                    e[i].key=k;
                    e[i].value=v;
                }

        }
//    cout<<"Number of collisions: "<<collisions<<endl;
}

void dictionary::getdict_WR()
{
    string k, v;
    string shiftk, shiftv;
    int i=0;
	int shift=0;
    int hashindex=0;
    while(1)
        {
            cout<<"Enter Key: ";
            cin>>k;
            if(k=="-1")
                {
                    break;
                }
            cout<<"Enter Val: ";
            cin>>v;
            hashindex=hashfunc(k);
            if(e[hashindex].key=="\0")
                {
                    e[hashindex].key=k;
                    e[hashindex].value=v;
//			e[hashindex]= new entry(k, v);
                }
            else
                {
             	int index=hashfunc(e[hashindex].key);
            		if(index==hashindex)//here key is on proper posn
            		{
            			while(e[index].key!="\0")
            			{
            				index++;
            			}
            			e[index].key=k;
            			e[index].value=v;
            		}
            		else
            		{
            			shiftk=e[hashindex].key;
            			shiftv=e[hashindex].value;
            			e[hashindex].key=k;
            			e[hashindex].value=v;
            			shift=hashindex;
            			while(e[shift].key!="\0")
            			{
            				shift++;
            			}
            			e[shift].key=shiftk;
            			e[shift].value=shiftv;

                }

        }
//    cout<<"Number of collisions: "<<collisions<<endl;
}
}

int dictionary::hashfunc(string key)
{
    int hashindex;
    char pt=key[0];
    if(pt>=65 && pt<=91)//for lower alphabets
        {
            pt=pt-65;//value stored gets
        }
    else if(pt>=97 && pt<=123)
        {
            pt=pt-97;
        }
    hashindex=pt;
    return hashindex;
}

void dictionary::display()
{
    cout<<"\n\n\n\t\t\t  #Hashtag Dictionary#\n";
    int i=0;
    string layout="----";
    while(i<max)
        {
            if(e[i].key!="\0")
                {
                    cout<<"\tHI: "<<i+1<<"\tKey: "<<e[i].key<<"\t\t\tValue: "<<e[i].value<<endl;
                }
            else
                {
                    cout<<"\tHI: "<<i+1<<"\tKey: "<<layout<<"\t\t\tValue: "<<layout<<endl;
                }
            i++;
        }
}

void dictionary::addword_WOR()
{
    string k, v;
    int hashindex=0;
    int i=0;
    cout<<"Enter Key: ";
    cin>>k;
    cout<<"Enter Val: ";
    cin>>v;
    hashindex=hashfunc(k);
    if(e[hashindex].key=="\0")
        {
            e[hashindex].key=k;
            e[hashindex].value=v;
            //			e[hashindex]= new entry(k, v);
        }
    else
        {
            collisions++;
            i=hashindex;
            while(e[i].key!="\0")
                {
                    i++;

                }
            e[i].key=k;
            e[i].value=v;
        }
//    cout<<"Number of collisions: "<<collisions<<endl;
}

void dictionary::addword_WR()
{
    string k, v;
    string shiftk, shiftv;
    int shift=0;
    int hashindex=0;
    int i=0;
    cout<<"Enter Key: ";
    cin>>k;
    cout<<"Enter Val: ";
    cin>>v;
    hashindex=hashfunc(k);
    if(e[hashindex].key=="\0")
        {
            e[hashindex].key=k;
            e[hashindex].value=v;
            //			e[hashindex]= new entry(k, v);
        }
    else//key already present on that entry
    {
    	int index=hashfunc(e[hashindex].key);
		if(index==hashindex)//here key is on proper posn
		{
			while(e[index].key!="\0")
			{
				index++;
			}
			e[index].key=k;
			e[index].value=v;
		}
		else
		{
			shiftk=e[hashindex].key;
			shiftv=e[hashindex].value;
			e[hashindex].key=k;
			e[hashindex].value=v;
			shift=hashindex;
			while(e[shift].key!="\0")
			{
				shift++;
			}
			e[shift].key=shiftk;
			e[shift].value=shiftv;

		}


    }
}

int dictionary::search()
{
    string sw;
    char retry;
    int flag=0;
    do
        {
            cout<<"\n\n[Search]\n\t\tEnter keyword: ";
            cin>>sw;
            int index= hashfunc(sw);
            if(e[index].key=="\0")
            {
            	cout<<"Word not found! Do you wish to retry? ";
            	cin>>retry;
            }
            else
            {
            	while(e[index].key!="\0")
            	{
            		if(e[index].key==sw)
            		{
            			cout<<"\tHI: "<<index+1<<"\tKey: "<<e[index].key<<"\t\t\tValue: "<<e[index].value<<endl;
            			flag=1;
            			retry='n';
            			break;
            		}
            		index++;
            	}
            	if(flag!=1)
            	{
                	cout<<"Word not found! Do you wish to retry? ";
                	cin>>retry;
            	}
            }

        }
    while(retry=='y');
    if(flag != 1)
    {
    	cout<<"[Search] unsuccessful\n";
    }
}


int dictionary::find()//for edit purpose
{
    string ew;
    char retry;
    do
        {
            cout<<"\n\n\t[Edit]\n\t\tEnter keyword: ";
            cin>>ew;
            int i=0;
            int flag =0;
            while(i<max)
                {
                    if(ew==e[i].key)
                        {
                            flag=1;
                            break;
                        }
                    i++;
                }
            if(flag==0)
                {
                    cout<<"Keyword not found! Retry? ";
                    cin>>retry;
                    return -1;
//		return flag;
                }
            else if(flag ==1)
                {
                    return i;
                    retry='n';
                }
        }
    while(retry=='y');
//	return flag;
}
void dictionary::edit()// to be done using hashfunc
{
    int index;
    string ev;
    again:
    index=find();
    if(index==-1)
        {
    		goto again;
//            cout<<"[Edit] unsuccessful\n";
        }
    else
        {
            cout<<"Enter new value for keyword '"<<e[index].key<<"': ";
            cin>>ev;
            cout<<"Previous Value: "<<e[index].value;
            e[index].value=ev;
            cout<<"\t\tNew Value: "<<e[index].value<<endl;
        }

}



void dictionary::delword()
{
	string dw;
	char retry;
	int flag=0;
	do{
		cout<<"Enter word to be deleted: ";
		cin>>dw;
		int index=hashfunc(dw);
		int cindex;
		cindex=index;
		if(e[index].key=="\0")
		{
			cout<<"Word not found! Retry? ";
			cin>>retry;
		}
		else
		{

			while(e[cindex].key!="\0")//while first letters are
			{
				if(e[cindex].key==dw)//word match
				{

					flag=1;
					retry='n';
					delfunc2(dw, cindex);
				}
				else
				{
					cindex++;
				}
			}
			if(flag!=1)
			{
				cout<<"Word not found! Retry? ";
				cin>>retry;
			}
		}
	}while(retry=='y');
}

void dictionary::delfunc(string dw, int cindex)//dw is word deleted, cindex is index where void is present
{
	int tdex;
	tdex=cindex;
	e[cindex].key="\0";
	tdex++;
	cout<<"Enter delfunc\n";
	while(e[tdex].key!="\0")
	{

		if(hashfunc(e[tdex].key)<=cindex)
		{
			cout<<"ping\n";
			e[cindex].key=e[tdex].key;
			e[cindex].value=e[tdex].value;

			delfunc(e[tdex].key, tdex);
			break;
		}
			tdex++;
	}

}

void dictionary::delfunc2(string dw, int cindex)//dw is word deleted, cindex is index where void is present
{
	int tdex, tdex2;
	tdex=cindex;
	e[cindex].key="\0";
	tdex++;
	int flag=0;
//	cout<<"Enter delfunc\n";
	while(e[tdex].key!="\0")
	{

		if(hashfunc(e[tdex].key)==cindex)
		{
			cout<<"ping\n";
			e[cindex].key=e[tdex].key;
			e[cindex].value=e[tdex].value;
			flag=1;
			delfunc(e[tdex].key, tdex);
			break;
		}
			tdex++;
	}

	if(flag!=1)
	{
		tdex2=cindex;
		while(e[tdex2].key!="\0")
		{

			if(hashfunc(e[tdex2].key)<cindex)
			{
				cout<<"ping\n";
				e[cindex].key=e[tdex2].key;
				e[cindex].value=e[tdex2].value;
				flag=1;
				delfunc(e[tdex2].key, tdex2);
				break;
			}
				tdex++;
		}
	}

}





int main()
{
    dictionary d;
    int choice;
    char select, select2;
//    d.getdict_WR();
//    d.display();
//	d.addword();
//	d.display();
//	d.search();
//    d.edit();
//    d.display();
//    d.addword_WR();
//    d.search();
//    d.delword();
//    d.display();
    do{
    cout<<"\t\t\t[MENU]\n\t1.Create Dictionary [W/O R]\n\t2.Create Dictionary [W R]\n";
    cout<<"\t3.Add Word [W/O R]\n\t4.Add Word [W R]\n";
    cout<<"\t5.Search Word\n\t6.Edit Word\n\t7.Delete Word\n\t\tEnter Choice: ";
    cin>>choice;
    switch(choice)
    {
    case 1: d.getdict_WOR();
    d.display();
	break;

    case 2: d.getdict_WR();
    d.display();
    break;

    case 3: d.addword_WOR();
    d.display();
    break;

    case 4: d.addword_WR();
    d.display();
    break;

    case 5: d.search();
    break;

    case 6: d.edit();
    d.display();
    break;

    case 7: d.delword();
    d.display();
    break;

    }
    	cout<<"\t\tDo you wish to continue--> ";
    	cin>>select;


    }while(select=='y');
    if(select=='n')
    {
    	cout<<"\n\n\t\t\t\t[Closing program]\n";
    }

}
