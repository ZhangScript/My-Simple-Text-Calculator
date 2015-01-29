#include "std_lib_facilities.h"
using namespace std;

extern const char number;    // a floating-point number
extern const char quit;    // an exit command
extern const char print;    // a print command
extern const string prompt;
extern const string result;  // indicate that a result follows
extern const char name;  // name token
extern const char let;  // declaration token
extern const string declkey; // declaration keyword
extern const char factorial;//declaration factorial
extern const char TheDeltaOfCharToInt;//the delta from char to int,used for solve the problem like 2e

class Token {
public:
	char kind;  // what kind of token
	double value;  // for numbers: a value 
	string name;  // for names: name itself
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n) : kind(ch), name(n) {}
};
class Variable {
public:
	string name;
	double value;
	Variable (string n, double v) :name(n), value(v) { }
};
extern vector<Variable> var_table;

void set_value(string s, double d);  // set the Variable named s to d

//create a class named Token_stream with buffer to become the place to store, and a pointer to judge if the buffer is empty or not
class Token_stream {
	bool full;    // is there a Token in the buffer?
	Token buffer; // here is where we keep a Token put back using putback()
public:
	Token get();    // get a Token
	void putback(Token t);  // put back a Token
	Token_stream();    // make a Token_stream that reads from cin
	void ignore(char c);  // discard tokens up to and including a c
};

extern Token_stream ts;

double get_value(string s);
bool is_declared(string var);
	// is var already in var_table?

double define_name(string var, double val);
	// add (var,val) to var_table

double declaration();
	// handle: name = expression
	// declare a variable called "name" with the initial value "expression"

double primary();
double middle();
double term();  // deal with * and /
double expression();

double statement();

double get_value(string s);  // return the value of the Variable names s

void clean_up_mess();
void calculate();
