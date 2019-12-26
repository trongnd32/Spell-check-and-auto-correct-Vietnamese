#ifndef _MYSQLCONN_CPP
#define _MYSQLCONN_CPP

#include "ConstVar.h"

using namespace std;

void MysqlConn() {
	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "1234", "ngramdb", 3306, NULL, 0);

	if (conn) {
		cerr << "Connect successful!\n";
	}
	else {
		cerr << "Connection to database has failed!";
	}
}

#endif // !_MYSQLCONN_CPP