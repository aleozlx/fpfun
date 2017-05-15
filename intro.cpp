#include <iostream>
#include <functional>
using lazy_number = std::function<int ()>;
using func_matrix = std::array<lazy_number, 4>;
using lazy_matrix = std::function<func_matrix ()>;

int const zero(){ return 0; };
int const one(){ return 1; };
auto const add(auto a, auto b){ return [=](){ return a()+b(); }; };
auto const mul(auto a, auto b){ return [=](){ return a()*b(); }; };
auto const dot(auto a1, auto a2, auto b1, auto b2){ 
	return add(mul(a1, a2), mul(b1, b2));
};

lazy_matrix const dot2(lazy_matrix const A, lazy_matrix const B) {
	auto const a = A(), b = B();
	return [=](){
		std::array<lazy_number, 4> const ret = {
			dot(a[0], b[0], a[1], b[2]), dot(a[0], b[1], a[1], b[3]),
			dot(a[2], b[0], a[3], b[2]), dot(a[2], b[1] ,a[3], b[3]) };
		return ret;
	};
};

func_matrix const _identity = { one, zero, zero, one };
auto const identity(){ return _identity; };
func_matrix const _magic = { one, one, one, zero };
auto const magic(){ return _magic; };

lazy_matrix const power(lazy_matrix const m, int n){
	if(n>1){
		return dot2(power(m, n-1), m);
	}
	else if(n==1) return m;
	else return identity;
}

int main(int argc, char const *argv[]){
	for(int i=0; i<9; ++i){
		lazy_matrix const F = power(magic, i);
		lazy_number const y = F()[0];
		std::cout<<i<<'\x20'<<y()<<std::endl;
	}
	return 0;
}
