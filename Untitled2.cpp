#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<random>
using namespace std;

#define iter 1000;

bool is_solved(vector <int> &v){
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				return 0;
			}
		}
	}
	return 1;
}

int count_conflicts(vector <int> &v){
	int conflicts=0;
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				conflicts++;
			}
		}
	}
	return conflicts;	
}

int randval(int x){
//	if(x==0){
//		
//	}
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
//	cout<<"Value chosen="<<bestvalchosen<<" for loc="<<loc<<endl;
	return bestvalchosen;
}

void min_conflicts(vector <int> &v){
	int n = v.size(),num_conf;
	vector <int> conflicts;
	for(int i=0;i<n;i++){
		num_conf = 0;
		for(int j=0;j<n;j++){
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

//	if(conflicts.size()==0){
//		cout<<"Yaay"<<endl;
//		for(int i=0;i<n;i++){
//			cout<<v[i]<<" ";
//		}
//		cout<<endl;
//		return;
//	}
	
	// Print all conflicting colums
//	for(int i=0;i<conflicts.size();i++){
//		cout<<conflicts[i]<<" ";
//	}
//	cout<<endl;

	int rand_loc = conflicts[randval(conflicts.size())];
//	cout<<"column selected="<<rand_loc<<endl;
	//Pass by ref instead
	v[rand_loc] = findbestval(v,rand_loc);
}

void solve(int n){
	int i,count=iter;
	vector <int> v;
	for(i=0;i<n;i++){
		v.push_back(randval(n));
	}
	v[0]=3;v[1]=0;v[2]=3;v[3]=1;
//	cout<<"Initial State:";
//	for(i=0;i<n;i++){
//		cout<<v[i]<<" ";
//	}
//	cout<<endl;
//	cout<<"==============="<<endl;
	
	while(!is_solved(v) && count){
//		cout<<"For iteration "<<count<<endl;
		min_conflicts(v);
		if(is_solved(v)){
			cout<<"Solved!";
			break;
		}
		if(count%20==0){
			cout<<count<<": "<<count_conflicts(v)<<" "<<endl;
		}
		count--;
	}
}

int main(){
	int n;
	srand (time(NULL));
	n = 500;
	solve(n);
	return 0;
}	
