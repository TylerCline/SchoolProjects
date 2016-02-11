struct BinaryNode {
  int value;
  BinaryNode *left;
  BinaryNode *right;

};

class BinaryTree {

public:
  BinaryTree();
  ~BinaryTree();
  void destroy(BinaryNode* node);

  void insert(int value);
  void search(int value);
  void iterative_print();
  void recursive_print();
  BinaryNode* r_rotate(BinaryNode *node);
  BinaryNode* l_rotate(BinaryNode *node);
  BinaryNode* lr_rotate(BinaryNode *node);
  BinaryNode* rl_rotate(BinaryNode *node);
  BinaryNode* balance(BinaryNode * node);
  int height(BinaryNode *n);
  int get_balance(BinaryNode * n);



private:
  BinaryNode* insert_helper(int value, BinaryNode* node);
  BinaryNode* create_node(int value);
  void search_helper(int value, BinaryNode* node, int& steps);
  void recursive_print_helper(BinaryNode* node);
  BinaryNode* root;
};
