#include <iostream>  
#include <random> 
#include <ctime>
#include <conio.h>  // _getch()

using namespace std;

int main() 
{ 
	const int I = 1000;
	int massive[I];
    mt19937 gen; 
    gen.seed(time(0)); // try to comment this string 
	int count1=0, count2=0, count3=0, count4=0, count5=0;
	for (int i=I-1; i>0; i--){
		massive[i] = (gen() % 5) + 1;
		cout << "My number: " << massive[i] << endl;
		switch (massive[i]){
		case 1: count1++;
			break;
		case 2: count2++;
			break;
		case 3: count3++;
			break;
		case 4: count4++;
			break;
		case 5: count5++;
			break;
		}
	}
	cout << "EDINIC: " << count1 << endl;
	cout << "DVOEK: " << count2 << endl;
	cout << "TROEK: " << count3 << endl;
	cout << "CHETVEROK: " << count4 << endl;
	cout << "PYATEROK: " << count5 << endl;
	getch();
}