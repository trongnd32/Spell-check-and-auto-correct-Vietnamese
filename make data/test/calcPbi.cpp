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
//#include <algorithm>
//
//using namespace std;
//
//map <wstring, int> MM;
//
//double D1 = 0.604;
//double D2 = 0.0507;
//double D3 = -0.52414;
//
//int main() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//
//	wifstream fin(L"./data new/uni.txt");
//	if (!fin) wcout << "Khong tim thay file input\n";
//	else fin.imbue(loc);
//
//	wstring input;
//	wofstream fout(L"bi with P.txt");
//	fout.imbue(loc);
//
//	while (fin.peek() != WEOF) {
//		getline(fin, input);
//
//		int n = input.length();
//
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
//			else frequency = frequency * 10 + input[i] - L'0';
//		}
//		MM[wstr] = frequency;
//	}
//	fin.close();
//
//	//-----------------------------------
//	wifstream fin2(L"./data new/bi.txt");
//	if (!fin2) wcout << "Khong tim thay file input\n";
//	else fin2.imbue(loc);
//
//	int count = 0;
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
//		int N1 = frequency;
//		int N2 = MM[wstr];
//
//		double D = D1;
//		if (N1 == 2) D = D2;
//		if (N1 >= 3) D = D3;
//
//		double P = max((N1 - D), 0.0) * 1.0 / N2;
//		fout.precision(17);
//		fout << fixed << wstr << L"," << wstr2 << L"," << frequency << L"," << P << endl;
//	}
//
//	fin2.close();
//	fout.close();
//}