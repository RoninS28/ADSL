//============================================================================
// Name        : Assignment1.cpp
// Author      : 21259
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define MAX 30
using namespace std;

class node
{
	int data;
	node* lchild;
	node* rchild;
public:
	node()
{
		data=0;
		lchild=rchild=NULL;
}
	node(int x)
	{
			data=x;
			lchild=rchild=NULL;
	}
	friend class Bintree;
	friend class queue;
};
class queue
{
	int front;
	int rear;
	node* que[MAX];
public:
	friend class node;
	queue()
{
		rear=-1;
		front=-1;
}
	void push(node* t)
	{
		if(!isfull())
		{
			if(front==-1)
			{
				front=0;
				rear=0;
			}
			else if(rear==MAX-1)
			{
				rear=0;
			}
			else
			{
				rear++;
			}
			que[rear]=t;
		}
		else
		{
			cout<<"Queue Overflow"<<endl;
		}
	}
	node* pop()
	{
		if(!isempty())
		{
			node* item=que[front];
			if(front==rear)
			{
				front=rear=-1;
			}
			else if(front==MAX-1)
			{
				front=0;
			}
			else{
			front++;
			}
			return item;
		}
		else
			cout<<"underflow"<<endl;
	}
	bool isempty()
	{
		if((front==-1))
		{
			return 1;
		}
		return 0;
	}
	bool isfull()
	{
		if(((rear==MAX-1)&&(front==0)) || (front==rear+1))
		{
			return 1;
		}
		return 0;
	}
	node* getrear()
	{
		return que[rear];
	}
	node* getfront()
	{
		return que[front];
	}
	void display()
	{
		if(front==-1)
		{
			cout<<"Queue Underflow"<<endl;
		}
		else
		{
			int temp=front;
			while(temp!=rear)
			{
				cout<<que[temp]->data<<endl;
				if(temp==MAX-1)
				{
					temp==0;
				}
				else
				{
					temp++;
				}
			}
			cout<<que[temp]->data<<endl;
		}
	}
};
class stack
{
	node* arr[MAX];
	int top;
public:
    stack()
{
		top=-1;
}
	void push(node* ele)
	{
		if(top==MAX-1)
		{
			cout<<"Stack Overflow"<<endl;
		}
		else
		{
         	top=top+1;
			arr[top]=ele;
		}
	}
	node* pop()
	{
		node* ele;
		if(top==-1)
		{
			cout<<"Stack Underflow"<<endl;
			return 0;
		}
		else
		{
		    ele=arr[top];
		    top=top-1;
		    return ele;
		}
	}
	int full()
	{
		if(top==MAX-1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int empty()
	{
		if(top==-1)
		{
			return 1;
		}
		else{
			return 0;
		}
	}
	node* topmost()
	{
		node* c;
		c=arr[top];
		return c;
	}
};
class Bintree
{
	node* root;
	int flag;
	int cntleaf;
	int cntint;
	int cntext;
	int height;
public:
	Bintree()
{
		root=NULL;
		flag=0;
		cntleaf=0;
		cntint=0;
		cntext=0;
		height=1;
}
	void create();
	node* create1();
	node* insert(node* t,int x);
	void inorder(node* t);
	void preorder(node* t);
	void postorder(node* t);
	void display();
	void create_nonrec();
	void inorder_nonrec();
	void preorder_nonrec();
	void postorder_nonrec();
	void display_nonrec();
	void delete_tree(node* t);
	void delete2();
	node* Copy(node *temp);
	void operator = (Bintree & t);//overloaded for Copy function
	void operator >> (Bintree & t);//overloaded for mirror function
	node* Mirror(node *temp);
	int Equal(node *t1,node *t2);
	void equal1(Bintree &t2);//Equal function called inside this... this function called inside main
	void downtoup(node *p);
	void downtoup1();//called inside main
	void findht(node *p);
	void findht1();//called inside main

};
void Bintree::create()
{
	root=create1();
}
node* Bintree::create1()
{
	int x;
	node* p;
	cout<<"\tEnter Data: ";
	cin>>x;
	if(x==-1)
	{
		return NULL;
	}
	else
	{
		p=new node(x);
		cout<<"Enter  leftchild of ' "<<p->data<<" ' :";
		p->lchild=create1();
		cout<<"Enter rightchild of ' "<<p->data<<" ' :";
		p->rchild=create1();
		return p;
	}
}
node* Bintree::insert(node* t,int x)
{
	node* p;
	char ans;
	if(t==NULL)
	{
		p=new node(x);
		return p;
	}
	else
	{
		cout<<"Where do you wish to insert (l/r) of ' "<<t->data<<" ' ?";
		cin>>ans;
		if(ans=='l' or ans=='L')
		{
			t->lchild=insert(t->lchild,x);
		}
		else
		{
			t->rchild=insert(t->rchild,x);
		}
		return t;
	}
}
void Bintree::inorder(node* t)
{
	if(t!=NULL)
	{
		inorder(t->lchild);
		cout<<t->data<<" - ";
		inorder(t->rchild);
	}
}
void Bintree::preorder(node* t)
{
	if(t!=NULL)
	{
		cout<<t->data<<" - ";
		preorder(t->lchild);
		preorder(t->rchild);
	}
}
void Bintree::postorder(node* t)
{
	if(t!=NULL)
	{
		postorder(t->lchild);
		postorder(t->rchild);
		cout<<t->data<<" - ";
	}
}
void Bintree::create_nonrec()
{
	queue q;
	int x;
	cout<<"Insert Root data: ";
	cin>>x;
	root=new node(x);
	q.push(root);
	while(!q.isempty())
	{
		node* t=q.pop();
		cout<<"Enter to the  left of ' "<<t->data<<" ': ";
		cin>>x;
		if(x!=-1)
		{
		   t->lchild=new node(x);
		   q.push(t->lchild);
		}
		cout<<"Enter to the right of ' "<<t->data<<" ': ";
		cin>>x;
		if(x!=-1)
		{
			t->rchild=new node(x);
			q.push(t->rchild);
		}
	}
}
void Bintree::display()
{
	cout<<"\t Preorder Traversal is"<<endl;
	preorder(root);
	cout<<endl;
	cout<<"\t Inorder Traversal is"<<endl;
	inorder(root);
	cout<<endl;
	cout<<"\t Postorder Traversal is"<<endl;
	postorder(root);
	cout<<endl;
}
void Bintree::display_nonrec()
{
	cout<<"\t Preorder Traversal is (Non_Rec)"<<endl;
	preorder_nonrec();
	cout<<endl;
	cout<<"\t Inorder Traversal is (Non_Rec)"<<endl;
	inorder_nonrec();
	cout<<endl;
	cout<<"\t Postorder Traversal is (Non_Rec)"<<endl;
	postorder_nonrec();
	cout<<endl;
}
void Bintree::inorder_nonrec()
{
	stack s;
	node* t=root;
	while(1)
	{
		while(t!=NULL)
		{
			s.push(t);
			t=t->lchild;
		}
		if(s.empty())
		{
			return;
		}
		t=s.pop();
		cout<<t->data<<" _ ";
		t=t->rchild;
	}
}
void Bintree::preorder_nonrec()
{
	stack s;
	node* t=root;
	while(t!=NULL)
	{
		cout<<t->data<<" _ ";
		s.push(t);
		t=t->lchild;
	}

	while(!s.empty())
	{
		t=s.pop();
		t=t->rchild;
		while(t!=NULL)
		{
			cout<<t->data<<" _ ";
			s.push(t);
			t=t->lchild;
		}
	}
}
void Bintree::postorder_nonrec()
{
	stack s1,s2;
	node* t=root;
	node* p1;
	s1.push(root);
	while(!s1.empty())
	{
		t=s1.pop();
		s2.push(t);
		if(t->lchild!=NULL)
		{
		    s1.push(t->lchild);
		}
		if(t->rchild!=NULL)
		{
			s1.push(t->rchild);
		}
	}
	while(!s2.empty())
	{
		t=s2.pop();
		cout<<t->data<<" _ ";
	}
}
void Bintree::delete_tree(node* t)
{
	if(t!=NULL)
	{
		delete_tree(t->lchild);
		delete_tree(t->rchild);
		delete t;
	}
}

void Bintree::delete2()
{
	delete_tree(root);
	display();
}

void Bintree::operator =(Bintree &t)
{
	root = Copy(t.root);
}


node* Bintree::Copy(node *temp)
{
	node * copynode = NULL;
//	cout<<"Copied Tree is\n";
	if(temp)
	{
		copynode = new node(temp->data);
		copynode->lchild = Copy(temp->lchild);
		copynode->rchild = Copy(temp->rchild);
	}
	return copynode;
}

node * Bintree::Mirror(node *temp)
{
	node * mnode = NULL;
//	cout<<"Mirror Image Tree is\n";
	if(temp)
	{
		mnode = new node(temp->data);
		mnode->lchild = Copy(temp->rchild);
		mnode->rchild = Copy(temp->lchild);
	}
	return mnode;

}

void Bintree::operator >> (Bintree &t)
{
	root = Mirror(t.root);
}

void Bintree::equal1(Bintree &t2)
{
	if(Equal(root, t2.root)==1)
	{
		cout<<"Trees are same\n";
	}
	else
	{
		cout<<"Trees are not same\n";
	}
}



int Bintree::Equal(node *t1, node *t2)
{
	if(t1!=NULL || t2!=NULL)
	{
		if(t1!=NULL && t2!=NULL)
		{
			if(t1->data == t2->data)
			{
				return (Equal(t1->lchild, t2->lchild) && Equal(t1->rchild, t2->rchild));
			}
		}
		else
		{
			return 0;
		}
	}
	if(t1==NULL && t2!=NULL)//if tree 1 has extra node
	{
		return 0;
	}
	else if(t1==NULL && t2==NULL)//same number of nodes // Ideal
	{
		return 1;
	}
}



//
//int Bintree::Equal(node *t1,node *t2)
//{
//	node *p = new node;
//	node *q = new node;
//	if(t1!=NULL && t2!=NULL && t1->data==t2->data && flag!=-1)
//	{
//		Equal(t1->lchild, t2->lchild);
//		Equal(t1->rchild, t2->rchild);
//	}
//	else
//	{
//		flag=-1;
//		return 1;
//	}
//
//	if(flag==0 && p==NULL && q==NULL)//Ideal
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}

//}
void Bintree::downtoup1()
{
	downtoup(root);
	cout<<"\nNumber of leafs in tree are: "<<cntleaf<<endl;
	cout<<"Number of interior nodes in tree are: "<<cntint<<endl;
	cout<<"Number of exterior nodes in tree are: "<<cntext<<endl;
}

void Bintree::downtoup(node *p)
{
	if(p==NULL)
	{
		return;
	}
	if(p!=NULL)
	{
		downtoup(p->lchild);
		downtoup(p->rchild);
		if(p->lchild==NULL && p->rchild==NULL)
		{
			cntleaf++;
			cout<<p->data<<" ";
		}
		else if(p->lchild!=NULL && p->rchild!=NULL)
		{
			cntint++;
			cout<<p->data<<"";
		}
		else
		{
			cntext++;
		}
	}
}

void Bintree::findht1()
{
	findht(root);
	cout<<"Height of Tree: "<<height<<endl;
}

void Bintree::findht(node *p)
{
	if(p->lchild!=NULL && p->rchild!=NULL)
	{
		height++;
		findht(p->lchild);
		findht(p->rchild);

	}

	else
	{

		if(p->lchild!=NULL && p->rchild==NULL)
		{

			findht(p->lchild);
		}
		else if(p->rchild!=NULL && p->lchild==NULL)
		{
//			height++;
			findht(p->rchild);
		}
		else if(p->rchild==NULL && p->lchild==NULL)
		{
//			height++;
		}
	}

}









int main()
{
	int choice;
	char select;
    Bintree t1,t2, t3, t4;
//    t1.create();
//    t1.show();
//    t3.create();
//    t1.nonrec_show();
    //t1.inorder_nonrec();
    //t1.preorder_nonrec();
//    t2.create_nonrec();
//    t2.show();
//    	t2=t1;
//    	t2.show();
//    	t3>>t1;
//    	t3.show();
//    	t1.equal1(t3);
//    	t1.downtoup1();
//    	t1.findht1();
    do{

	cout<<"1. Create Tree 1\n2. Create Tree 2\n3. Display Tree 1 (Rec) \n4. Display Tree 1 (Non-Rec) \n5. Display Tree 2 (Rec)  \n6. Display Tree 2 (Non-Rec) \n7. Delete Tree 1\n8. Delete Tree 2";
	cout<<"\n9. Copy Tree 1  \n10. Mirror of Tree 1  \n11. Node Details of Tree 1  \n12. Check Equality of Tree 1 & 2"<<endl;
	cout<<"\tEnter Choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1: t1.create();
				t1.display();
			break;
		case 2: t2.create();
				t2.display();
		break;
		case 3: t1.display();
		break;
		case 4: t1.display_nonrec();
		break;
		case 5: t2.display();
		break;
		case 6: t2.display_nonrec();
		break;
		case 7: t1.delete2();
		break;
		case 8: t2.delete2();
		break;
		case 9: {
				t3=t1;
				cout<<"Copied Tree 3 is\n";
				t3.display();
			break;
				}
		case 10: {
				t4>>t1;
				cout<<"Mirror Tree 4 is\n";
				t4.display();
			break;
				 }
		case 11: {
				t1.downtoup1();
			break;

				 }
		case 12: t1.equal1(t2);
		break;
		case 13:
		break;
	}
	cout<<"Do you wish to continue?: ";
	cin>>select;
	}while(select=='y');















	return 0;
}

