// algebre.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "composition.hpp"

using namespace std;

template rationnel<long long>;
template polynome<rationnel<long long>>;
template rationnel<polynome<rationnel<long long>>>;


//template matrice<double>;


//template rationnel<polynome<double>>;
//template matrice< rationnel<polynome<double>>>;

//fraction

int main()
{
    long question;

    /*
//    polynome<rationnel<long>> mon_polynome(mon_vecteur);
    vector<rationnel<long>> mon_vecteur1 = { rationnel<long>(6,1),rationnel<long>(5,1), rationnel<long>(1,1) }; //X^2 +5X +6
    vector<rationnel<long>> mon_vecteur2 = { rationnel<long>(3,1),rationnel<long>(1,1) }; //X+3
    polynome<rationnel<long>> mon_poly1(mon_vecteur1);
    polynome<rationnel<long>> mon_poly2(mon_vecteur2);
    rationnel<polynome<rationnel<long>>> ma_frac(mon_poly1,mon_poly2);

    cin >> question;
    polynome<rationnel<long>> m_pgcd = ma_frac.PGCD();
    //polynome<rationnel<long>> m_pgcd = (mon_poly1 % mon_poly2);

    cout << ma_frac << endl;
    cout << m_pgcd << endl;
    cin >> question;
    ma_frac.simplifier();
    cin >> question;
    cout << ma_frac << endl;
    cout << "fin simplifier" << endl;
    cout << ma_frac * ma_frac << endl;
    cin >> question;

    */


    /*


    cout << endl<<m_pgcd.degre<<" PGCD degre"<<endl;

    ma_frac.simplifier();

    cout << ma_frac << endl;
    //    ma_frac.denominateur.majListe();

    cout << endl << "fraction simplifiee : degres : " << ma_frac.numerateur.degre << " et " << ma_frac.denominateur.degre << endl;

    cin >> question;

    cout << mon_poly1(mon_poly1) << endl;
    cout << "composition" << endl;
    cin >> question;
    cout << ma_frac(ma_frac) << endl;
    cout << "composition fraction" << endl;
    cin >> question;

    cout << derivee(ma_frac) << endl;
    cout << "derivee " << endl;
    cin >> question;

    matrice<rationnel<long>> ma_matrice(true, 10);
    cin >> question;

    */


    
    vector<vector<rationnel<long long>>> vec = { {rationnel<long long>(5,4) , rationnel<long long>(2,11) , rationnel<long long>(3,1) } ,
        { rationnel<long long>(4,1) , rationnel<long long>(5,1) , rationnel<long long>(6,1) } ,
        {rationnel<long long>(7,1) , rationnel<long long>(8,1) , rationnel<long long>(9,1)} };
    matrice<rationnel<long long>> m_matrice(vec);

    //    polynome<rationnel<long>> m_poly = m_matrice.polynomeCaracteristique();
    auto det = m_matrice.determinant();
    cout << "determinant " << endl << det << endl << endl;
    cin >> question;

    auto inv = m_matrice.inverse();
    cout << "inverse :" << endl << inv << endl;
    cin >> question;

    polynome<rationnel<long long>> polyCar = m_matrice.polynomeCaracteristique();
    cin >> question;


    cout << "determinant " << endl <<  det << endl << endl;
    cout << "inverse :"<<endl << inv << endl;
    cout << "polynome Caracteristique" << endl << polyCar << endl << endl;
    cout << "matrice * son inverse" << endl << m_matrice * inv << endl;
    cout << "polynome_car(matrice)" << endl << polyCar(m_matrice) << endl << endl;
    cout << "derivee int " << endl << derivee(5) << endl << endl;
    cout << "derivee poly" << endl << derivee(polyCar) << endl << endl;

    cin >> question;
    
//    cout << (double )rationnel<long>(3, 7) << endl << endl;
    cout << (polynome<double>) polyCar << endl << endl;
    cin >> question;

    /*
    vector<vector<corps>> vec = { { corps(1,11), corps(2,11), corps(3,11)},{corps(5,11),corps(7,11),corps(8,11)}, {corps(4,11),corps(2,11),corps(1,11) } };
    matrice<corps> m_matrice(vec);
    
    auto det = m_matrice.determinant();
    auto inv = m_matrice.inverse();
    auto polyCar = m_matrice.polynomeCaracteristique();

    cout << det << endl << endl;
    cout << inv << endl;
    cout << polyCar << endl;
    cout << m_matrice * inv << endl;
    cin >> question;
    */

        /*
        vector<vector<double>> vec = { {5.,2.,3.},{4.,5.,6.},{7.,8.,9.} };
        matrice<double> m_matrice(vec);

        double det = m_matrice.determinant();
        auto inv = m_matrice.inverse();
        auto polyCar = m_matrice.polynomeCaracteristique();
        cout << det << endl << endl;
        cout << inv << endl;

        cout << polyCar << endl;

    //    long question;
        cin >> question;
        */

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

/*
template<class U> U operator()(const U& element) {

    J'ai cet operateur dans la classe polynome. Je peux donc faire des polynomes de polynomes P(Q(X)). Ca utilise juste la multiplication et l'addition des polynomes, et la multiplication par un scalaire.Mais lors de la compilation il dit qu'il ne trouve pas operator() ...
*/