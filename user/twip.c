#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

typedef uint32 u32;
typedef uint8 u8;

const u8 TRUE = 1;
const u8 FALSE = 0;

const u32 LIMIT = 1000000;
const u32 PRIME_FLOOR = 2;

const u32 INITIAL_PRIME_SIZE = 1;
const u32 INITIAL_PRIME_CAPACITY = 200;

//  Hold a list of prime numbers. In order to avoid reallocation, 
//  `size` tracks how many elements of the list are valid entries. Elements 
//  beyond `primes[size - 1]` are garbage values.
struct PrimeList {
    u32 size;
    u32 capacity;
    u32* primes;
};

u8 isPrime(u32 check, struct PrimeList primeList);

void appendPrime(u32 newPrime, struct PrimeList* primeList);

int main() {
    u32 initialPrimes[INITIAL_PRIME_CAPACITY];
    initialPrimes[0] = PRIME_FLOOR;

    struct PrimeList primeList 
        = {INITIAL_PRIME_SIZE, INITIAL_PRIME_CAPACITY, initialPrimes};

    u32 current = PRIME_FLOOR;
    ++current;

    while (current * current <= LIMIT) {
        if (isPrime(current, primeList)) {
            appendPrime(current, &primeList);
        }

        ++current;
    }

    printf(
        "To determine whether a number between %u and %u is prime,"\
        "up to %u prime numbers must be checked\n",
        PRIME_FLOOR, LIMIT, primeList.size);

    exit(0);
}

u8 isPrime(u32 check, struct PrimeList primeList) {
    u32 index = 0;
    
    while (index < primeList.size) {
        u32 currentPrime = primeList.primes[index];

        if (check % currentPrime == 0) {
            return FALSE;
        }

        ++index;
    }

    printf("Found no divisors, %u is prime\n", check);
    return TRUE;
}

void appendPrime(u32 newPrime, struct PrimeList* primeList) {
    if (primeList->size < primeList->capacity) {
        ++primeList->size;
        primeList->primes[primeList->size - 1] = newPrime;
    }
}