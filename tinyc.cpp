// tinyc.cpp : définit le point d'entrée de l'application.
//

#include "tinyc.h"
#include "src/main.h"
//#include "src/main_test.h"



using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	int no=0;
	//no = 1;
	if (no == 1) {
		//test_all();
	}
	else {
		start(0, NULL);
	}
	return 0;
}
