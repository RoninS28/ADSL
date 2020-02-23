//============================================================================
// Name        : Assignment_2.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//Dictionary
//Create, Insert, Display, Search

#include <iostream>
#include<string.h>
using namespace std;

class node
{
	char word[20];
	char ming[20];
	node * lchild;
	node * rchild;
public:
	friend class Dnary;
	node()
{
		lchild=NULL;
		rchild=NULL;
}
	node(char insw[20], char insm[20])
	{
		strcpy(word, insw);
		strcpy(ming, insm);
//		ming=insm;
		rchild=NULL;
		lchild=NULL;
	}
};


class Dnary
{
	node *root;
public:
	Dnary()
{
		root=NULL;
}
	void  create(); //to be called inside main function
	node* insert(node *t, char inw[20], char inm[20]);//to be called in above function
	void insert1();
	void display(node * p);//ascending
	void display1();//ascending main
	void display_desc(node * p);//descending
	void display2();//descending main
	int search(node *p, char sw[20]);
	void search1();
	void edit(node *p, char ew[20], char em[20]);
	void edit1();
	void deltree(node *p);
	void deltree1();
	node* delword(node *p, char dw[20]);
	void delword1();
	void getroot();
};


void Dnary::create()
{
//	node *p = new node;
//	node *t = new node;
	char w1[20];
	char m1[20];
	while(1)
	{
		cout<<"Enter keyword: ";
		cin>>w1;
//		cin.getline(w1, 18);
		if(!strcmp(w1, "-1"))
		{
//			cout<<"Breaking bad";
			break;
		}
		cout<<"Enter meaning: ";
		cin>>m1;
//		cin.getline(m1, 18);
//		cout<<"bug";
		root=insert(root,w1, m1);
	}
}

node* Dnary::insert(node * t, char w2[20], char m2[20])
{
//	cout<<"enter insert";
	if(t==NULL)
	{
		t=new node(w2, m2);
		strcpy(t->word, w2);
		strcpy(t->ming, m2);
		return t;
	}
	else if(strcmp(w2, t->word)>0)
		{
			t->rchild=insert(t->rchild, w2, m2);
			return t;
		}

	else if(strcmp(w2, t->word)<0)
		{
			t->lchild=insert(t->lchild, w2, m2);
			return t;
		}
	else
		{
			cout<<"Word already exists\n";
			return t;
		}


//	return t;
}


void Dnary::insert1()
{
//	node *t = new node;
	char insw[20], insm[20];
	cout<<"Enter Keyword: ";
	cin>>insw;
	cout<<"Enter Meaning: ";
	cin>>insm;
	root=insert(root, insw, insm);
}



void Dnary::display(node *p)
{
	if(p!=NULL)
	{
		display(p->lchild);
		cout<<"Keyword: "<<p->word<<"\t\t Meaning: "<<p->ming<<endl;
		display(p->rchild);
	}
}
void Dnary::display1()
{
	cout<<"\t\t\t\t* * * * * TREE DICTIONARY * * * * *\n";
	display(root);
}
void Dnary::display_desc(node *p)
{
	if(p!=NULL)
	{
		display_desc(p->rchild);
		cout<<"Keyword: "<<p->word<<"\t\t Meaning: "<<p->ming<<endl;
		display_desc(p->lchild);
	}
}
void Dnary::display2()
{
	cout<<"\t\t\t\t* * * * * TREE DICTIONARY * * * * *\n";
	display_desc(root);
}

int Dnary::search(node *p, char sw[20])
{
	if(p==NULL)
	{
		cout<<"Word not found! Please try again!"<<endl;
		return 0;
	}
	else
	{

		if(strcmp(sw, p->word)>0)
		{

			return(1+ search(p->rchild, sw));
		}
		else if(strcmp(sw, p->word)<0)
		{
			return(1+ search(p->lchild, sw));
		}
		else if(strcmp(sw, p->word)==0)
		{
			cout<<"Word found!\n Keyword: "<<p->word<<"\t Meaning: "<<p->ming<<endl;
//			cout<<"Comparisons: "<<count<<endl;
			return 1;
		}
	}
}

void Dnary::search1()
{
	int count;
	char sw[20];
	cout<<"Enter Word to be searched: ";
	cin>>sw;
	count=search(root, sw);
	cout<<"Comparisons: "<<count<<endl;
}

void Dnary::edit(node *p, char ew[20], char em[20])
{
	if(p==NULL)
	{
		return;
	}
	else
	{
		if(strcmp(ew, p->word)>0)
		{
			edit(p->rchild, ew, em);
		}
		else if(strcmp(ew, p->word)<0)
		{
			edit(p->lchild, ew, em);
		}
		else if(strcmp(ew, p->word)==0)
		{
			cout<<"Word found!\n Keyword: "<<p->word<<"\n Previous Meaning: "<<p->ming<<endl;
			strcpy(p->ming, em);
			cout<<"New Meaning: "<<p->ming<<endl;
		}
		else
		{
			cout<<"Word not found! Please try again!"<<endl;
		}
	}

}

void Dnary::edit1()
{
	char ew[20], em[20];
	cout<<"Enter Word whose meaning is to be edited: ";
	cin>>ew;
	cout<<"Enter New Meaning: ";
	cin>>em;
	edit(root, ew, em);
}


void Dnary::deltree(node *p)
{
	if(p!=NULL)
	{
		deltree(p->lchild);
		deltree(p->rchild);
		delete p;
	}
}

void Dnary::deltree1()
{
	deltree(root);
}

void Dnary::delword1()
{
	char dw[20];
	cout<<"Enter Word to be deleted: ";
	cin>>dw;
	delword(root, dw);
}

node* Dnary::delword(node *t, char dw[20])
{
	node *q = new node;
	if(t==NULL)
	{
		return NULL;
	}
	if(strcmp(dw, t->word)<0)
	{
		t->lchild=delword(t->lchild, dw);
	}
	else if(strcmp(dw, t->word)>0)
	{
		t->rchild=delword(t->rchild, dw);
	}
	else if(strcmp(dw, t->word)==0)
	{
		if(t->lchild==NULL && t->rchild==NULL)
		{
			delete t;
			return NULL;
		}
		else if(t->lchild==NULL && t->rchild!=NULL)
		{
			q=t->rchild;
			delete t;
			return q;
		}
		else if(t->lchild!=NULL && t->rchild==NULL)
		{
			q=t->lchild;
			delete t;
			return q;
		}
		else
		{
			//findminn
			q=t->rchild;
			while(q->lchild!=NULL)
			{
				q=q->lchild;
			}
			strcpy(t->word, q->word);
//			t->word=q->word;
			t->rchild=delword(t->rchild, q->word);
			return t;
		}

	}

}


void Dnary::getroot()
{
	cout<<"Root is: "<<root->word;
}
int main()
{
	Dnary d;
	char select;
	int choice;


do{
	cout<<"1. Create Tree\t 2. Display Tree(Asc)\t 3. Display Tree(Des)\t 4. Add Word\t 5. Search Word\t 6. Edit Word\t 7. Delete Word\n";
	cout<<"\t  Enter Choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1: d.create();
				d.display1();
				d.getroot();
		break;
		case 2: d.display1();
		break;
		case 3: d.display2();
		break;
		case 4: d.insert1();
				d.display1();
		break;
		case 5: d.search1();
		break;
		case 6: d.edit1();
				d.display1();
		break;
		case 7: d.delword1();
				d.display1();
		break;

	}
	cout<<"Do you wish to continue?";
	cin>>select;
}while(select=='y');




	return 0;
}

