// wap to add numbers using two concept of function and multiple parameterss
#include <iostream>
using namespace std;
//this is a new function with two parameters
void add(int num1, int num2) {
    cout << "sum: " << (num1 + num2);
}

int main() {
// calling the above function 
    add(3, 2);
    return 0;
}
