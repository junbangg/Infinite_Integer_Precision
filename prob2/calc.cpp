#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

#include "../prob1/inf_int.h"

using namespace std;

int main() {

    while(1) {
        //string to hold expression
        string exp;
        //prompt user
        cout<< "(+number)(space)(operator)(space)(-number)"<<endl;
        cout<<endl;
        cout<< "Input: ";
        //get and split string
        getline(cin, exp);
        istringstream buf(exp);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);
        //vector to hold tokenized expression
        vector<string> expression;
        //check if input was 0
        if(exp == "0") {break;}
        //push tokenized expression to vector
        for(int i=0;i<tokens.size();i++) {
            expression.push_back(tokens[i]);
        }
        //pointers to hold numbers
        const char *x_ptr = expression[0].c_str();
        const char *y_ptr = expression[2].c_str();
        //char to hold operator
        char op[1];
        //initialize class
        inf_int x(x_ptr);
        inf_int y(y_ptr);
        //result class
        inf_int result;
        //copy operator to char
        strcpy(op, expression[1].c_str());
        //calculate
        switch(op[0]) {
            case '+':
                result = operator+(x,y);
                cout << "Output: "<< result << endl;
                break;
            case '-':
                result = operator-(x,y);
                cout << "Output: " << result << endl;
                break;
            case '*':
                result = operator*(x,y);
                cout << "Output: " << result << endl;
                break;
            default:
                cout<<"Wrong expression format" << endl;
        }

    }
       
}
