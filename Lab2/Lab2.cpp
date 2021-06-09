#include <iostream>
#include <windows.h>
#include "haffman.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	haffman hff;
	string input;
	getline(cin, input);
	int inVolume = input.length() * 8;
	cout << "Объём памяти, занимаемый входной строкой: " << inVolume << " бит." << endl;
	hff.parser(input);	
	hff.print_freq_list();
	hff.Encode();
	hff.print_char_codes();
	hff.print_encoded_expr();
	string dec = hff.getDecode();
	int outVolume = dec.length() - input.length();
	cout << "Объём памяти, занимаемый зашифрованной строкой: " << outVolume << " бит." << endl;
	double koeff = (inVolume * 1.0) / (outVolume * 1.0);
	cout << "Коэффициент сжатия: " << koeff << endl;
	return 0;
}