#include <iostream>
#include <functional>
#include <chrono>
#include <cstdint>
using fibonacci_t = uint64_t;
using lazy_number = std::function<int ()>;
using func_matrix = std::array<lazy_number, 4>;
using lazy_matrix = std::function<func_matrix ()>;

inline fibonacci_t const zero(){ return 0ul; }
inline fibonacci_t const one(){ return 1ul; }
auto const add(auto a, auto b){ return [=](){ return a()+b(); }; }
auto const mul(auto a, auto b){ return [=](){ return a()*b(); }; }
auto const dot(auto a1, auto a2, auto b1, auto b2){ 
	return add(mul(a1, a2), mul(b1, b2));
}

lazy_matrix const dot2(lazy_matrix const &A, lazy_matrix const &B) {
	auto const a = A(), b = B();
	return [=](){
		std::array<lazy_number, 4> const ret = {
			dot(a[0], b[0], a[1], b[2]), dot(a[0], b[1], a[1], b[3]),
			dot(a[2], b[0], a[3], b[2]), dot(a[2], b[1] ,a[3], b[3]) };
		return ret;
	};
}

func_matrix const _identity = { one, zero, zero, one };
inline auto const identity(){ return _identity; }
func_matrix const _magic = { one, one, one, zero };
inline auto const magic(){ return _magic; }

lazy_matrix const power(lazy_matrix const &m, int n){
	if(n>1){
		auto t0 = power(m, (n>>1));
		auto t1 = dot2(t0, t0);
		return (n&1)?dot2(t1, m):t1;
	}
	else if(n==1) return m;
	else return identity;
}

fibonacci_t fibonacci1(int i){
	int s0 = 1, s1 = 1, t;
	if(i>=0) {
		while(--i) { t = s1; s1 += s0; s0 = t; }
		return s1;
	}
	else return 0;
}

fibonacci_t fibonacci2(int i){
	if(i>=0) return power(magic, i)()[0]();
	else return 0;
}

int main(int argc, char const *argv[]){
	for(int n = 55; n>0; n-=10){
		std::cout<<"f("<<n<<") = ";
		auto t1 = std::chrono::high_resolution_clock::now();
		fibonacci_t f1 = fibonacci1(n);
		auto t2 = std::chrono::high_resolution_clock::now();
		fibonacci_t f2 = fibonacci2(n);
		auto t3 = std::chrono::high_resolution_clock::now();
		std::cout<<f1<<'\x20'<<f2<<std::endl;
		std::chrono::duration<double, std::milli> time1 = t2 - t1, time2 = t3 - t2;
		double slowdown = time2 / time1;
		std::cout<<"FP slowdown: "<<slowdown<<std::endl;
	}
	
	return 0;
}
