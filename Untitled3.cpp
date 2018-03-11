#include<iostream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<random>
using namespace std;
bool is_solved(vector <int> &v){
	int j,flag=0;
	for(int i=0;i<v.size();i++){
		for(j=i+1;j<v.size();j++){
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				flag = 1;
				i = j = v.size();
			}
		}
	}
	if(flag){
		return 0;
	}
	return 1;
}

int count_conflicts(vector <int> &v){
	int conflicts=0,j;
	for(int i=0;i<v.size();i++){
		for(j=0;j<v.size();j++){
			if(i==j){
				continue;
			}
			else if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				conflicts++;
			}
		}
	}
	return conflicts;	
}

int randval(int x){
	return rand()%x;
}

int findbestval(vector <int> &v, int loc){
	int i,n = v.size();
	vector <int> v1 = v;
	vector <int> all_conflicts;
	for(i=0;i<n;i++){
		v1[loc] = i;
		all_conflicts.push_back(count_conflicts(v1));
	}
	int minval = all_conflicts[0];
	for(i=1;i<n;i++){
		if(minval>all_conflicts[i]){
			minval = all_conflicts[i];
		}
	}
	vector <int> choosefromthesevals;
	for(i=0;i<n;i++){
		if(all_conflicts[i]==minval){
			choosefromthesevals.push_back(i);
		}
	}
	int bestvalchosen = choosefromthesevals[randval(choosefromthesevals.size())];
	return bestvalchosen;
}

void min_conflicts(vector <int> &v){
	int n = v.size(),num_conf,j;
	vector <int> conflicts;
	for(int i=0;i<n;i++){
		num_conf = 0;
		for(j=0;j<n;j++){
			if(i==j){
				continue;
			}
			else{
				if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
					num_conf++;
					break;
				}
			}
		}
		if(num_conf>0){
			conflicts.push_back(i);
		}
	}
	int rand_loc = conflicts[randval(conflicts.size())];
	v[rand_loc] = findbestval(v,rand_loc);
}

vector <int> generate_board(int n){
	vector <int> v;
	int i,j;
	for(i=0;i<n;i++){
		vector <int> best;
		v.push_back(randval(n));
		j = 50;
		while(!is_solved(v) && j--){
			v[v.size()-1] = randval(n);
			best.push_back(count_conflicts(v));
		}
		//v[v.size()-1] = *min_element(best.begin(),best.end());
	}
	cout<<"Done"<<endl;
	return v;
}
/*
vector <int> generate_board(int n){
	vector <int> v;
	int i,j;
	for(i=0;i<n/2;i++){
		v.push_back(randval(n));
		j = n;
		while(!is_solved(v) && j--){
			min_conflicts(v);
		}
	}
	for(i=n/2;i<n;i++){
		v.push_back(randval(n));
	}
	cout<<"Done"<<endl;
	return v;
}*/

int solve(int n){
	int i,count=0;
	const int numiter = 1000;
	vector <int> v = generate_board(n);

	while(!is_solved(v)&&count<numiter){
		min_conflicts(v);
		if(is_solved(v)){
			break;
		}
		count++;
	}
	return count;
}

int main(){
	int i, n=300, m=3;
	srand(time(NULL));
	for(i=4;i<n;i++){
		clock_t startTime = clock();
		solve(i);
		clock_t endTime = clock();
	    clock_t clockTicksTaken = endTime - startTime;
	    double timeInSeconds = clockTicksTaken/(double) CLOCKS_PER_SEC;
	    cout<<i<<" queens in "<<timeInSeconds<<endl;
	}
	return 0;
}	
