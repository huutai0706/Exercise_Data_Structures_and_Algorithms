#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <sstream>
#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> convertMatrix(const string& filename) {
    ifstream inFile(filename);
    vector<vector<int>> adjList;
    if (!inFile) return adjList;

    int n;
    inFile >> n; 
    adjList.resize(n);
    inFile.ignore(); 

    for (int i = 0; i < n; ++i) {
        string line;
        getline(inFile, line);
        istringstream iss(line);
        int val;
        int j = 0;
        while (iss >> val) {
            if (val == 1) {
                adjList[i].push_back(j);
            }
            j++;
        }
    }
    inFile.close();
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream inFile(filename);
    int n;
    inFile >> n;
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    string line;
    inFile.ignore(); 
    for (int i = 0; i < n; ++i) {
        getline(inFile, line);
        if (line.empty() || line == "0") continue;
        int neighbor;
        istringstream iss(line);
        while (iss >> neighbor) {
            int j = neighbor - 1; 
            if (adjMatrix[i][j] == 0) { 
                adjMatrix[i][j] = 1;
                adjMatrix[j][i] = 1; 
            }
        }
    }
    inFile.close();
    return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                return true; 
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int edges = 0;
    int n = adjMatrix.size();
    bool directed = isDirected(adjMatrix);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] > 0) {
                edges++;
            }
        }
    }
    return directed ? edges : edges / 2;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> isolated;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        bool hasEdge = false;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] > 0 || adjMatrix[j][i] > 0) {
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            isolated.push_back(i);
        }
    }
    return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) return false;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                if (adjMatrix[i][j] != 0) return false; 
            } else {
                if (adjMatrix[i][j] != 1) return false; 
            }
        }
    }
    return true;
}


bool isBipartite(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) return false; 
    int n = adjMatrix.size();
    vector<int> color(n, -1); 
    queue<int> q;
    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue; 
        color[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] > 0) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u]; 
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    if (!isBipartite(adjMatrix)) return false; 
    int n = adjMatrix.size();
    vector<int> color(n, -1); 
    queue<int> q;
    color[0] = 0;
    q.push(0);
    vector<int> setA, setB;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (color[u] == 0) setA.push_back(u);
        else setB.push_back(u);
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            }
        }
    }

    for (int u : setA) {
        for (int v : setB) {
            if (adjMatrix[u][v] != 1) return false;
        }
    }
    return !setA.empty() && !setB.empty();
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirected(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] > 0 || adjMatrix[j][i] > 0) {
                undirected[i][j] = undirected[j][i] = 1;
            }
        }
    }
    return undirected;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) return {}; 
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                complement[i][j] = adjMatrix[i][j] == 0 ? 1 : 0;
            }
        }
    }
    return complement;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) return {};
    int n = adjMatrix.size();
    vector<vector<int>> adj = adjMatrix; 
    vector<int> degree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            degree[i] += adjMatrix[i][j];
        }
    }

    for (int d : degree) {
        if (d % 2 != 0) return {};
    }
    vector<int> cycle;
    stack<int> currPath;
    currPath.push(0); 
    int curr = 0;
    while (!currPath.empty()) {
        if (degree[curr] > 0) {
            currPath.push(curr);
            int next = -1;
            for (int v = 0; v < n; ++v) {
                if (adj[curr][v] > 0) {
                    next = v;
                    break;
                }
            }
            adj[curr][next]--;
            adj[next][curr]--;
            degree[curr]--;
            degree[next]--;
            curr = next;
        } else {
            cycle.push_back(curr);
            curr = currPath.top();
            currPath.pop();
        }
    }
    return cycle;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    if (isDirected(adjMatrix)) return {}; 
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && !visited[v]) {
                tree[u][v] = tree[v][u] = 1;
                visited[v] = true;
                s.push(v);
            }
        }
    }
    return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    if (isDirected(adjMatrix)) return {}; 
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && !visited[v]) {
                tree[u][v] = tree[v][u] = 1;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return tree;
}


bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (curr == v) return true;
        for (int next = 0; next < n; ++next) {
            if (adjMatrix[curr][next] > 0 && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && !visited[v]) {
                int weight = adjMatrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    vector<int> path;
    if (dist[end] == INT_MAX) return path; 
    for (int v = end; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    dist[start] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] > 0 && dist[u] != INT_MAX) {
                    int weight = adjMatrix[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                    }
                }
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && dist[u] != INT_MAX) {
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    return {};
                }
            }
        }
    }
    vector<int> path;
    if (dist[end] == INT_MAX) return path; 
    for (int v = end; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

