void reset_handler(void)
{
	while (1)
	{	
		func0();
		func1(1,2);
		func2(1,2,3);
		func3(1,2,3,4);
	}
	;
}
int func0(){
	func1(3,4);
	return 16;
}
int func1(int a,int b){
	return a+b;
}
int func2(int a,int b,int c){
	return c+func1(a,b);
}
int func3(int a,int b,int c,int d){
	return a+func2(b,c,d);
}
int func_caller(){
	return func1(4,5);
}

