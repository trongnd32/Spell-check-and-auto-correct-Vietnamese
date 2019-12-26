#ifndef _CORRECTSEN_CPP
#define _CORRECTSEN_CPP


#include "lib.h"
#include "ConstVar.h"
#include "NearSyll.h"
#include "GeneralFunc.h"
#include "A2U.h"
#include "U2A.h"

#define E_THRESH 1.0e-8
#define D_THRESH 1.0e-10
#define CONST_ALPHA 1.0e-1
#define CONST_P 1.0e-5
#define CONST_FIX 0.4

const double D[4][4] = {
	{0,0,0,0},
	{0,0.487,-0.01469,-0.33026},
	{0,0.5923,0.04445,-0.52177},
	{0,0.72606,0.13425,-0.5683},
};

double calcAlpha(int db, wstring w1, wstring w2) {
	MYSQL_ROW row;
	MYSQL_RES* res;

	if (db == 1) {
		string word1 = wstring_to_utf8(w1);

		 /*string query = "select sum(bidb.frequency), sum(bidb.frequency = 1), sum(bidb.frequency = 2), sum(bidb.frequency >= 3), unidb.frequency, unidb.Pbkn2 "
		 	"from bidb, unidb where bidb.word1 = \"" + word1 + "\" and unidb.word1 = \"" + word1 + "\"";
		 const char* q = query.c_str();
		 int qstate = mysql_query(conn, q);
		 if (!qstate)
		 {
		 	res = mysql_store_result(conn);
		 	row = mysql_fetch_row(res);
			
		 	if (row[0] != NULL) {
		 		int sumFreBi = stoi(row[0]);
		 		int cntFre1 = stoi(row[1]);
		 		int cntFre2 = stoi(row[2]);
		 		int cntFre3 = stoi(row[3]);
		 		int sumFreUni = stoi(row[4]);
		 		double sumP = stod(row[5]);

		 		double rs = (1.0 - (sumFreBi - D[2][1] * cntFre1 - D[2][2] * cntFre2 - D[2][3] * cntFre3) * 1.0 / sumFreUni) * 1.0 / (1.0 - sumP);
		 		return rs;
		 	}
		 	else return CONST_ALPHA;
		 }
		 else cerr << "Query fail\n";*/

		string query = "SELECT alpha FROM unidb WHERE word1 = \"" + word1 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			int numrow = mysql_num_rows(res);
			row = mysql_fetch_row(res);

			if (numrow > 0 && row[0] != NULL) {
				double alpha = stod(row[0]);

				return alpha;
			}
			else return CONST_ALPHA;

		} else cerr << "Query fail\n";
	}

	if (db == 2) {
		string word1 = wstring_to_utf8(w1);
		string word2 = wstring_to_utf8(w2);

		 /*string query = "select sum(tridb.frequency), sum(tridb.frequency = 1), sum(tridb.frequency = 2), sum(tridb.frequency >= 3), bidb.frequency, bidb.Pbkn2 "
		 	"from bidb, tridb where((tridb.word1 = \"" + word1 + "\" and tridb.word2 = \"" + word2 + "\") and (bidb.word1 = \"" + word1 + "\" and bidb.word2 = \"" + word2 + "\"))";
		 const char* q = query.c_str();
		 int qstate = mysql_query(conn, q);
		 if (!qstate)
		 {
		 	res = mysql_store_result(conn);
		 	row = mysql_fetch_row(res);

		 	if (row[0] != NULL) {
		 		int sumFreTri = stoi(row[0]);
		 		int cntFre1 = stoi(row[1]);
		 		int cntFre2 = stoi(row[2]);
		 		int cntFre3 = stoi(row[3]);
		 		int sumFreBi = stoi(row[4]);
		 		double sumP = stod(row[5]);

		 		double rs = (1.0 - (sumFreTri - D[3][1] * cntFre1 - D[3][2] * cntFre2 - D[3][3] * cntFre3) * 1.0 / sumFreBi) * 1.0 / (1.0 - sumP);

		 		return rs;
		 	}
		 	else return CONST_ALPHA;
		 }
		 else cerr << "Query fail\n";*/

		string query = "SELECT alpha FROM bidb WHERE word1 = \"" + word1 + "\" and word2 = \"" + word2 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			int numrow = mysql_num_rows(res);
			row = mysql_fetch_row(res);

			if (numrow > 0 && row[0] != NULL) {
				double alpha = stod(row[0]);
				
				return alpha;
			}
			else return CONST_ALPHA;

		} else cerr << "Query fail\n";
		
	}
}

double dbQuery(int db, wstring w1, wstring w2, wstring w3) {
	MYSQL_ROW row;
	MYSQL_RES* res;

	if (db == 1) {
		string word1 = wstring_to_utf8(w1);

		string query = "SELECT Pbkn FROM unidb where word1 = \"" + word1 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			int rowNum = mysql_num_rows(res);

			if (rowNum == 0) {
				return CONST_P;
			}
			else {
				row = mysql_fetch_row(res);
				return stod(row[0]);
			}

		}
		else {
			cerr << "Query Pbkn db = 1 fail\n";
		}
	}

	if (db == 2) {
		string word1 = wstring_to_utf8(w1);
		string word2 = wstring_to_utf8(w2);

		string query = "SELECT Pbkn FROM bidb where word1 = \"" + word1 + "\" and word2 = \"" + word2 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			int rowNum = mysql_num_rows(res);

			if (rowNum == 0) {
				double alpha1 = calcAlpha(1, w1, L"");
				double P2 = dbQuery(1, w2, L"", L"");
				return alpha1 * P2 * CONST_FIX;
			}
			else {
				row = mysql_fetch_row(res);
				return stod(row[0]);
			}

		}
		else {
			cerr << "Query Pbkn db = 2 fail\n";
		}
	}

	if (db == 3) {
		string word1 = wstring_to_utf8(w1);
		string word2 = wstring_to_utf8(w2);
		string word3 = wstring_to_utf8(w3);

		string query = "SELECT Pbkn FROM tridb where word1 = \"" + word1 + "\" and word2 = \"" + word2 + "\" and word3 = \"" + word3 + "\"";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			int rowNum = mysql_num_rows(res);

			if (rowNum == 0) {
				double alpha1 = calcAlpha(2, w1, w2);
				double P2 = dbQuery(2, w2, w3, L"");

				return alpha1 * P2 * CONST_FIX;
			}
			else {
				row = mysql_fetch_row(res);
				return stod(row[0]);
			}

		}
		else {
			cerr << "Query Pbkn db = 3 fail\n";
		}
	}
}

double calcP(wstring w1, wstring w2, wstring w3, wstring w4, wstring w5) {
	int dem = 0;
	if (w1.compare(L"") != 0) dem++;
	if (w2.compare(L"") != 0) dem++;
	if (w3.compare(L"") != 0) dem++;
	if (w4.compare(L"") != 0) dem++;
	if (w5.compare(L"") != 0) dem++;

	if (dem == 1) {
		return dbQuery(1, w3, L"", L"");
	}
	if (dem == 2) {
		if (w2.compare(L"") != 0) {
			double res = 0.0;
			double P1 = dbQuery(2, w2, w3, L"");
			double P2 = dbQuery(1, w2, L"", L"");

			res = P1 * P2;
			return res;
		}
		else {
			double res = 0.0;
			double P1 = dbQuery(2, w3, w4, L"");
			double P2 = dbQuery(1, w3, L"", L"");

			res = P1 * P2;
			return res;
		}
	}
	if (dem == 3) {
		if (w2.compare(L"") == 0) {
			double res = 0.0;
			double P1 = dbQuery(3, w3, w4, w5);
			double P2 = dbQuery(2, w3, w4, L"");
			double P3 = dbQuery(1, w3, L"", L"");
			res = P1 * P2 * P3;

			return res;
		}
		if (w4.compare(L"") == 0) {
			double res = 0.0;
			double P1 = dbQuery(3, w1, w2, w3);
			double P2 = dbQuery(2, w1, w2, L"");
			double P3 = dbQuery(1, w1, L"", L"");
			res = P1 * P2 * P3;

			return res;
		}

		double res = 0.0;
		double P1 = dbQuery(3, w2, w3, w4);
		double P2 = dbQuery(2, w2, w3, L"");
		double P3 = dbQuery(1, w2, L"", L"");
		res = P1 * P2 * P3;

		return res;
	}
	if (dem == 4) {
		if (w5.compare(L"") == 0) {
			double res = 0.0;

			double P1 = dbQuery(3, w1, w2, w3);
			double P2 = dbQuery(2, w1, w2, L"");
			double P3 = dbQuery(1, w1, L"", L"");
			double value1 = P1 * P2 * P3;

			P1 = dbQuery(3, w2, w3, w4);
			P2 = dbQuery(2, w2, w3, L"");
			P3 = dbQuery(1, w2, L"", L"");
			double value2 = P1 * P2 * P3;

			res = (value1 + value2) / 2.0;
			return res;
		}

		//other case 
		double res = 0.0;

		double P1 = dbQuery(3, w2, w3, w4);
		double P2 = dbQuery(2, w2, w3, L"");
		double P3 = dbQuery(1, w2, L"", L"");
		double value1 = P1 * P2 * P3;

		P1 = dbQuery(3, w3, w4, w5);
		P2 = dbQuery(2, w3, w4, L"");
		P3 = dbQuery(1, w3, L"", L"");
		double value2 = P1 * P2 * P3;

		res = (value1 + value2) / 2.0;
		return res;
	}
	if (dem == 5) {
		double res = 0.0;

		double P1 = dbQuery(3, w1, w2, w3);
		double P2 = dbQuery(2, w1, w2, L"");
		double P3 = dbQuery(1, w1, L"", L"");
		double value1 = P1 * P2 * P3;

		P1 = dbQuery(3, w2, w3, w4);
		P2 = dbQuery(2, w2, w3, L"");
		P3 = dbQuery(1, w2, L"", L"");
		double value2 = P1 * P2 * P3;

		P1 = dbQuery(3, w3, w4, w5);
		P2 = dbQuery(2, w3, w4, L"");
		P3 = dbQuery(1, w3, L"", L"");
		double value3 = P1 * P2 * P3;

		res = (value1 + value2 + value3) / 3.0;
		return res;
	}
}

bool isWrongSyll(double P1, double P2) {
	if (P1 < P2 + D_THRESH) return false;
	if (P1 < E_THRESH) return false;
	return true;
}

void recalcP(int pos, vector <IWs> sentence, vector <wstring> nearSyll, set <DI, greater<> >& PP, double& P, set <DI, greater<> >& Fratio, double& maxFratio) {
	int n = sentence.size();

	wstring w1 = L"", w2 = L"", w3 = L"", w4 = L"", w5 = L"";
	w3 = sentence[pos].second;
	if (pos > 1) w1 = sentence[pos - 2].second;
	if (pos > 0) w2 = sentence[pos - 1].second;
	if (pos < n - 1) w4 = sentence[pos + 1].second;
	if (pos < n - 2) w5 = sentence[pos + 2].second;

	P = calcP(w1, w2, w3, w4, w5);

	int m = nearSyll.size();
	PP.clear();
	for (int j = 0; j < m; j++) {
		PP.insert(DI(calcP(w1, w2, nearSyll[j], w4, w5), j));
	}

	set <DI>::iterator it = Fratio.find(DI(maxFratio, pos));
	if (it != Fratio.end()) {
		Fratio.erase(it);
	}
	maxFratio = ((*PP.begin()).first);
	if (isWrongSyll(maxFratio, P)) Fratio.insert(DI(maxFratio / P, pos));
}

vector<IWs> correctSen(vector <IWs> sentence) {

	set <DI, greater<> > PP[100];
	double P[100];
	double maxFratio[100];
	int choose[100];
	set <DI, greater<> > Fratio;
	vector <wstring> nearSyll[100];

	int n = sentence.size();

	for (int i = 0; i < n; i++) {
		string tmp = U2A(sentence[i].second);
		sentence[i].second = A2U(tmp);
	}

	for (int i = 0; i < n; i++) {
		//
		nearSyll[i] = nearWSyll(sentence[i].second);

		//wcout << sentence[i].second << L":\n";for (auto j : nearSyll[i]) {wcout << j << L' ';}wcout << endl;

		recalcP(i, sentence, nearSyll[i], PP[i], P[i], Fratio, maxFratio[i]);


		/*
		int m = nearSyll[i].size();

		wstring w1 = L"", w2 = L"", w3 = sentence[i], w4 = L"", w5 = L"";
		if (i > 0) w2 = sentence[i - 1];
		if (i > 1) w1 = sentence[i - 2];
		if (i < n - 1) w3 = sentence[i + 1];
		if (i < n - 2) w4 = sentence[i + 2];

		//
		P[i] = calcP(w1, w2, w3, w4, w5);

		for (int j = 0; j < m; j++) {
			PP[i].insert(DI(calcP(w1, w2, nearSyll[i][j], w4, w5), j));
		}

		maxFratio[i] = ((*PP[i].begin()).first);
		if (isWrongSyll(maxFratio[i], P[i])) Fratio.insert(DI(maxFratio[i] / P[i], i));
		*/
	}
	/*for (auto f : Fratio) {
		wcout << f.first << L" " << P[f.second] << L" " << (*PP[f.second].begin()).first << L" " << nearSyll[f.second][(*PP[f.second].begin()).second] << L" " << sentence[f.second].second <<endl;
	}*/

	while (!Fratio.empty()) {
		DI u = *(Fratio.begin());
		Fratio.erase(u);
		int i = u.second;

		choose[i] = (*PP[i].begin()).second;
		sentence[i].second = nearSyll[i][choose[i]];

		// re-calc P[i]
		wstring w1 = L"", w2 = L"", w3 = sentence[i].second, w4 = L"", w5 = L"";
		if (i > 0) w2 = sentence[i - 1].second;
		if (i > 1) w1 = sentence[i - 2].second;
		if (i < n - 1) w4 = sentence[i + 1].second;
		if (i < n - 2) w5 = sentence[i + 2].second;

		P[i] = calcP(w1, w2, w3, w4, w5);

		// re-calc P[i-1]
		if (i > 0) {
			recalcP(i - 1, sentence, nearSyll[i - 1], PP[i - 1], P[i - 1], Fratio, maxFratio[i - 1]);
		}

		// re-calc P[i-2];
		if (i > 1) {
			recalcP(i - 2, sentence, nearSyll[i - 2], PP[i - 2], P[i - 2], Fratio, maxFratio[i - 2]);
		}

		// re-calc P[i+1];
		if (i < n - 1) {
			recalcP(i + 1, sentence, nearSyll[i + 1], PP[i + 1], P[i + 1], Fratio, maxFratio[i + 1]);
		}

		// re-calc P[i+2];
		if (i < n - 2) {
			recalcP(i + 2, sentence, nearSyll[i + 2], PP[i + 2], P[i + 2], Fratio, maxFratio[i + 2]);
		}
	}


	//free
	Fratio.erase(Fratio.begin(), Fratio.end());
	for (int i = 0; i < 100; i++) {
		nearSyll[i].clear();
		nearSyll[i].shrink_to_fit();
		PP[i].erase(PP[i].begin(), PP[i].end());
	}


	return sentence;
}

#endif // !_CORRECTSEN_CPP