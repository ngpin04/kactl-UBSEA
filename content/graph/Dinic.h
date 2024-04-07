/**
 * Tested with https://www.acmicpc.net/problem/1210
 * 
 */
#pragma once

struct Edge {
    int v, pos; long long flow, cap;

    Edge(){}
    Edge(int _v, int _pos, long long _flow, long long _cap) {
        v = _v;
        pos = _pos;
        flow = _flow;
        cap = _cap;
    }

    long long rem() {
        return cap - flow;
    }
};

struct Dinic {
	int n;
	vector <vector <Edge>> adj;
	vector <int> ptr, lev;
 
	Dinic (int _n) {
		n = _n;
		adj.assign(n + 5, vector <Edge> (0));
		lev = ptr = vector <int>(n + 5, 0);
		lev.assign(n + 5, 0);
	}
 
	void addEdge(int u, int v, long long cap, long long rcap = 0) {
		Edge a = Edge(v, adj[v].size(), 0, cap);
		Edge b = Edge(u, adj[u].size(), 0, rcap);
		adj[u].push_back(a);
		adj[v].push_back(b);
	}
 
	bool bfs(int s, int t) {
		ptr = lev = vector <int> (n + 5, 0);
 
		lev[s] = 1;
 
		queue <int> q({s});
 
		while (q.size()) {
			int u = q.front();
			q.pop();
 
			for (Edge e : adj[u]) if (e.rem() && lev[e.v] == 0) {
				lev[e.v] = lev[u] + 1;
				q.push(e.v);
			}
		}
		return lev[t] > 0;
	}
 
	long long dfs(int u, long long flow, int t) {
		if (u == t)
			return flow;
		for (int &i = ptr[u]; i < (int) adj[u].size(); i++) {
			Edge &e = adj[u][i];
 
			if (lev[u] + 1 != lev[e.v] || !e.rem()) 
				continue;
 
			long long new_flow = min(flow, e.rem());
			if (long long val = dfs(e.v, new_flow, t)) {
				e.flow += val;
				adj[e.v][e.pos].flow -= val;
				return val;
			}
		}
		return 0;
	}
    
    // If mincut is not needed
	long long maxFlow(int s, int t) {
		long long res = 0;
 
		while (bfs(s, t)) {
			while (int val = dfs(s, ooo, t)) 
				res += val;
		}
		return res;
	}

	// If mincut is needed
	vector <Edge> mincut(int s, int t) {
		long long res = 0;
		while (bfs(s, t)) {
			while (long long val = dfs(s, ooo, t))
				res += val;
        }
		bfs(s, t);

        vector <Edge> edges;

		for (int i = 0; i <= n; i++) 
		for (Edge e : adj[i]) {
			if (lev[i] > 0 && lev[e.v] == 0 && e.flow > 0) {
				edges.push_back(e);
            }
        }
        return edges;
	}
};