#include <iostream>
#include "binary.h"
using namespace std;

int main() {
  BinaryTree tree;
  char option;
  int value;

  do {
    cin >> option;
    switch(option) {
      case 'i':
        cin >> value;
        tree.insert(value);
        break;
      case 's':
        cin >> value;
        tree.search(value);
        break;
      case 'p':
        tree.iterative_print();
        break;
      case 'r':
        tree.recursive_print();
        break;
      default:
        break;
    }
  } while(option != 'q');
}
