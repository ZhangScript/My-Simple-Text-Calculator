Simple calculator
Revision history:
Revised by dali zhang Novermber 2013
Originally written by Bjarne Stroustrup
(bs@cs.tamu.edu) Spring 2004.
This program implements a basic expression calculator.
Input from cin; output to cout.
The grammar for input is:
Statement:
	Expression
	Print
	Quit
Print:
	;
Quit:
	q;
Expression :
	Term
	Expression ‘+’ Term     e.g., 1+2, (1-2)+3, 2*3+1
	Expression ‘-’ Term
Term :
	Primary
	Term ‘*’ Primary      e.g., 1*2, (1-2)*3.5
	Term ‘/’ Primary
	Term ‘%’Primary
Primary :
	Number       e.g., 1, 3.5
	‘(’ Expression ‘)’    e.g., (1+2*3)
	"-" Primary
	"+" Primary
	Primary !
Number :
	floating-point literal    e.g., 3.14, 0.274e1

Input comes from cin through the Token_stream called ts.



change the cin into ist,and change the cout into ost,
we can input the data in the file.and put out the data to a new file 
#include<fstream>
string FileName;
cin>>FileName;
ifstream ist(FileName.c_str());
if(!ist) error("");
string OutputFile;
cin>>OutputFile;
ofstream ost(OutputFile.c_str());
