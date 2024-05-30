#pragma once
#include "ECS.h"

class Func
{
public:
	static std::vector<std::string> SplitLine(std::string line)
	{
		std::vector<std::string> words;
		std::string newWord = "";

		for (auto x : line)
		{
			if (x != ' ')
			{
				newWord += x;
			}
			else
			{
				words.push_back(newWord);
				newWord = "";
			}
		}
		words.push_back(newWord);
		return words;
	}
};