#include <iostream>
#include <vector>
#include <stack>
#include <omp.h> // Include OpenMP
using namespace std;

const int MAX = 100;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node) {
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        int curr_node;

        #pragma omp critical
        {
            curr_node = s.top();
            s.pop();
        }

        if (!visited[curr_node]) {
            #pragma omp critical
            {
                visited[curr_node] = true;
                cout << curr_node << " ";
            }

            int neighbors = graph[curr_node].size();

            // Parallelize pushing neighbors
            #pragma omp parallel for
            for (int i = 0; i < neighbors; i++) {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node]) {
                    #pragma omp critical
                    {
                        s.push(adj_node);
                    }
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter number of nodes, edges and starting node: ";
    cin >> n >> m >> start_node;

    cout << "Enter " << m << " edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "\nNodes visited in DFS order starting from " << start_node << ":" << endl;
    
    #pragma omp parallel
    {
        #pragma omp single
        dfs(start_node);
    }

    cout << endl;
    return 0;
}
