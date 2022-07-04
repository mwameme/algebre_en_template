//#ifndef POLYNOME_H
//#define POLYNOME_H

#pragma once 

#include <vector>
#include <iostream>

template<typename T> class polynome;
template<typename T> class matrice;
template<typename T> class rationnel;


template<typename T> class polynome {
public:


    friend polynome<T> derivee(const polynome<T>& element) {
        polynome<T> result(element);

        for (long i(0); i < result.coeffs.size() - 1; ++i) {
            result.coeffs[i] = (i + 1) * result.coeffs[i + 1];
        }
        result.coeffs[result.coeffs.size() - 1] = false;
        result.getDegre();
        return result;
    };

    polynome(std::vector<T> tab) {
        coeffs = tab;
        if (coeffs.size() == 0) {
            coeffs.resize(1);
            coeffs[0] = false;
        }
        getDegre();
    };

    polynome() : degre(-1), coeffs(1, false) {};

    polynome(const T& element) {
        coeffs.resize(1);
        coeffs[0] = element;
        getDegre();
    };

    polynome(const polynome<T>& copie) {
        coeffs = copie.coeffs;
        getDegre();

    };



    polynome<T>& operator=(const polynome<T>& temp) {
        coeffs = temp.coeffs;
        degre = temp.degre;
        return (*this);
    };

    polynome<T>& operator=(bool test) {
        coeffs.resize(1);
        coeffs[0] = test;
        getDegre();
        return (*this);
    };



    friend polynome<T> operator*(const polynome<T>& temp1, const polynome<T>& temp2) {

        polynome<T> result;
        result.coeffs[0] = temp1.coeffs[0];
        result = false;
        T faux = result.coeffs[0];

        if ((temp1.degre < 0) || (temp2.degre < 0))
            return result;

        result.coeffs.resize(temp1.degre + temp2.degre + 1);
        for (int i(0); i < result.coeffs.size(); ++i) {
            T temp(faux);
            for (int j(0); j <= i; ++j) {
                if ((j < temp1.coeffs.size()) && ((i - j) < temp2.coeffs.size()))
                    temp = temp + (temp1.coeffs[j] * temp2.coeffs[i - j]);
            }
            result.coeffs[i] = temp;
        }
        result.getDegre();

        return result;
    };

    template<class U> friend polynome<T> operator*(const U& scalaire, const polynome<T>& temp) {
        polynome<T> result(temp);

        for (int i(0); i < temp.coeffs.size(); ++i)
            result.coeffs[i] = scalaire * result.coeffs[i];
        result.getDegre();
        return result;
    };

    friend polynome<T> operator%(const polynome<T>& temp1, const polynome<T>& temp2) {
        T faux = temp1.coeffs[0];
        faux = false;

        if (temp2.degre > temp1.degre)
            return temp1;
        if (temp2.degre < 0)
            return temp1;
        if (temp1.degre < 0)
            return temp1;

        polynome<T> A(temp1);
        while (A.degre >= temp2.degre) {
            polynome<T> monome(A);
            monome.coeffs.resize(A.degre - temp2.degre + 1);
            for (int i(0); i < monome.coeffs.size(); ++i)
                monome.coeffs[i] = false;

            monome.coeffs[A.degre - temp2.degre] = A.coeffs[A.degre] / temp2.coeffs[temp2.degre];
            monome.getDegre();

            int A_degre = A.degre;
            A = (A - (temp2 * monome));

            if (A_degre < A.coeffs.size())
                A.coeffs[A_degre] = false;
            A.getDegre();
        }

        return A;
    };


    friend polynome<T> operator/(const polynome<T>& temp1, const polynome<T>& temp2) {
        polynome<T> result(temp1);

        if (temp2.degre > temp1.degre) {
            result = false;
            return result;
        }

        if (temp2.degre < 0) {
            result = false;
            return result;
        }

        if (temp1.degre < 0) {
            result = false;
            return result;
        }

        result.coeffs.resize(temp1.degre - temp2.degre + 1);
        for (int k(0); k < result.coeffs.size(); ++k)
            result.coeffs[k] = false;

        polynome<T> A(temp1);
        polynome<T> B(temp2);
        A.getDegre();
        B.getDegre();
        while (A.degre >= B.degre) {
            result.coeffs[A.degre - B.degre] = A.coeffs[A.degre] / B.coeffs[B.degre];

            polynome<T> temp(A);
            temp.coeffs.resize(A.degre - B.degre + 1);
            for (int i(0); i < temp.coeffs.size(); ++i)
                temp.coeffs[i] = false;

            temp.coeffs[A.degre - B.degre] = A.coeffs[A.degre] / B.coeffs[B.degre];
            temp.getDegre();

            int A_degre = A.degre;
            A = A - (temp * B);
            if(A_degre < A.coeffs.size())
                A.coeffs[A_degre] = false;

            A.getDegre();
        }
        result.getDegre();

        return result;
    };

    friend polynome<T> operator+(const polynome<T>& temp1, const polynome<T>& temp2) {
        polynome<T> result;

        if (temp1.degre < 0)
            return temp2;
        if (temp2.degre < 0)
            return temp1;
        if (temp1.degre >= temp2.degre) {
            result.coeffs.resize(temp1.degre + 1);
            for (int i(0); i <= temp2.degre; ++i) {
                result.coeffs[i] = (temp1.coeffs[i] + temp2.coeffs[i]);
            }
            for (int i(temp2.degre + 1); i <= temp1.degre; ++i) {
                result.coeffs[i] = temp1.coeffs[i];
            }
        }
        else {
            result.coeffs.resize(temp2.degre + 1);
            for (int i(0); i <= temp1.degre; ++i) {
                result.coeffs[i] = (temp1.coeffs[i] + temp2.coeffs[i]);
            }
            for (int i(temp1.degre + 1); i <= temp2.degre; ++i) {
                result.coeffs[i] = temp2.coeffs[i];
            }

        }

        result.getDegre();
        return result;
    };

    friend polynome<T> operator-(const polynome<T>& temp1, const polynome<T>& temp2) {
        polynome<T> result(false);

        if (temp1.degre < 0)
            return (-temp2);
        if (temp2.degre < 0)
            return temp1;
        if (temp1.degre >= temp2.degre) {
            result.coeffs.resize(temp1.degre + 1);
            for (int i(0); i <= temp2.degre; ++i) {
                result.coeffs[i] = (temp1.coeffs[i] - temp2.coeffs[i]);
            }
            for (int i(temp2.degre + 1); i <= temp1.degre; ++i) {
                result.coeffs[i] = temp1.coeffs[i];
            }
        }
        else {
            result.coeffs.resize(temp2.degre + 1);
            for (int i(0); i <= temp1.degre; ++i) {
                result.coeffs[i] = (temp1.coeffs[i] - temp2.coeffs[i]);
            }
            for (int i(temp1.degre + 1); i <= temp2.degre; ++i) {
                result.coeffs[i] = - temp2.coeffs[i];
            }

        }
        result.getDegre();

        return result;
    };



    friend polynome<T> operator-(const polynome<T>& temp) {
        polynome<T> result(temp);

        for (int i(0); i < result.coeffs.size(); ++i)
            result.coeffs[i] = - result.coeffs[i];

        result.getDegre();
        return result;
    };

    template<class U> U operator()(const U& element) const{
        U result(element);
        result = false;
        U puissance(result);
        puissance = true;

        if (degre == 0)
            return result;

        for (int i(0); i <= degre; ++i) {
            result = result + (coeffs[i] * puissance);
            puissance = puissance * element;
        }

        return result;
    };


    friend bool operator==(const polynome<T>& a, const polynome<T>& b) {
        if (a.degre != b.degre)
            return false;
        for (int i(0); i <= a.degre; ++i)
            if (!(a.coeffs[i] == b.coeffs[i]))
                return false;
        return true;

    };

    friend bool operator>(const polynome<T>& a, const polynome<T>& b) {
        return (a.degre > b.degre);
    };



    operator bool() const {
        if (coeffs.size() == 0)
            return false;
        for (int i(0); i < coeffs.size(); ++i) {
            if ((bool) coeffs[i]) {
                return true;
            }
        }
        return false;
    };

    template<class U> operator polynome<U>()const {
        polynome<U> result;
        result.coeffs.resize(coeffs.size());
        for (int i(0); i < coeffs.size(); ++i) {
            result.coeffs[i] = (U)coeffs[i];
        }
        result.getDegre();
        return result;
    };


    void majListe() {
        int i(coeffs.size() - 1);
        while (i >= 1) {
            if (!((bool)coeffs[i])) {
                coeffs.erase(coeffs.begin() + i);
            }
            else
                break;
            --i;
        };

    };

    void getDegre() {
        if (coeffs.size() == 0)
            degre = -1;
        int i;
        for (i = (coeffs.size() - 1) ; i >= 0; --i) {
            if ((bool)coeffs[i]) {
                break;
            }
        }
        degre = i;
        majListe();
    };

    friend std::ostream& operator<<(std::ostream& os, const polynome<T>& element) {
        //        element.getDegre();
        os << "(";
        if (element.degre == -1)
            os << "0 *X^0)";
        else {
            for (int i(0); i < element.degre; ++i) {
                os << element.coeffs[i] << " *X^" << i << " + ";
            }
            os << element.coeffs[element.degre] << " *X^" << element.degre << ")";
        }
        return os;
    };

    friend T resultant(const polynome<T>& poly1, const polynome<T>& poly2) {
        T faux = poly1.coeffs[0];
        faux = false;
        matrice<T> m_matrice(poly1.degre + poly2.degre, faux);

        for (int i(0); i < poly2.degre; ++i)
            for (int j(0); j < poly1.coeffs.size(); ++j)
                m_matrice.coeffs[i][i + j] = poly1.coeffs[j];

        for (int i(0); i < poly1.degre; ++i)
            for (int j(0); j < poly2.coeffs.size(); ++j)
                m_matrice.coeffs[i + poly2.degre][i + j] = poly2.coeffs[j];

        return m_matrice.determinant();
    };

    //protected:
    int degre;
    std::vector<T> coeffs;
};


