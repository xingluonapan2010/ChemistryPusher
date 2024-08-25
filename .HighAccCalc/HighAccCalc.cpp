#include"HighAccCalc.h"


std::vector<int> HighAccCalc::HighAccCalcPlus(std::vector<int> a, std::vector<int> b) {
    std::vector<int> p;
    int f = 0;
    for (int i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) {
            f += a[i];
        }
        if (i < b.size()) {
            f += b[i];
        }
        p.push_back(f % 10);
        f /= 10;
    }
    if (f) {
        p.push_back(1);
    }
    return p;
}


std::vector<int> HighAccCalc::HighAccCalcTimes(std::vector<int> a, std::vector<int> b) {
    std::vector<int> p;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            t += a[i] * b[j];
            if (p.size() <= i + j) {
                p.push_back(t % 10);
            }
            else {
                p[i + j] += t;
                t = p[i + j];
                p[i + j] %= 10;
                t -= p[i + j];
            }
            t /= 10;
        }
        if (t) {
            p.push_back(t);
            t = 0;
        }
    }
    return p;
}

