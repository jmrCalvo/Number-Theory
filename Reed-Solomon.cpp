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

NTL_CLIENT
using namespace std;

vector<string> leerfichero(const char* entrada){
		ifstream ficheroEntrada(entrada);
		vector <string> s1;
		string cadena;
		string total="";
		if (ficheroEntrada.is_open()) {
				 while (! ficheroEntrada.eof() ) {
						ficheroEntrada>>cadena;
						if(! ficheroEntrada.eof())
						if(total.size()==0){total=cadena;}
						else{
						total=total+" "+cadena;
						}
				}
				

			ficheroEntrada.close();}
		 else cout << "Fichero inexistente" << endl;
//total has the full cadena of data with spaces inclusive
	while(total.size()>=20){
		s1.push_back(total.substr(0,20));
		total=total.substr(20,total.size());
	}
	if(total.size()!=0){
	while(total.size()!=20){total=total+"0";}	
	s1.push_back(total);
	}
	
		 return s1;
}


vector<ZZ> multiplicar2by2(vector<ZZ> x,vector<ZZ>y, ZZ p){
		
		vector <ZZ> sol;		
		int tam=x.size()+y.size()-1;
		ZZ zero=(ZZ)0;		
		for(int i=0;i<tam;i++){
			sol.push_back(zero);
		}
		for(int i=0;i<x.size();i++){
			for(int j=0;j<y.size();j++){
				sol[i+j]=(sol[i+j]+MulMod(x[i],y[j],p))%p;		
			}		
		}
	return sol;
}

ZZ freecoeficiente(vector<ZZ>zvector1,vector<int>A,int P){
		ZZ p=(ZZ)P;
		ZZ sumatoria=(ZZ)0;
		for(int i=0;i<A.size();i++){
			ZZ multiplicatoria=(ZZ)1;
			ZZ arriba=(ZZ)1;
			ZZ abajo=(ZZ)1;
			ZZ  inside=(ZZ)0;
			for(int j=0;j<A.size();j++){
				if(j!=i){
					int t=j-i;
					if(t<0){t=t+P;}
					ZZ J=(ZZ)j;
					arriba=MulMod(arriba,J,p);
					ZZ T=(ZZ)t;
					abajo=MulMod(abajo,T,p);						
				}
				ZZ Down=InvMod(abajo,p);
				inside=MulMod(arriba, Down, p); 
			}
			sumatoria=sumatoria+MulMod(zvector1[A[i]], inside, p); 	
		}
		sumatoria=sumatoria%p;
		return sumatoria;
}




int main()
{
//For read 20 character and it storage in a vector
 vector<string> st=leerfichero("archivo.txt");

/*
for(int i=0;i<st	.size();i++){
cout<<st[i]<<endl;	
}
*/


//for storage in a vector the characters encrypted by the function ZZFromBytes
long int n=160;
ZZ p=(ZZ)161;
ZZ zero=(ZZ)0;

vector<ZZ> zvector;

for(int i=0;i<st.size();i++){
	ZZ z;
	unsigned char* uc = (unsigned char*)st[i].c_str();
 	ZZFromBytes(z,uc, n);
	zvector.push_back(z%p);
}

cout<<"******************************Represent the input**************************"<<endl;
for(int i=0;i<zvector.size();i++){
cout<<zvector[i]<<"	";
}
cout<<endl<<endl;
//choose the polinomial  which P(0)=0



//encode m as the vector y=(P(1),P(2),.....,P(n)) where n=k+2*s
int s=1;
vector<ZZ> y;
for(int j=0;j<zvector.size();j++){
	ZZ zacu=(ZZ)0;
	for(int i=1;i<zvector.size();i++){	
		ZZ zsol=(ZZ) zvector[i]*pow(j+2*s,zvector.size()-i);
		zacu=zacu+zsol;	
	}	
	y.push_back(zacu%p);
	zacu=(ZZ)0;
}


cout<<"***********Encode m as the vector y=(P(1),P(2),.....,P(n)) where n=k+2*s **************************"<<endl;
for(int i=0;i<y.size();i++){
cout<<y[i]<<"	";
}
cout<<endl<<endl;






//****************************************************************************************************************//
//						DECODING													//
//************************************************************************************************************//
ZZ z1=(ZZ)9;ZZ z2=(ZZ)0;ZZ z3=(ZZ)6;ZZ z4=(ZZ)5;ZZ z5=(ZZ)8;
vector<ZZ> zvector1; zvector1.push_back(z1);zvector1.push_back(z2);zvector1.push_back(z3);zvector1.push_back(z4);zvector1.push_back(z5);

//Generate A and compute the free coeficient 
vector <int>A;A.push_back(1);A.push_back(3);A.push_back(4);//A.push_back(5);
p=(ZZ)11;
int P=11;
ZZ fc=freecoeficiente(zvector1,A,P);
cout<<"**DECODE**"<<endl;
cout<<"The free coeficient is "<<fc<<endl;
cout<<"**************"<<endl;
cout<<endl<<endl;

ZZ one=(ZZ)1;
//if free coeficient is equal to 0 then ....
if(fc==zero){
	int Ichoose=1;
	vector<vector<ZZ> >ecuaciones;
	for(int i=0;i<A.size();i++){
		if(A[i]!=Ichoose){		
		vector<ZZ> aux;
		int valor=P-A[i];
		ZZ val=(ZZ)valor;
		aux.push_back(one);				
		aux.push_back(val);
		ecuaciones.push_back(aux);	
	}
}

if(ecuaciones.size()>=2){
	for(int j=1;j<ecuaciones.size();j++){
		ecuaciones[0]= multiplicar2by2(ecuaciones[0],ecuaciones[j],p);
	}
}
vector<ZZ>sol=ecuaciones[0];

cout<<"******THE SOLUTION OF THE MULTIPLICATION********"<<endl;
for(int i=0;i<sol.size();i++){
cout<<sol[i]<<"	";
}
cout<<endl<<endl;

}

cout<<"*******NOW I ADD 2 in the second position*********************"<<endl;
zvector[1]=zvector[1]+one+one;
cout<<"the free coeficient is "<<freecoeficiente(zvector,A,P)<<endl;



return 0;
}


