#include <stdio.h>
#include <stdlib.h>
#include <vector>


struct int_linked_list_node {
  int_linked_list_node *next_node;
  int data;
  int_linked_list_node(int data){
    this->data = data;
    next_node = nullptr;
  }
};

struct int_linked_list{
  int length;
  int_linked_list_node* first_node;
  int_linked_list(std::vector<int> data){
    this->length=data.size();
    if(data.size() == 0){
      this->first_node=nullptr;
      return;
    }
    this->first_node=new int_linked_list_node(data[0]);
    int_linked_list_node *last_node=this->first_node;
    for(int i=1;i<data.size();i++){
      int_linked_list_node *node=new int_linked_list_node(data[i]);
      last_node->next_node=node;
      last_node=node;
    }
  }
};


void print_int_linked_list(int_linked_list* list){
  int_linked_list_node *l = list->first_node;
  while (true)
  {
    printf("%d, ",l->data);
    if (l->next_node==nullptr){
      break;
    }
    l=l->next_node;
  }
  printf("\n");
}



int main() {
  int_linked_list* test = new int_linked_list(std::vector<int>{1,2,3,4});
  print_int_linked_list(test);
  return 0;
}
