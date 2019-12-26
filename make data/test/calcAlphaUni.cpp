//#include <cstring>
//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>  
//#include <string>
//#include <vector>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//#include <map>
//
//using namespace std;
//
//map <wstring, double> UPbkb2;
//map <wstring, int> UFre;
//map <wstring, int> BiFre1;
//map <wstring, int> BiFre2;
//map <wstring, int> BiFre3;
//
//const double D[4][4] = {
//	{0,0,0,0},
//	{0,0.493,0.0157,-0.3783},
//	{0,0.603,0.052,-0.14},
//	{0,0.745,0.131,-0.5794},
//};
//
//int main() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//
//	wifstream fin(L"./data new/uni with 2 P.txt");
//	if (!fin) wcout << "Khong tim thay file input\n";
//	else fin.imbue(loc);
//
//	wstring input;
//
//	while (fin.peek() != WEOF) {
//		getline(fin, input);
//
//		int n = input.length();
//
//		wstring wstr = L"";
//		int frequency = 0;
//		string P1 = "";
//		string P2 = "";
//		double Pbkn = 0;
//		double Pbkn2 = 0;
//		int flag = 0;
//
//		for (int i = 0; i < n; i++) {
//			if (input[i] == L',') {
//				flag++;
//				continue;
//			}
//			if (flag == 0) wstr += input[i];
//			if (flag == 1) frequency = frequency * 10 + input[i] - L'0';
//			if (flag == 2) P1 += input[i];
//			if (flag == 3) P2 += input[i];
//		}
//		Pbkn = stod(P1);
//		Pbkn2 = stod(P2);
//
//		UPbkb2[wstr] = Pbkn2;
//		UFre[wstr] = frequency;
//	}
//	fin.close();
//
//	-----------------------------------
//	wifstream fin2(L"./data new/bi.txt");
//	if (!fin2) wcout << "Khong tim thay file input\n";
//	else fin2.imbue(loc);
//
//	int count = 0;
//
//	wstring wstrOld = L"-1";
//	double sumP = 0.0;
//
//	while (fin2.peek() != WEOF) {
//		count++;
//		if (count % 50000 == 0) cerr << count << endl;
//
//		getline(fin2, input);
//
//		int n = input.length();
//
//		wstring wstr2 = L"";
//		wstring wstr = L"";
//		int frequency = 0;
//		int flag = 0;
//
//		for (int i = 0; i < n; i++) {
//			if (input[i] == L',') {
//				flag++;
//				continue;
//			}
//			if (flag == 0) wstr += input[i];
//			if (flag == 1) wstr2 += input[i];
//			if (flag == 2) frequency = frequency * 10 + input[i] - L'0';
//		}
//
//		if (frequency == 1) BiFre1[wstr]++;
//		if (frequency == 2) BiFre2[wstr]++;
//		if (frequency >= 3) BiFre3[wstr]++;
//	}
//	fin2.close();
//
//	------------------------------------------------
//
//	wifstream fin3(L"./data new/uni with 2 P.txt");
//	if (!fin3) wcout << "Khong tim thay file input\n";
//	else fin3.imbue(loc);
//
//	wofstream fout1(L"./data new/uni with 2 P alpha.txt");
//	fout1.imbue(loc);
//	wofstream fout2(L"./data new/uni with alpha only.txt");
//	fout2.imbue(loc);
//
//	while (fin3.peek() != WEOF) {
//		getline(fin3, input);
//
//		int n = input.length();
//
//		wstring wstr = L"";
//		int frequency = 0;
//		string P1 = "";
//		string P2 = "";
//		double Pbkn = 0;
//		double Pbkn2 = 0;
//		int flag = 0;
//
//		for (int i = 0; i < n; i++) {
//			if (input[i] == L',') {
//				flag++;
//				continue;
//			}
//			if (flag == 0) wstr += input[i];
//			if (flag == 1) frequency = frequency * 10 + input[i] - L'0';
//			if (flag == 2) P1 += input[i];
//			if (flag == 3) P2 += input[i];
//		}
//
//		int fre1 = BiFre1[wstr];
//		int fre2 = BiFre2[wstr];
//		int fre3 = BiFre3[wstr];
//
//		int freUni = UFre[wstr];
//		double P2Uni = UPbkb2[wstr];
//
//		double alpha = (1.0 - (fre1 + fre2 + fre3 - D[2][1] * fre1 - D[2][2] * fre2 - D[2][3] * fre3) * 1.0 / freUni) * 1.0 / (1.0 - P2Uni);
//
//		fout1.precision(17);
//		fout1 << fixed << input << L"," << alpha << endl;
//
//		fout2.precision(17);
//		fout2 << fixed << alpha << endl;
//	}
//	fin3.close();
//
//	fout1.close();
//	fout2.close();
//}