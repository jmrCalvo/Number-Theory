// CPP program to check for primality using
// Lucas-Lehmer series.
#include <cmath>
#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/xdouble.h>
#include <NTL/quad_float.h>

NTL_CLIENT
using namespace std;
 
// Function to check whether (2^p - 1)
// is prime or not.
ZZ pow(ZZ base,ZZ exp){
	ZZ zero=(ZZ)0;
	ZZ one=(ZZ)1;	
	ZZ resultado=one;
	while(exp!=zero){
		resultado=resultado*base;
	exp=exp-one;
	}

	return resultado;	
}

bool isPrime(ZZ p) {
 	ZZ dos=(ZZ)2;
	ZZ one=(ZZ)1;
	ZZ four=(ZZ)4;
	ZZ zero=(ZZ)0;
  // generate the number
  ZZ checkNumber = pow(dos,p)-one;
 
  // First number of the series
  ZZ nextval = four % checkNumber;
 
  // Generate the rest (p-2) terms
  // of the series.
  for (ZZ i =(ZZ) 1; i < p - one; i=i+one) 
    nextval = (nextval * nextval - dos) % checkNumber;  
 
  // now if the (p-1)th term is
  // 0 return true else false.
  return (nextval == zero);
}
 
// Driver Program
int main() {
  // Check whether 2^p-1 is prime or not.
  ZZ p =(ZZ) 7;
  ZZ dos=(ZZ)2;
  ZZ one=(ZZ)1;
 
  ZZ checkNumber =pow(dos,p)-one;
 
  if (isPrime(p))
    cout << checkNumber << " is Prime.";
  else
    cout << checkNumber << " is not Prime.";
 
  return 0;
}
