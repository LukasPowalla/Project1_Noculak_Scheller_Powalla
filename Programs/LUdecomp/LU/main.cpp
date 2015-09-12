#include <iostream>
#include <armadillo>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace arma;
int main()
{
    int n;
    cout << "How many Grindpoints do you want to have?"<<endl;
    cin >> n;
    clock_t start, finish;  //  declare start and final time
    start = clock();
    double h=1.0/(n+1);//steplength h
    vec btilde(n);//vector on the "right side"
    vec v(n);//solution vector
    mat A(n,n);//Matrix A
    vec x(n);
    for(int i=0;i<n;i++){//initialize vectors and matrix
        x(i)=h*(i+1);
        btilde(i)=h*h*(100.0*exp(-10.0*x[i]));
        v[i]=0;
        for(int j=0;j<n;j++){
            A(i,j)=0;
            if(i==j){A(i,j)=2;}
            if(i==j+1){A(i,j)=-1;}
            if(i==j-1){A(i,j)=-1;}
        }
    }
    mat L, U, P;
    lu(L, U, P, A);
    vec y(n);
    y=solve(trimatl(L), btilde);
    v=solve(trimatu(U), y);
    finish = clock();
    ofstream Ziel("output_lu.txt");
    Ziel << v << endl;
    Ziel.close();

    ofstream Ziel2("zeitlu.txt",ios::app);
    Ziel2 << n<<"  "<<double ( (finish - start)/(double)CLOCKS_PER_SEC ) << endl;
    Ziel2.close();

    cout<<double ( (finish - start)/(double)CLOCKS_PER_SEC )<<endl;
    return 0;
}

