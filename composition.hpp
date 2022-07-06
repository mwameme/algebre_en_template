#pragma once

template <typename T> class rationnel;
template <typename T> class polynome;
template <typename T> class matrice;


template<class T> T derivee(const T& element) {
    T result(false);
    return result;
};


template<class T> rationnel<T> derivee(const rationnel<T>& element);
template<class T> polynome<T> derivee(const polynome<T>& element);
template<class T> matrice<T> derivee(const matrice<T>& element);


#include <iostream>
#include "polynome.hpp"
#include "rationnel.hpp"
#include "matrice.hpp"
#include "corps fini.hpp"
#include "complexe.hpp"

template<class T> bool rationnel<T>::type = true;
template<class T> bool polynome<T>::type = false;
template<class T> bool matrice<T>::type = true;
template<class T> bool complexe<T>::type = true;
bool corps::type = true;

template<class T> void rationnel<T>::simplifier() {
    T pgcd = PGCD();

    if ((bool)pgcd) {
        numerateur = numerateur / pgcd;
        denominateur = denominateur / pgcd;
    }
    if (!(bool)numerateur)
        if ((bool)denominateur)
            denominateur = true;
    if (!(bool)denominateur)
        if ((bool)numerateur)
            numerateur = true;

    return;
};

/*
template<class T> void rationnel<polynome<T>> :: simplifier() {
    polynome<T> pgcd = PGCD();

    if (pgcd.degre >= 1) {
        numerateur = numerateur / pgcd;
        denominateur = denominateur / pgcd;
    }

    return;

};
*/


long long f_PPCM(long long a, long long b);

long long f_PGCD(long long a, long long b);

template<> void rationnel<polynome<rationnel<long long>>>::simplifier() {

    auto pgcd_ratio = PGCD();

    if (pgcd_ratio.degre >=1 ) {
        numerateur = numerateur / pgcd_ratio;
        denominateur = denominateur / pgcd_ratio;
    }
    
    long long ppcm = 1;
    for (int i(0); i < numerateur.coeffs.size(); ++i)
        ppcm = f_PPCM(ppcm, numerateur.coeffs[i].denominateur);
    for (int i(0); i < denominateur.coeffs.size(); ++i)
        ppcm = f_PPCM(ppcm, denominateur.coeffs[i].denominateur);

    for (int i(0); i < numerateur.coeffs.size(); ++i) {
        numerateur.coeffs[i].numerateur = numerateur.coeffs[i].numerateur * (ppcm / numerateur.coeffs[i].denominateur);
        numerateur.coeffs[i].denominateur = 1;
    }

    for (int i(0); i < denominateur.coeffs.size(); ++i) {
        denominateur.coeffs[i].numerateur = denominateur.coeffs[i].numerateur * (ppcm / denominateur.coeffs[i].denominateur);
        denominateur.coeffs[i].denominateur = 1;
    }

    long long pgcd = 1;
    for (int i(0); i < numerateur.coeffs.size(); ++i)
        pgcd = f_PGCD(pgcd, numerateur.coeffs[i].numerateur);
    for (int i(0); i < denominateur.coeffs.size(); ++i)
        pgcd = f_PGCD(pgcd, denominateur.coeffs[i].numerateur);

    for (int i(0); i < numerateur.coeffs.size(); ++i) {
        numerateur.coeffs[i].numerateur = numerateur.coeffs[i].numerateur /pgcd;
    }

    for (int i(0); i < denominateur.coeffs.size(); ++i) {
        denominateur.coeffs[i].numerateur = denominateur.coeffs[i].numerateur /pgcd;
    }


    long long pgcd_haut = 1;
    long long pgcd_bas = 1;

    for (int i(0); i < numerateur.coeffs.size(); ++i)
        pgcd_haut = f_PGCD(pgcd_haut, numerateur.coeffs[i].numerateur);
    for (int i(0); i < denominateur.coeffs.size(); ++i)
        pgcd_bas = f_PGCD(pgcd_bas, denominateur.coeffs[i].numerateur);

    for (int i(0); i < numerateur.coeffs.size(); ++i) {
        numerateur.coeffs[i].numerateur = numerateur.coeffs[i].numerateur / pgcd_haut;
        numerateur.coeffs[i].denominateur = numerateur.coeffs[i].denominateur * pgcd_bas;
    }

    for (int i(0); i < denominateur.coeffs.size(); ++i) {
        denominateur.coeffs[i].numerateur = denominateur.coeffs[i].numerateur / pgcd_bas;
        denominateur.coeffs[i].denominateur = denominateur.coeffs[i].denominateur * pgcd_bas;
    }


    return;
};

long long f_PPCM(long long a, long long b) { // a est non-nul
    if (b == 0)
        return a;
    long long x = a;
    long long y = b;
    long long r = 1;
    while ((bool)r) {
        r = (x % y);

        x = y;
        y = r;
    };
    return (a * b) / x;
};

long long f_PGCD(long long a, long long b) { // a est non-nul
    if (b == 0)
        return a;
    long long x = a;
    long long y = b;
    long long r = 1;
    while ((bool)r) {
        r = (x % y);

        x = y;
        y = r;
    };
    return x;
};
