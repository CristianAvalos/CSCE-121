#include "Vect.h"
#include <cstdlib>

Vect vect_construct(unsigned int n, int val) {
	Vect A;
	A.size = n;
	A.capacity = n*2;
	A.arr = new int[A.capacity];
	for (int i = 0; i <= n; i++) {
		A.arr[i] = val;
	}
	return A;
}
	
unsigned int vect_size(const Vect &v) {
	unsigned int n = v.size;
	return n;
}

unsigned int vect_capacity(const Vect &v) {
	unsigned int c = v.capacity;
	return c;
}

bool vect_empty(const Vect &v) {
	bool f;
	if (v.size == 0) {
		f = true;
	}
	else {
		f = false;
	}
	return f;
}

void vect_resize(Vect &v, unsigned int n) {
	int size = v.size;
	if (n < size) {
		int* temp = new int[n];
		for (int i = 0; i < n; ++i) {
			temp[i] = v.arr[i];
		}
		delete [] v.arr;
		v.size = n;
		v.capacity = n;
		v.arr = temp;
	}
	else {
		int* temp = new int[n];
		for (int i = 0; i < v.size; ++i) {
			temp[i] = v.arr[i];
		}
		delete [] v.arr;
		v.capacity = n;
		v.arr = temp;
	}
}
int& vect_at(Vect &v, unsigned int idx){
	int size = v.size;
	if ((idx < 0) || (idx > v.size)) {
		exit(1);
	}
	return v.arr[idx];
}
void vect_erase(Vect &v, unsigned int idx){
	if((idx < 0) || (idx > v.size)) {
		exit(1);
	}
	if ((idx >= 0) && (idx < (v.size - 1))) {
		for (int i = idx; i < (v.size - 1); ++i) {
			v.arr[i] = v.arr[i + 1];
		}
	}
	else if (idx == (v.size - 1)) {
		v.arr[idx] = 0;
	}
	v.size -= 1;
}
void vect_push_back(Vect &v, int val){
	if ((v.size + 1) > v.capacity) {
		vect_resize(v, (v.size * 2));
	}
	v.size += 1;
	v.arr[v.size - 1] = val;
}
void vect_insert(Vect &v, unsigned int idx, int val){
	if((idx < 0) || (idx > (v.size - 1))) {
		exit(1);
	}
	if ((v.size + 1) > v.capacity) {
		vect_resize(v, (v.size * 2));
	}
	v.size += 1;
	for (int i = (v.size - 1); i > idx; i--) {
		v.arr[i] = v.arr[i - 1];
	}
	v.arr[idx] = val;
}
void vect_clear(Vect &v){
	if (v.size >= 20) {
		vect_resize(v, 20);
	}
	v.size = 0;
}
void vect_destruct(Vect &v){
	delete [] v.arr;
	int* arr = nullptr;
	v.size = 0;
	v.capacity = 0;
}

