#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;


int main() {
    //Ask for number of grid points
	int n;
    cout << "How many grid points do you want to have?"<<endl;
    cin >> n;
    clock_t start, finish;  //  declare start and final time
    start = clock();		//start clock;
    /*
    Initialize vectors and matrix according to the project
    */
    double h=1.0/(n+1);//steplength h
    double *btilde = new double[n];//vector on the "right side"
    double *v = new double[n];//solution vector
    double **A = new double*[n];//Matrix A
    double *x = new double[n];
    for(int i=0;i<n;i++){//initialize vectors
        A[i] = new double[n];
        x[i]=h*(i+1);
        btilde[i]=h*h*(100.0*exp(-10.0*x[i]));
        //cout << btilde[i] << endl;
        v[i]=0;
        for(int j=0;j<n;j++){
            A[i][j]=0;
            if(i==j){A[i][j]=2;}
            if(i==j+1){A[i][j]=-1;}
            if(i==j-1){A[i][j]=-1;}
        }
    }
    /*
    Forward substitution
    */
    double factor;
    for(int outerLine=0 ; outerLine<n ; outerLine++){
        for(int innerLine=outerLine+1; innerLine<n;innerLine++){
            //Column [o] of every line [o+i] should be equal to zero by adding (factor*Matrix[o][o])
            factor=-A[innerLine][outerLine]/A[outerLine][outerLine];
            for(int column=outerLine;column<n;column++){
                A[innerLine][column]+=factor*A[outerLine][column];
            }
            btilde[innerLine]+=factor*btilde[outerLine];
        }
    }
    /*
    Backward substitution
    */
    for(int outerLine=n-1; outerLine>=0; outerLine--){
        for(int innerLine=outerLine-1; innerLine>=0; innerLine--){
            btilde[innerLine]-=btilde[outerLine]*(A[innerLine][outerLine]/A[outerLine][outerLine]);
        }
    }
		
	/*
	Normalization and output
	*/
	ofstream Ziel("output_gauss.txt");
    for(int i=0;i<n;i++){
        btilde[i]=(btilde[i]/A[i][i]);
        Ziel << btilde[i] << endl;
    }
    Ziel.close();
    delete [] v, A, x, btilde;
    finish = clock();
    cout<<double ( (finish - start)/(double)CLOCKS_PER_SEC )<<endl;
    return(0);
}
