#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Matrice{
    public:
        Matrice(const std::string &fileMatrice);

        std::vector< std::vector <int> > getMatrice(); 
        void toString();

    private:
        void loadFromFile(const std::string &Path);

    private:
        std::vector< std::vector <int> > m_Matrice;
};