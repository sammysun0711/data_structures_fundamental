#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
// https://github.com/jimboweb/TreeHeight/blob/master/TreeHeight/src/tree_height.java
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
  //if (node->parent == NULL) {
  //  height = 1;
    //return height;
  //}
  
  if(node->children.size() == 0){
    maxHeight = 1;
  }
  else {
    for (int i = 0; i < node->children.size(); i++){
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
/**
int compute_height(std::vector<Node> nodes){
  int maxHeight = 0;
  std::vector<int> heights;
  for (int i = 0; i < nodes.size(); i++){
    heights.push_back(0);
  }
  for (int vertex = 0; vertex < nodes.size(); vertex++){
    if (heights[vertex] != 0)
      continue;
    int height = 0;
      for (int i = vertex; i != -1; i = nodes[i].key){
        if (heights[i] != 0){
          height += heights[i];
          break;
        }
        height++;
      }
      maxHeight = std::max(maxHeight, height);
      for (int i = vertex; i!=-1; i= nodes[i].key){
        if (heights[i]!= 0)
          break;
        heights[i] = height--;
      }
  }
  return maxHeight;
}
**/
/**
void visit_children(std::vector<Node> nodes){
  Node * currentParent;
  std::vector<Node *> currentChildren = currentParent->children;
  for (std::vector<Node *>::iterator it = currentChildren.begin(); it != currentChildren.end(); it++){
      compute_height(&it);
  }
}

int compute_height(Node* it){
  int maxHeight = 0;
  int height = 0;
  if (it->parent == NULL){
    height = 1;
  }
  else{
    //height = compute_height();
  }
}
**/

/**
int compute_height(std::vector<Node> nodes){      
  int maxHeight = 0;
  int height = 0;
  int n = nodes.size();
  int children[n][2];
  std::vector<int> childrenArray;
  childrenArray.resize(n);
  int vDepth[n];
  Node *currentParent;
  for (int vertex = 0; vertex < n; vertex++){
    currentParent = &nodes[vertex];
    if (currentParent == NULL){
      height = 1;
      continue;
    }
    else {
      std::vector<Node *> children = currentParent->children;
      for (std::vector<Node *>::iterator it = children.begin(); it != children.end(); it++){
        height = compute_height(&it);
      } 
    }
    if (height >  maxHeight){
      maxHeight = height;
    }
  }
  return maxHeight;
}
**/
/**
int Height(std::vector<Node> nodes){
  int MaxHeight = 0;
  if (nodes.empty())
    return 0;
  else 
    while(nodes.empty())
      Node node = nodes.at(0);
      nodes.pop_back();
      int height = Height(node.children);
      if (height > MaxHeight){
        MaxHeight = height;
      }
    return MaxHeight;
    }
}
**/

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
  //std::cout << compute_height(nodes) << std::endl;
  
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
  /**
  int MaxHeight = Height(nodes); 
  std::cout << MaxHeight << std::endl;
  return 0;
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
