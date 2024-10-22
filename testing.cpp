#define BLOOM_FILTER_ARRAY_SIZE 20  // Internal array size 'm'

#include "BloomFilter.hpp"
#include <iostream>

int hash0(int n) { return (13 - (n % 13)); }
int hash1(int n) { return (3 + 5 * n); }
int hash2(int n) { return (2 + 7 * (n % 10)); }

int main() {

    std::function<int(int)> hashing_functions[] = {hash0, hash1, hash2};

    BloomFilter<int> *bf = new BloomFilter<int>(hashing_functions);

    int test_numbers[] = {1, 2, 3, 10, 15, 20, 100, 200};


    for (int i : test_numbers) {
        bf->add(i);
        std::cout << "Added " << i << std::endl;
        std::cout << "Error rate: " << bf->error_rate() << std::endl;
        for (int j : test_numbers) {
            std::cout << j << " possibly exists: " << bf->probably_contains(j) << std::endl;
        }
        std::cout << std::endl;
    }

    delete bf;
}
