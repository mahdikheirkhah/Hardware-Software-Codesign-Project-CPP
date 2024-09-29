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

#define MAXFIFO 1024
class fifo_t {
	complex data[MAXFIFO]; 
	unsigned wptr; 
	unsigned rptr;
	public:
	fifo_t() {
	this->wptr = this->rptr = 0;
	}
	void put_fifo(complex d) {
		if ((this->wptr + 1) %  MAXFIFO != (this->rptr)) {
			this->data[this->wptr] = d;
			this->wptr = (this->wptr + 1) % MAXFIFO;
		}
	}
	complex get_fifo() {
		complex r ;
		if (this->rptr != this->wptr) {
			r = this->data[this->rptr];
			this->rptr = (this->rptr + 1) % MAXFIFO;
			return r;
		}	
		return -1;
	}
	unsigned fifo_size() {
		if (this->wptr >= this->rptr)
			return this->wptr - this->rptr;
		else
			return  MAXFIFO - (this->rptr - this->wptr) + 1;
	}
	void reset() {
		this->wptr = this->rptr = 0;
	}	
};

typedef struct actrio {
	fifo_t  in[4];
	fifo_t  out[4];
}actrio_t ;

void reorder(actrio_t *g);
void fft2 (actrio_t *g);
void fft4 (actrio_t *g);
void fft8 (actrio_t *g);


int main(){
	int i;
	double x[8];
	actrio_t g;
	while(1){	
		for (i = 0 ; i < 8 ; i++){
				cin >> x[i];
				g.in[0].put_fifo(complex(x[i],0));  
		}
	
		auto firsttime = high_resolution_clock::now();
	
		reorder(&g);
		fft2(&g);
		fft4(&g);
		fft8(&g);
	
		auto secondtime = high_resolution_clock::now();
		auto difftime = duration_cast<nanoseconds>(secondtime - firsttime);		
		cout << "time it takes: " << difftime.count() << " nanoseconds" <<endl;
	
		while(g.out[3].fifo_size() >= 8){	
			for (i = 0 ; i < 8 ; i++){
				g.out[3].get_fifo().print(i);
			}
		}
	}
	return  0;
}

void reorder (actrio_t *g){
	int i,j;
	complex c[8];
	while(g -> in[0].fifo_size() >= 8){     
		for(i = 0 ; i < 8 ; i++)
			c[i] = g -> in [0].get_fifo();
		for(j = 0 ; j < 2 ; j++){
			for(i = j; i < 4  ; i += 2){	
				g -> out[0].put_fifo(c[i]);
				g -> out[0].put_fifo(c[i + 4]);
			}
		}
	}
	g -> in[1] = g -> out[0];
	g -> out[0].reset();
}

void fft2 (actrio_t *g){
	int i;
	complex c[2],w;
	while(g -> in[1].fifo_size() >= 2){	
		for(i = 0 ; i < 2 ; i++)
			c[i] = g -> in [1].get_fifo();
		for(i = 0 ; i < 1 ; i ++){
		g -> out[1].put_fifo(c[i] + c[i + 1] * w.w_cal(0,2));
		g -> out[1].put_fifo(c[i] - c[i + 1] * w.w_cal(0,2));
		}
	}
	g -> in[2] = g -> out[1];
	g -> out[1].reset();
}

void fft4 (actrio_t *g){
	int i;
	complex c[4],w;
	while(g -> in[2].fifo_size() >= 4){
		for(i = 0 ; i < 4 ; i++)
				c[i] = g -> in [2].get_fifo();
		for(i = 0; i < 1 ; i ++){				
			g -> out[2].put_fifo( c[i] + c[i + 2] * w.w_cal(0,4));
			g -> out[2].put_fifo( c[i + 1] +(c[i + 3] * w.w_cal(1,4)));
			g -> out[2].put_fifo( c[i] - c[i + 2] * w.w_cal(0,4));
			g -> out[2].put_fifo( c[i + 1] - (c[i + 3] * w.w_cal(1,4)));
		}			
	}
	g -> in[3] = g -> out[2];	
	g -> out[2].reset();
}

void fft8 (actrio_t *g){
	int i;
	complex c[8],w;
	while(g -> in[3].fifo_size() >= 8){
		for(i = 0 ; i < 8 ; i++)
			c[i] = g -> in [3].get_fifo();
		for(i = 0 ; i < 4 ; i++)	
			g -> out[3].put_fifo( c[i] + c[i+4] * w.w_cal(i,8));
		for(i = 0 ; i < 4 ; i++)	
			g -> out[3].put_fifo( c[i] - c[i+4] * w.w_cal(i,8));
	}	
}
