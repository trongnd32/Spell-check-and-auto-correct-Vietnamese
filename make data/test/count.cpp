//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>    //_setmode()
//#include <string>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//#include <vector>
//
//#define __FORM1__
////#define __FORM2__
//
//
//using namespace std;
//
////read __form2__
//void splitWstr3(wstring wstr, wstring& word1, wstring& word2, wstring& word3, int& fre) {
//	int n = wstr.length();
//	word1 = L"";
//	word2 = L"";
//	word3 = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag++;
//		}
//		else {
//			if (flag == 0) word1 += wstr[i];
//			if (flag == 1) word2 += wstr[i];
//			if (flag == 2) word3 += wstr[i];
//			if (flag == 3) fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
////read __form1__
//void splitWstr2(wstring wstr, wstring& word1, wstring& word2, int& fre) {
//	int n = wstr.length();
//	word1 = L"";
//	word2 = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag++;
//		}
//		else {
//			if (flag == 0) word1 += wstr[i];
//			if (flag == 1) word2 += wstr[i];
//			if (flag == 2) fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
//void splitWstr1(wstring wstr, wstring& word1, int& fre) {
//	int n = wstr.length();
//	word1 = L"";
//	fre = 0;
//	int flag = 0;
//	for (int i = 0; i < n; i++) {
//		if (wstr[i] == L'"') continue;
//		if (wstr[i] == L',') {
//			flag++;
//		}
//		else {
//			if (flag == 0) word1 += wstr[i];
//			if (flag == 1) fre = fre * 10 + wstr[i] - L'0';
//		}
//	}
//}
//
//void count() {
//	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
//	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
//	// nhớ chuyển font của console sang Consolas (size 16)
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//	// lưu file tiếng Việt (UTF-8 without BOM)
//
//	// đọc file tiếng Việt (định dạng UTF-8 without BOM)
//	wifstream fin1(L"./data new/tri.txt");
//	if (!fin1) {
//		wcout << L"Không thể đọc file tri1.txt\n";
//	}
//	else { fin1.imbue(loc); }
//
//#ifdef __FORM1__
//	//fout << L"word1, frequency" << endl;
//#endif // __FORM1__
//
//
//	wstring wstr1 = L"";
//
//	wstring word1 = L"";
//	wstring word2 = L"";
//	wstring word3 = L"";
//
//	int fre = 0;
//
//	int read = 0;
//	int count1 = 0;
//	int count2 = 0;
//	int count3 = 0;
//	int count4 = 0;
//	int count = 0;
//
//	while (fin1.peek() != WEOF) {
//		getline(fin1, wstr1);
//		splitWstr3(wstr1, word1, word2, word3, fre);
//		//splitWstr2(wstr1, word1, word2, fre);
//		//splitWstr1(wstr1, word1, fre);
//		if (fre == 1) count1++;
//		if (fre == 2) count2++;
//		if (fre == 3) count3++;
//		if (fre == 4) count4++;
//		count++;
//	}
//	fin1.close();
//
//	cerr << count << endl << count1 << endl << count2 << endl << count3 << endl << count4;
//}
//
//int wmain(int argc, wchar_t* argv[]) {
//	count();
//}