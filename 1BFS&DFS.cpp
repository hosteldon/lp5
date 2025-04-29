#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>
using namespace std;

const int MAX=100;
vector<int> graph[MAX] ;
bool visited[MAX]={false};

void dfs(int s){
	stack<int> st;
	st.push(s);

	while(!st.empty()){
		int curr = st.top();
		st.pop();

		if (!visited[curr]) {
			visited[curr]=true;
			cout<<curr <<" ";
			#pragma omp parallel for
			for ( int i = 0; i <graph[curr].size(); i++) {
				if (!visited[graph[curr][i]]) {
					st.push(graph[curr][i]);
				}
			}
		}
	}
}

void bfs(int s){
	queue<int> q;
	q.push(s);

	while(!q.empty()){
		int curr = q.front();
		q.pop();

		if (!visited[curr]) {
			visited[curr]=true;
			cout<<curr<<" ";
			#pragma omp parallel for
			for ( int i= 0; i < graph[curr].size(); i++) {
				if (!visited[graph[curr][i]]) {
					q.push(graph[curr][i]);
				}
			}
		}

	}
}


int main(){
	cout << "enter n";
	int n;
	cin>> n;
	cout << "enter e";
	int e;
	cin>>e;
	cout << "enter s";
	int s;
	cin>>s;

	cout<<"enter edges : ";
	for (  int i = 0; i < e; i++) {
		int v;
		cout <<"enter v :";
		cin >> v;
		int u;
		cout <<"enter u :";
		cin >> u;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	cout << "visit order : ";
	dfs(s);
	for (int i = 0; i < sizeof(visited); i++) {
	        visited[i] = false;
	}

	cout << "\nBFS Visit Order: ";
	bfs(s);


}
