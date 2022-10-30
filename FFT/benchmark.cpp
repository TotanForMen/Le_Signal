#include <bits/stdc++.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include "FFT.cpp"
#define START 20
#define AMOUNT 4
#define STOP START+AMOUNT
void benchmark(void (*func)(int)){
	int const REPEAT = 10;
	double results[AMOUNT];
	std::cout << std::endl << std::endl;
	std::cout << "n\ttime (sec)\n";
	struct timeval start, end;
	for (int i = START ; i <= STOP ; i++) {
		gettimeofday(&start, NULL);
		for (int j = 0 ; j < REPEAT ; ++j) {
			func(i);
		}
		double time_taken;
  		gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
  	std::cout << i << '\t' << time_taken / (double) AMOUNT << std::setprecision(12)<< std::endl;
   	 }
	std::cout << std::endl;

	 
}
Le_complex<double>* comp;
short* data;
void wrapper_solve_FFT(int n){
	Le_FFT::FFT(data,comp,n);
}
int main()
{
	data=(short*)malloc((1<<STOP)*sizeof(short));
	comp=(Le_complex<double>*)malloc((1<<STOP)*sizeof(Le_complex<double>));
	benchmark(wrapper_solve_FFT);
	return 0;
}
