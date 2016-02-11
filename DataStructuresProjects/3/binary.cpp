#include <stack>
#include <iostream>
#include "binary.h"
using namespace std;

//******CREATE AND DESTROY

BinaryTree::BinaryTree() {
  root = NULL;
}

BinaryTree::~BinaryTree() {
  destroy(root);
}

void BinaryTree::destroy(BinaryNode* node) {
  if(node == NULL)
    return;

  if(node->left != NULL)
    destroy(node->left);

  if(node->right != NULL)
    destroy(node->right);

  delete node;
}
//****************

//*******INSERT
void BinaryTree::insert(int value)
{
  root = insert_helper(value, root);
}

//** REVISE THIS FUNCTION
BinaryNode* BinaryTree::insert_helper(int value, BinaryNode* node)
{

  //** Root is NULL
  if(node == NULL)
  {
    return create_node(value);
  }
  //** Move left
  else if(value < node->value)
  {
      node->left = insert_helper(value, node->left);
      node = balance(node);
  }
  //** Move right
  else if(value >= node->value)
  {
    node->right = insert_helper(value, node->right);
    node = balance(node);
  }
  return node;
}

BinaryNode* BinaryTree::create_node(int value)
{
    BinaryNode* node = new BinaryNode;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
//****************

//*********PRINT
void BinaryTree::iterative_print()
{
  stack<BinaryNode*> stack1;
  BinaryNode *current = root;
  bool done = false;
  cout<<"Iterative In order "<<endl;
  while(!done)
  {
      if(current)
      {
          stack1.push(current);
          current = current->left;
      }
      else
      {
        if(stack1.empty())
         {
          done = true;
         }
        else
         {
            current = stack1.top();
            stack1.pop();
            cout<<current->value<<" ";
            current = current->right;
         }
      }
  }
  cout<<endl;
}

void BinaryTree::recursive_print() {
  recursive_print_helper(root);
  cout << endl;
}

void BinaryTree::recursive_print_helper(BinaryNode* node) {
  if(node == NULL)
    return;

  recursive_print_helper(node->left);
  cout << node->value << " ";
  recursive_print_helper(node->right);
}
//****************

//*********SEARCH
void BinaryTree::search(int value) {
  int steps = 0;
  search_helper(value, root, steps);

  cout << "Value: " << value << " Steps: " << steps << endl;
}

void BinaryTree::search_helper(int value, BinaryNode* node, int& steps) {
  steps++;

  //** Root is NULL
  if(node == NULL) {
    return;
  }

  //** Item found
  if(value == node->value) {
    return;
  }

  //** Move left
  if(value < node->value) {
    if(node->left == NULL) {
      return;
    }
    search_helper(value, node->left, steps);
  }
  //** Move right
  else {
    if(node->right == NULL) {
      return;
    }
    search_helper(value, node->right, steps);
  }
}
//***

BinaryNode* BinaryTree::r_rotate(BinaryNode *node)
{
    BinaryNode * tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    return tmp;
}

BinaryNode* BinaryTree::l_rotate(BinaryNode *node)
{
   BinaryNode* tmp = node->left;
   node->left =  tmp->right;
   tmp->right = node;
   return tmp;
}
BinaryNode* BinaryTree::lr_rotate(BinaryNode *node)
{
    BinaryNode* tmp;
    tmp = node->left;
    node->left = r_rotate(tmp);
    return l_rotate(node);
}
BinaryNode* BinaryTree::rl_rotate(BinaryNode *node)
{
    BinaryNode* tmp;
    tmp = node->right;
    node->right = l_rotate(tmp);
    return r_rotate(node);
}
BinaryNode* BinaryTree::balance(BinaryNode * node)
{
   int bal = get_balance(node);
   if (bal > 1)
   {
       if(get_balance(node->left) > 0)
          node = l_rotate(node);
       else
          node = lr_rotate(node);
   }
   else if(bal < -1)
   {
       if(get_balance(node->right) > 0)
          node = rl_rotate(node);
       else
          node = r_rotate(node);
   }
   return node;
}


int BinaryTree::height(BinaryNode *n)
{   int K = 0;
    if(n != NULL)
    {
        int lheight = height (n->left);
        int rheight = height (n->right);
        int maximum = max(lheight, rheight);
        K = maximum + 1;
    }
    return K;
}

int BinaryTree::get_balance(BinaryNode *n)
{
  int lheight = height(n->left);
  int rheight = height(n->right);
  int bal = lheight - rheight;
  return bal;
}

