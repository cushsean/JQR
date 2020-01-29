#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "que.h"


int main(){
	int num = 0;
	void* ptr = &num;
	node_t* front = mkQue(10);
	ptList(front);
	printf("%d\n", que_get_size(front));
	num = 4;
	front = que_find_by_elem(front, num);
	printf("The %dth element is: %d\n", num, *((int*)front->data));
	printf("%d\n", que_get_size(front));
	ptList(front);
	num = 6;
	ptr = &num;
	front = que_find_by_val(front, ptr);
	printf("The element with value %d is: %d\n", num, *((int*)front->data));
	printf("%d\n", que_get_size(front));
	ptList(front);
	num = 7;
	ptr = &num;
	front = rm_que_item(front, ptr);
	ptList(front);
	rmQue(front);
	//ptList(front);
	
	return 0;	
}
