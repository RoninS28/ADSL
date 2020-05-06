//============================================================================
// Name        : Assignment_8.cpp
// Author      : Rohan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string.h>
using namespace std;

class node
{
    public:
    string word, ming;
    node *left;
    node *right;
//    int bfactor;
    int height;

    node()
    {
        word="\0";
        ming="\0";
        left=right=NULL;
        height=0;
    }
};

class AVL
{
    node *root;
public:
    AVL()
    {
        root=NULL;
    }
    int checkbfactor(node *t);
    int checkht(node *t);
    void add();
    void insert1();
    node *insert(node *t, string iw, string im);
    void inorder(node *t);
    void delentry();
    node *del(node *t, string x);
    node *RR(node *t);
    node *LL(node *t);
    node *RL(node *t);
    node *LR(node *t);
    node *RotateRight(node *t);
    node *RotateLeft(node *t);
    void search1();
    void search(node *t, string x);
    void modify(node *t, string mw, string mm);
    void modify1();
    void display();

};

int AVL::checkbfactor(node *t)
{
	int lh, rh;
	if(t == NULL)
	{
		return 0;
	}
	else
	{
		if(t->left == NULL)
		{
			lh=0;
		}
		else
		{
			lh = 1+ t->left->height;
		}
		if(t->right == NULL)
		{
			rh=0;
		}
		else
		{
			rh = 1+ t->right->height;
		}
		return (lh - rh);
	}
}

int AVL::checkht(node *t)
{
	int lh, rh;
	if(t == NULL)
	{
		return 0;
	}
	if(t->left == NULL && t->right == NULL)
	{
		return 0;
	}
	else
	{
		lh = lh + checkht(t->left);
		rh = rh + checkht(t->right);
		if(lh>rh)
		{
			return lh+1;
		}
		else
		{
			return rh+1;
		}
	}

}

void AVL::add()
{
	string aw, am;
	cout<<"Enter Word: ";
	cin>>aw;
	cout<<"Enter Meaning: ";
	cin>>am;
	root = insert(root, aw, am);

}
void AVL::insert1()
{
	string iw, im;
	while(1)
	{
		cout<<"Enter Word: ";
		cin>>iw;
		if(iw=="-1")
		{
			break;
		}
		cout<<"Enter Meaning: ";
		cin>>im;
		root = insert(root, iw, im);
	}
}

node* AVL::insert(node *t, string iw, string im)
{
    if(t==NULL){
        t = new node();
        t->left = t->right = NULL;
        t->word = iw;
        t->ming = im;
    }
    else if(t->word != iw)
    {
    	if(t->word > iw)
    	{
    		t->left = insert(t->left, iw, im);
    		if(checkbfactor(t)==2)
    		{
    			if(t->left->word > iw)
    			{
    				t = LL(t);
    			}
    			else
    			{
    				t = LR(t);
    			}
    		}
    	}
    	else if(t->word < iw)
    	{
    		t->right = insert(t->right, iw, im);
    		if(checkbfactor(t) == -2)
    		{
    			if(t->right->word > iw)
    			{
    				t = RR(t);
    			}
    			else
    			{
    				t = RL(t);
    			}
    		}
    	}
    }
    else
    {
    	cout<<"[Error] Invalid!\n";
    }
    t->height = checkht(t);
    return t;
}

node* AVL::RotateLeft(node *t)
{
	node *temp;
	temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t->height = checkht(t);
	temp->height = checkht(temp);
	return temp;
}
node* AVL::RotateRight(node *t)
{
	node *temp;
	temp = t->left;
	t->left = temp->right;
	temp->left = t;
	t->height = checkht(t);
	temp->height = checkht(temp);
	return temp;
}

node* AVL::RR(node *t)
{
	t=RotateRight(t);
	return t;
}
node* AVL::LL(node *t)
{
	t = RotateLeft(t);
	return t;
}
node* AVL::RL(node *t)
{
	t->right = RotateRight(t->right);
	t = RotateLeft(t);
	return t;
}
node* AVL::LR(node *t)
{
	t->left= RotateLeft(t->left);
	t = RotateRight(t);
	return t;
}
void AVL::inorder(node *t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		cout<<"\t\tWord: "<<t->word<<"\t\tMeaning: "<<t->ming<<endl;
		inorder(t->right);
	}
}

void AVL::display()
{
	cout<<"\n\n\t\t\t* * * DISPLAY * * *\n";
	inorder(root);
}

void AVL::delentry()
{
	string dw;
	cout<<"\t[Delete] Enter Word: ";
	cin>>dw;
	root = del(root, dw);
}

node* AVL::del(node *t, string x)
{
	node *temp;
	if(t==NULL)
	{
		return 0;
	}
	else if(x > t->word)
	{
		t->right = del(t->right, x);
		if(checkbfactor(t) == 2)
		{
			if(checkbfactor(t->left)>=0)
			{
				t = LL(t);
			}
			else
			{
				t = LR(t);
			}
		}
	}
	else
	if(x < t->word)
	{
		t->left = del(t->left, x);
		if(checkbfactor(t)==-2)
		{
			if(checkbfactor(t->right)<=0)
			{
				t = RR(t);
			}
			else
			{
				t = RL(t);
			}
		}
	}
	else
	{
		if(t->right!=NULL)
		{
			temp = t->right;
			while(temp->left!=NULL)
			{
				temp = temp->left;
			}
			t->word = temp->word;
			t->right = del(t->right, temp->word);
			if(checkbfactor(t)==2)
			{
				if(checkbfactor(t->left)>=0)
				{
					t = LL(t);
				}
				else
				{
					t = LR(t);
				}
			}
		}
		else
		{
			return (t->left);
		}

	}
		t->height = checkht(t);
		return t;
	}

void AVL::search1()
{
	string sw;
	cout<<"\t[Search] Enter Word: ";
	cin>>sw;
	search(root, sw);
}

void AVL::search(node *t, string x)
{
    int flag = 0;
    if(t == NULL)
    {
        return;
    }
    while(t!=NULL)
    {
        if(x == t->word)
        {
            flag =1;
            break;
        }
        else if(x > t->word)
        {
            t = t->right;
        }
        else
        {
            t = t->left;
        }

    }
    if(flag ==1)
    {
        cout<<"\tData Found!"<<endl;
        cout<<"\t\tWord: "<<t->word<<"\t\tMeaning: "<<t->ming<<endl;
    }
    else
    {
        cout<<"\t[Error] Data not found!"<<endl;
    }

}

void AVL::modify1()
{
	string mw, nm;
	cout<<"\t[Modify] Enter Word: ";
	cin>>mw;
	cout<<"\t[Modify] Enter New Meaning: ";
	cin>>nm;
	modify(root, mw, nm);
}

void AVL::modify(node *t, string mw, string mm)
{
	int flag=0;
    if(t)
    {
        if(t->word == mw)
        {
            t->ming = mm;
            flag=1;
        }
        else if(mw < t->word)
        {
            modify(t->left,mw,mm);
        }
        else
        {
            modify(t->right,mw,mm);
        }
    }
    if(flag!=1)
    {
    	cout<<"\t[Error] Data not found!\n";
    }

}



int main()
{
	AVL a;
	int choice;
	char select;
	do{
		cout<<"\n\t\t\t\t[MENU]\n";
		cout<<"\t\t1. Insert\n";
		cout<<"\t\t2. Add \n";
		cout<<"\t\t3. Display \n";
		cout<<"\t\t4. Search \n";
		cout<<"\t\t5. Modify \n";
		cout<<"\t\t6. Delete \n";
		cout<<"\t\tEnter Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:{
				a.insert1();
				a.display();
				break;
			}
			case 2: {
				a.add();
				a.display();
				break;
			}
			case 3: {
				a.display();
				break;
			}
			case 4: {
				a.search1();
				break;
			}
			case 5: {
				a.modify1();
				a.display();
				break;
			}
			case 6: {
				a.delentry();
				a.display();
				break;
			}
		}
		cout<<"\n\t\tDo you wish to continue? ";
		cin>>select;
	}while(select == 'y');
}










































