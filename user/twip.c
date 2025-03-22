#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

typedef uint32 u32;
typedef uint8 u8;

const u8 TRUE = 1;
const u8 FALSE = 0;

const u32 LIMIT = 10000000;
const u32 FIRST_PRIME = 2;

const u32 INITIAL_PRIME_SIZE = 1;
const u32 INITIAL_PRIME_CAPACITY = 500;
const u32 FIRST_TWIN_PRIME = 3;

//  Hold a list of prime numbers. In order to avoid reallocation, 
//  `size` tracks how many elements of the list are valid entries. Elements 
//  beyond `primes[size - 1]` are garbage values.
struct PrimeList {
    u32 size;
    u32 capacity;
    u32* primes;
};

//  @breif  Determines if `check` is divisible by or equal to a known prime 
//          from `primeList`
//  @param  check Number to check 
//  @param  primeList List of known primes
//  @return Whether or not check is prime
u8 isPrime(u32 check, struct PrimeList primeList);

//  @breif  Adds `newPrime` to `primeList`. Does not verify is `newPrime` is 
//          prime
//  @param  newPrime Number to add
//  @param  primeList List to modify
void appendPrime(u32 newPrime, struct PrimeList* primeList);

void countTwinPrimes();

int main() {
    countTwinPrimes();

    exit(0);
}

void countTwinPrimes() {
    //  Allocate prime list
    u32 initialPrimes[INITIAL_PRIME_CAPACITY];
    initialPrimes[0] = FIRST_PRIME;

    //  Initialize prime list
    struct PrimeList primeList 
        = {INITIAL_PRIME_SIZE, INITIAL_PRIME_CAPACITY, initialPrimes};

    //  First prime was already added to prime list, so begin 
    u32 current = FIRST_PRIME;
    ++current;

    //  Populate list of primes which must be checked to determine if a number 
    //  less than the limit is prime. This reduces the upfront allocation 
    //  required compared to a standard Sieve of Eratosthenes
    while (current * current <= LIMIT) {
        if (isPrime(current, primeList)) {
            appendPrime(current, &primeList);
        }

        ++current;
    }

    printf(
        "To determine whether a number between %u and %u is prime, "\
        "up to %u prime numbers must be checked\n",
        FIRST_PRIME, LIMIT, primeList.size);

    current = FIRST_TWIN_PRIME;
    u32 previousPrime = current;
    u32 twinPrimeCount = 0;

    //  Verify both that the current number is prime and that the previous 
    //  prime is at most 2 less than the current
    while (current < LIMIT) {
        if (isPrime(current, primeList)) {
            if (current - previousPrime <= 2 && current != previousPrime) {
                twinPrimeCount += 1;
            }

            previousPrime = current;
        }

        ++current;
    }
    
    printf(
        "There are %u twin primes between %u and %u\n", 
        twinPrimeCount, FIRST_PRIME, LIMIT);
}

u8 isPrime(u32 check, struct PrimeList primeList) {
    u32 index = 0;
    
    while (index < primeList.size) {
        u32 currentPrime = primeList.primes[index];

        if (check == currentPrime) {
            return TRUE;
        }

        if (check % currentPrime == 0) {
            return FALSE;
        }

        ++index;
    }

    return TRUE;
}

void appendPrime(u32 newPrime, struct PrimeList* primeList) {
    if (primeList->size < primeList->capacity) {
        ++primeList->size;
        primeList->primes[primeList->size - 1] = newPrime;
    }
}
