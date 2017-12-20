//Exercise 1 Exam 3 
//Chess board problem, knight
//Collaboration with Nick Rossiter 

#include <iostream> 
#include <iomanip>
#include <random>
#include <functional>

using namespace std; 

int main (int argc, char*argv[]){

int N = stoi(argv[1]);
int trials = stoi(argv[2]);

if (N<3){
    cout << "The size of the chess board is too small." << endl;
    return 0;
    }
int x = 1;
int y = 1;

random_device rd;
int seed_value = rd();

mt19937 generator(seed_value);
	uniform_int_distribution<> distribution(1,8);
	auto draw = bind(distribution, generator);

random_device rd_2;
int seed_value_2 = rd_2();

mt19937 generator_2(seed_value_2);
	bernoulli_distribution distribution_2(.5);
	auto draw_2 = bind(distribution_2, generator_2);

double total_moves = 0.0;

for (int i=1; i<=trials; i++) {

double moves = 0.0;
int drawing = draw_2();

if (drawing==0) {
    x +=2;
    y += 1;
    moves ++;
} else {
    x +=1;
    y+=2;
    moves ++;
}
while (!(x==1 && y==1)) {
    int draww = draw();
    switch (draww) {
        case 1: 
        if (x<N-1 && y<N) {
            x+=2;
            y+=1;
            moves ++;
        }
        break;
        case 2: 
        if (x<N-1 && y>1) {
            x+=2;
            y -=1;
            moves ++;
        }
        break;
        case 3:
        if (x>2 && y<N) {
            x -=2;
            y +=1;
            moves ++;
        }
        break;
        case 4:
        if (x>2 && y>1){
            x-=2;
            y -=1;
            moves ++;
        }
        break;
        case 5:
        if (x<N && y<N-1) {
            x+=1;
            y+=2;
            moves ++;
        }
        break;
        case 6:
        if (x>1 && y<N-1) {
            x -=1;
            y +=2;
            moves ++;
        }
        break;
        case 7:
        if (x<N && y>2) {
            x+=1;
            y -=2;
            moves ++;
        }
        break;
        case 8:
        if (x>1 && y>2) {
            x -=1;
            y -=2;
            moves ++;
        }
        break;
    }
}
total_moves += moves;
}
cout << "The average total number of moves needed is " << total_moves/trials << endl;
return 0;
}