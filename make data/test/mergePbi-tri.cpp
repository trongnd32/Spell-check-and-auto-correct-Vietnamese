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
//map <wstring, double> MM;
//map <wstring, double> MM2;
//
//double D1 = 0.493;
//double D2 = 0.0157;
//double D3 = -0.3783;
//
//int main() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//
//	wifstream fin(L"./data new/bi with P.txt");
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
//		wstring wstr2 = L"";
//		int frequency = 0;
//		double Pbkn = 0;
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
//			if (flag == 3) {
//				Pbkn = stod(input.substr(i));
//				break;
//			}
//		}
//
//		wstring ww = wstr + L' ' + wstr2;
//
//		MM[ww] = Pbkn;
//	}
//	fin.close();
//
//	//-----------------------------------
//	wifstream fin2(L"./data new/tri.txt");
//	if (!fin2) wcout << "Khong tim thay file input\n";
//	else fin2.imbue(loc);
//
//	int count = 0;
//
//	wstring wwOld = L"-1";
//	double sumP = 0.0;
//
//	while (fin2.peek() != WEOF) {
//		count++;
//		if (count % 500000 == 0) cerr << "tri: " << count << endl;
//
//		getline(fin2, input);
//
//		int n = input.length();
//
//		wstring wstr = L"";
//		wstring wstr2 = L"";
//		wstring wstr3 = L"";
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
//			if (flag == 2) wstr3 += input[i];
//			if (flag == 3) frequency = frequency * 10 + input[i] - L'0';
//		}
//
//		wstring ww = wstr + L' ' + wstr2;
//		wstring ww2 = wstr2 + L' ' + wstr3;
//
//		if (ww.compare(wwOld) != 0) {
//			MM2[wwOld] = sumP;
//			sumP = MM[ww2];
//			wwOld = ww;
//		}
//		else sumP += MM[ww2];
//
//		if (fin2.peek() == WEOF) MM2[ww] = sumP;
//
//	}
//	fin2.close();
//
//	wifstream fin3(L"./data new/bi with P.txt");
//	if (!fin3) wcout << "Khong tim thay file input\n";
//	else fin3.imbue(loc);
//
//	wofstream fout(L"./data new/bi with 2 P.txt");
//	fout.imbue(loc);
//
//	count = 0;
//	while (fin3.peek() != WEOF) {
//
//		count++;
//		if (count % 500000 == 0) cerr << "bi2P: " << count << endl;
//
//		getline(fin3, input);
//
//		int n = input.length();
//
//		wstring wstr = L"";
//		wstring wstr2 = L"";
//		int frequency = 0;
//		double Pbkn = 0;
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
//			if (flag == 3) {
//				Pbkn = stod(input.substr(i));
//				break;
//			}
//		}
//
//		wstring ww = wstr + L' ' + wstr2;
//
//		fout.precision(17);
//		fout << fixed << wstr << L"," << wstr2 << L"," << frequency << L"," << Pbkn << L"," << MM2[ww] << endl;
//	}
//	fin3.close();
//
//	fout.close();
//}