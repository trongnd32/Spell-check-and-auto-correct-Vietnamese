//#include <iostream>
//#include <fcntl.h> //_O_WTEXT
//#include <io.h>    //_setmode()
//#include <string>
//#include <locale>
//#include <codecvt> //possible C++11?
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//int wmain(int argc, wchar_t* argv[])
//{
//	_setmode(_fileno(stdout), _O_WTEXT); //needed for output
//	_setmode(_fileno(stdin), _O_WTEXT); //needed for input
//	// nhớ chuyển font của console sang Consolas (size 16)
//	locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
//	// lưu file tiếng Việt (UTF-8 without BOM)
//	wstring wstr;
//
//	// đọc file tiếng Việt (định dạng UTF-8 without BOM)
//	wifstream fin(L"VNTQcorpus-big.txt");
//	if (!fin) {
//		wcout << L"Không thể đọc file data1.txt\n";
//	}
//	else { fin.imbue(loc); }
//	
//
//	wofstream fout1(L"VNcorpus1.txt");
//	fout1.imbue(loc);
//	wofstream fout2(L"VNcorpus2.txt");
//	fout2.imbue(loc);
//	wofstream fout3(L"VNcorpus3.txt");
//	fout3.imbue(loc);
//	wofstream fout4(L"VNcorpus4.txt");
//	fout4.imbue(loc);
//
//	int count = 0;
//	while (fin.peek() != WEOF) {
//		count++;
//		//read a line
//		getline(fin, wstr);
//		if (count <= 500000) {
//			fout1 << wstr << endl;
//			continue;
//		}
//		if (count <= 1000000) {
//			fout1.close();
//			fout2 << wstr << endl;
//			continue;
//		}
//		if (count <= 1500000) {
//			fout1.close();
//			fout2.close();
//			fout3 << wstr << endl;
//			continue;
//		}
//		fout4 << wstr << endl;
//		fout1.close();
//		fout2.close();
//		fout3.close();
//	}
//
//	fout4.close();
//	fin.close();
//}