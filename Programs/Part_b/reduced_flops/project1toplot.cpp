#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <time.h>


/*
Some of the comments are missing. I will comment on more steps later. You need Gnuplot to create the plotfile. 
This program uses a Gnuplot- skript to plot. 


missing:

dynamical allocated storage (was too lazy yet)
time determination 
everything, which makes your algorhythm faster

enjoy reading ;)

Lukas

*/

using namespace std;

/*
we want to solve the following equation:
-(d^2/dx^2)u(x)=f(x)
with boundary conditions: u(0)=u(1)=0



*/

inline double u(double z){
	return(1-(1-exp(-10))*(z)-exp(-10*z));
}



int main(){
	int n;
	cout << "How many Grindpoint do you want to have?"<<endl;
	cin >> n;
	
	clock_t start, finish;  //  declare start and final time
        start = clock();
	double h;
        double *b = new double[n];
        double *c = new double[n];
        double *a = new double[n];
        double *x = new double[n];
        double *v = new double[n];
        double *btilde = new double[n];
	
	
	h=1.0/(n+1);



	for(int i=0;i<n;i++){ //filling up the vektors with the right number to solve the given linear sets of equation
	  	b[i]=2.0;
		 x[i]=(i+1)*h;
		btilde[i]=h*h*(100.0*exp(-10.0*x[i]));
	}
	// solving equations through kind of gaussian algorhithm, first elemination of the under-part of the thriangle (aim is a[i]=0 for i=1...n) , 
	// Of course, you have to change btilde as well. 
	// second, elimination of the upper part of the triangle (aim is c[i]=0 for i=0...n)
	


	//first
	for(int i=0;i<n;i++){
		b[i+1]=2-1/b[i];
		btilde[i+1]= btilde[i+1]+btilde[i]/b[i];
	}
	//second
	for(int i=n-1;i>0;i--){
		btilde[i-1]=btilde[i-1]+btilde[i]/b[i];
	}
	//normalization

	ofstream Zieldatei("Daten.txt");
	for(int i=0;i<n;i++){
		btilde[i]=btilde[i]/b[i];	// normalization of the Koeficient (be careful, btilde is from now an not the original btilde)
		Zieldatei << x[i]<<"  "<<btilde[i]<<"  "<<1-(1-exp(-10))*(h*(i+1))-exp(-10*h*(i+1))<<endl;
	}
	Zieldatei.close();
	finish = clock();
        cout<<double ( (finish - start)/(double)CLOCKS_PER_SEC )<<endl;
    system("start gnuplot plot1.txt");

	// Part c) of the Project 1
	double *epsilon = new double[n];
	double maximum=0;
	
	// calculate the relative errors and find the maximum of all the points
	for(int i=0;i<n;i++){
		epsilon[i]=log(abs((btilde[i]-u((i+1)*h))/u((i+1)*h)));
		if(epsilon[i]>maximum){
			maximum=epsilon[i];
		}
	}
	//write the maximum of the relative error in a text-file
	
	ofstream Zieldatei1("maximumrelativeerror_grid_n.txt", ios::app);
	Zieldatei1<<endl<<log(h)<<"  "<<log(maximum); //Gridpoints  "<<"epsilonmax"<<endl<<n<<"  "<<maximum;
	Zieldatei1.close();
	
	ofstream Zieldatei2("zeit.txt", ios::app);
	Zieldatei2<<endl<<n<<"  "<<double ( (finish - start)/(double)CLOCKS_PER_SEC ); //Gridpoints  "<<"epsilonmax"<<endl<<n<<"  "<<maximum;
	Zieldatei2.close();
	
	delete [] a, b, c, x, v, btilde,epsilon;
	}
