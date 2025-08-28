/**
 * Half Plane Intersection
 * tested with https://www.acmicpc.net/problem/11001\
 * Author: Rain
 * Description: given a list of half planes, return the list of intersections (could be empty and unbounded)
 * Half plane constructor, given points a, b then the half plane is one the left side of the line ab 
 */
#pragma once

typedef long double ld;
typedef Point<ld> P;
const ld eps = 1e-15, inf = 1e9;

struct Halfplane {
    P p, pq;
    ld angle;
    Halfplane() {}
    Halfplane(const P& a, const P& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);    
    }
    bool out(const P& r) { 
        return pq.cross(r - p) < -eps; 
    }
    bool operator<(const Halfplane& e) const { 
        return angle < e.angle;
    }
    friend P inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
        return s.p + (s.pq * alpha);
    }
};
vector<P> hp_intersect(vector<Halfplane> H) { 

    P box[4] = {  // Bounding box in CCW order
        P(inf, inf), 
        P(-inf, inf), 
        P(-inf, -inf), 
        P(inf, -inf) 
    };
    
    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl(H[i].pq.cross(dq[len-1].pq)) < eps) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (H[i].pq.dot(dq[len-1].pq) < 0.0)
                return vector<P>();

            // Same direction half-plane: keep only the leftmost half-plane.
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<P>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<P> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}
