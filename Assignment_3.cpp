
//============================================================================
// Name        : Assignment_3.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
class node
{
	int data;
	node* lchild;
	node* rchild;
	int lbit,rbit;
public:
	node()
{
		data=0;
		lbit=rbit=0;
		lchild=rchild=NULL;
}
	node(int x)
	{
			data=x;
			lbit=rbit=0;
			lchild=rchild=NULL;
	}
	friend class TBT;
};
class TBT
{
	node* head;
	node* root;
public:
	TBT()
{
		head=new node(-1);
        head->rchild=head;
        head->lchild=head;
        root=NULL;
}
	void create();
	void insert(int x);
	void insert1();
	void inorder();
	node* in_succ(node* t);
	void preorder();
	node* pre_succ(node* t);
};

	void TBT::insert1()
	{
		int x;
		cout<<"Enter Data: ";
		cin>>x;
		if(x!=-1)
		{
			insert(x);
		}
	}



	void TBT::create()
	{
		int x;
        cout<<"\t\t\t Threaded Binary Tree Data Entry"<<endl;
        while(1)
        {
        	cout<<"Enter Data: ";
        	cin>>x;
        	if(x==-1)
        	{
        		break;
        	}
        	insert(x);
        }
	}
	void TBT::insert(int x)
	{
		if(root==NULL)
		{
			root=new node(x);
			root->lchild=head;
			root->rchild=head->rchild;
			head->lbit=1;
			head->lchild=root;
		}
		else
		{
			node* p=root;
			while(1)
			{
				if(x<p->data)
				{
					if(p->lbit!=0)
					{
						p=p->lchild;
					}
					else
					{
						node* c=new node(x);
                        c->rchild=p;
                        c->lchild=p->lchild;
                        p->lchild=c;
                        p->lbit=1;
                        return ;
					}
				}
				else if(x>p->data)
				{
					if(p->rbit!=0)
					{
						p=p->rchild;
					}
					else
					{
						node* c=new node(x);
				        c->lchild=p;
				        c->rchild=p->rchild;
				        p->rchild=c;
				        p->rbit=1;
				        return ;
				    }
			    }
				else
				{
					cout<<"Data already present"<<endl;
					return ;
				}
			}
		}
	}
	void TBT::inorder()
	{
//		cout<<"INORDER"<<endl;
        node* t=root;
        while(t->lbit==1)
        {
        	t=t->lchild;
        }
        while(t!=head)
        {
        	cout<<t->data<<" ";
        	t=in_succ(t);
        }
        cout<<endl;
	}
	node* TBT::in_succ(node* t)
	{
		if(t->rbit==0)
		{
			return t->rchild;
		}
		t=t->rchild;
		while(t->lbit==1)
		{
			t=t->lchild;
		}
		return t;
	}
	void TBT::preorder()
	{
		cout<<"\tPreorder Traversal"<<endl;
		node* t=root;
		while(t!=head)
		{
		    cout<<t->data<<" ";
		    t=pre_succ(t);
		}
		cout<<endl;
	}
	node* TBT::pre_succ(node* t)
	{
		if(t->lbit==1)
		{
			return t->lchild;
		}
		if(t->rbit==1)
		{
			return t->rchild;
		}
		while(t->rbit==0 && t!=head)
		{
			t=t->rchild;
		}
		return t->rchild;
	}

int main()
{
    TBT t;
    int choice;
    char select;

    do{
    	cout<<"\t1. Create TBT\n\t2. Insert Element\n\t3. Inorder Display\n\t4. Preorder Display\n\t5. Exit\n";
    	cout<<"\t\tEnter Choice: ";
    	cin>>choice;
    	switch(choice)
    	{
			case 1: t.create();
					t.inorder();
			break;

			case 2: t.insert1();
					t.inorder();
			break;

			case 3: cout<<"\tInorder Traversal\n";
				t.inorder();
			break;

			case 4: t.preorder();
			break;

			case 5: cout<<"\t\tTerminating Threaded Binary Tree\n";
			break;

			default: cout<<"Error! Enter valid choice\n";

    	}
    	if(choice!=5)
    	{
			cout<<"Do you wish to continue? ";
			cin>>select;
    	}
    	if(choice==5)
    	{
    		select='n';
    	}
    }while(select=='y');

    if(select=='n' && choice!=5)
    {
    	cout<<"\t\tTerminating Threaded Binary Tree\n";
    }



	return 0;
}
