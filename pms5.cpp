#include<bits/stdc++.h>
using namespace std;


/* MATH */
/* GFG */


// O(sqrt(n))xO(1)
bool isPrime(int n){
    if(n==1) return false;
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return false;
    }
    return true;
}


// If a # is not divisible by 2 then it cannot be divisible by 2, 4, 6, 8 ... all it's multiples -> no need to check. Half # eliminated eliminated.
// Similarly for 3.
// O(sqrt(n))xO(1) 3x faster (sqrt(n)/3) than isPrime since incremenet by 6 & 2 ops per iteration.
bool isPrime_alt(int n){
    if(n==1) return false;
    if(n==2 || n==3) return true;
    if(n%2==0 || n%3==0) return false;

    // If you do i+=2 then you will remove checking for all even numbers.
    // To eliminate checking for all 3 multiples as well i+=6. #s 5+6k, 7+6k are all #s not divisible by 2 & 3 & we've to check these.
    // Begin with 5 b/o n is not mul of 2, 3 and also 4. So start with 5.
    for(int i=5;i*i<=n;i+=6){
        if(n%i==0 || n%(i+2)==0) return false;
    }
    return true;
}


// 18/12/2022 Print all prime factors of n
// Every n = 2^a x 3^b x 5^c ...
// O(sqrt(n))xO(1). When n is prime then we don't reduce n non-linearly in this case all sqrt(n) ops are done.
// For composite it's <sqrt(n).
void primeFactors(int n){
    if(n<=1) return;
    for(int i=2;i*i<=n;i++){
        // Once you remove all 2s & 3s then your n will have only 5s, 7s, 9s. Then for new n you don't need to 
        // start from 2 again. Since 2s & 3s are removed they can't be factors hence you can continue.
        while(n%i==0){
            cout << i << " ";
            n/=i;
        }
    }
    
    // If you are left with n being a prime since you removed all 2s, 3s, 5s and only one 7 is remaining.
    // Then i will be 6. i is not <= sqrt(7) if there were 2 7s then 6*6<=n will be true but still n%6 would be false
    // then i=7 & you would print all 7s & left with n=1. Then below statement in not needed.
    if(n>1) cout << n;
    cout << endl;    
}


// O(sqrt(n))xO(1). Technicall O(sqrt(n)/3)xO(1).
void primeFactors_alt(int n){
    if(n<=1) return;
    while(n%2==0){
        cout << 2 << " ";
        n/=2;
    }

    while(n%3==0){
        cout << 3 << " ";
        n/=3;
    }

    for(int i=5;i*i<=n;i+=6){
        while(n%i==0){
            cout << i<< " ";
            n/=i;
        }

        while(n%(i+2)==0){
            cout << i+2<<" ";
            n/=(i+2);
        }
    }
    if(n>3){
        cout << n;
    }
    cout <<endl;
}


// O(sqrt(n)) x O(1)
void divisors(int n){
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            cout << i << " ";
            if(i!=n/i){
                cout << n/i<<" ";
            }
        }
    }
    cout << endl;
}


// O(sqrt(n)) x O(1). 2 traversal b/2 [1, sqrt(n)]
void divisorsSorted(int n){
    int i=1;
    for(;i*i<n;i++) if(n%i==0) cout << i << " ";
    for(;i>=1;i--) if(n%i==0) cout << n/i << " ";
    cout << endl;   
}

// 18/12/2022 
// Naive: O(n*sqrt(n)) => calling isPrime on each n below n
// Sieve of Eratosthenes
// O(nloglogn)xO(n). Almost linear.
void printPrimes(int n){
    bool isprime[n+1];
    fill(isprime, isprime+n+1, true);

    // technically i*i<=n is enough. to make small code size & print i here itself instead of separate loop.
    // Anyway inner loop will stop running when i croses sqrt(n);
    for(int i=2;i<=n;i++){
        if(!isprime[i]) continue;
        cout << i << " ";
        // No need to consider from j=2i, 3i, 4i, 5i, ... upto i*i
        // Since if they are composite then they would've been marked false by some divisor <=sqrt(i*i-1). So start from i*i
        for(int j=i*i;j<=n;j+=i){
            isprime[j]=false;
        }
    }
    cout << endl;
}


// 26/12/2022 Binary Exponentiation
// finds a^n % m using binpow where n is positive
// O(logn)
int binpow(int a, int n, int m = 1e9+7){
    long long result = 1;
    long long count=a;
    count%=m;
    while(n>=1){
        if(n&1) result = (result*count)%m;
        n>>=1;
        count  = (count*count)%m;
    }

    return result;
}


// 26/12/2022 Modular Multiplicative Inverse i.e a^-1 mod m
// Given m is prime Or else complicated formula but still MMI exists only when gcd(a,m)=1 i.e co-prime
// By fermat's little theorem it is equal to a^m-2 mod m
int modMulInv(int a, int m=1e9+7){
    return binpow(a, m-2, m);
}


int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    cout << isPrime(n) << endl;
    primeFactors(n);
    primeFactors(n);
    divisors(n);
    divisorsSorted(n);
    printPrimes(n);
    return 0;
}