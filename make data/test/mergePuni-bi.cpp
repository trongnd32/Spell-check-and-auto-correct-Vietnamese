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
//double D1 = 0.49736;
//double D2 = -0.01649;
//double D3 = -0.3655;
//
//int main() {
//
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stdin), _O_WTEXT);
//
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//
//	wifstream fin(L"./data new/uni with P.txt");
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
//		double Pbkn = 0;
//		int flag = 0;
//
//		for (int i = 0; i < n; i++) {
//			if (input[i] == L',') {
//				flag++;
//				continue;
//			}
//			if (flag == 0) wstr += input[i];
//			if (flag == 1) frequency = frequency * 10 + input[i] - L'0';
//			if (flag == 2) {
//				Pbkn = stod(input.substr(i));
//				break;
//			}
//		}
//
//		MM[wstr] = Pbkn;
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
//		if (wstr.compare(wstrOld) != 0) {
//			MM2[wstrOld] = sumP;
//			sumP = MM[wstr2];
//			wstrOld = wstr;
//		}
//		else sumP += MM[wstr2];
//
//		if (fin2.peek() == WEOF) MM2[wstr] = sumP;
//
//	}
//	fin2.close();
//
//	wifstream fin3(L"./data new/uni with P.txt");
//	if (!fin3) wcout << "Khong tim thay file input\n";
//	else fin3.imbue(loc);
//
//	wofstream fout(L"./data new/uni with 2 P.txt");
//	fout.imbue(loc);
//
//	while (fin3.peek() != WEOF) {
//		getline(fin3, input);
//
//		int n = input.length();
//
//		wstring wstr = L"";
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
//			if (flag == 1) frequency = frequency * 10 + input[i] - L'0';
//			if (flag == 2) {
//				Pbkn = stod(input.substr(i));
//				break;
//			}
//		}
//
//		fout.precision(17);
//		fout << fixed << wstr << L"," << frequency << L"," << Pbkn << L"," << MM2[wstr] << endl;
//	}
//	fin3.close();
//
//	fout.close();
//}