#ifndef QUE_H_CUSHMAN
#define QUE_H_CUSHMAN

node_t* mkQue(int);
node_t* que_find_by_elem(node_t*, int);
node_t* que_find_by_val(node_t*, void*);
node_t* rm_que_item(node_t*, void*);
void rmQue(node_t*);
int que_get_size(node_t*);
node_t* dQue(node_t*);

#endif /* QUE_H_CUSHMAN */