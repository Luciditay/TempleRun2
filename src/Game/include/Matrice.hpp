#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Matrice
{
public:
    Matrice(const std::string &fileMatrice, int beginFile = 0, int lenghtFirstPart = 0);

    std::vector<std::vector<int>> getMatrice();
    void toString();

private:
    void loadFromFile(const std::string &Path);

private:
    std::vector<std::vector<int>> m_Matrice;
    int m_beginningFile;
    int m_lenghtFirstPart;
};