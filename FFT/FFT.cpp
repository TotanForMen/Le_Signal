#include "Le_complex.cpp"
namespace Le_FFT{
	void FFT(short* input,Le_complex<double>* output,int size){	//number of samples=2^size
		short *short_dp1,*short_dp2;
		Le_complex<double> *complex_dp1,*complex_dp2;
		Le_complex<double> Le_2PI(0.0,-M_PI*2.0);
		Le_complex<double> Le_W;
		complex_dp1=(Le_complex<double>*)malloc(sizeof(Le_complex<double>)<<size);
		short_dp1=input;short_dp2=(short*)complex_dp1;
		for(int i=size-1;i>0;i--){
			for(unsigned int j=0;j < 1<<(size-i);j++){
				for(int k=0;1<<i > k;k++){
					//std::cout << "i:" << i << "j:" << j << "k:" << k << "     " << (1<<i)*j+k << " " << ((1<<i)*(j&0xfffffffe)+ (k<<1) + (j&1)) <<std::endl;
					short_dp2[(j<<i)+k]=short_dp1[((j&0xfffffffe) << i) + (k<<1) + (j&1)];
				}
			}				
			short_dp1=(short*)((long int)short_dp1 ^ (long int)short_dp2);
			short_dp2=(short*)((long int)short_dp1 ^ (long int)short_dp2);
			short_dp1=(short*)((long int)short_dp1 ^ (long int)short_dp2);
		}
		for(int i=0;i < 1<<(size-1);i++){
			output[i<<1]=Le_complex<double>((double)(short_dp1[i<<1]+short_dp1[(i<<1)+1]),0.0);
			output[(i<<1)+1]=Le_complex<double>((double)(short_dp1[i<<1]-short_dp1[(i<<1)+1]),0.0);
		}
		complex_dp2=complex_dp1;
		for(int i=0;i<size-1;i++){
			Le_W=Le_2PI / (double)(1<<(i+2));
			for(unsigned int j=0;j < 1<<(size-i-2);j++){
				for(unsigned int k=0;k < 1<<(i+1);k++){
					//std::cout << "i:" << i << "j:" << j << "k:" << k << "     " << (j<<(i+2))+k << " " << (j<<(i+2))+k+(1<<(i+1)) <<std::endl;
					complex_dp1[(j<<(i+2))+k] = output[(j<<(i+2))+k+(1<<(i+1))] * Le_W.exp(Le_W * (double)k);
				}
				for(unsigned int k=0;k < 1<<(i+1);k++){
					//std::cout << "i:" << i << "j:" << j << "k:" << k << "     " << (1<<i)*j+k << " " << ((1<<i)*(j&0xfffffffe)+ (k<<1) + (j&1)) <<std::endl;
					output[(j<<(i+2))+k]=output[(j<<(i+2))+k]+complex_dp1[(j<<(i+2))+k];
				}
				for(unsigned int k=0;k < 1<<(i+1);k++){
					//std::cout << "i:" << i << "j:" << j << "k:" << k << "     " << (1<<i)*j+k << " " << ((1<<i)*(j&0xfffffffe)+ (k<<1) + (j&1)) <<std::endl;
					output[(j<<(i+2))+k+(1<<(i+1))]=output[(j<<(i+2))+k]-(complex_dp1[(j<<(i+2))+k]*2.0);
				}
			}				
		}
		free(complex_dp1);
	}
	void FFT_Print(Le_complex<double>* output,int size){
		for(int i=0;i<size;i++){
		output[i].print();
	}
	}
};
