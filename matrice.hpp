#pragma once
#include <vector>
#include <iostream>
#include "polynome.hpp"
#include "rationnel.hpp"

template<typename T> class polynome;
template<typename T> class matrice;
template<typename T> class rationnel;


template<class T> class matrice {
public :

	friend matrice<T> derivee(const matrice<T>& element) {
		matrice<T> result(element);
		for (int i(0); i < element.taille; ++i)
			for (int j(0); j < element.taille; ++j)
				result.coeffs[i][j] = derivee(result.coeffs[i][j]);
		return result;
	};

	matrice(int m_taille, T element) : coeffs(m_taille, std::vector<T>(m_taille, element)), taille(m_taille) {
	};

	matrice(matrice<T> const& copie) {
		taille = copie.taille;
		coeffs = copie.coeffs;
	};

	matrice(const std::vector<std::vector<T>>& vec) : coeffs(vec), taille(vec.size()) {
	};

	matrice() : taille(0), coeffs(0, std::vector<T>(0, false)) {};

	operator bool() const {
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				if ((bool)coeffs[i][j])
					return true;
		return false;
	};

	template<class U> operator matrice<U>()const {
		matrice<U> result(*this);

		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				result.coeffs[i][j] = (U)coeffs[i][j];

		return result;
	};


	matrice<T>& operator=(bool test) {
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				coeffs[i][j] = false;
		if (test)
			for (int i(0); i < taille; ++i)
				coeffs[i][i] = true;
		return *this;

	};

	template<class U> friend matrice<T> operator*(U scalaire, const matrice<T>& m_matrice) {
		matrice<T> result(m_matrice);
		for (int i(0); i < result.taille; ++i)
			for (int j(0); j < result.taille; ++j)
				result.coeffs[i][j] = scalaire * result.coeffs[i][j];
		return result;
	};

	matrice<T> operator*(const matrice<T>& autre) const {
		T faux = coeffs[0][0];
		faux = false;

		if (taille != autre.taille)
			return matrice<T>(taille,faux);
		matrice<T> result(taille,faux);
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j) {
				T somme(faux);
				for (int k(0); k < taille; ++k)
					somme = somme + (coeffs[i][k] * autre.coeffs[k][j]);
				result.coeffs[i][j] = somme;
			}
		return result;
	};

	matrice<T> operator+(const matrice<T>& autre) const {
		T faux = coeffs[0][0];
		faux = false;

		if (taille != autre.taille)
			return matrice<T>(taille,faux);
		matrice<T> result( taille,faux);
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				result.coeffs[i][j] = coeffs[i][j] + autre.coeffs[i][j];
		return result;
	};

	matrice<T> operator-(const matrice<T>& autre) const {
		T faux = coeffs[0][0];
		faux = false;
		if (taille != autre.taille)
			return matrice<T>(taille,faux);

		matrice<T> result(taille,faux);
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				result.coeffs[i][j] = coeffs[i][j] - autre.coeffs[i][j];
		return result;
	};

	friend 	matrice<T> operator-(const matrice<T>& element) {
		matrice<T> result(element.taille,false);
		for (int i(0); i < result.taille; ++i)
			for (int j(0); j < result.taille; ++j)
				result.coeffs[i][j] = -element.coeffs[i][j];
		return result;
	};

	T determinant() const {
		T vrai = coeffs[0][0];
		vrai = true;

		matrice<rationnel<T>> m_matrice(taille,rationnel<T>(vrai,vrai));
		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				m_matrice.coeffs[i][j] = rationnel<T>(coeffs[i][j], vrai);


		rationnel<T> det(vrai,vrai);

		std::cout << "avant boucle determinant" << std::endl;
		int question;
		std::cin >> question;

		for (int i(0); i < taille; ++i) {
			int j;
			for (j=i; j < taille; ++j) {
				if ((bool) coeffs[i][j])
					break;
			}
			if (j == taille)
				return (vrai = false);
			if (!((bool)coeffs[i][j]))
				return (vrai = false);
			if (i != j) {
				m_matrice.echangerLigne(i, j);
				det = - det;
			}
			for (j = i + 1; j < taille; ++j) {
				m_matrice.ajouterLigne(i, j, ((- m_matrice.coeffs[j][i]) / m_matrice.coeffs[i][i]));
			}
			
		}

		std::cout << "avant calcul det (multiplication)" << std::endl << std::endl;
		std::cout << m_matrice << std::endl;	
		std::cin >> question;

		for (int i(0); i < taille; ++i)
			det = (det * m_matrice.coeffs[i][i]);


		std::cout << "avant fraction determinant" << std::endl;
		std::cout << det;
		std::cin >> question;
		return (det.numerateur / det.denominateur);


	};

	void echangerLigne(int i, int j) {
		if ((i < 0) || (i >= taille) || (j < 0) || (j >= taille))
			return;
		if (i == j)
			return;
		for (int k(0); k < taille; ++k) {
			T temp = coeffs[i][k];
			coeffs[i][k] = coeffs[j][k];
			coeffs[j][k] = temp;
		}
		return;
	};

	void ajouterLigne(int i, int j, T coefficient) { // ajouter ligne i * coeffs à la ligne j ...
		if ((i < 0) || (i >= taille) || (j < 0) || (j >= taille))
			return;
		if (i == j)
			return;
		for (int k(0); k < taille; ++k) {
			coeffs[j][k] = coeffs[j][k] + (coefficient * coeffs[i][k]);
		}
		return;
	};

	void multiplierLigne(int i, T coefficient) {
		for (int j(0); j < taille; ++j)
			coeffs[i][j] = coefficient * coeffs[i][j];
	};

	matrice<T> inverse() const {
		T vrai = coeffs[0][0];
		vrai = true;

		matrice<T> m_matrice(*this);
		matrice<T> resultat(taille, vrai);
		resultat = true; //identité

		for (int i(0); i < taille; ++i) {
			int j(i);
			for (j = i; j < taille; ++j)
				if ((bool)coeffs[i][j])
					break;

			if (j == taille) {
				return (resultat=false);
			}
			if (!((bool)coeffs[i][j])) {
				return (resultat = false);
			}
			if (i != j) {
				m_matrice.echangerLigne(i, j);
				resultat.echangerLigne(i, j);
			}
			resultat.multiplierLigne(i, vrai / m_matrice.coeffs[i][i]);
			m_matrice.multiplierLigne(i, vrai / m_matrice.coeffs[i][i]);

			for( j=0; j < taille; ++j) {
				if (j == i)
					continue;
				resultat.ajouterLigne(i, j, -m_matrice.coeffs[j][i]);
				m_matrice.ajouterLigne(i, j, -m_matrice.coeffs[j][i]);
			}
		}

		return resultat;
	};


	polynome<T> polynomeCaracteristique() const {
		T faux = coeffs[0][0];
		faux = false;

		T mvrai = faux;
		mvrai = true;
		mvrai = -mvrai;

		polynome<T> m_poly(faux);
		matrice<polynome<T>> m_matrice(taille, m_poly);

		for (int i(0); i < taille; ++i)
			for (int j(0); j < taille; ++j)
				if (i != j)
					m_matrice.coeffs[i][j] = polynome<T>(coeffs[i][j]);
				else
					m_matrice.coeffs[i][j] = polynome<T>(std::vector<T>{ coeffs[i][j], mvrai });

		std::cout << "avant det (polycar)" << std::endl;
		std::cout << m_matrice << std::endl;
		int question;
		std::cin >> question;

		return (m_matrice.determinant());

	};

	friend std::ostream& operator<<(std::ostream& os, const matrice<T>& element) {
		os << "{ ";
		for (int i(0); i < element.taille; ++i) {
			os << "{ ";
			for (int j(0); j < element.taille - 1; ++j)
				os << element.coeffs[i][j] << " , ";
			os << element.coeffs[i][element.taille - 1] << " } ";
			if (i < element.taille -1)
				os <<std::endl;
		}
		os << "}" << std::endl;
		return os;
	};


	int taille;
	std::vector < std::vector< T>> coeffs;
};

template matrice<rationnel<long long>>;
//template matrice<double>;
