#include<iostream>
#include<string.h>
using namespace std;

class node
{
    int data;
    node *next;
public:
    node()
    {
        data=-1;
        next = NULL;
    }
    node(int x)
    {
        data=x;
        next=NULL;
    }
    friend class Set;
    friend class Iterator;
};

class Iterator
{
    node *itr;
public:
       Iterator()
       {
           itr=NULL;
       }
       Iterator(node *p)
       {
           itr=p;
       }
       void operator ++ (int)
       {
           if(itr!=NULL)
           {
               itr = itr->next;
           }
       }
       friend class Set;
};

class Set
{
    node *head;
    int length;
public:
    Set()
    {
        head=NULL;
        length=0;
    }
    void insert();
    void insert1(int x);
    void add();
    void display();
    void sorte();
    int check(int x);
    void remove();
    void remove1(int x);
    Iterator iterate(node *t);
    void Union1(Set u);//for menu
    void Subset(Set u);//for menu
    void Intersection(Set u);
    void Difference(Set u);
    
};

void Set::add()
{
    int x;
    again:
    cout<<"Enter element: ";
    cin>>x;
    if(x == -1)
    {
        return;
    }
    if(head==NULL)
    {
        head->data = x;
        length++;
    }
    else
    {
        int c=check(x);
        if(c != -1)//-1 means no match found
        {
            cout<<"\t\t[Error] Element already exists!\n";
            goto again;
        }
        node *t = new node;
        t=head;
        while(t->next != NULL)
        {
            t = t->next;
        }
        t->next = new node(x);
        length++;
    }
    sorte();
}

void Set::insert1(int x)
{
//    int x;
//    again:
//    cout<<"Enter element: ";
//    cin>>x;
    if(head==NULL)
    {
//        head->data = x;
        node *p = new node(x);
        head = p;
//        cout<<"test";
        length++;
    }
    else
    {
        int c=check(x);
        if(c != -1)//-1 means no match found
        {
//            cout<<"\t[Error] Element already exists!\n";
//            goto again;
              return;
        }
        node *t = new node;
        t=head;
        while(t->next != NULL)
        {
            t = t->next;
        }
        t->next = new node(x);
        length++;
    }
    sorte();
}

void Set::insert()
{
    int x;
    int c;
    while(1)
    {
    again:
        cout<<"Enter element: ";
        cin>>x;
        if(x == -1)
        {
            break;
        }
        c = check(x);
        if(c != -1)//-1 means no match found
        {
            cout<<"\t[Error] Element already exists!\n";
            goto again;
        }
        if(head==NULL)
        {
            head = new node(x);
            length++;
         }
        else
        {
            node *t = new node;
            t=head;
            while(t->next != NULL)
            {
                t = t->next;
            }
            t->next = new node(x);
            length++;
        }
        sorte();
    }
}

void Set::display()
{
    if(head == NULL)
    {
        cout<<"Set underflow\n";
    }
    else
    {
        node *t = new node;
        t=head;
        cout<<"{ ";
        while(t->next!=NULL)
        {
            cout<<t->data<<", ";
            t=t->next;
        }
        cout<<t->data<<" }\n";
    }
}

void Set::sorte()
{
    int d;
    node *p = new node;
    node *q = new node;
//    for(int i=0; i<length-1; i++)
//    {
//         p=head;
//         q=head->next;
//    }
      for(p = head; p!=NULL; p=p->next)
      {
          for(q = p->next; q!=NULL; q=q->next)
          {
              if(p->data > q->data)
              {
                  d=p->data;
                  p->data = q->data;
                  q->data = d;
              }
          }
      }
}

int Set::check(int x)
{
    int flag=0;
    int count=0;
    if(head == NULL)
    {
        flag=0;//no match found
    }
    else
    {
        node *t = new node;
        t=head;
        while(t != NULL)
        {

            if(t->data == x)
            {
                flag=1;//found
                break;
            }
            count++;//tells us how many times we have to probe
            t=t->next;
        }
    }
    if(flag == 0)
    {
        return -1;//no match found --> good to go
    }
    else
    {
        return count;//match found
    }
}

void Set::remove()
{
    int del;
    char retry;
    int c1=0;
    do{
        cout<<"Enter element to be removed: ";
        cin>>del;
        int c=check(del);
        if(c == -1)
        {
            cout<<"\t[Error] Element not found!\n\t\tTry again? --> ";
            cin>>retry;
        }
        else
        {
            node *t = new node;
            node *prev = new node;
            t=head;
            while(c1<c)
            {
                prev=t;
                t=t->next;
                c1++;
            }
            //now prev is pointing to previous node of tbd node
            //t is pointing to the tbd node
            if(t == head)//first node
            {
                if(head->next == NULL)//only and only node in the set
                {
                    head=NULL;
                }
                else
                {
                    head = head->next;
                    delete t;
                }

            }
            if(t->next == NULL)//last node
            {
                prev->next = NULL;
                delete t;
            }
            else
            {
                prev->next = t->next;
                t->next = NULL;
                delete t;
            }
            retry='n';
        }
    }while(retry=='y');
}

void Set::remove1(int del)
{
    int c1=0;
    int c=check(del);
    if(c == -1)
    {
        return;
    }
    else
    {
        node *t = new node;
        node *prev = new node;
        t=head;
        while(c1<c)
        {
            prev=t;
            t=t->next;
            c1++;
        }
        //now prev is pointing to previous node of tbd node
        //t is pointing to the tbd node
        if(t == head)//first node
        {
            if(head->next == NULL)//only and only node in the set
            {
                head=NULL;
            }
            else
            {
                head = head->next;
                delete t;
            }
            
        }
        else if(t->next == NULL)//last node
        {
            prev->next = NULL;
            delete t;
        }
        else//in between node
        {
            prev->next = t->next;
            t->next = NULL;
            delete t;
        }
       
    }
    
}

Iterator Set::iterate(node *t)
{
    Iterator temp(t);
    return temp;
}

void Set::Union1(Set u1)
{
    cout<<" Enter Set2 \n";
    u1.insert();
    cout<<"Set 1 --> ";
    display();
    cout<<"Set 2 --> ";
    u1.display();
    Set U;//final union set
    Iterator i,j;
    for(i=iterate(head);  i.itr != NULL; i++)
    {
        U.insert1(i.itr->data);
    }
    for( j=iterate(u1.head); j.itr != NULL; j++)
    {
        U.insert1(j.itr->data);
    }
    cout<<"Union --> ";
    U.display();
}

void Set::Difference(Set d1)
{
    Set D;
    cout<<" Enter Set 2 \n";
    d1.insert();
    cout<<"Set 1 --> ";
    display();
    cout<<"Set 2 --> ";
    d1.display();
    Iterator i, j;
    for( i = iterate(head); i.itr!=NULL; i++)
    {
        D.insert1(i.itr->data);
    }
    for( j = iterate(d1.head); j.itr!=NULL; j++)
    {
        D.remove1(j.itr->data);
    }
    cout<<"Diff. --> ";
    D.display();
}

void Set::Subset(Set s1)
{
    Set S;
    int flag=0;
    cout<<" Enter Set 2 \n";
    s1.insert();
    cout<<"Set 1 --> ";
    display();
    cout<<"Set 2 --> ";
    s1.display();
    Iterator i, j;
    for( i = iterate(head); i.itr!=NULL; i++)
    {
        S.insert1(i.itr->data);
    }
    j = iterate(s1.head);
    while(j.itr!=NULL)
    {
        if(check(j.itr->data) == -1)//no match found in set1
        {
            flag=1;
            break;
        }
        j++;
    }
    if(flag != 1)//all match
    {
        cout<<"Set 2 is a subset of Set 1\n";
    }
    else//case of failure
    {
        cout<<"Set 2 is not a subset of Set 1\n";
    }
    
}

void Set::Intersection(Set i1)
{
    Set I;
    cout<<" Enter Set 2\n";
//    i1.insert();
    cout<<"Set 1 --> ";
    display();
    cout<<"Set 2 --> ";
    i1.display();
    Iterator i, j;
    for(i = iterate(head); i.itr!=NULL; i++)
    {
        for(j = iterate(i1.head); j.itr!=NULL; j++)
        {
            if(i.itr->data == j.itr->data)
            {
                I.insert1(i.itr->data);
            }
        }
    }
    I.display();
}



int main()
{
    Set s, s1;
    Set u, i1;
    Set d;
    int choice;
    char select;
//    s.insert();
//    s.display();
//    s.add();
//    s.display();
//    s.remove();
//    s.display();
//      s.Union1(u);
//      s.Difference(d);
//        s.Subset(s1);
//s.Intersection(i1);
    do{

        cout<<"\t\t\t[MENU]\n\t\t1. Insert\n\t\t2. Add\n\t\t3. Display\n\t\t4. Remove\n\t\t5. Union\n\t\t6. Difference\n\t\t7. Subset\n\t\t  Enter Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: {
                cout<<"\n\t\t\t[Insert]\n\n";
                s.insert();
                cout<<"Set --> ";
                s.display();
                break;
            }
            case 2: {
                cout<<"\n\t\t\t[Add]\n\n";
                s.add();
                cout<<"Set --> ";
                s.display();
                break;
            }
            case 3: {
                cout<<"\n\t\t\t[Display]\n\n";
                s.display();
                break;
            }
            case 4: {
                cout<<"\n\t\t\t[Remove]\n\n";
                s.remove();
                cout<<"Set --> ";
                s.display();
                break;
            }
            case 5: {
                cout<<"\n\t\t\t[Union]\n\n";
                s.Union1(u);
                break;
            }
            case 6: {
                cout<<"\n\t\t\t[Difference]\n\n";
                s.Difference(d);
                break;
            }
            case 7: {
                cout<<"\n\t\t\t[Subset]\n\n";
                s.Subset(s1);
                break;
            }
        }
        cout<<"\tDo you wish to continue -> ";
        cin>>select;
    }while(select == 'y');
    if(select == 'n')
    {
        cout<<"\n\t\t\t\t[EXIT]\n";
    }
    return 0;
}
































