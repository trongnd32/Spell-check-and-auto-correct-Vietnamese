#include <cstring>
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>  
#include <string>
#include <vector>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;
typedef pair <int, double> ID;
typedef pair <double, double> DD;
typedef pair <ID, DD> IDDD;
typedef pair <ID, double> IDD;

map <wstring, IDD> UNI;
map <wstring, IDD> BI;
map <wstring, double> NBI;
map <wstring, double> TRI;
map <wstring, double> BI2;
map <wstring, double> sumPBi;
map <wstring, double> sumPUni;

double D[4][4] = {
	{0, 0, 0, 0},
	{0, 0.487, 0.487, 0.487},
	{0, 0.5923, 0.5923, 0.5923},
	{0, 0.72606, 0.72606, 0.72606}
};

void readUni() {
	locale loc(locale(), new codecvt_utf8<wchar_t>);

	wifstream fin(L"./data new/uni.txt");
	if (!fin) wcout << "Khong tim thay file input\n";
	else fin.imbue(loc);

	wstring input;

	while (fin.peek() != WEOF) {

		getline(fin, input);

		int n = input.length();

		wstring wstr = L"";
		int frequency = 0;
		int flag = 0;

		for (int i = 0; i < n; i++) {
			if (input[i] == L',') {
				flag++;
				continue;
			}
			if (flag == 0) wstr += input[i];
			else frequency = frequency * 10 + input[i] - L'0';
		}

		UNI[wstr].first.first = frequency;
	}
}

void readNCalcP_Bi() {
	locale loc(locale(), new codecvt_utf8<wchar_t>);

	wifstream fin(L"./data new/bi.txt");
	if (!fin) wcout << "Khong tim thay file input\n";
	else fin.imbue(loc);

	wstring input;
	while (fin.peek() != WEOF) {
		getline(fin, input);

		int n = input.length();

		wstring wstr2 = L"";
		wstring wstr = L"";
		int frequency = 0;
		int flag = 0;

		for (int i = 0; i < n; i++) {
			if (input[i] == L',') {
				flag++;
				continue;
			}
			if (flag == 0) wstr += input[i];
			if (flag == 1) wstr2 += input[i];
			if (flag == 2) frequency = frequency * 10 + input[i] - L'0';
		}
		wstring ww = wstr + L' ' + wstr2;

		int N1 = frequency;
		int N2 = UNI[wstr].first.first;
		
		double DD = D[2][1];
		if (N1 == 2) DD = D[2][2];
		if (N1 >= 3) DD = D[2][3];
		
		double P = max((N1 - DD), 0.0) * 1.0 / N2;

		BI[ww].first.first = frequency;
		BI[ww].first.second = P;
		NBI[wstr2] += 1;

		BI2[wstr] += frequency - DD;
	}
	fin.close();
}

void readNCalcP_Tri() {
	locale loc(locale(), new codecvt_utf8<wchar_t>);

	wifstream fin(L"./data new/tri.txt");
	if (!fin) wcout << "Khong tim thay file input\n";
	else fin.imbue(loc);

	wofstream fout(L"./data new/tri with P.txt");
	fout.imbue(loc);

	wstring input;
	wstring wwOld = L"-1";
	double sumP = 0.0;

	while (fin.peek() != WEOF) {
		getline(fin, input);

		int n = input.length();

		wstring wstr = L"";
		wstring wstr2 = L"";
		wstring wstr3 = L"";
		int frequency = 0;
		int flag = 0;

		for (int i = 0; i < n; i++) {
			if (input[i] == L',') {
				flag++;
				continue;
			}
			if (flag == 0) wstr += input[i];
			if (flag == 1) wstr2 += input[i];
			if (flag == 2) wstr3 += input[i];
			if (flag == 3) frequency = frequency * 10 + input[i] - L'0';
		}
		wstring ww = wstr + L' ' + wstr2;
		wstring ww2 = wstr2 + L' ' + wstr3;

		int N1 = frequency;
		int N2 = BI[ww].first.first;
		
		double DD = D[3][1];
		if (N1 == 2) DD = D[3][2];
		if (N1 >= 3) DD = D[3][3];
		
		double P = (N1 - DD) * 1.0 / N2;

		fout.precision(17);
		fout << fixed << wstr << L"," << wstr2 << L"," << wstr3 << L"," << frequency << L"," << P << endl;
		
		if (ww.compare(wwOld) != 0) {
			sumPBi[wwOld] = sumP;
			sumP = BI[ww2].first.second;
			wwOld = ww;
		}
		else sumP += BI[ww2].first.second;
		
		if (fin.peek() == WEOF) sumPBi[ww] = sumP;

		TRI[ww] += frequency*1.0 - DD;
	}
	fin.close();
	fout.close();
}

void calcP_Uni() {
	for (auto i : UNI) {
		wstring u = i.first;

		int N1 = NBI[u];
		int N2 = 2325513;

		double DD = D[2][1];
		if (N1 == 2) DD = D[2][2];
		if (N1 >= 3) DD = D[2][3];

		double P = (N1 - DD) * 1.0 / N2;

		UNI[u].first.second = P;
	}
}

void calcAlpha_Bi() {

	double sumP = 0.0;
	wstring wstr1 = L"";
	wstring wstr2 = L"";

	wstring wstrOld = L"-1";

	for (auto i : BI) {
		wstring u = i.first;
		double alpha = 0.0;
		alpha = (1.0 - TRI[u] / i.second.first.first) / (1.0 - sumPBi[u]);

		BI[u].second = alpha;

		//-----------------
		int n = u.length();
		wstr1 = L"";
		wstr2 = L"";
		int ff = 0;

		for (int j = 0; j < n; j++) {
			if (u[j] == L' ') {
				ff++;
				continue;
			}
			if (ff == 0) wstr1 += u[j];
			else wstr2 += u[j];
		}

		sumPUni[wstr1] += UNI[wstr2].first.second;
		/*if (wstr1.compare(wstrOld) != 0) {
			sumPUni[wstrOld] = sumP;
			sumP = UNI[wstr2].first.second;
			wstrOld = wstr1;
		}
		else sumP += UNI[wstr2].first.second;*/
			
	}
	//sumPUni[wstr1] = sumP;
	map<wstring, double>().swap(TRI);
}

void calcAlpha_Uni() {
	for (auto i : UNI) {
		wstring u = i.first;
		

		double alpha = 0.0;
		alpha = (1.0 - BI2[u] / i.second.first.first) / (1.0 - sumPUni[u]);

		UNI[u].second = alpha;
	}
}

void print() {
	locale loc(locale(), new codecvt_utf8<wchar_t>);

	wofstream fout(L"./data new/uni with P alpha.txt");
	fout.imbue(loc);

	for (auto i : UNI) {
		fout.precision(17);
		fout << fixed << i.first << L"," << i.second.first.first << L"," << i.second.first.second << L"," << i.second.second << endl;
	}
	fout.close();

	wofstream fout1(L"./data new/bi with P alpha.txt");
	fout1.imbue(loc);

	for (auto i : BI) {
		wstring u = i.first;

		int n = u.length();
		wstring wstr1 = L"";
		wstring wstr2 = L"";
		int ff = 0;

		for (int j = 0; j < n; j++) {
			if (u[j] == L' ') {
				ff++;
				continue;
			}
			if (ff == 0) wstr1 += u[j];
			else wstr2 += u[j];
		}

		fout1.precision(17);
		fout1 << fixed << wstr1 << L"," << wstr2 << L"," << i.second.first.first << L"," << i.second.first.second << L"," << i.second.second << endl;
	}
	fout1.close();
}

int main() {

	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);

	readUni();
	readNCalcP_Bi();
	readNCalcP_Tri();
	calcP_Uni();
	calcAlpha_Bi();
	calcAlpha_Uni();
	print();
}
