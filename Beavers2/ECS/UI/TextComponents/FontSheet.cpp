#include "FontSheet.h"


FontSheet::FontSheet(std::string file_name, int cur_w, int cur_h, int cur_l_in_s)
{
	file_to_operate = file_name;
	l_height = cur_h;
	l_width = cur_w;
	letters_in_string = cur_l_in_s;
}
void FontSheet::Divide_fontlist()
{
	//��� ��� ��� �����-�� ����� ���� �������� ��������� �������� �� ������ � �������� ��� �������� � new F_char[x]
}
