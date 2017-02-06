#include"calculate3.h"

int main()
try {		// predefine names:
	cout<<"Now you can use the calculator designed by zdl"<<endl
		<<"	It supports many functions,but still has many weaknesses"<<endl;
	cout<<"Here are some Instructions for you:"<<endl
		<<"		1.We allow + - * / ! ^and mitipu-! calculating method ,"<<endl
		<<"		2.!! means like this <4!!=4*2>,!!!means like this <6!!!=6*3>"<<endl
		<<"		3.You can define the val by yourself and use it in the following"
		<<"		calculating,but it dosen't support the repeated val defination"<<endl
		<<"		4.You can even calculate the value of 2.1^3.2"<<endl
		<<"		5.It can not support the scentific input,so 2e means 2*e"<<endl
		<<"		6.Don't put the space after the number,we considered it a error"<<endl
		<<"		7.Attention :do not enter chinese characters in the programe,"<<endl
		<<"		it has no idea about that"<<endl
		<<"		8.To make it more general,we have already set pi(3.1415926) and"<<endl
		<<"		e(2.78) for you"<<endl
		<<"		9.You need to enter a ';' behind the expression to print the "<<endl
		<<"		result"<<endl;
	cout<<"Anyway,it's not a too bad calcutor,try to use it :"<<endl<<endl;
	define_name("pi",3.1415926535);
	define_name("e",2.7182818284);
	calculate();
	keep_window_open();		 // cope with Windows console mode
	return 0;
}
// to catch the expected errors
catch(exception& e){
	cerr<<e.what()<<endl;
	keep_window_open("~~");
	return 1;
}
// to catch the unexpected errors
catch(...){
	cerr<<"exception\n";
	keep_window_open("~~");
	return 2;
}
