#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

bool is_solved(vector <int> &v){
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if(v[i] == v[j]){
				return 0;
			}
			else if(v[i]-v[j] == i-j){
				return 0;
			}
			else if(v[i]-v[j] == j-i){
				return 0;
			}
		}
	}
	return 1;
}

int num_conflicts(vector <int> v){
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

int count_conflicts(vector <int> v){
	int conflicts=0;
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				conflicts++;
				break;
			}
		}
	}
	return conflicts;	
}


int findbestval(vector <int> v, int x){
	int n = x;
	vector <int> tmp(v.size(),0);
	for(int i=0;i<v.size();i++){
		tmp[i] = v[i];
	}
	for(int j=0;j<v.size();j++){
		tmp[x] = j;
		if(num_conflicts(tmp)<num_conflicts(v)){
			v = tmp;
			n = j;
		}
	}
	return n;
}

void min_conflicts(vector <int> &v){
	vector <int> conflicts(v.size(),0);
	int min_val = v.size()+2, min_loc = 0;
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size();j++){
			if(i==j){
				continue;
			}
			else{
				if(v[i] == v[j]){
					conflicts[i]++;
				}
				else if(v[i]-v[j] == i-j){
					conflicts[i]++;
				}
				else if(v[i]-v[j] == j-i){
					conflicts[i]++;
				}
			}
		}
		if((min_val>=conflicts[i])&&(conflicts[i]>0)){
			srand (time(NULL));
			if(rand()%(v.size()-3)==i){
				min_val = conflicts[i];
				min_loc = i;			
			}
		}
	}
	vector <int> t(v.size());
	for(int i=0;i<v.size();i++){
		t[i] = v[i];
	}
	t[min_loc] = findbestval(v,min_loc);
	if(count_conflicts(v) > count_conflicts(t)){
		v = t;
	}
}

void solve(int n){
	int i,count=n*n;
	srand (time(NULL));
	vector <int> v;
	for(i=0;i<n;i++){
		v.push_back(rand()%n);
	}
	while(!is_solved(v) && count){
		min_conflicts(v);
		if(count%100 == 0){
			cout<<count_conflicts(v)<<" ";	
		}
		count--;
	}
	if(is_solved(v)){
		for(i=0;i<n;i++){
			cout<<v[i]<<" ";
		}
	}
}

int main(){
	int n;
	cin>>n;
	solve(n);
	return 0;
}	
