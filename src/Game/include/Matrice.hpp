#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Matrice
{
public:
    Matrice(const std::string &fileMatrice, int beginFile = 0, int lenghtFirstPart = 0, int lenghtSecondPart = 0);

    std::vector<std::vector<int>> getMatrice();
    void toString();

    int getLenghtFirstPart()
    {
        return m_lenghtFirstPart;
    }

    int getLenghtSecondPart()
    {
        return m_lenghtSecondPart;
    }

    bool isZero(int i, int j);

private:
    void loadFromFile(const std::string &Path);

private:
    std::vector<std::vector<int>> m_Matrice;
    int m_beginningFile;
    int m_lenghtFirstPart;
    int m_lenghtSecondPart;
};