#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct node{
     int data;
     node * link;
};


// These are the three I have written for you
void build_list(node* & head);  // note that we are passing by reference
void show_list(const node* head);
int size(const node* head);

//These are the two that you are to write, as described in the
//instructions page.
 void remove_repeats(node*& head);
 void split_list(const node* original, node*& lesser,node*& greater,int split_value);



int main(){
    int start, stop;
    int split;
    node* head = NULL;
    node *lesser = NULL;
    node * greater = NULL;

    start = time(NULL);
    build_list(head);
    stop = time(NULL);
    cout<<"Time to build list = "<<stop - start <<"seconds.\n";
    start = time(NULL);
    remove_repeats(head);
    show_list(head);
    stop = time(NULL);
    cout<<"Time to print list = "<<stop - start<<"seconds.\n";
    cout<<"Size of the list = "<<size(head)<<endl;

  cout<<"Enter in a value --> ";
  cin >> split;
    split_list(head,lesser,greater,split);
    show_list(lesser);
    cout<<endl<<endl<<endl;
    show_list(greater);

return 0;
}

// builds a linked list of 2000 random integers, all in the 1 to 500 range
void build_list(node*& head){
     node* cursor;
     head = new node;
     head->data = rand()%500 + 1;
     cursor = head;
     for(int i = 0; i < 2000; ++i){
	cursor->link = new node;
        cursor = cursor->link;
        cursor->data = rand()%500 + 1;
     }
     cursor->link = NULL;
}

// outputs the contents of a linked list to the screen
void show_list(const node* head){
      const node * cursor = head;
      while(cursor !=  NULL){
   	cout<<cursor->data<<"  ";
	cursor = cursor->link;
      }
     cout<<endl;
}

// returns the number of nodes in a linked list
int size(const node* head){
	const node* cursor = head;
	int count = 0;
	while(cursor != NULL){
  	    count++;
	    cursor = cursor->link;
	}
	return count;
}

void remove_repeats(node*& head)
{
  node *cursor, *previous, *rmptr;

  cursor=head;

  while(cursor != NULL && cursor->link != NULL)
   { previous=cursor;

    while(previous -> link != NULL)
    {  if(cursor->data == previous->link->data)
        {rmptr = previous->link;
         previous->link = previous->link->link;
          delete rmptr;
        }
      else
       {previous=previous->link;}
    }
     cursor=cursor->link;
    }
}


void split_list(const node* original, node*& lesser,node*& greater,int split_value)

{const node *cursor=original;
 node *tmp1, *tmp2;


  while (cursor != NULL)
     {
        if(cursor->data < split_value)
          {
            if(lesser == NULL)
              {
               lesser = new node;
               lesser->data = cursor->data;
               lesser->link=NULL;
               tmp1=lesser;
              }
            else
              {
               tmp1->link = new node;
               tmp1 = tmp1->link;
               tmp1->data=cursor->data;
               tmp1->link=NULL;
              }
           }
        else if(cursor->data > split_value)
          {
            if(greater==NULL)
              {
               greater = new node;
               greater->data = cursor->data;
               greater->link=NULL;
               tmp2=greater;
              }
            else
              {
               tmp2->link = new node;
               tmp2 = tmp2->link;
               tmp2->data=cursor->data;
               tmp2->link=NULL;
               }
           }
      cursor=cursor->link;}
}



























