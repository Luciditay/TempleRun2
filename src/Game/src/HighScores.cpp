#include "HighScores.hpp"

HighScores::HighScores(const glimac::FilePath filePath) : _scoresFilePath(filePath.dirPath() + "scores/highscores.txt")
{
	load();
}

void HighScores::load()
{
	std::ifstream file(_scoresFilePath);
	if (file)
	{
		size_t size;
		file >> size;
		size = std::min(size, size_t(10));
		std::vector<int> data(size);
		if (size == 0)
		{
			data.push_back(0);
		}
		for (size_t i = 0; i < size; i++)
		{
			file >> data[i];
		}
		_highScores = data;
	}
	else
	{
		std::cout << "Problème de chargement des Meilleurs Scores" << std::endl;
	}
}

void HighScores::save()
{
	if (_highScores[0])
	{
		std::ofstream file(_scoresFilePath);
		if (file)
		{
			size_t size = std::min(_highScores.size(), size_t(10));
			file << size << std::endl;
			for (int i = 0; i < int(size); i++)
			{
				file << _highScores[i] << std::endl;
			}
		}
		else
		{
			std::cout << "Problème de sauvegarde des Meilleurs Scores" << std::endl;
		}
	}
}

void HighScores::newScore(const int valueScore)
{
	bool insert = false;
	for (std::vector<int>::iterator it = _highScores.begin(); it < _highScores.end(); it++)
	{
		if (valueScore >= *it && !insert)
		{
			if (valueScore > *it)
			{
				_highScores.insert(it, valueScore);
			}
			insert = true;
		}
	}
	_highScores.resize(10);
}

int HighScores::getValue(const int position) const
{
	return _highScores[position];
}

int HighScores::getSize() const
{
	return _highScores.size();
}