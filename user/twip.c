#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const int LIMIT = 1000000;  //  Inclusive
const int FLOOR = 2;        //  Inclusive

const int ELEMENT_COUNT = LIMIT - FLOOR + 1;
const int NOT_PRIME = 0;

int main() {
    uint32 prime_candidates[ELEMENT_COUNT];
    uint32 index = 0;

    //  Initialize candidates
    while (index < ELEMENT_COUNT) {
        prime_candidates[index] = index + FLOOR;

        ++index;
    }

    //  Sieve of Eratosthenes
    int candidateIndex = 0;
    int primeCount = ELEMENT_COUNT;
    int candidate = prime_candidates[candidateIndex];

    while (candidate * candidate < LIMIT) {
        int searchIndex = candidateIndex;        

        while (searchIndex < ELEMENT_COUNT) {
            int current = prime_candidates[searchIndex];

            if (current % candidate == 0) {
                prime_candidates[searchIndex] = NOT_PRIME; 

                --primeCount;
            }

            ++searchIndex;
        }

        ++candidateIndex;

        if (candidateIndex < ELEMENT_COUNT) {
            while (prime_candidates[candidateIndex] == NOT_PRIME) {
                ++candidateIndex;
            }
        }
    }

    //  Count twin primes
    
}