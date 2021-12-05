#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <glimac/FilePath.hpp>

class HighScores {
    public:
    HighScores(const glimac::FilePath filePath);
    const void load();
    const void save();
    const void newScore(const int valueScore);
    const int getValue(const int position) const;
    const int getSize() const;

    private:
    const std::string _scoresFilePath;
    std::vector<int> _highScores;
};