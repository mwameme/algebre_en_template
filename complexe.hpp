#pragma once
#include <iostream>


template<typename T> class complexe {
public:

	friend complexe<T> derivee(const complexe<T>& element) {
		return complexe<T>(derivee(element.x), derivee(element.y));
	}


	complexe(T c_x,T c_y) : x(c_x),y(c_y) {};

	complexe() : x(), y() {};

	complexe(complexe<T>& copie) {
		x = copie.x;
		y = copie.y;
	};

	operator bool() {
		return (((bool)x) || ((bool)y));
	};

	template<class U> operator complexe<U>() {
		complexe<U> result;
		result.x = (U)x;
		result.y = (U)y;
		return result;
	};

	friend complexe<T> operator*(const complexe<T>& z1, const complexe<T>& z2) {
		return complexe<T>((z1.x * z1.x) - (z1.y * z2.y), (z1.x * z2.y) + (z1.y * z2.x));
	};

	template<class U> friend complexe<T> operator*(const U& scalaire, const complexe<T>& z) {
		complexe<T> result(z);
		result.x = scalaire * result.x;
		result.y = scalaire * result.y;
		return result;
	};

	friend complexe<T> operator+(const complexe<T>& z1, const complexe<T>& z2) {
		return complexe<T>(z1.x + z2.x, z1.y + z2.y);
	};

	friend complexe<T> operator-(const complexe<T>& z1, const complexe<T>& z2) {
		return complexe<T>(z1.x - z2.x, z1.y - z2.y);
	};

	friend complexe<T> operator-(const complexe<T>& z1) {
		return complexe<T>(-z1.x, -z1.y);
	};

	complexe<T> conjugue() {
		return complexe<T>(x, -y);
	};

	friend complexe<T> operator/(const complexe<T>& z1, const complexe<T>& z2) {
		T vrai(z1);
		vrai = true;

		T inv_module = vrai / ((z2.x * z2.x) + (z2.y * z2.y));
		return complexe<T>(inv_module * (z1.x * z2.x + z1.y * z2.y), inv_module * ((z1.y * z2.x) - (z1.x * z2.y)));
	};

	complexe<T>& operator=(bool test) {
		x = test;
		y = false;

		return *this;
	};

	friend bool operator==(const complexe<T>& temp1, const complexe<T>& temp2) {
		return ((temp1.x == temp2.x) && (temp1.y == temp2.y));
	}

	friend std::ostream& operator<<(std::ostream& os, const complexe<T>& element) {
		os << "(" << element.x << " + i*" << element.y << ")";
		return os;
	};

	T x;
	T y;

};
