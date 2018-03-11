//Explicit solutions
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<random>
using namespace std;

bool is_solved(vector <int> &v){
	long long count = 0;
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			count++;
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				return 0;
			}
		}
	}
	cout<<count<<endl;
	return 1;
}

void explicitsol(int n){
	vector <int> v;
	if((n%6==2)||(n%6==3)){
		vector <int> v(int(n/2),0), a(int(n+1/2),0);
		int i;
		for(i=0;i<int(n/2);i++){
			v[i] = 2*i+2;
			a[i] = 2*i+1;
		}
		if(n%2){
			a[int(n/2)]=2*i+1;
		}
		if(n%6==2){
			swap(a[0],a[1]);
			a.erase(a.begin()+2);
			a.push_back(5);
		}
		else if(n%6==3){
			v.erase(v.begin());
			v.push_back(2);
			a.erase(a.begin());
			a.erase(a.begin());
			a.push_back(1);
			a.push_back(3);
		}
		v.insert(v.end(),a.begin(),a.end());
	}
	else{
		vector <int> v(n,0);
		int i;
		if(n%2==0){
			if(n%6!=2){
				for(i=0;i<int(n/2);i++){
					v[i] = 2*i+2;
					v[int(n/2)+i] = 2*i+1;
				}
			}
			else{
				for(i=0;i<int(n/2);i++){
					v[i] = 1+((2*i+int(n/2)-1)%n);
					v[n-i] = n-(2*i+int(n/2)-1)%n;
				}
			}
		}
		else{
			for(i=0;i<int(n/2);i++){
				v[i] = 2*i+2;
				v[int(n/2)+i] = 2*i+1;
			}
			v[n-1] = n;
		}
	}
	cout<<is_solved(v);
}

int main(){
	long long n=1000, i=4;
	srand (time(NULL));
	//cin>>n;
	explicitsol(n);
	return 0;
}	
