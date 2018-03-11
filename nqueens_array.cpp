#include<iostream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<random>
#include<numeric>
using namespace std;

const int MAX_ITER = 2000;

// Algorithm to generate greedy board
vector<int> generate_greedy_board(int n){
	vector<int> v;
	return v;
}

void print_vector(vector <int> &v){
	for(int i=0; i<v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

int hits_for_board(int board[], int n, int col, int col_val){
	int total=0;
	for (int j=0; j<n; j++){
		if (j==col) {continue;}
		if ((board[j]==col_val) || abs(j-col)==abs(board[j]-col_val)){
			total++;
		} 
	}
	return total;
}

void find_conflicts(int conflicts[], int board[], int n){
	for(int col=0; col<n; col++){
		int col_val = board[col];
		int total = hits_for_board(board, n, col, col_val);
		conflicts[col] = total;
	}
}

int get_random_confl_col(int board[], int conflicts[], int n){
	int col=0;

	bool flag=false;
	while (!flag){
		col = rand()%n;
		if (conflicts[col]!=0){flag=true;}
	}
	return col;
}

int get_best_row_val(int col, int board[], int n){
	int i;
	int best_val;
	int all_conflicts[n];
	
	// Count conflicts for all values for the column
	for (i=0; i<n; i++){
		board[col]=i;
		all_conflicts[i] = hits_for_board(board, n, col, i);
	}
	
	// Linear
	int minval = all_conflicts[0];
	for(i=1;i<n;i++){
		if(minval>all_conflicts[i]){
			minval = all_conflicts[i];
		}
	}
	
	// Linear
	vector <int> choosefromthesevals;
	for(i=0;i<n;i++){
		if(all_conflicts[i]==minval){
			choosefromthesevals.push_back(i);
		}
	}
	
	best_val = choosefromthesevals[rand()%(choosefromthesevals.size())];
	return best_val;
}

int min_conflicts(int board[], int n){
	int i;
	for(i=0;i<MAX_ITER;i++){
		int conflicts[n];
		find_conflicts(conflicts, board, n);
		int sum = 0;
		for (int j=0; j<n; j++)
			sum += conflicts[j];
		if (sum==0){
			return i;
		}
		int col = get_random_confl_col(board, conflicts, n);
		int board_cp[n];
		memcpy(board_cp, board, n*sizeof(*board));
		board[col] = get_best_row_val(col, board_cp, n);
	}
	
	return i;
}

int solve(int n_queens){
	int board[n_queens];
	for (int i=0; i<n_queens;i++){
		board[i]=rand()%n_queens;
	}
	
//	print_vector(v); //implement to see the generated board
	clock_t startTime = clock();
	int steps_taken = min_conflicts(board, n_queens);
	clock_t clockTicksTaken = clock() - startTime;
	double timeInSeconds = clockTicksTaken/(double) CLOCKS_PER_SEC;
	
	if (steps_taken < MAX_ITER){
	    cout<<n_queens<<","<<timeInSeconds<<","<<steps_taken<<endl;
	} else {
		cout<<n_queens<<","<<timeInSeconds<<","<<-1<<endl;
	}
}

int main() {
	srand(time(NULL));
	
	int max_n=3000;
	for (int i=50; i<max_n;i+=50){
		solve(i);
	}
	
	return 0;
}
