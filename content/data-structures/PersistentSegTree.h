/**
 * Convexhull Trick
 * Author: me
 * Description: Store versions of segment trees in roots
 * Time: $O(N \log(N))$
 */

 #pragma once 

 struct Node {
    ll sum;
    Node *lef, *rig;
 
    Node(ll sum) : sum(sum), lef(nullptr), rig(nullptr) {};
};
 
struct PIT {
    vector<Node*> roots; // list of versions of the tree
    int n;
 
    PIT(int n) : n(n) {};
 
    Node* build(int l, int r, const vector<int> &a) {
        if (l == r) {
            return new Node(a[r]);
        }
 
        int mid = (l + r) >> 1;
        Node* cur = new Node(0);
        cur->lef = build(l, mid, a);
        cur->rig = build(mid + 1, r, a);
        cur->sum = cur->lef->sum + cur->rig->sum;
        return cur;
    }
 
    Node* update(Node* cur, int l, int r, int pos, int val) {
        if (l > pos || r < pos) {
            return cur;
        }
 
        if (l == r) {
            return new Node(val);
        }
 
        int mid = (l + r) >> 1;
        Node* res = new Node(0);
        res->lef = update(cur->lef, l, mid, pos, val);
        res->rig = update(cur->rig, mid + 1, r, pos, val);
        res->sum = res->lef->sum + res->rig->sum;
        return res;
    }
 
    Node* update(Node* cur, int pos, int val) {
        return update(cur, 0, n - 1, pos, val);
    }
 
    ll getsum(Node *cur, int l, int r, int u, int v) {
        if (l > v || r < u) {
            return 0;
        }
 
        if (l >= u && r <= v) {
            return cur->sum;
        }
 
        int mid = (l + r) >> 1;
        return getsum(cur->lef, l, mid, u, v) + getsum(cur->rig, mid + 1, r, u, v);
    }
 
    ll getsum(Node* cur, int l, int r) {
        return getsum(cur, 0, n - 1, l, r);
    }
};