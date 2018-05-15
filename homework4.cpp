#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<map>

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
  return checkNumber;}
  else{
	  int num=rand()%5;
	funcionprime(num);}		
}
//*************************************************************************//
//**************GENERATE A PRIME P & Q******************************//
int generatePQ(){
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
	int solution=pow(valor,i);
	solution=solution%p;
	if(alreadyis(solution,root)){
		return false;	
	}
	else{
		root.push_back(solution);
	}
	}
return true;
}




int primitiveroot(int &p){
	int alfa=2;
	 p=generatePQ();
	while(!test(alfa,p)){
		alfa++;
	}
	return alfa;
}
struct Triple{
	int x, y, z;
	Triple(const int a, const int b, const int c) : x(a), y(b), z(c) { }
};

Triple ExtendedGCD(const int a, const int b){
	if (b == 0) return Triple(1, 0, a);
	const Triple last = ExtendedGCD(b, a%b);
	return Triple(last.y, last.x - a / b * last.y, last.z);
}
void insertTo(vector<pair<int,int> > &myvector,int base,int i){
	pair<int,int> p(base,i);
	myvector.push_back(p);
}


int BabyStep(int A, int B, int C){
	const int sqrtn = static_cast<int>(std::ceil(std::sqrt(C)));
	int base = 1;
	/*hash.clear();*/vector<pair<int,int> > myvector; 
	for (int i = 0; i < sqrtn; ++i)
	{
		/*hash.insert(base, i);*/insertTo(myvector,base,i);
		base = base*A % C;
	}
	int i = 0, j = -1, D = 1;
	for (; i < sqrtn; ++i)
	{
		Triple res = ExtendedGCD(D, C);
		const int c = C / res.z;
		res.x = (res.x * B / res.z % c + c) % c;
		
		if(res.x<myvector.size()){j = (myvector[res.x]).second;}
		else{j=-1;}
		if (j != -1) return i * sqrtn + j;
		D = D * base % C;
	}
	return -1;
}

void bsgs(int t,int g,int y){
		//cout<<BabyStep(y,g, t);
	int valor=pow(y,BabyStep(y,g, t-1));
	valor=valor%t;
	if(valor==t-1){cout<<"se cumple"<<endl;}
	else{cout<<"no se cumple"<<endl;}
}
//**********************************************************************************************************//
//***************************************************Silver-Pohlig-Hellman*******************************//
int Power(int a, int b, int c){
	int buf = 1;
	int jx = 0;
	while (jx < c){
		buf *= a;
		buf %= b;
		jx++;
	}
	return buf;
}


int xModP(int n, int b, int y, int p, int h){
	int x = 0;
	int buf;
	map<int, int> r;
	for (int ix = 0; ix < p; ix++){
		buf = Power(b, n, (n - 1) / p * ix);
		r[buf] = ix;
	}
	for (int ix = 0; ix < h; ix++){
		buf = Power(y, n, (n - 1) / pow(p, ix + 1));
		x += pow(p, ix)*r[buf];
		buf = -r[buf];
		while (buf < 0)
			buf += n - 1;
		buf = Power(b, n, pow(p, ix)*buf);
		y = y*buf;
		y %= n;
	}
	buf = pow(p, h);
	return x % buf;
}

int ext_euclid(int a, int b, int &x, int &y)
{
	int d;
	if (b == 0)
	{
		d = a;
		x = 1;
		y = 0;
		return d;
	}
	int q, r, x1 = 0, x2 = 1, y1 = 1, y2 = 0;
	while (b > 0)
	{
		q = a / b, r = a - q * b;
		x = x2 - q * x1; 
		y = y2 - q * y1;
		a = b;
		b = r;
		x2 = x1; 
		x1 = x; 
		y2 = y1; 
		y1 = y;
	}
	d = a; 
	x = x2;
	y = y2;
	return d;
}

int ChiResTheory(vector<int> a, map<int, int> nums, int n){
	int x=0, M = 1;
	vector<int> b;
	for (std::map<int,int>::iterator  it = nums.begin(); it != nums.end(); it++){
		b.push_back(pow(it->first, it->second));
	}
	for (int i = 0; i < b.size(); i++){M *= b[i];}
	int q, z;
	for (int i = 0; i < a.size(); i++){
		ext_euclid(M/b[i], b[i], q, z);
		x += a[i] * M / b[i] * q;
		if (x > n-1){x %= (n-1);}
		while (x < 0){x += n-1;}
	}
	return x;
}

void decomposition( map<int,int> &m,int n){
	for (int i = 2; n > 1; i++){
		while (n%i == 0){
			m[i]++;
			n /= i;
		}
	}
}



int SPH(int n, int b, int y){
	map<int, int> nums;
	decomposition(nums,n-1);
	vector<int> x;
	for (std::map<int,int>::iterator  it = nums.begin(); it != nums.end(); it++)
		x.push_back(xModP(n, b, y, it->first, it->second));
	
	return ChiResTheory(x, nums, n);
}

//*************************************************************************************************//
//*************************************************************************************************//
//*************************************************************************************************//

int main(){

// Generate α, a primitive root modulo a prime p, where p is an odd prime, using one of the algorithms discussed in class (assume that the prime factorization of p − 1 is known in advance - the simplest choice will be p = 2q + 1, where p and q are odd primes).
int p;
int alfa=primitiveroot(p);
int beta=rand()%(p-1);
// For p and α generated as above and an arbitrary β ∈ Z ∗ p , compute the discrete logarithm log α β, using one of the algorithms discussed in class (Skanks or Pollard). Use moderate-sized primes (e.g., p is on 32 bits).
bsgs(29,2,17);
//Implement the Silver-Pohlig-Hellman algorithm for computing discrete logarithms modulo a large prime p (e.g., p is on 1024 bits). Assume that p − 1 has only small prime divisors and that its prime factorization is known in advance.
cout<<endl;
cout<<SPH(251,71,210)<<endl;
	

}
