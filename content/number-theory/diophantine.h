// usage find integers x and y such that ax + by = 1
// Complexity: O(log(n))
// Note: To use diophantine to calculate inverse modulo of a with modulo m (gcd(a, m) = 1)
// find solution (x, y) such that ax - my = 1 (remember to normalize x)
#pragma once

function <pair <long long, long long>(int, int)> solve = [&](int a, int b) {
    if (b == 0) 
        return mp(1LL, 0LL);

    auto [c, d] = solve(b, a % b);
    return mp(d, c - (a / b) * d);
};	
