#include "Matrice.hpp"

Matrice::Matrice(const std::string &fileMatrice, int beginFile, int lenghtFirstPart, int lenghtSecondPart)
    : m_beginningFile(beginFile), m_lenghtFirstPart(lenghtFirstPart), m_lenghtSecondPart(lenghtSecondPart)
{
    loadFromFile(fileMatrice);
}

std::vector<std::vector<int>> Matrice::getMatrice()
{
    return m_Matrice;
}

void Matrice::toString()
{
    std::cout << "STARTMATRIX" << std::endl;
    for (unsigned int i = 0; i < m_Matrice.size(); i++)
    {
        for (unsigned int j = 0; j < m_Matrice.at(i).size(); j++)
        {
            std::cout << m_Matrice.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
}

bool Matrice::isZero(int i, int j)
{
    std::cout << m_Matrice.at(i).at(j) << std::endl;
    if (m_Matrice.at(i).at(j) == 0)
    {
        return true;
    }
    return false;
}

void Matrice::loadFromFile(const std::string &Path)
{

    std::ifstream matFile(Path);
    if (!matFile)
    {
        std::cout << "Le fichier " << Path << " n'existe pas"
                  << "\n";
    }
    std::vector<int> ligneMatrice(12, 0);
    int number;
    int rowCount = 0;

    while (matFile >> number)
    {
        if (rowCount == 12)
        {
            std::cout << number << std::endl;
            m_Matrice.push_back(ligneMatrice);
            rowCount = 0;
        }
        ligneMatrice.at(rowCount) = number;
        rowCount++;
    }
    // ligneMatrice.at(rowCount) = number;
    m_Matrice.push_back(ligneMatrice);
    toString();
}
