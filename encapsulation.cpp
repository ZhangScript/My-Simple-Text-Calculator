#include"calculate3.h"


const char number = '8';    // a floating-point number
const char quit = 'q';    // an exit command
const char print = ';';    // a print command
const string prompt = "> ";
const string result = "= ";  // indicate that a result follows
const char name = 'a';  // name token
const char let = 'L';  // declaration token
const string declkey = "let"; // declaration keyword
const char factorial='!';//declaration factorial
const char TheDeltaOfCharToInt='0';//beacuse the Asc of zero is 48
const char IndexCalculate='^';


vector<Variable> var_table;
Token_stream ts;

void set_value(string s, double d)  // set the Variable named s to d
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) {
			var_table[i].value = d;
		return;
	}
	error("set: undefined variable ", s);
}

//initialize Token_stream
Token_stream::Token_stream() :full(false),buffer(0) {};
//put the judged Token into the Token_stream, make the buffer empty
void Token_stream::putback (Token t)
{
	if (full) error("putbake() into a full buffer");
	buffer=t;
	full=true;
}
void Token_stream::ignore(char c)
	// skip characters until we find a c; also discard that c
{
	// first look in buffer:
	if (full && c==buffer.kind) {  // && meresult and
		full = false;
		return;
	}
	full = false;  // discard the contents of buffer
	// now search input:
	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}
Token Token_stream::get() 
{
	if (full){
		full=false;
		return buffer;
	}
	
	char ch;
	cin>>ch;

	switch (ch) {
	case ';':   // print 
	case 'q':  //  quit
	case '(':
	case ')': 
	case '+': 
	case '-':
	case '*': 
	case '/': 
	case '%':
	case '=':
	case '!':
	case IndexCalculate:
		return Token ( ch );  // the meaning of the character matches itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		{ 
			cin.putback(ch);
			double val1=0;
			while(true){
				char t3=getchar();
				if(isdigit(t3)){
					double t8=t3- TheDeltaOfCharToInt;
					val1=10*val1+t8;
					continue;
				} 
				else {
					cin.putback(t3);
					break;
				}
			}
			double  val4=0;
			char t4=getchar();
			int times = 1;
			if(t4=='.'){
				while (true){
					char t5=getchar();
					if(isdigit(t5)){
						 double t7=t5- TheDeltaOfCharToInt;
						val4=val4+t7/pow(10.0,times);
						times++;
						continue;
					}
					else {
						cin.putback(t5);
						break;
					}
				}
			} else cin.putback(t4);
			double  val=val1+val4;
			char t2=getchar();
			if (t2=='.')  error("too many points in one number");									//to solve the problem like 1.1.1
			if (isspace(t2)) error("sorry, don't put the space or enter between the expression, \ncheck if you have entered ';'");	//we don't allow the space between the expression
			cin.unget();
			return Token(number,val);  // use'8' to represent that it is a number
		}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
			cin.putback(ch);
			if (s == declkey) return Token(let); // keyword "let"
			return Token(name,s);
		}
	error("Bad token");
	}
}


 double calculate_factorial(double x,int y){
	int zero_factorial=1;
	if (int(x)!=x||x<0)
		error ("Sorry not a positive integer, Please check it");
	else if (x>100) error("Oops,it's a too big number,try again");
	else if (x==0)  return zero_factorial;
	else {
		for (int i=x-y;i>0;i-=y)
			x*=i;
	}
	return x;
}

double expression();

double get_value(string s);
bool is_declared(string var)
	// is var already in var_table?
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == var) return true;
	return false;
}
double define_name(string var, double val)
	// add (var,val) to var_table
{
	if (is_declared(var)) error(var," declared twice");
	var_table.push_back(Variable(var,val));
	return val;
}
double declaration()
	// handle: name = expression
	// declare a variable called "name" with the initial value "expression"
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");
	string var_name = t.name;
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);
	double d = expression();
	define_name(var_name,d);
	cout<<"in this case "<<var_name;
	return d;
}

double primary()
{ 
	Token t=ts.get();	
	double result=0;
	switch(t.kind){			
	case name:
		result = get_value (t.name);
		break;
	case'(':				
		result=expression();
		t=ts.get();
		if(t.kind!=')')	error("')' expected");
		break;
	case number:		
		result=t.value;
		break;
	case'-':			
		result=-primary();
		break;
	case'+':
		result=primary();		
		break;
	default:				
		ts.putback(t);
		error("primary expected");
	}
	Token t3 = ts.get();
	if ( t3.kind == factorial)
	{
		int factorial_time=1;
		Token t2 = ts.get();
		while(t2.kind == factorial){
			factorial_time++;
			t2 = ts.get();
		}
		ts.putback(t2);
		return calculate_factorial (result,factorial_time);
	}
	else {
		ts.putback(t3);
		return result;
	}
}

double middle()
{
	double left=primary();
	while (true){
		Token t=ts.get();
		switch (t.kind){
		case IndexCalculate:
			{
				double val2=primary();
				//to prevent the user to put a too large number in the expression 
				if (left<-1000||left>1000||val2>=1000) error("it's a too large number ");
				left= pow(left,val2);
				return left;
			}

		default:
			ts.putback(t);
			break;
		}
		break;
	}
	return left;
}
double term()  // deal with  '*' and '/'
{
	double left = middle();  
	Token t = ts.get();  // get the next token from the input
	while (true) {		
		switch (t.kind) {
		case '*':
			left*=middle();
			t=ts.get();
			break;
		case '/':
			{
				double d=middle();
				if(d==0) error("divide by zero");
				left/=d;
				t=ts.get();
				break;
			}
		case '%':
			{
				double d = middle();
				int i1 = int(left);
				if (i1 != left) error ("left-hand operand of % not int");
				int i2 = int(d);
				if (i2 != d) error ("right-hand operand of % not int");
				if (i2 == 0) error("%: divide by zero");
				left = i1%i2;
				t = ts.get();
				break;
			}
		case name:
			return left*=get_value(t.name);
		default:
			ts.putback(t);  // put the unused token back to the token stream
			return left;
		}
	}
}
double expression() {
     // deal with + and -
	double left = term(); 	
	while (true) {
		Token t = ts.get();  // get the next token from the token stream
		switch (t.kind) {
		case '+':    left += term(); break;
		case '-':    left -= term(); break;
		default:    ts.putback(t);  // put the unused token back to the token stream
		return left;
		}
	}
}
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
	return expression();
	}
}
double get_value(string s)  // return the value of the Variable names s
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined variable ", s);
}

void clean_up_mess()
{ 
	ts.ignore(print);
} 
void calculate()
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get(); 
		if (t.kind  == quit) return; 
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl; 
		clean_up_mess();
	}
} 
