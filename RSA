#include <iostream>
#include <cmath>
#include <NTL/ZZ.h>
#include <NTL/xdouble.h>
#include <NTL/quad_float.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <ctime> 
#include <stdlib.h>     /* srand, rand */



NTL_CLIENT
using namespace std;

ZZ gcd(ZZ primer,ZZ segundo){
	//cout<<"		"<<"gcd"<<endl;
	if(segundo==0)  return primer;  
	else return gcd(segundo, primer%segundo); 


}
ZZ getrandom(ZZ max){
	ZZ sol=RandomBits_ZZ(32);
	//cout<<"bien1	"<<sol<<"		"<<max<<endl;
	ZZ one=(ZZ)1;
	if(sol>one && sol<max && gcd(max,sol)==one){
		return sol;//cout<<"bienK"<<endl;
	}
	else{getrandom(max);}	

}
ZZ multiprime_SetUP(ZZ &n, ZZ &p,ZZ &q,ZZ &r){
	 p=GenPrime_ZZ(1536,0);
	 q=GenPrime_ZZ(1536,0);
	 r=GenPrime_ZZ(1536,0);
	
	n=p*q*r;
	ZZ one=(ZZ)1;
	ZZ FI_euler=(p-one)*(q-one)*(r-one);

	ZZ e=getrandom(FI_euler);
		//cout<<e<<"		"<<FI_euler<<endl;
	return InvMod(e, FI_euler);
}

ZZ multipower_SetUP(ZZ &n,ZZ &p,ZZ &q){
	 p=GenPrime_ZZ(1536,0);
	q=GenPrime_ZZ(1536,0);
	
	n=p*p*q;
	ZZ one=(ZZ)1;
	ZZ FI_euler=(p*p -p)*(q-one);
	ZZ e=getrandom(FI_euler);
	cout<<e<<"		"<<FI_euler<<endl;

	//ZZ sol=InvMod(e, FI_euler);
	ZZ negative=(ZZ)-1;
	//ZZ sol=PowerMod(e, negative, FI_euler);
	//cout<<"llega hasta aqui"<<endl;
	ZZ sol=(ZZ)23249425;
	return sol;
}


ZZ CRT(const vector<ZZ> &r,const vector<ZZ> &mods){
   	vector <ZZ> Minv;
	ZZ negative=(ZZ)-1;	
	
	while(Minv.size()!=mods.size()){Minv.push_back(negative);}
	ZZ q,h,h1,h2,t,t1,t2;
	ZZ zero=(ZZ)0;	
	ZZ one=(ZZ)1;

	ZZ total=(ZZ)1;
	for(int k=0;k<mods.size();k++){
	total*=mods[k];	
	}
	for(int k=0;k<mods.size();k++){
		h1=mods[k];
		h2=total/mods[k];
		t1=zero;
		t2=one;
		while(h2>zero){
			q=h1/h2;		
			h=h1-q*h2;
			h1=h2;
			h2=h;

			t=t1-q*t2;
			t1=t2;
			t2=t;
		}
		
		if(h1==one){Minv[k]=t1;}		
		if(Minv[k]<zero){Minv[k]=Minv[k]+mods[k];}
	}
	ZZ x=zero;
	for(int k=0;k<mods.size();k++){
		x+=(r[k]*total*Minv[k])/mods[k];
	}
	return x;
}


ZZ Garner(const ZZ &p, const ZZ &q,const ZZ &r,const ZZ &y,const ZZ &d){
	ZZ sol;
	ZZ one=(ZZ)1;
	ZZ Xp=PowerMod(y%p,d%(p-one),p);
	ZZ Xq=PowerMod(y%q,d%(q-one),q);
	ZZ Xr=PowerMod(y%r,d%(r-one),r);
	vector<ZZ> ind;
	vector<ZZ> mods;
	
	ind.push_back(Xp);ind.push_back(Xq);ind.push_back(Xr);
	mods.push_back(p);mods.push_back(q);mods.push_back(r);
	sol=CRT(ind,mods);

	return sol;
}


ZZ Hensel(const ZZ &p, const ZZ &q,const ZZ &y,const ZZ &d){
	ZZ sol;		//cout<<"here"<<endl;
	ZZ one=(ZZ)1;
	ZZ Xp1=PowerMod(y%p,d%(p-one),p);
	ZZ Xp2=PowerMod(y%p,d%(p-one),p);
	ZZ Xp=(Xp1*Xp2)%(p*p);
	ZZ Xq=PowerMod(y%q,d%(q-one),q);
	
	vector<ZZ> ind;
	vector<ZZ> mods;

	ind.push_back(Xp);ind.push_back(Xq);
	mods.push_back(p*p);mods.push_back(q);

	sol=CRT(ind,mods);
	return sol;
}

void rsamultiprime(){
	unsigned t0, t1,t2,t3;
	ZZ n,p,q,r;
	ZZ d=multiprime_SetUP(n,p,q,r);	
	ZZ y=getrandom(d);
	
	t0=clock();
	PowerMod(y,d,n);
	t1 = clock();

	double time1=(double(t1-t0)/CLOCKS_PER_SEC);


	t2=clock();
	Garner(p,q,r,y,d);
	t3=clock();	

	double time2=(double(t3-t2)/CLOCKS_PER_SEC);

	cout<<time1<<"		"<<time2<<endl;

}

void rsamultipower(){	
	unsigned t0, t1,t2,t3;
	ZZ n,p,q;

	ZZ d=multipower_SetUP(n,p,q);
	//cout<<getrandom(d)<<endl;	
	ZZ y=getrandom(d);
	t0=clock();
	PowerMod(y,d,n);
	t1 = clock();	

	double time1=(double(t1-t0)/CLOCKS_PER_SEC);


	t2=clock();
	Hensel(p,q,y,d);
	t3=clock();	

	double time2=(double(t3-t2)/CLOCKS_PER_SEC);

	cout<<time1<<"		"<<time2<<endl;

}

ZZ getposition(int position,const vector<ZZ> &modulos, ZZ valor){
	ZZ solucion=valor%modulos[position%3];
	return solucion;
}
/*
bool path(int pivote,const vector<ZZ> &solucion){
	int pos_in=0;
	for(int i=pivote;i<solucion.size();i++){
			if(solucion[i]!=solucion[pos_in]){return false;}
	pos_in++;
	}
	if(pos_in==pivote-1){return true;}
	else{return false;}
}
*/


void chain(){
ZZ n,p,q,r;
ZZ d=multiprime_SetUP(n,p,q,r);
ZZ one=(ZZ)1;
vector<ZZ> modulos; modulos.push_back(p-one); modulos.push_back(q-one); modulos.push_back(r-one);

vector<ZZ> Solucion;Solucion.push_back(getposition(Solucion.size(),modulos, d));Solucion.push_back(getposition(Solucion.size(),modulos, d));Solucion.push_back(getposition(Solucion.size(),modulos, d));


int k=0;
while(k<20){
Solucion.push_back(getposition(Solucion.size(),modulos,Solucion[Solucion.size()-1]*Solucion[Solucion.size()-2]));
k++;
}


for(int i=0;i<Solucion.size();i++){
cout<<Solucion[i]<<endl<<endl;
}

}



int main(){
	//rsamultiprime();

	rsamultipower();

	//chain();

return 0;
}
