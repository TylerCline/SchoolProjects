#include<iostream>
#include<string>

struct Node{
    std::string data;
    Node *link;
};

class Lilist{
    public:
        Lilist(){head = NULL;}
        void add(std::string item);
        void show();
        Node* search(std::string target);
        void move_front_to_back();
    private:
        Node *head;
};

void Lilist::add(std::string item){
    Node * tmp;
    if(head == NULL){
        head = new Node;
        head -> data = item;
        head -> link = NULL;
    }
    else{
        for(tmp = head; tmp->link != NULL; tmp = tmp -> link)
            ;  // this loop simply advances the pointer to last node in
                //the list
        tmp->link = new Node;
        tmp = tmp->link;
        tmp->data = item;
        tmp->link = NULL;
    }
}

void Lilist::show(){
    for(Node *tmp = head; tmp != NULL; tmp = tmp->link)
        std::cout<<tmp->data<<"  ";
}

Node* Lilist::search(std::string target)
{   Node *tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->link)
       {if(tmp->data == target){
           return (tmp);}
       }

   return tmp;
}

void Lilist::move_front_to_back()
{   Node *tmp, *last;
    tmp = head;
    head = head->link;
    for(last=tmp; last->link != NULL; last = last->link);
       last->link=tmp;
       tmp->link=NULL;

}


