#include "inf_int.h"

using namespace std;
/*
Originally written by
컴퓨터공학부
정진경
*/
//Edited by 경영학부 방준석


inf_int::inf_int()
{
	this->digits=new char[2];	// 동적할당

	this->digits[0]='0';		// default 값 0 설정
	this->digits[1]='\0';
	this->length=1;
	this->thesign=true;
}

inf_int::inf_int(int n){
	char buf[100];

	if(n<0){		// 음수 처리
		this->thesign=false;
		n=-n;
	}else{
		this->thesign=true;
	}

	int i=0;
	while(n>0){			// 숫자를 문자열로 변환하는 과정
		buf[i]=n%10+'0';

		n/=10;
		i++;
	}

	if(i==0){	// 숫자의 절댓값이 0일 경우
		new (this) inf_int();	// 생성자 재호출...gcc에서 컴파일에러가 있다고 함. inf_int()의 경우 별개의 인스턴스가 생성됨. 
	}else{
		buf[i]='\0';

		this->digits=new char[i+1];
		this->length=i;
		strcpy(this->digits, buf);
	}
}
/*
 Function to reverse string
*/
char* reverse(char const* str) 
{ 
    // find length of string 
    int n = strlen(str); 
  
    // create a dynamic pointer char array 
    char *rev = new char[n+1]; //n+1
  
    // copy of string to ptr array 
    strcpy(rev, str); 
  
    // Swap character starting from two 
    // corners 
    for (int i=0, j=n-1; i<j; i++,j--) 
        swap(rev[i], rev[j]);        
    
    // return pointer of the reversed string 
    return rev; 
} 
/*
 Constructor for number in string format
*/
inf_int::inf_int(const char* str)
{
	// 부호 처리 
    int n = strlen(str);
    //char *temp = new char[n+1];
    char c = str[0];
    if(c=='-') {
        //음수
        this->thesign = false;
        this->length = n-1;
    }else {
        //양수
        this->thesign = true;
        this->length = n;
    }
    //Save reversed digits
    this->digits = new char[n+1];//+1
    this->digits = reverse(str);//str
    this->digits[length] = '\0';
}

inf_int::inf_int(const inf_int& a){
	this->digits=new char[a.length+1];

	strcpy(this->digits, a.digits);
	this->length=a.length;
	this->thesign=a.thesign;
}

inf_int::~inf_int(){
	delete digits;		// 메모리 할당 해제
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if(this->digits) {
		delete this->digits;		// 이미 문자열이 있을 경우 제거.
	}
	this->digits=new char[a.length+1];

	strcpy(this->digits, a.digits);
	this->length=a.length;
	this->thesign=a.thesign;

	return *this; 
}

bool operator==(const inf_int& a, const inf_int& b)
{
    // we assume 0 is always positive.
    if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )	// 부호가 같고, 절댓값이 일치해야함.
        return true;
    return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}
/*
 Function to compare the absolute values of a and b(doesn't consider a.thesign)

*/
bool operator>(const inf_int& a, const inf_int& b)
{
    int i;
    if(a.length > b.length) { return true; }
    else if(a.length < b.length) { return false; }
    else {
        for(i=a.length;i>=0;i--) {
            if((a.digits[i] - '0') > (b.digits[i] - '0')) {return true;}
            if((a.digits[i] - '0') < (b.digits[i] - '0')) {return false;}
        }
        return false;
    }
}
bool operator<(const inf_int& a, const inf_int& b)
{
	if(operator>(a, b) || operator==(a, b)) {
		return false;
	}else{
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if(a.thesign==b.thesign){	// 이항의 부호가 같을 경우 + 연산자로 연산
		for(i=0; i<a.length; i++){
			c.Add(a.digits[i], i+1);
		}	
		for(i=0; i<b.length; i++){
			c.Add(b.digits[i], i+1);
		}

		c.thesign=a.thesign;	

		return c;
	}else{	// 이항의 부호가 다를 경우 - 연산자로 연산
		c=b;
		c.thesign=a.thesign;

		return a-c;
	}
}
/*
 Function to subtract two numbers
*/
inf_int operator-(const inf_int& a, const inf_int& b)
{
    //new number
    inf_int c;

    unsigned int i;
    
    //if both are positive
    if(a.thesign == true && b.thesign == true) {
        //if a is bigger
        if(operator>(a,b)) {
            for(i=0;i<a.length;i++){
                c.Add(a.digits[i],i+1);
            }
            for(i=0;i<b.length;i++){
                c.Subtract(b.digits[i],i+1);
            }
            c.thesign = a.thesign;
            //cout << "++->+" << endl;
        //if b is bigger
        }
        if(operator>(b,a)) {
            for(i=0;i<b.length;i++) {
                c.Add(b.digits[i],i+1);
            }
            
            for(i=0;i<a.length;i++){
                c.Subtract(a.digits[i],i+1);
            }
            
            c.thesign = false;
            //cout << "++->-" << endl;
        }
        //if the numbers are the same ex) 10-10, then we leave c to its default value 0
    }
    //if both are negative 
    if(a.thesign == false && b.thesign == false) {
        //if a is bigger
        if(operator>(a,b)) {
            for(i=0;i<a.length;i++) {
                c.Add(a.digits[i],i+1);
            }
            for(i=0;i<b.length;i++) {
                c.Subtract(b.digits[i], i+1);
            }
            c.thesign = false;
            //cout << "--=>-" <<endl;
        }
        //if b is bigger
        else if(operator>(b,a)) {
            for(i=0;i<b.length;i++) {
                c.Add(b.digits[i],i+1);
            }
            for(i=0;i<a.length;i++) {
                c.Subtract(a.digits[i],i+1);
            }
            c.thesign = true;
            //cout<< "--=>+" << endl;
        }
        // if the numbers are the same default value is 0
    }
    //if it is + -
    if(a.thesign == true && b.thesign == false) {
        for(i=0;i<a.length;i++){
            c.Add(a.digits[i],i+1);
        }
        for(i=0;i<b.length;i++) {
            c.Add(b.digits[i],i+1);
        }
        c.thesign = true;
        //cout << "+- => +" << endl;
    }
    if(a.thesign == false && b.thesign == true) {
        for(i=0;i<a.length;i++){
            c.Add(a.digits[i],i+1);
        }
        for(i=0;i<b.length;i++) {
            c.Add(b.digits[i],i+1);
        }
        c.thesign = false;
        //cout << "-+ => -" << endl;
    }
    return c;
}
/*
 Function to multiply two numbers
*/
inf_int operator*(const inf_int& a, const inf_int& b)
{
    inf_int c;
    bool result_sign;
    if(a.thesign == b.thesign){result_sign = true;}
    else{result_sign = false;}
    char* temp_a = reverse(a.digits);
    char* temp_b = reverse(b.digits);
    //save numbers in variables, have to reverse
    string x, y;
    x.assign(temp_a,a.length);
    y.assign(temp_b,b.length);

    int n = a.length;
    int m = b.length;
    string ans(n+m, '0');
    for(int i = n - 1; i>=0; i--){
      for(int j = m - 1; j >= 0; j--){
         int p = (x[i] - '0') * (y[j] - '0') + (ans[i + j + 1] - '0');
         ans[i+j+1] = p % 10 + '0';
         ans[i+j] += p / 10 ;
      }
   }
    for(int i = 0; i < m + n; i++){
        if(ans[i] !='0'){
            string temp = ans.substr(i);
            const char *c = temp.c_str(); 
            inf_int result(c);
            result.thesign = result_sign;
            return result;
        }
   }
   string temp = "0";
   const char *d = temp.c_str();
   inf_int result(d);
   result.thesign = result_sign;
   return result;
}


ostream& operator<<(ostream& out, const inf_int& a)
{
	int i;
    if(a.digits[a.length-1]=='+' || a.digits[a.length-1]=='-') {
        i = a.length-2;
    }
    else{
        i = a.length-1;
    }
	if(a.thesign==false){
		out<<'-'; // $
    }
    if( (a.length != 1) && (a.digits[a.length-1] == '0') ) {
        a.digits[a.length-1] = '\0';
        for(int i=a.length-2;i>=0; i--){
            out << a.digits[i];
	    }
    }else{
        for(int i=a.length-1;i>=0; i--){
            out << a.digits[i];
	    }
    }
    out << endl;
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if(this->length<index){
		this->digits=(char*)realloc(this->digits, index+1);

		if(this->digits==NULL){		// 할당 실패 예외처리
			cout<<"Memory reallocation failed, the program will terminate."<<endl;

			exit(0);
		}
		this->length=index;					// 길이 지정
		this->digits[this->length]='\0';	// 널문자 삽입
	}
	if(this->digits[index-1]<'0'){	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index-1]='0';
	}
	this->digits[index-1]+=num-'0';	// 값 연산

	if(this->digits[index-1]>'9'){	// 자리올림이 발생할 경우
		this->digits[index-1]-=10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index+1);			// 윗자리에 1을 더한다
	}
}
void inf_int::Subtract(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if(this->length<index){
		this->digits=(char*)realloc(this->digits, index+1);

		if(this->digits==NULL){		// 할당 실패 예외처리
			cout<<"Memory reallocation failed, the program will terminate."<<endl;

			exit(0);
		}
		this->length=index;					// 길이 지정
		this->digits[this->length]='\0';	// 널문자 삽입
	}
	if(this->digits[index-1]<'0'){	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index-1]='0';
	}
    //check if this->digits[index-1] > num
    if(this->digits[index-1] >= num) { this->digits[index-1]-=num-'0'; }
    else {
        //add 10 to number before subtracting
        this->digits[index-1] += 10;
        this->digits[index-1] -= num-'0';
        Subtract('1', index+1);
    }
}
