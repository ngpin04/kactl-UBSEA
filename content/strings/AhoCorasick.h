/**
 * Tested with https://www.acmicpc.net/problem/9250
 */

struct AHC {
    struct node {
        bool leaf;
        array <int, 26> ptr;  // modifies this if binary
        int link, par, pch;

        node (int _pch = 0, int _par = 0){
            pch = _pch;
            par = _par;
            leaf = false;
            for(int i = 0; i < 26; i++)  // modifies this if binary
                ptr[i] = -1;
            link = -1;
        }
    };
    vector <node> tree;
    int cnt;

    AHC() {
        cnt = 0;
        tree.assign(1, node());
    }

    #define tr tree[u]

    bool &leaf(int u) {
        return tr.leaf;
    }

    int &ptr(int u, int c) {
        return tr.ptr[c];
    }

    int &pch(int u) {
        return tr.pch;
    }

    int &link(int u) {
        return tr.link;
    }

    int &par(int u) {
        return tr.par;
    }
    
    #undef tr

    void add(string s) {
        int cur = 0;
        for(int i = 0; i < (int) s.size(); i++){
            int val = s[i] - 'a';  // modifies this 
            if (ptr(cur, val) < 0) {
                ptr(cur, val) = ++cnt;
                tree.push_back(node(val, cur));
            }
            cur = ptr(cur, val);
        }
        leaf(cur) = true;
    }

    int getptr(int u, int c) { 
        int &res = ptr(u, c);
        if(res < 0) {
            if(u == 0)
                return res = 0;
            return res = getptr(getlink(u), c);
        }
        return res;
    }

    int getlink(int u) {
        int &res = link(u);
        if(res < 0) {
            if(u == 0 || par(u) == 0)
                res = 0;
            else
                res = getptr(getlink(par(u)), pch(u));
        }
        return res;
    }
};