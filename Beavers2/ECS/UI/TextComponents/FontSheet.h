#pragma once
#include <iostream>
#include "Texture.h"

class F_char
{
private: 
	int index;
	Texture char_texture;
public: 
	F_char();
	void draw_character();
};
class FontSheet
{
private: 
	std::string file_to_operate;
	int l_width;
	int l_height;
	int letters_in_string;
	std::vector<F_char> F_str; // OR HOWEVER THIS IS MADE
public: 
	FontSheet(std::string file_name, int cur_w, int cur_h, int cur_l_in_s);
	~FontSheet();
	void Divide_fontlist();

};