#include <iostream>
#include <cstdlib>
#include <math.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

class complex {
    double real,imag;
public:    
    complex(double x = 0,double y = 0){
        real = x;
        imag = y;
    }
    complex (const complex& k){
        real = k.real;
        imag = k.imag;
    }
    complex operator +(const complex& k){
        complex c;
        c.real = real + k.real;
        c.imag = imag + k.imag;
        return c; 
    }
    complex operator -(const complex& k){
        complex c;
        c.real = real - k.real;
        c.imag = imag - k.imag;
        return c;
    }
    complex operator *(const complex& k){
        complex c;
        c.real = (real * k.real) - (imag * k.imag);
        c.imag = (real * k.imag) + (imag * k.real);
        return c;
    }
    complex& operator =(double a){
        this -> imag = 0;
        this -> real = a;
        return *this;
    }    
    complex& operator =(const complex& k ){
        this -> imag = k.imag;
        this -> real = k.real;
        return *this;
    } 
     complex w_cal (const int k,const int n){
		complex c;	
		c.real = cos(M_PI * 2 *(-1) * k / n);
		c.imag = sin(M_PI * 2 *(-1) * k / n);
		return c;
	} 
   void print(int i){
            cout << "output["<<i<<"] = "<< this -> real<<" + ("<< this -> imag <<") i"<<endl;
        }
};

int main(){
	int i,j,k;
	double x[8];
	complex input[8],reorder[8],w,a_fft2[4], b_fft2[4], c_fft4[4], d_fft4[4], e_fft8[4], f_fft8[4], output[8]; 
	while(1){	
		//input
		for (i = 0 ; i < 8 ; i++){
				cin >> x[i];
				input[i] = complex(x[i],0);
		}
	
		auto firsttime = high_resolution_clock::now();
		//reorder
		k = 0;
		for(j = 0 ; j < 2 ; j++){
			for(i = j ; i < 4 ; i += 2){
				reorder[k] = input[i];
				reorder[k + 1] = input[i + 4];
				k += 2;		
			}
		}
				
		//reorder to fft2 
		k = 0;	
		for(i = 0 ; i < 4 ; i++){
			a_fft2[i] = reorder[k] + reorder[k + 1] * w.w_cal(0,2);
			b_fft2[i] = reorder[k] - reorder[k + 1] * w.w_cal(0,2);
			k += 2 ;	
			}
	
		//fft2 to fft4
		for(i = 0 ; i < 3 ; i += 2){
			c_fft4[i] = a_fft2[i] + a_fft2[i + 1] * w.w_cal(0,4);
			d_fft4[i] = a_fft2[i] - a_fft2[i + 1] * w.w_cal(0,4);
		}
		for(i = 1 ; i < 4 ; i += 2){
			c_fft4[i] = b_fft2[i - 1] + b_fft2[i] * w.w_cal(1,4);
			d_fft4[i] = b_fft2[i - 1] - b_fft2[i] * w.w_cal(1,4);
		}
		
		//fft4 to fft8
		for(i = 0 ; i < 2 ; i++){
			e_fft8[i] = c_fft4[i] + c_fft4[i + 2] * w.w_cal(i,8);
			f_fft8[i] = c_fft4[i] - c_fft4[i + 2] * w.w_cal(i,8);
		}
		for(i = 2 ; i < 4 ; i++){
			e_fft8[i] = d_fft4[i - 2] + d_fft4[i] * w.w_cal(i,8);
			f_fft8[i] = d_fft4[i - 2] - d_fft4[i] * w.w_cal(i,8);
		}
		 
		//fft8 to ouput
		for (i = 0 ; i < 4 ; i++){
			output[i] = e_fft8[i]; 
			output[i + 4] = f_fft8[i];
		}
		
		//time calculator
		auto secondtime = high_resolution_clock::now();
		auto difftime = duration_cast<nanoseconds>(secondtime - firsttime);
		cout << "time it takes: " << difftime.count() << " nanoseconds" <<endl;
		
		//print output
		for (i = 0 ; i < 8 ; i++){
				output[i].print(i);
		}
	}
	return  0;
}

