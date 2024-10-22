# pragma once

// === HEADERS ===
#include <functional>
#include <bits/stdc++.h>
#include <initializer_list>
#include <algorithm>


// === CONSTANTS ===
#ifndef BLOOM_FILTER_ARRAY_SIZE
    #define BLOOM_FILTER_ARRAY_SIZE 10  // Internal array size 'm'
#endif
#ifndef BLOOM_FILTER_HASH_FUNCTION_COUNT
    #define BLOOM_FILTER_HASH_FUNCTION_COUNT 3  // Number of hash functions 'k'
#endif

// === BLOOM FILTER ===
template <typename T> class BloomFilter {
    private:
        int size;  // Number of items already added
        bool bit_array[BLOOM_FILTER_ARRAY_SIZE];  // Internal bit array
        std::function<int(T)> hash_functions[BLOOM_FILTER_HASH_FUNCTION_COUNT];  // Array of hash functions

    public:
        // --- Constructors ---
        BloomFilter(std::function<int(T)> input_hash_functions[]);  // Constructor must include hash functions, as the filter breaks if hash functions are changed after adding data.
        BloomFilter(std::initializer_list<std::function<int(T)>> input_hash_functions);

        // --- Data manipulation ---
        void add(T value);

        // --- Data retrieval ---
        bool probably_contains(T value);
        float error_rate();
};

// --- Methods ---
template <typename T> BloomFilter<T>::BloomFilter(  // Constructor
    std::function<int(T)> input_hash_functions[]  // Hash functions
) {
    // Copy functions in
    for (int i = 0; i < BLOOM_FILTER_HASH_FUNCTION_COUNT; i++) {
        hash_functions[i] = input_hash_functions[i];
    }
}

template <typename T> BloomFilter<T>::BloomFilter(std::initializer_list<std::function<int(T)>> input_hash_functions) {
    // Copy functions in
    std::copy(input_hash_functions.begin(), input_hash_functions.end(), hash_functions);
}

template <typename T> void BloomFilter<T>::add(  // Add item
    T value  // Value to add
) {

    // Hash with every function, and set the bit at the resulting index
    for (int i = 0; i < BLOOM_FILTER_HASH_FUNCTION_COUNT; i++) {
        bit_array[hash_functions[i](value) % BLOOM_FILTER_ARRAY_SIZE] = true;
    }
    ++size;

}

template <typename T> bool BloomFilter<T>::probably_contains(  // Check whether item may be contained
    T value  // Value to check for
) {

    // Result variable
    bool result = true;

    // Hash with every function, and unset result if bit is unset
    for (int i = 0; i < BLOOM_FILTER_HASH_FUNCTION_COUNT; i++) {
        result = result && bit_array[hash_functions[i](value) % BLOOM_FILTER_ARRAY_SIZE];
    }

    // Return result
    return result;
}

template <typename T> float BloomFilter<T>::error_rate() {  // Get error rate
    return (std::exp(-1 * (BLOOM_FILTER_HASH_FUNCTION_COUNT * BLOOM_FILTER_ARRAY_SIZE) / size));
}
