#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

Node* find_root_ptr(std::vector<Node> nodes){
  Node* currentParent;
  currentParent = &nodes[0];
  while(currentParent->parent != NULL){
    currentParent = currentParent->parent;
  }
  //std::cout << "root index is " << currentParent->key<<std::endl;
  return currentParent;
}



int compute_height(Node* node){
  int maxHeight = 0;  
  int height = 0;
  if (node == NULL){
    return 0;
  }
  else{
    if(node->children.size() == 0){
      maxHeight = 1;
    }
    else {  
      for (unsigned int i = 0; i < node->children.size(); i++){
        height = compute_height(node->children.at(i)) + 1;
        if (height > maxHeight){
          maxHeight = height;
        }
        //std::cout << "height is " << height << std::endl;
        //std::cout << "maxHeight is " << maxHeight << std::endl;
      }
    }
    //std::cout << "returned maxHeight is " << maxHeight << std::endl;
    return maxHeight;
  }
} 

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
   
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  Node* root = find_root_ptr(nodes);
  int tree_height = compute_height(root);
  std::cout << tree_height << std::endl;
  return tree_height; 
}
  // Replace this code with a faster implementation
  /**int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
  **/

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
