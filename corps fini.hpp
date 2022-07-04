#pragma once
#include <iostream>

 class corps {
public:
    corps(int val, int p1) {
        x = val % p1;
        if (x < 0)
            x = x + p1;
        p = p1;
    };

    corps(bool test,int p1) {
        x = test;
        p = p1;
    };

    corps(const corps& copie) {
        p = copie.p;
        x = (copie.x % p);
    };

    corps() : x(0), p(0) {};

    corps(bool test) : x(test), p(1) {};

    corps& operator=(bool test) {
        x = test;
        return *this;
    };

    inline corps modulo(int u) const {
        int resultat = u % p;
        if (resultat < 0)
            return corps(resultat + p, p);
        else
            return corps(resultat, p);
    }

    friend corps operator*(const corps& temp1, const corps& temp2) {
        return temp1.modulo(temp1.x * temp2.x);
    };

    friend corps operator*(int scalaire, const corps& temp) {
        return temp.modulo(scalaire * temp.x);
    };


    friend corps operator+(const corps& temp1, const corps& temp2) {
        return temp1.modulo(temp1.x + temp2.x);
    };

    friend corps operator-(const corps& temp1, const corps& temp2) {
        return temp1.modulo(temp1.x - temp2.x);
    };

    friend corps operator-(const corps& temp1) {
        return temp1.modulo(-temp1.x);
    };

    friend corps operator/(const corps& temp1, const corps& temp2) {
        int p = temp1.p;
        int a, b, ua, va, ub, vb, c,q,wa,wb;
        if ((temp2.x % p) == 0)
            return corps(0, p);
            
        a = p;
        b = temp2.x;
        ua = 1;
        vb = 1;
        ub = 0;
        va = 0;
        c = 1;
        while (c != 0)
        {
            c = a % b;
            q = a / b;
            wa = ua - q * va;
            wb = ub - q * vb;
            a = b;
            b = c;
            ua = va;
            ub = vb;
            va = wa;
            vb = wb;
        }


        return temp1.modulo(temp1.x * ub);
    };

    friend corps operator%(const corps& temp1, const corps& temp2) {
        corps result = temp1;
        result = false;
        return result;
    }

    operator bool() const {
        if ((x%p) == 0)
            return false;
        else
            return true;
    };

    friend std::ostream& operator<<(std::ostream& os, const corps& element) {
        os <<element.x ;
        return os;
    }

    friend bool operator==(const corps& temp1, const corps& temp2) {
        return ((temp1.x == temp2.x) && (temp1.p == temp2.p));
    }

	int x;
    int p;
};