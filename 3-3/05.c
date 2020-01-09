#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "que.h"


int main(){
	
	node_t* front = mkQue(10);
	ptList(front);
	printf("%d\n", que_get_size(front));
	int num = 4;
	front = que_find_by_elem(front, num);
	printf("The %dth element is: %d\n", num, front->data);
	printf("%d\n", que_get_size(front));
	ptList(front);
	num = 6;
	front = que_find_by_val(front, num);
	printf("The element with value %d is: %d\n", num, front->data);
	printf("%d\n", que_get_size(front));
	ptList(front);
	front = rm_que_item(front, 7);
	ptList(front);
	rmQue(front);
	//ptList(front);
	
	return 0;	
}
