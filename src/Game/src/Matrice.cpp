#include "Matrice.hpp"

Matrice::Matrice(const std::string &fileMatrice){
    loadFromFile(fileMatrice);
}

std::vector< std::vector <int> > Matrice::getMatrice(){
    return m_Matrice;
}

void Matrice::toString(){
    for (int i =0; i < m_Matrice.size(); i++){
        for (int j=0; j<m_Matrice.at(i).size(); j++){
            std::cout << m_Matrice.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
}

void Matrice::loadFromFile(const std::string &Path){

    std::ifstream matFile(Path);
    if (!matFile){
        std::cout << "Le fichier " << Path << " n'existe pas"<< "\n";
    }
    std::vector<int> ligneMatrice = {1, 2, 3};
    int number;
    int i=0;

    while (matFile >> number){
        if (i==3){
            m_Matrice.push_back(ligneMatrice);
            i=0;
        }
        ligneMatrice.at(i) = number;
        i++;
    }
    m_Matrice.push_back(ligneMatrice);
}

