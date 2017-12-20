//Exercise 4 Exam 3
//Solving system of equations
//Collaboration with Nick Rossiter and Gaussian elimination code from Martin Thoma website.

#include <iostream> 
#include <fstream> 
#include <string>
#include <vector> 
#include <cmath>
#include <vector>
#include <sstream> 


using namespace std;

vector<double> gauss(vector <vector<double>> A);

int main (int argc, char*argv[]) {

ifstream matrixfile; 
matrixfile.open(argv[1]);
ifstream vectorfile; 
vectorfile.open(argv[2]);

vector <vector <double>> matrixA;
vector <double> matrixB;
string line;
while(getline(matrixfile, line)){ 
//Put into a string-stream called linedata
            istringstream linedata(line); 

            vector<double> row; 
            string num;    

//Get all numbers in a line
            while(!linedata.eof()) { 
                linedata >> num; 
// Convert to integer and store in vector 
                if (!num.empty()){ 
                    row.push_back(stoi(num));                   
                }               
            }
// Push row data in vector
                matrixA.push_back(row);     
    
}
double x;
while (vectorfile >>x) {
    matrixB.push_back(x);
}
for (int i=0; i<matrixB.size();i++) {
    matrixA[i].push_back(matrixB[i]);
}

vector <double> sol = gauss(matrixA);

ofstream output_file("vector output.dat");

for (int i=0; i<sol.size(); i++) {
    output_file << sol[i] << endl; 
}
cout << "The size of matrix A is " << matrixA.size() << "x"<< matrixA.size() << endl;

matrixfile.close();
vectorfile.close();

return 0;
}
vector<double> gauss(vector< vector<double> > A) {
    int n = A.size();
    int count = 0;
    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            count +=2;
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                    count +=2;
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        count ++;
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
            count +=2; 
        }
    }
    cout << "The number of operations used is " << count << endl;
    return x;
}
    

