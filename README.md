# Bloom Filter
This is a quick implementation of a Bloom Filter. \
From Wikipedia:
A Bloom filter is a space-efficient probabilistic data structure, conceived by Burton Howard Bloom in 1970, that is used to test whether an element is a member of a set. False positive matches are possible, but false negatives are not – in other words, a query returns either "possibly in set" or "definitely not in set".

## Reference
### Constants
Two constants are defined as follows:
```cpp
#define BLOOM_FILTER_ARRAY_SIZE 10  // Internal array size 'm'
#define BLOOM_FILTER_HASH_FUNCTION_COUNT 3  // Number of hash functions 'k'
```
Internally, these are enclised in `#ifndef`, so it is possible to edit them by defining them before including `BloomFilter.cpp`:
```cpp
// Set constants
#define BLOOM_FILTER_ARRAY_SIZE 20
#define BLOOM_FILTER_HASH_FUNCTION_COUNT 5

// ...then include header
#include "BloomFilter.hpp"
```
These must be set at compile time as any changes to these after data has been added will result in all previous data becoming unreliable.
### Constructors
There are two constructors, both taking some sort of input data structure containing the hashing functions. These must be defined at the start as if the hashing functions change after data is added, all previous data becomes invalid.  \
Signatures:
```cpp
// Construction by function array
BloomFilter(std::function<int(T)> input_hash_functions[]);

// Construction by initializer list
BloomFilter(std::initializer_list<std::function<int(T)>> input_hash_functions);
```
Usage:
```cpp
// Example hashing functions
int hash0(int n) { return (13 - (n % 13)); }
int hash1(int n) { return (3 + 5 * n); }
int hash2(int n) { return (2 + 7 * (n % 10)); }

// Construction by function array
std::function<int(int)> hashing_functions[] = {hash0, hash1, hash2};
BloomFilter<int> *bf = new BloomFilter<int>(hashing_functions);

// Construction by initializer list
BloomFilter<int> *bf = new BloomFilter<int>({hash0, hash1, hash2});
```

### Adding a value
The following method may be used to add a value to the filter. Note that values scannot be removed after being added due to the nature of the filter. \
Signature:
```cpp
void add(T value);
```

Usage (assuming integer filter):
```cpp
// Adding via literal value
bf->add(3);

// Adding a variable
int x = 10;
bf->add(x);
```

### Checking if a value is (possibly) in the filter
The following value may be used to check if a value is in the filter. The method will return `true` if the value might be in the function, and `false` if it is not. Remember, false positives are possible (i.e. be skeptical of `true` and trust `false`). \
Signature:
```cpp
bool probably_contains(T value);
```

Usage:
```cpp
// Checking a literal value
bool is_10_contained = bf->probably_contains(10);

if (is_10_contained)
    cout << "10 has probably been added." << endl;
else
    cout << "10 has never been added." << endl;
```

### Checking error probability
The possibility of an error can be checked using the following method. Note that it assumes 'good' hash functions with not much overlap. \
Signature:
```cpp
float error_rate();
```

Usage:
```cpp
// Calculate error probability
float error_probability = bf->error_rate();
```

## References
* Someone's lecture page: https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1206/lectures/esoteric-data-structures/
* Wikipedia article: https://en.wikipedia.org/wiki/Bloom_filter
