int cmp_int(int num1, int num2){
	if(num1 == num2)
		return 0;
	else if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
	else{
		fprintf(stderr, "ERROR: Compare Failed\n");
		return 0;
	}
}