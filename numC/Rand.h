/**
 * @file Rand.h
 *
 * @brief Random Number Generators
 *
 * RNGs are struct object because it must 
 * maintain internal state between calls
 *
 * @date Feb 15, 2022
 * @author C J Park \n chanjure@snu.ac.kr
 * @bug No known bugs.
 * @version 1.0
 */

#ifndef RAND_H
#define RAND_H

// Library dependencies
#include <limits.h>

/**
 * @brief Linear Congruential Generator
 *
 * This is Linear Congruential Generator
 * for c = 0, it is called Multiplicative LCG
 * 
 * I_{n+1} = a*I_{n} + c (mod m)
 * a,c,m are chosen as in Numerical Recipes v3 p348 C1
 *
 * Period : 2^64
 * Diehard : No
 * TestU01 : 
 *
 * Avoid using this RNG on its own.
 *
 * Parameters:
 * @param a (int) multiplier
 * @param c (int) increment
 * @param m (int) modulus
 * @param I0 (int) seed
 *
 * Returns
 * @return returns random number
 *
 * Example:
 * @details LCG myRand(seed);
 *
 * Tag: LCG RNG
 */
struct LCG{
	unsigned long long a,m,c,I;
	
	LCG(unsigned long long I0) : a(3935559000370003845ULL), m(ULLONG_MAX), c(2691343689449507681ULL) {
		I = (a*I0 + c) % m;
	}
	
	inline unsigned long long randint(){
		I = (a*I + c) % m;
		return I;
	}
	inline double uniform() { return 5.42101086242752217033113759205528e-20*randint(); }
};

/**
 * @brief Multiple Recursive Generator
 *
 * This is Multiple Recursive Generator of order k=3
 * I_{n} = a_{1}*I_{n-1} + a_{2}*I_{n-2} (mod m)
 * a_{i} and m are chosen from L'Ecuyer (1998)
 *
 * Period : ~ 2^63
 * Diehard : 
 * TestU01 :
 *
 * Parameters:
 * @param a_{1}, a_{2} (int) multipliers
 * @param m (int) modulus
 * @param Ip (int) I_{n-1}
 * @parma Ipp (int) I_{n-2}
 * @param I0 (int) seed
 *
 * Returns
 * @return returns random number
 *
 * Example:
 * @details MRG(seed)
 *
 * Tag: MRG RNG
 */
struct MRG{
	long long a1,a2,m,Ip,Ipp,I;
	
	MRG(long long I0) : a1(3308108773LL), a2(6149300867LL), m(LLONG_MAX - 21129) {
		Ipp = (a2*I0) % m;
		Ip = (a1*Ipp - a2*I0) % m;
	}
	
	inline long long randint(){
		I = (a1*Ip - a2*Ipp) % m;
		if (I < 0.0) I += m;
		Ipp = Ip;
		Ip = I;
		return I;
	}
	inline double uniform() { return 1.0842021724855069177094666532869e-19*randint(); }
};

/**
 * @brief Combined Multiple Recursive Generator
 *
 * This is Combined Multiple Recursive Generator of order k=3
 * I_{1n} = a_{11}*I_{1n-1} + a_{12}*I_{1n-2} (mod m1)
 * I_{2n} = a_{21}*I_{2n-1} + a_{22}*I_{2n-2} (mod m2)
 * I_n = I_{1n} - I_{2n}
 * a_{i} and m are chosen from L'Ecuyer (1998)
 *
 * Period : ~ 2^63
 * Diehard : 
 * TestU01 :
 *
 * Parameters:
 * @param a_{ij} (int) multipliers
 * @param m1, m2 (int) modulus
 * @param Ip1, Ip2 (int) I_{n-1}
 * @parma Ipp1, Ipp2 (int) I_{n-2}
 * @param I0 (int) seed
 *
 * Returns
 * @return returns random number
 *
 * Example:
 * @details MRG(seed)
 *
 * Tag: CMRG RNG
 */
struct CMRG{
	long long a11,a12,a21,a22,m1,m2,Ip1,Ip2,Ipp1,Ipp2,I1,I2;
	
	CMRG(long long I0) : a11(3308108773LL), a12(6149300867LL), a21(3262668826LL), a22(7914571809LL), m1(LLONG_MAX - 21129), m2(LLONG_MAX - 275025) {
		// First component
		Ipp1 = (a12*I0) % m1;
		Ip1 = (a11*Ipp1 - a12*I0) % m1;
		
		// Second component
		Ipp2 = (a22*I0) % m2;
		Ip2 = (a21*Ipp2 - a22*I0) % m2;
	}
	
	inline long long randint(){
		// First component
		I1 = (a11*Ip1 - a12*Ipp1) % m1;
		if (I1 < 0.0) I1 += m1;
		Ipp1 = Ip1;
		Ip1 = I1;

		// Second component
		I2 = (a21*Ip2 - a22*Ipp2) % m2;
		if (I2 < 0.0) I2 += m2;
		Ipp2 = Ip2;
		Ip2 = I2;

		// Combination
		if (I1 <= I2) return I1 - I2 + m1;
		else return I1 - I2;
	}
	inline double uniform() { return 1.0842021724855069177094666532869e-19*randint(); }
};

/**
 * @brief Fibonacci RNG
 *
 * This is Multiple Recursive Generator
 * 
 *
 * Period : 
 * Diehard : 
 * TestU01 :
 *
 * Parameters:
 * @param a (int) multiplier
 * @param c (int) increment
 * @param m (int) modulus
 * @param I0 (int) seed
 *
 * Returns
 * @return returns 0
 *
 * Example:
 * @details ftn(x,y);
 *
 * Tag: LCG RNG
 */
struct Fib{
};
#endif
