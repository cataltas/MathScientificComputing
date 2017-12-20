//Exercise 1 Exam 3 
//Chess board problem, king
//Collaboration with Nick Rossiter 

#include <iostream> 
#include <iomanip>
#include <random>
#include <functional>
#include <vector>

using namespace std; 

int main (int argc, char*argv[]){

int N = stoi(argv[1]);
int trials = stoi(argv[2]);

if (N<3){
    cout << "The size of the chess board is too small." << endl;
    return 0;
    }

random_device rd;
int seed_value = rd();

mt19937 generator(seed_value);
	uniform_int_distribution<> distribution(1,8);
	auto draw = bind(distribution, generator);

double total_moves = 0;

for (int i=1; i<=trials; i++) {
int x = N-1;
int y = 0;
double moves = 0.0;
int square = 1; 

vector <vector<int>> location(N,vector<int>(N,0)); 
location [N-1][0] = 1;


while (square < pow(N,2)) {
    int draww = draw();
    switch (draww) {
        case 1: 
        if (x<N-1 && y<N-1) {
            x+=1;
            y+=1;
            moves ++;
        }
        break;
        case 2: 
        if (x<N-1) {
            x+=1;
            moves ++;
        }
        break;
        case 3:
        if (x<N-1 && y>0) {
            x +=1;
            y -=1;
            moves ++;
        }
        break;
        case 4:
        if (y>0){
            y -=1;
            moves ++;
        }
        break;
        case 5:
        if (x>0 && y>0) {
            x-=1;
            y-=1;
            moves ++;
        }
        break;
        case 6:
        if (x>0) {
            x -=1;
            moves ++;
        }
        break;
        case 7:
        if (x>0 && y<N-1) {
            x-=1;
            y +=1;
            moves ++;
        }
        break;
        case 8:
        if (y<N-1) {
            y +=1;
            moves ++;
        }
        break;
    }
if (location[x][y] == 0){
    location[x][y] ++;
    square ++;
    }

}
total_moves += moves;
}
cout << "The average total number of moves needed is " << total_moves/trials << endl;
return 0;
}