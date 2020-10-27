#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
    //testing constructors 
	inf_int a, e;
	inf_int b(100);
	inf_int c("-62343242340");
	inf_int d("223423460");
	inf_int f=d;
    inf_int g(f);
    //testing operations
    a = c+d;
    cout<< c << "Addition " << d << "=> " << a <<endl;

    b = d-c;
    cout << d << "Subtraction " << c << "=> " << b<<endl;

    e = c*d;
    cout << c<< "Multiplication " << d << "=> " << e <<endl;

	return 0;
    
}

