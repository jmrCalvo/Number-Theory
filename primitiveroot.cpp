#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


 //************GENERATE AN ODD PRIME RANDOM q**********************// 
bool isPrime(int p) {
  long long checkNumber = pow(2, p) - 1;
  long long nextval = 4 % checkNumber;
  for (int i = 1; i < p - 1; i++) 
    nextval = (nextval * nextval - 2) % checkNumber;  
  return (nextval == 0);
}
int funcionprime(int n) {
  long long checkNumber = pow(2, n) - 1;
  if (isPrime(n)){
  return CheckNumber;}
  else{
	  int num=rand()%5;
	funcionprime(p+n);}		
}
//*************************************************************************//
//**************GENERATE A PRIME P & Q******************************//
int generateP&Q(){
	int numero=rand()%10+2;//it could be between 2 and 11	
	int q=funcionprime(numero);
	int p=2*q+1;
	return p;
}
//***********************************************************************//
//***********************Baby-step giant-step algorithm*************//
bool alreadyis(int solution,vector<int> &root){
	for(int i=0;i<root.size();i++){
		if(root[i]==solution){return true;}
	}
return false;
}

bool test(int valor, int p){
	vector<int> root;
	int top=sqrt(p)+1;
	for (int i=0;i<top;i++){
	int solution=pow(valor,i)%p;
	if(alreadyis(solution,root)){
		return false;	
	}
	else{
		root.push_back(solution);
	}
	}
return true;
}




int primitiveroot(){
	int alfa=2;
	int p=generateP&Q();
	while(!test(alfa,p)){
		alfa++;
	}
}



int main(){

// Generate α, a primitive root modulo a prime p, where p is an odd prime, using one of the algorithms discussed in class (assume that the prime factorization of p − 1 is known in advance - the simplest choice will be p = 2q + 1, where p and q are odd primes).

// For p and α generated as above and an arbitrary β ∈ Z ∗ p , compute the discrete logarithm log α β, using one of the algorithms discussed in class (Skanks or Pollard). Use moderate-sized primes (e.g., p is on 32 bits).

//Implement the Silver-Pohlig-Hellman algorithm for computing discrete logarithms modulo a large prime p (e.g., p is on 1024 bits). Assume that p − 1 has only small prime divisors and that its prime factorization is known in advance.


}
