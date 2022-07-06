//#ifndef RATIONNEL_H
//#define RATIONNEL_H

#pragma once
#include <vector>
#include <iostream>


//template rationnel<polynome<double>>;
//template polynome<double>;





template<typename T> class rationnel {
public:

    friend rationnel<T> derivee(const rationnel<T>& element) {
        rationnel<T> result(false);
        result.numerateur = (derivee(element.numerateur) * element.denominateur) - (element.numerateur * derivee(element.denominateur));
        result.denominateur = element.denominateur * element.denominateur;
        result.simplifier();
        return result;
    }


    rationnel(bool test) {
        numerateur = test;
        denominateur = true;
    };
    rationnel() {
        numerateur = false;
        denominateur = true;
    };
    rationnel(T const& a, T const& b) {
        numerateur = a;
        denominateur = b;
    };

    rationnel(const T& num) {
        numerateur = num;
        denominateur = true;
    }

    rationnel(const rationnel<T>& copie) {
        numerateur = copie.numerateur;
        denominateur = copie.denominateur;
    };

    rationnel<T>& operator=(bool test) {
        numerateur = test;
        denominateur = true;
        return *this;

    }

    rationnel<T>& operator=(const rationnel<T>& temp) {
        numerateur = temp.numerateur;
        denominateur = temp.denominateur;

        return (*this);
    };

    friend rationnel<T> operator%(const rationnel<T>& temp1, const rationnel<T>& temp2) {
        rationnel<T> result = temp1;
        result = false;
        return result;
    };

    T PGCD() const {
        T x(numerateur);
        T y(denominateur);

        if (numerateur > denominateur) {
            x = numerateur;
            y = denominateur;
        }
        else {
            x = denominateur;
            y = numerateur;
        }

        T r(x);
        r = true;

        T faux(r);
        faux = false;

        if (! (bool) y)
            return faux;

        if (! (bool) x)
            return faux;

        while ((bool) r) {
            r = (x%y);
//            r = x - y * (x / y);

            x = y;
            y = r;
        };

        return x;
    };

    void simplifier();

    //    template<typename U> 
    friend rationnel<T> operator* (const rationnel<T>& temp1, const rationnel<T>& temp2) {
        rationnel<T> result;
        result.numerateur = (temp1.numerateur * temp2.numerateur);
        result.denominateur = (temp1.denominateur * temp2.denominateur);
        result.simplifier();
        return result;
    };

    template<class U> friend rationnel<T> operator*(const U& scalaire, const rationnel<T>& temp) {
        rationnel<T> result;
        result.numerateur = scalaire * temp.numerateur;
        result.denominateur = temp.denominateur;
        result.simplifier();
        return result;
    };

    template<class U> U operator()(const U& element) {
        return (numerateur(element) / denominateur(element));
    };

    friend rationnel<T> operator/(const rationnel<T>& temp1, const rationnel<T>& temp2) {
        rationnel<T> result;
        result.numerateur = (temp1.numerateur * temp2.denominateur);
        result.denominateur = (temp1.denominateur * temp2.numerateur);

        result.simplifier();

        return result;
    };

    friend rationnel<T> operator+ (const rationnel<T>& temp1, const rationnel<T>& temp2) {
        rationnel<T> result;
        result.numerateur = ((temp1.numerateur * temp2.denominateur) + (temp2.numerateur * temp1.denominateur));
        result.denominateur = (temp1.denominateur * temp2.denominateur);

        result.simplifier();

        return result;
    };

    friend rationnel<T> operator-(const rationnel<T>& temp1, const rationnel<T>& temp2) {
        rationnel<T> result;
        result.numerateur = (temp1.numerateur * temp2.denominateur) - (temp2.numerateur * temp1.denominateur);
        result.denominateur = temp1.denominateur * temp2.denominateur;
        result.simplifier();
        return result;
    };

    friend rationnel<T> operator-(const rationnel<T>& temp) {
        rationnel<T> result;

        result.numerateur = -temp.numerateur;
        result.denominateur = temp.denominateur;
        return result;
    };

    friend bool operator==(const rationnel<T>& a, rationnel<T>& b) {
        return (!((bool) ((a.numerateur * b.denominateur) - (b.numerateur * a.denominateur))));
    };


    operator bool() const {
        return ((bool) numerateur);
    };

    explicit operator double() const;
    /*
    operator double() const {
        double result;
        result = ((double)numerateur) / ((double)denominateur);
        return result;
    };
    */


    template<class U> operator rationnel<U>()const {
        rationnel<U> result;
        result.numerateur = (U)numerateur;
        result.denominateur = (U)denominateur;
        return result;
    };
    

    friend std::ostream& operator<<(std::ostream& os, const rationnel<T>& element) {
        os << "(" << element.numerateur << "/" << element.denominateur << ")";
        return os;
    };

    T numerateur;
    T denominateur;

    static bool type; // corps
};

template rationnel<long long>;

template<> rationnel<long long> :: operator double() const {
    double result;
    result = ((double)numerateur) / ((double)denominateur);
    return result;
};

/*
template<> double rationnel<double>::PGCD() const {
    return (double)1.;
};
*/