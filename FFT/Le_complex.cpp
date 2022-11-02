#ifndef LE_COMPLEX
#define LE_COMPLEX 0
#include<iostream>
#include<math.h>
class Le_complex{
	private:
		double real,img;
	public:
		Le_complex(double real,double img){
			this->real=real;
			this->img=img;
		}
		Le_complex(){
		}
		Le_complex conj(){
			Le_complex result(this->real,-this->img);
			return result;
		}
		Le_complex operator*(Le_complex b){
			Le_complex result(this->real*b.real-this->img*b.img,this->real*b.img+this->img*b.real);
			return result;
		}
		Le_complex operator*(double b){
			Le_complex result(this->real*b,this->img*b);
			return result;
		}
		Le_complex operator+(Le_complex b){
			Le_complex result(this->real+b.real,this->img+b.img);
			return result;
		}
		Le_complex operator-(Le_complex b){
			Le_complex result(this->real-b.real,this->img-b.img);
			return result;
		}
		Le_complex operator/(double b){
			Le_complex result(this->real/b,this->img/b);
			return result;
		}
		Le_complex operator/(Le_complex b){
			Le_complex result;
			result=(b.conj()* *this)/(b.real*b.real+b.img*b.img);
			return result;
		}
		Le_complex exp(Le_complex C){
			Le_complex result(std::cos(C.img),std::sin(C.img));
			return result*std::exp(C.real);
			
		}
		void print(){
			std::cout << "real:" << this->real << "\timg:" << this->img << std::endl;
		}
		void printAbs(){
			std::cout << "abs:" << std::sqrt(this->real*this->real+this->img*this->img) << std::endl;
		}
		void printArg(){
			std::cout << "arg:" << std::atan(this->img/this->real)<< std::endl;
		}
};
#endif
