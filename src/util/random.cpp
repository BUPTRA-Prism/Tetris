#include "util/random.h"
#include <random>
#include <algorithm>

int selectRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

std::vector<int> selectRandomList(int n, int m) {
    if (n < m) {
        return std::vector<int>(m, 0);
    }

    std::vector<int> pool(n);
    std::vector<int> result;

    std::iota(pool.begin(), pool.end(), 0);
    
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(pool.begin(), pool.end(), g);
    
    for (int i = 0; i < m; i++) {
        result.push_back(pool[i]);
    }
    
    return result;
}