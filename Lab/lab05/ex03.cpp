#include<iostream>
using std::cout;
using std::endl;
bool isPrime(int num) {
    if (num <= 1) return false;
	for(int i = 2; i * i <= num; ++i)
		if(num % i == 0)
			return false;
	return true;
}
int main() {
	int a = 23;
	cout<<isPrime(a)<<endl;
return 0;
}
