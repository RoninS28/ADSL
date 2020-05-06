//============================================================================
// Name        : Assignment_7.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
using namespace std;
#define max 26

class symbol
{
	string name;
	string type;
	double value;
public:
	friend class symtab;
	symbol()
{
		name="\0";
		type="\0";
		value=-1;
}

};

class symtab
{
	symbol sym[max];
	int chain[max];
public:
	symtab()
{
		for(int i=0; i<max; i++)
		{
			chain[i]=-1;
		}
}
	int hashfunc(string name);
	void insert_WOR();
	void add_WOR();
	void display();
	void search_WOR();
	void edit_WOR();
	void insert_WR();
	void add_WR();
	void search_WR();
    void edit_WR();
	void updateindex(int oldex, int newdex, int shifthash);
	void delentry_WR();
	void delentry_WOR();
	void delindex(int index);

};

int symtab::hashfunc(string name)
{
    int hashindex;
    char pt=name[0];
    if(pt>=65 && pt<=91)//for lower case
        {
            pt=pt-65;//value stored gets
        }
    else if(pt>=97 && pt<=123)//for upper case
        {
            pt=pt-97;
        }
    hashindex=pt;
    return hashindex;
}

void symtab::insert_WOR()
{
	int index;
	int trav;
	int tdex;
	int cindex;//chain index
	string n, t;
	double v;
	while(1)
	{
		cout<<"Enter name: ";
		cin>>n;
		if(n=="-1")
		{
			break;
		}
		cout<<"Enter type: ";
		cin>>t;
		cout<<"Enter value: ";
		cin>>v;
		index=hashfunc(n);
		if(sym[index].name=="\0")//no word is present at this bucket
		{
			sym[index].name=n;
			sym[index].type=t;
			sym[index].value=v;
		}
		else//bucket isnt empty
		{
			if(hashfunc(sym[index].name)==index)//bucket word matches with to be inserted word
			{
				cindex=index;
				while(chain[cindex]!=-1)
				{
					cindex=chain[cindex];
				}
				//now cindex is pointing to last word of that letter
				trav=cindex;
				trav++;
				while(sym[trav].name!="\0")
				{
					trav++;
				}
				//now trav is index of empty bucket
				sym[trav].name=n;
				sym[trav].type=t;
				sym[trav].value=v;
				chain[cindex]=trav;
			}
			else//bucket word is other than to be inserted word
			{
//				cout<<"Bucket trespass\n";
				tdex=index;
				while(sym[tdex].name!="\0" && index!=hashfunc(sym[tdex].name))
				{
					tdex++;
				}
//				if(sym[tdex].name=="\0")//here it is the first word in the table
//				{
//					cout<<"ALone\n";
//					sym[tdex].name=n;
//					sym[tdex].type=t;
//					sym[tdex].value=v;
//				}
				if( index==hashfunc(sym[tdex].name) )
				{
//					cout<<"Refuge match\n";
					cindex=tdex;
//					cindex=index;
					while(chain[cindex]!=-1)
					{
						cindex=chain[cindex];
					}
					//now cindex is pointing to last word of that letter
					trav=cindex;
					trav++;
					while(sym[trav].name!="\0")
					{
						trav++;
					}
					//now trav is index of empty bucket
					sym[trav].name=n;
					sym[trav].type=t;
					sym[trav].value=v;
//					cout<<"cool\n";
					chain[cindex]=trav;
//					chain[cindex]=tdex;
				}
				else
				{
//					cout<<"ALone\n";
					sym[tdex].name=n;
					sym[tdex].type=t;
					sym[tdex].value=v;
				}


			}
		}
	}
}

void symtab::add_WOR()
{
	int index;
	int trav;
	int tdex;
	int cindex;//chain index
	string n, t;
	double v;

		cout<<"Enter name: ";
		cin>>n;
		cout<<"Enter type: ";
		cin>>t;
		cout<<"Enter value: ";
		cin>>v;
		index=hashfunc(n);
		if(sym[index].name=="\0")//no word is present at this bucket
		{
			sym[index].name=n;
			sym[index].type=t;
			sym[index].value=v;
		}
		else//bucket isnt empty
		{
			if(hashfunc(sym[index].name)==index)//bucket word matches with to be inserted word
			{
				cindex=index;
				while(chain[cindex]!=-1)
				{
					cindex=chain[cindex];
				}
				//now cindex is pointing to last word of that letter
				trav=cindex;
				trav++;
				while(sym[trav].name!="\0")
				{
					trav++;
				}
				//now trav is index of empty bucket
				sym[trav].name=n;
				sym[trav].type=t;
				sym[trav].value=v;
				chain[cindex]=trav;
			}
			else//bucket word is other than to be inserted word
			{
//				cout<<"Bucket trespass\n";
				tdex=index;
				while(sym[tdex].name!="\0" && index!=hashfunc(sym[tdex].name))
				{
					tdex++;
				}
				if( index==hashfunc(sym[tdex].name) )
				{
					cindex=tdex;
					while(chain[cindex]!=-1)
					{
						cindex=chain[cindex];
					}
					//now cindex is pointing to last word of that letter
					trav=cindex;
					trav++;
					while(sym[trav].name!="\0")
					{
						trav++;
					}
					//now trav is index of empty bucket
					sym[trav].name=n;
					sym[trav].type=t;
					sym[trav].value=v;
					chain[cindex]=trav;
				}
				else
				{
					sym[tdex].name=n;
					sym[tdex].type=t;
					sym[tdex].value=v;
				}


			}
		}

}
void symtab::display()
{
	string layout="-----";
	cout<<"\t\t\t\t\t\t#Symbol Table#\n\n";
	cout<<"\tHI\t\t\tName\t\t\tType\t\t\tValue\t\t\tChain Index"<<endl;
	for(int i=0; i<max; i++)
	{
		if(sym[i].name!="\0" && chain[i]!=-1)
		{
//			cout<<"\tHI: "<<i+1<<"\t\t\tName: "<<sym[i].name<<"\t\t\tType: "<<sym[i].type<<"\t\t\tValue: "<<sym[i].value<<"\t\t\tChain: "<<chain[i]+1<<endl;
			cout<<"\t "<<i+1<<"\t\t\t  "<<sym[i].name<<"\t\t\t  "<<sym[i].type<<"\t\t\t   "<<sym[i].value<<"\t\t\t  "<<chain[i]+1<<endl;
		}
		else if(sym[i].name!="\0" && chain[i]==-1)
		{
//			cout<<"\tHI: "<<i+1<<"\t\t\tName: "<<sym[i].name<<"\t\t\tType: "<<sym[i].type<<"\t\t\tValue: "<<sym[i].value<<"\t\t\tChain: "<<chain[i]+1<<endl;
			cout<<"\t "<<i+1<<"\t\t\t  "<<sym[i].name<<"\t\t\t  "<<sym[i].type<<"\t\t\t   "<<sym[i].value<<"\t\t\t "<<chain[i]<<endl;
		}

		else
		{
//			cout<<"\tHI: "<<i+1<<"\t\t\tName: "<<layout<<"\t\t\tType: "<<layout<<"\t\t\tValue: "<<layout<<endl;
			cout<<"\t "<<i+1<<"\t\t\t "<<layout<<"\t\t\t "<<layout<<"\t\t\t "<<layout<<"\t\t\t "<<chain[i]<<endl;
		}
	}
}

void symtab::search_WOR()
{
	string sname;
	char retry;
	int flag=-1;
	int csi=-1;//chaining index
	int psi=-1;//probing index
	do{
	cout<<"Enter Name to be searched: ";
	cin>>sname;
	int si=hashfunc(sname);
	if(sym[si].name=="\0")//if that bucket is empty
	{
		flag=0;
	}
	else//entry present at that bucket
	{
		if(si==hashfunc(sym[si].name))//first letter matches
		{
			csi=si;
//			while(sym[csi].chain!=-1)
			while(chain[csi]!=-1)
			{
				if(sym[csi].name==sname)
				{
					flag=1;//successful word searched
					break;
				}
				csi=chain[csi];
//				csi=sym[csi].chain;
			}
				if(sym[csi].name==sname)
				{
					flag=1;//successful word searched
					//break;
				}
		}
		else//some other word is present
		{
			psi=si;
			while(sym[psi].name!="\0")
			{
				psi++;
				if(hashfunc(sym[psi].name)==si)
				{
//					csi=si;
					csi=psi;
					while(chain[csi]!=-1)
					{
						if(sym[csi].name==sname)
						{
							flag=1;//successful word searched
							break;
						}
						csi=chain[csi];
		//				csi=sym[csi].chain;
					}
					if(sym[csi].name==sname)
					{
						flag=1;//successful word searched
						break;
					}
				}
			}
		}
	}
	if(flag!=1)
	{
		cout<<"Entry not present! Retry? ";
		cin>>retry;
	}
	else
	{
		cout<<"\tHashIndex: "<<csi+1<<"\n\tName: "<<sym[csi].name<<"\tType: "<<sym[csi].type<<"\tValue: "<<sym[csi].value<<endl;
//		cout<<"\tHI: "<<csi+1<<"\t\t\tName: "<<sym[csi].name<<"\t\t\tType: "<<sym[csi].type<<"\t\t\tValue: "<<sym[csi].value<<endl;
		retry='n';
	}
	}while(retry=='y');
}

void symtab::edit_WOR()
{
	string sname;
	string stype;
	double sval;
	char retry;
	int flag=-1;
	int csi=-1;//chaining index
	int psi=-1;//probing index
	do{
	cout<<"Enter Name to be edited: ";
	cin>>sname;
	cout<<"Enter new Type: ";
	cin>>stype;
	cout<<"Enter new Value: ";
	cin>>sval;
	int si=hashfunc(sname);
	if(sym[si].name=="\0")//if that bucket is empty
	{
		flag=0;
	}
	else//entry present at that bucket
	{
		if(si==hashfunc(sym[si].name))//first letter matches
		{
			csi=si;
//			while(sym[csi].chain!=-1)
			while(chain[csi]!=-1)
			{
				if(sym[csi].name==sname)
				{
					flag=1;//successful word searched
					break;
				}
				csi=chain[csi];
//				csi=sym[csi].chain;
			}
				if(sym[csi].name==sname)
				{
					flag=1;//successful word searched
					//break;
				}
		}
		else//some other word is present
		{
			psi=si;
			while(sym[psi].name!="\0")
			{
				psi++;
				if(hashfunc(sym[psi].name)==si)
				{
//					csi=si;
					csi=psi;
					while(chain[csi]!=-1)
					{
						if(sym[csi].name==sname)
						{
							flag=1;//successful word searched
							break;
						}
						csi=chain[csi];
		//				csi=sym[csi].chain;
					}
					if(sym[csi].name==sname)
					{
						flag=1;//successful word searched
						break;
					}
				}
			}
		}
	}
	if(flag!=1)
	{
		cout<<"Entry not present! Retry? ";
		cin>>retry;
	}
	else
	{
//		cout<<"\tHashIndex: "<<csi+1<<"\n\tName: "<<sym[csi].name<<"\tType: "<<sym[csi].type<<"\tValue: "<<sym[csi].value<<endl;
//		cout<<"\tHI: "<<csi+1<<"\t\t\tName: "<<sym[csi].name<<"\t\t\tType: "<<sym[csi].type<<"\t\t\tValue: "<<sym[csi].value<<endl;
		sym[csi].type=stype;
		sym[csi].value=sval;
//		cout<<"\tHashIndex: "<<csi+1<<"\n\tName: "<<sym[csi].name<<"\tType: "<<sym[csi].type<<"\tValue: "<<sym[csi].value<<endl;
		retry='n';
	}
	}while(retry=='y');
}

//-------------- appended---------------------
void symtab::updateindex(int oldex, int newdex, int shifthash)
{
    int tempindex;
    int flag=0;
    //old is hashindex where new entry is to be entered
    //new is the place where the pre existing entry is shifted to
    int cindex;
    cindex=oldex;
    while(cindex>=0)
    {
        if(hashfunc(sym[cindex].name)==shifthash)
        {
            flag=1;
            break;
        }
        cindex--;
    }
    if(flag==1)
    {
        chain[cindex]=newdex;//link pointing to prev loc now pt to updated index of shifted entry
    }
    //Optional::: we should also shift the prev->index to new location's chaining index
    tempindex = chain[oldex];
    chain[oldex] = -1;
    chain[newdex] = tempindex;
}

void symtab::insert_WR()
{
    string shiftn, shiftt;
    double shiftv;
    int index;
    int shifthash;
	int trav;
	int tdex;
	int cindex;//chain index
	string n, t;
	double v;
	while(1)
	{
		cout<<"Enter name: ";
		cin>>n;
		if(n=="-1")
		{
			break;
		}
		cout<<"Enter type: ";
		cin>>t;
		cout<<"Enter value: ";
		cin>>v;
		index=hashfunc(n);
		if(sym[index].name=="\0")//no word is present at this bucket
		{
			sym[index].name=n;
			sym[index].type=t;
			sym[index].value=v;
		}
		else//bucket isnt empty
		{
			if(hashfunc(sym[index].name)==index)//bucket word matches with to be inserted word
			{
				cindex=index;
				while(chain[cindex]!=-1)
				{
					cindex=chain[cindex];
				}
				//now cindex is pointing to last word of that letter
				trav=cindex;
				trav++;
				while(sym[trav].name!="\0")
				{
					trav++;
				}
				//now trav is index of empty bucket
				sym[trav].name=n;
				sym[trav].type=t;
				sym[trav].value=v;
				chain[cindex]=trav;
			}
			else//bucket word is other than to be inserted word
			{
				shiftn=sym[index].name;
				shiftt=sym[index].type;
				shiftv=sym[index].value;
				sym[index].name=n;
    			sym[index].type=t;
    			sym[index].value=v;
    			trav=index;
    			shifthash=hashfunc(shiftn);
    			while(sym[trav].name != "\0")
    			{
    			    trav++;
                }
                sym[trav].name=shiftn;
				sym[trav].type=shiftt;
				sym[trav].value=shiftv;
				cout<<"Updated\n";
				updateindex(index, trav, shifthash);
//    			while(sym[trav].name != "\0" && hashfunc(sym[trav].name) != shifthash )
//    			{
//    			    trav++;
//                }
//                if(sym[trav].name == "\0")//no entry is present after it of its hashinddex
//                {
//                    sym[trav].name=shiftn;
//    				sym[trav].type=shiftt;
//    				sym[trav].value=shiftv;
//                }
//                else//some entry of that hasindex is present
//                {
//                    cindex=trav;
//                    while(chain[cindex] != -1)
//                    {
//                        cindex = chain[cindex];
//                    }
//                    // now cindex is pointing to the last entry of that hashindex
//                    trav=cindex;
//                    while(sym[trav].name != "\0")
//                    {
//                        trav++;
//                    }
//                    //now trav is pointing to an empty bucket
//                    sym[trav].name=shiftn;
//    				sym[trav].type=shiftt;
//    				sym[trav].value=shiftv;
//    				chain[cindex]=trav;
//                }

			}
		}
	}
}
void symtab::add_WR()
{
    string shiftn, shiftt;
    double shiftv;
    int index;
    int shifthash;
	int trav;
	int tdex;
	int cindex;//chain index
	string n, t;
	double v;
		cout<<"Enter name: ";
		cin>>n;
		cout<<"Enter type: ";
		cin>>t;
		cout<<"Enter value: ";
		cin>>v;
		index=hashfunc(n);
		if(sym[index].name=="\0")//no word is present at this bucket
		{
			sym[index].name=n;
			sym[index].type=t;
			sym[index].value=v;
		}
		else//bucket isnt empty
		{
			if(hashfunc(sym[index].name)==index)//bucket word matches with to be inserted word
			{
				cindex=index;
				while(chain[cindex]!=-1)
				{
					cindex=chain[cindex];
				}
				//now cindex is pointing to last word of that letter
				trav=cindex;
				trav++;
				while(sym[trav].name!="\0")
				{
					trav++;
				}
				//now trav is index of empty bucket
				sym[trav].name=n;
				sym[trav].type=t;
				sym[trav].value=v;
				chain[cindex]=trav;
			}
			else//bucket word is other than to be inserted word
			{
				shiftn=sym[index].name;
				shiftt=sym[index].type;
				shiftv=sym[index].value;
				sym[index].name=n;
    			sym[index].type=t;
    			sym[index].value=v;
    			trav=index;
    			shifthash=hashfunc(shiftn);
    			while(sym[trav].name != "\0")
    			{
    			    trav++;
                }
                sym[trav].name=shiftn;
				sym[trav].type=shiftt;
				sym[trav].value=shiftv;
				cout<<"Updated\n";
				updateindex(index, trav, shifthash);
			}
		}

}

void symtab::search_WR()
{
    string sname;
    int cindex;
    int flag=0;
    char retry;
    do{

    cout<<"Enter word to be searched: ";
    cin>>sname;
    int hashindex=hashfunc(sname);
    if(hashfunc(sym[hashindex].name) != hashindex)//some other word is present at that bucket
    {
        flag=0;
    }
    else//both hashindex matches
    {
        cindex=hashindex;
        while(chain[cindex] != -1)
        {
            if(sym[cindex].name == sname)
            {
                flag=1;
                break;
            }
            cindex=chain[cindex];
        }
        if(sym[cindex].name == sname)
        {
            flag=1;
        }
    }
    if(flag!= 1)
    {
        cout<<"Entry not present! Retry? ";
        cin>>retry;
    }
    else
    {
        cout<<"/t Word found!\n";
         cout<<"\tHI: "<<cindex+1<<"\t\t\tName: "<<sym[cindex].name<<"\t\t\tType: "<<sym[cindex].type<<"\t\t\tValue: "<<sym[cindex].value<<endl;
         retry='n';
    }
    }while(retry=='y');
}


void symtab::edit_WR()
{
    string sname;
    string et;
    double ev;
    int cindex;
    int flag=0;
    char retry;
    do{

    cout<<"Enter word to be edited: ";
    cin>>sname;
    int hashindex=hashfunc(sname);
    if(hashfunc(sym[hashindex].name) != hashindex)//some other word is present at that bucket
    {
        flag=0;
    }
    else//both hashindex matches
    {
        cindex=hashindex;
        while(chain[cindex] != -1)
        {
            if(sym[cindex].name == sname)
            {
                flag=1;
                break;
            }
            cindex=chain[cindex];
        }
        if(sym[cindex].name == sname)
        {
            flag=1;
        }
    }
    if(flag!= 1)
    {
        cout<<"Entry not present! Retry? ";
        cin>>retry;
    }
    else
    {
        cout<<"/t Entry found! Existing data:-\n";
        cout<<"\tHI: "<<cindex+1<<"\t\t\tName: "<<sym[cindex].name<<"\t\t\tType: "<<sym[cindex].type<<"\t\t\tValue: "<<sym[cindex].value<<endl;
        cout<<"Enter new Type: ";
        cin>>et;
        cout<<"Enter new Value: ";
        cin>>ev;
        sym[cindex].type=et;
        sym[cindex].value=ev;
//        cout<<"/tUpdated data:-\n";
//        cout<<"\tHI: "<<cindex+1<<"\t\t\tName: "<<sym[cindex].name<<"\t\t\tType: "<<sym[cindex].type<<"\t\t\tValue: "<<sym[cindex].value<<endl;
        retry='n';
    }
    }while(retry=='y');
}


void symtab::delentry_WOR()
{
    string dw;
    int tindex;//for probing
    int cindex;
    int flag = 0;
    int prev;
    int temp;
    cout<<"Enter word to be deleted: ";
    cin>>dw;
    int index = hashfunc(dw);
    if(sym[index].name == "\0")
    {
        //nothing is present at that bucket
        flag = 0;
    }
    else
    {
        //something is present at that bucket
        if(hashfunc(sym[index].name) == index)
        {
            //same category entry
            tindex=index;
            prev = index;
            while(chain[tindex] != -1)
            {
                if( sym[tindex].name == dw)
                {
                    //word found
                    flag = 1;

                }
                prev=tindex;
//                tindex++;
                  tindex = chain[tindex];
            }
            if(flag ==1 && prev==index)//first word itself is to be deleted
            {
                if(chain[prev] == -1)//only word present
                {
                    sym[prev].name = "\0";
                    sym[prev].type = "\0";
                    sym[prev].value= -1;
                }
                else
                {
                    cindex=prev;
                    while(chain[cindex] != -1)
                    {
                        temp = chain[cindex];
                        sym[cindex].name = sym [temp].name;
                        sym[cindex].type = sym [temp].type;
                        sym[cindex].value = sym [temp].value;
                        temp=cindex;//acts as prev
                        cindex = chain[cindex];
                    }
                    chain[temp] = -1;//last entry of that type
                    sym[cindex].name = "\0";
                    sym[cindex].type = "\0";
                    sym[cindex].value= -1;

                }
            }
            else if(flag ==1 && tindex==index)//word is midway
            {
                cindex=tindex;
                while(chain[cindex] != -1)
                {
                    temp = chain[cindex];
                    sym[cindex].name = sym [temp].name;
                    sym[cindex].type = sym [temp].type;
                    sym[cindex].value = sym [temp].value;
                    temp=cindex;//acts as prev
                    cindex = chain[cindex];
                }
                chain[temp] = -1;
                sym[cindex].name = "\0";
                sym[cindex].type = "\0";
                sym[cindex].value= -1;
            }

        }
        else if(hashfunc(sym[index].name) != index)//some other word is present at that bucket
        {
            tindex=index;
            while(sym[tindex].name != "\0" && index != hashfunc(sym[tindex].name))
            {
//                if(sym[tindex].name ==dw)
//                {
//                    flag=1;//word found
//                    break;
//                }
                tindex++;
            }
            if(sym[tindex].name == "\0")
            {
                //word not found of same hashindex
                flag=0;
            }
            else if(index == hashfunc(sym[tindex].name))//word of same hashindex found
            {
                cindex=index;
                prev = index;
                while(chain[cindex] != -1)
                {
                    if(sym[cindex].name == dw)
                    {
                        flag = 1;
                        break;
                    }
                    prev=cindex;
                    cindex++;
                }
                if(flag == 1)
                {
                    if(prev == index)//first word is to be deleted
                    {
                        sym[prev].name = "\0";
                        sym[prev].type = "\0";
                        sym[prev].value= -1;
                    }
                    else
                    {
                        while(chain[cindex] != -1)
                        {
                            temp = chain[cindex];
                            sym[cindex].name = sym [temp].name;
                            sym[cindex].type = sym [temp].type;
                            sym[cindex].value = sym [temp].value;
                            temp=cindex;//acts as prev
                            cindex = chain[cindex];
                        }
                        //now cindex is pointing to the last entry
                        //temp is pointing to second last entry
                        chain[temp] = -1;
                        sym[cindex].name = "\0";
                        sym[cindex].type = "\0";
                        sym[cindex].value= -1;
                    }
                }
            }
        }
        if(flag != 1)
        {
            cout<<"[Error] Word to be deleted not found\n";
        }
    }

}

void symtab::delentry_WR()
{
    string dw;
    cout<<"Enter word to be deleted: ";
    cin>>dw;
    int prev, temp, tindex, cindex;
    int flag=0;
    int hashindex = hashfunc(dw);
    if(sym[hashindex].name =="\0" || hashindex != hashfunc(sym[hashindex].name))
    {
        //case of failure
        flag=0;
    }
    else//hashindex matches with dw
    {
        tindex = hashindex;
        prev = hashindex;
        while(chain[tindex] != -1)
        {
//            prev = tindex;
            if(sym[tindex].name == dw)
            {
                flag =1;
                break;
            }
            prev = tindex;
            tindex = chain[tindex];
        }
        if(sym[tindex].name == dw)
            {
                flag =1;
//                break;
            }
        if(flag == 1)
        {

            if(prev == hashindex && chain[prev] ==-1) //whole sole entry
            {
                sym[prev].name = "\0";
                sym[prev].type = "\0";
                sym[prev].value= -1;
            }
            else
            {
              temp = prev;
                while(chain[tindex] != -1)
                {
                    temp = chain[tindex];
                    sym[tindex].name = sym [temp].name;
                    sym[tindex].type = sym [temp].type;
                    sym[tindex].value = sym [temp].value;
                    temp=tindex;//acts as prev
                    tindex = chain[tindex];
                }
                chain[temp] = -1;//second last entry
                sym[tindex].name = "\0";
                sym[tindex].type = "\0";
                sym[tindex].value= -1;

            }
        }
        if(flag != 1)
        {
            cout<<"[Error] Word not found\n";
        }
    }
}

int main()
{
	symtab s, s1;
	int repl;
	int choice, choice2;
    char select, select2;
//	s.insert_WOR();
//	s.display();
//	s.search_WOR();
//	s.edit_WOR();
	do{

	    cout<<"\tEnter Operation type:-\t1. With Replacement\n\t\t\t\t2. Without Replacement\n\tEnter Choice: ";
    cin>>repl;
    do{
        cout<<"\t\t\t\t\t\t[MENU]\n";
        cout<<"\t\t1. Insert Entries\n";
        cout<<"\t\t2. Display\n";
        cout<<"\t\t3. Search\n";
        cout<<"\t\t4. Edit\n";
        cout<<"\t\t5. Delete\n";
        cout<<"\t\t6. Add Entry\n";
        cout<<"\t Enter Choice: ";
        cin>>choice;
        choice2=choice;
        if(repl == 1)
        {
            switch(choice)
            {
                case 1: {
                    cout<<"[Insert]\n";
                    s.insert_WR();
                    s.display();
                    break;
                }
                case 2: {
                    cout<<"[Display]\n";
                    s.display();
                    break;
                }
                case 3: {
                    cout<<"[Search]\n";
                    s.search_WR();
                    break;
                }
                case 4: {
                    cout<<"[Edit]\n";
                    s.edit_WR();
                    s.display();
                    break;
                }
                case 5: {
                    cout<<"[Delete]\n";
                    s.delentry_WR();
                    s.display();
                    break;
                }
                case 6: {
                	cout<<"[Add]\n";
                	s.add_WR();
                	s.display();
                	break;
                }

            }
        }
        else if(repl == 2)
        {
            switch(choice2)
            {
                case 1: {
                    cout<<"[Insert]\n";
                    s1.insert_WOR();
                    s1.display();
                    break;
                }
                case 2: {
                    cout<<"[Display]\n";
                    s1.display();
                    break;
                }
                case 3: {
                    cout<<"[Search]\n";
                    s1.search_WOR();
                    break;
                }
                case 4: {
                    cout<<"[Edit]\n";
                    s1.edit_WOR();
                    s1.display();
                    break;
                }
                case 5: {
                    cout<<"[Delete]\n";
                    s1.delentry_WOR();
                    s1.display();
                    break;
                }
                case 6: {
                	cout<<"[Add]\n";
                	s1.add_WOR();
                	s1.display();
                	break;
                }

            }

        }
        cout<<"\tDo you wish to continue? ";
        cin>>select;
    }while(select == 'y');
    cout<<"\n\tDo you wish to restart program? ";
    cin>>select2;
    cout<<"\n\n"<<endl;
}while(select2 == 'y');

}















