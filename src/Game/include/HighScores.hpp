#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <glimac/FilePath.hpp>

/// \class Highscores
/// \brief defining class that can read and write in the highscores file
class HighScores {
    public:
    /// \brief constructor
    /// \param filePath : application path
    HighScores(const glimac::FilePath filePath);
    /// \brief load the highscore from the file
    const void load();
    /// \brief save the highscore in the file
    const void save();
    /// \brief put a new score in the highscores vector if it is good enough
    /// \param valueScore : value of the new score
    const void newScore(const int valueScore);
    /// \brief return the value at a given position
    /// \param position : index of the value needed
    const int getValue(const int position) const;
    /// \brief give the size of the highscore vector
    const int getSize() const;

    private:
    const std::string _scoresFilePath; /*!< highscores file path */ 
    std::vector<int> _highScores; /*!< loaded vector of best scores */ 
};