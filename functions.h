#ifndef FUNCTION_H  
#define FUNCTION_H 

struct list_node_s;
int Insert(int value, struct list_node_s** head_pp);
int Member(int value, struct list_node_s* head_p);
int Delete(int value, struct list_node_s** head_pp);
int * getRandom();

#endif