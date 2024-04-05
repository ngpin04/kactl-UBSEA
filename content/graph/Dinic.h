/**
 * Tested with https://cses.fi/problemset/task/1694/
 * 
 */
#pragma once

struct Dinic {
	struct Edge {
		int v, pos; long long flow, cap;
 
		Edge(){}
		Edge(int _v, int _pos, long long _flow, long long _cap) {
			v = _v;
			pos = _pos;
			flow = _flow;
			cap = _cap;
		}
	};
 
	int n;
	vector <vector <Edge>> adj;
	vector <int> ptr;
	vector <int> lev;
 
	Dinic (int _n) {
		n = _n;
		adj.assign(n + 5, vector <Edge> (0));
		ptr.assign(n + 5, 0);
		lev.assign(n + 5, 0);
	}
 
	void addEgde(int u, int v, long long cap, long long rcap = 0) {
		Edge a = Edge(v, adj[v].size(), 0, cap);
		Edge b = Edge(u, adj[u].size(), 0, rcap);
		adj[u].push_back(a);
		adj[v].push_back(b);
	}
 
	bool bfs(int s, int t) {
		ptr = lev = vector <int> (n + 5, 0);
 
		lev[s] = 1;
 
		queue <int> q;
		q.push(s);
 
		while (q.size()) {
			int u = q.front();
			q.pop();
 
			for (Edge e : adj[u]) if (e.flow < e.cap && lev[e.v] == 0) {
				lev[e.v] = lev[u] + 1;
				q.push(e.v);
			}
		}
		//cerr << lev[t] << endl;
		return lev[t] > 0;
	}
 
	int dfs(int u, int flow, int t) {
		if (u == t)
			return flow;
		for (int &i = ptr[u]; i < (int) adj[u].size(); i++) {
			Edge &e = adj[u][i];
 
			if (lev[u] + 1 != lev[e.v] || e.flow == e.cap) 
				continue;
 
			int new_flow = min(0LL + flow, e.cap - e.flow);
			if (int val = dfs(e.v, new_flow, t)) {
				e.flow += val;
				adj[e.v][e.pos].flow -= val;
				return val;
			}
		}
		return 0;
	}
 
	long long maxFlow(int s, int t) {
		long long res = 0;
 
		while (bfs(s, t)) {
 
			while (int val = dfs(s, (int) 1e9, t)) 
				res += val;
		}
		return res;
	}

	// If mincut is needed
	void mincut(int s, int t) {
		int res = 0;
		while (bfs(s, t)) 
			while (int val = dfs(s, t, (int) 1e9))
				res += val;
		cout << res << "\n";
		bfs(s, t);
		for (int i = 1; i <= n; i++) 
		for (Edge e : adj[i])
			if (dis[i] > 0 && dis[e.v] == 0)
				cout << i << " " << e.v << "\n";
	}
};

