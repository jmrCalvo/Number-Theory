// C++ program to implement Solovay-Strassen
// Primality Test
#include <NTL/ZZ.h>
#include <NTL/xdouble.h>
#include <NTL/quad_float.h>
#include<iostream>


NTL_CLIENT
using namespace std;
 
// modulo function to perform binary exponentiation
long long modulo(long long base, long long exponent,
                                      long long mod)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
 
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
 
    return x % mod;
}
 
// To calculate Jacobian symbol of a given number
ZZ calculateJacobian(ZZ a, ZZ n){
   	ZZ dos=(ZZ)2;
	ZZ zero=(ZZ)0;
	ZZ one=(ZZ)1;
	ZZ four=(ZZ)4;
	ZZ three=(ZZ)3;
	ZZ eight=(ZZ)8;
	ZZ five=(ZZ)5;

 if (a==zero)
        return zero;
 
    ZZ ans = one;
    if (a < zero){
        a = -a; // (a/n) = (-a/n)*(-1/n)
        if (n % four == three)
            ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
    }
 
    if (a == one)
        return ans;// (1/n) = 1
 
    while (a!=zero){
		if (a < zero){
			a = -a;// (a/n) = (-a/n)*(-1/n)
			if (n % four == three)
			ans = -ans;// (-1/n) = -1 if n = 3 (mod 4)
		}
		while (a % dos == zero){
			a = a / dos;
			if (n % eight == three || n % eight == five)
			ans = -ans;
		}
		//swap
		ZZ aux=a;
		a=n;
		n=aux;

		if (a % four == three && n % four == three){
			ans = -ans;
		}

		a = a % n;

		if (a > n / dos){
		a = a - n;
		}
    }
 
    if (n == one)
        return ans;
 
    return zero;
}
 
// To perform the Solovay-Strassen Primality Test
bool solovoyStrassen(ZZ p, int iterations){
	ZZ dos=(ZZ)2;
	ZZ zero=(ZZ)0;
	ZZ one=(ZZ)1;
    if (p < dos)
        return false;
    if (p != dos && p % dos == zero)
        return false;
 
    for (int i = 0; i < iterations; i++)
    {
        // Generate a random number a
       ZZ a = RandomBits_ZZ(32) % (p - one) + one;
        ZZ jacobian = (p + calculateJacobian(a, p)) % p;
        ZZ mod =PowerMod(a,(p-one)/dos,p);
 
        if (jacobian==zero || mod != jacobian)
            return false;
    }
    return true;
}
 

int main()
{
    int iteraciones = 50;
    ZZ num1 =(ZZ) 15;
    ZZ num2 =(ZZ) 13000;
 
    if (solovoyStrassen(num1, iteraciones))
        cout<<num1<<" is prime"<<endl;
    else
        cout<<num1<<" is composite"<<endl;
 
    if (solovoyStrassen(num2, iteraciones))
        cout<<num2<<" is prime"<<endl;
    else
       cout<<num2<<" is composite"<<endl;
 
    return 0;
}
