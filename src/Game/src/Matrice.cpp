#include "Matrice.hpp"

Matrice::Matrice(const std::string &fileMatrice, int beginFile, int lenghtFirstPart)
    : m_beginningFile(beginFile), m_lenghtFirstPart(lenghtFirstPart)
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
    for (int i = 0; i < m_Matrice.size(); i++)
    {
        for (int j = 0; j < m_Matrice.at(i).size(); j++)
        {
            std::cout << m_Matrice.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
}

void Matrice::loadFromFile(const std::string &Path)
{

    std::ifstream matFile(Path);
    if (!matFile)
    {
        std::cout << "Le fichier " << Path << " n'existe pas"
                  << "\n";
    }
    std::vector<int> ligneMatrice = {1, 2, 3};
    int number;
    int rowCount = 0;
    int lineCount = 0;
    int segmentCount = 0;
    bool lenghtFirstPartComputed = false;

    if (m_beginningFile != 0)
    {
        std::string ligne;
        for (int i = 0; i < m_beginningFile; i++)
        {
            getline(matFile, ligne); // On saute à la bonne partie du fichier
        }
        // matFile.ignore(); // On change de mode pour passer en lecture par "mot"
    }

    while (matFile >> number)
    {
        if (number == 10 || number == 20 || number == 30)
        {
            segmentCount++;
        }

        if (segmentCount == 9 && lenghtFirstPartComputed == false)
        {
            m_lenghtFirstPart = lineCount + 1;
            lenghtFirstPartComputed = true;
        }
        if (rowCount == 3)
        {
            m_Matrice.push_back(ligneMatrice);
            rowCount = 0;
            lineCount++;
            if (segmentCount == 9)
            {
                break; // Si on arrive à deux croisements, on sort de la boucle
            }
        }
        ligneMatrice.at(rowCount) = number;
        rowCount++;
    }
    std::cout << "a" << m_lenghtFirstPart << std::endl;
    toString();
}
