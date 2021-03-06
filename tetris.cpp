/**
	Console Tetris Game.
*/

#include <iostream> // cin, �out
#include <conio.h> // _getch()
#include <clocale> // ����������� �������� ������
#include <stdlib.h> // ��������� ������� ������� ������ system("cls") � rand()
#include <time.h> // ����� ��������� time() (����� ��� ��������� ���� �����) 


using namespace std;

const int strings = 22; // ���������� ����� � ������� (�� ����� 98)
const int columns = 15; // ���������� ������� � ������� (����� ��������)
int x = 5; // ��� ���������� ��� �������� ��������� ������
int y = 2;
int square_x0 = 5;  // �������(���������) ���������� �������� �� x
int square_y0 = 14;  // �������(���������) ���������� �������� �� y
int square_x1 = 6; // ������ ���������� �������� �� x
int square_y1 = 15; // ������ ���������� �������� �� y
bool beyond; // ������� ��� ������ �� ����
char map[strings][columns]; // ������ ��� �������� ������� �����
//int bottom_x[columns]; // ������ ��� �������� ��� �� x
int bottom_y[strings][columns]; // ������ ��� �������� ��� �� y
int control = 0; // ���������� ��� ������ �� ����
int warehouse_x; // ��� ���������� ��� �������� ��������� ������
int warehouse_y;
char post_step = ' '; // ������ ������� �������� ����� ���� ��� ����� "����" � ������ ����������
char square_symbol = '0'; // ������ �������� (� ���� �����)
int slice_count = 0;
int summ = 0;


// ��������� (���������� �������)
int game_init(); // ������� ���������������� ������ ����� (map)
int bottom_init(); // ������� ������������� ���
int on_limits(); // ������� �������� ������ �� ������� ����
void on_bottom(); // ������� �������� �� ������� ��������� ���
int interaction(int& warehouse_count, int fuel, int full_fuel); // ������� ��� �������������� � ��������� �� ����� (�����)
void display_map(); // ������� ����������� ��������� ������ �� �����
int slice(); // ������� ����� ���
char square_filling(char symbol); // ���������� ��������� �������� ���������� ���������
int display_object(); // ������� �������� ������� �� �����
int movement_if(int warehouse_count, int& fuel); // ������� ��� �������� ������
int clock_down();
void game_over(int warehouse_count, int& fuel); // ������� ��� ������ ����������� ���� �� �����
void rand_gener(); // ������� ��� ��������� ��������� ���������
int tm_sec;

int main ()
{
  static int warehouse_count = 0; // ������  ��������� ������ (����������� ���������� ���������� 1 ��� � �������� � ������ ��� ���������, ���� ����� ��� �� ����������� �.�. main() ���������� ������ �������)
  static int full_fuel = 10; // ������� ��� �������
  static int fuel = 10; // �������
  setlocale(LC_CTYPE,"Russian"); // ��������� �������� �����
  srand(time(NULL)); // �������(NULL) ��������� ����� ������ ��� ��������� ������ ��������� �����

  rand_gener(); // ������� ��������� ��������� ��������� (��� ������)
  game_init(); // ������� ���������������� ������ ����� (map)
  bottom_init(); // ������� ������������� ���
  while (control == 0) // ���� ��� �������� �������� ����������� ���� ����� �� ������ F1
  {
    on_limits(); // ������� ��������� �� ����� �� �������
	on_bottom(); // ������� �������� �� ������� �������� ���
	slice(); // ������� �������� �� ���� ���
	fuel = interaction(warehouse_count, fuel, full_fuel); // ������� ��� �������������� � ��������� �� ����� (�����, �������) ���������� ������� �������
	display_map(); // ���� ��� ��������� (����� � �������� ����� � �� ��������������� � ���������) ��������� �����
	clock_down();
	//movement_if(warehouse_count, fuel); // ������� �������� ������ ��� ������� ������ (���������� ���������� � �����)
	if (control == 0) // ��� ������ �� ���� ����� ������� �� ����
		system("cls"); // ������� ������
  }
  game_over(warehouse_count, fuel); // ������� ��� ������ ����������� ���� �� �����
  return 0; // ������� �� main()
}

// ��������� ��������� ���������
void rand_gener()
{
	int real_columns = ((columns-1)/2-3); // ���������� ������� �� ����� �� ������� ������� ����� ��������� ����� (�� �����)
	int real_strings = (strings-3); // ���������� ����� �� ����� �� ������� ������� ����� ��������� ����� (�� �����)
	warehouse_x = rand() % real_columns + 2; // ���������� ��������� ����� �� 2 �� 13 ������������
	warehouse_y = rand() % real_strings + 2; // ���������� ��������� ����� �� 2 �� 10 ������������
	if (warehouse_x == x || warehouse_y == y ) // ���� ���������� ������ �������� � ������������ ������ - ���������� ����� ������
	{
		rand_gener(); // ���������� ���������� ������ ������
	}
}
// ������������� ������� �����
int game_init() // ������� ���������������� ������ ����� (map)
{
	int digits[strings]; // ������ ��� �������� ����
	int letters[columns]; // ������ ��� �������� ����

  	for (int i = 0; i < strings; i++) // ������� ���� �������� �� ������
	{
	  digits[i] = i; // ��������� ������ ������� �� 0 �� i
	  for (int j = 0; j < columns; j++) // ���������� ���� �������� �� �������
	  {
		letters[j] = j; // ��������� ������ ������� �� 0 �� j
		map[i][j] = ' ';	  // ��������� ���� ������ 0-���
		//map[0][j] = letters[j] + 63; // ������������ ������� �������(1-�� ��������) �������� �� �������
		//map[1][j] = '-';	  // ������������ ������� �������
		map[strings-1][j] = '-'; // ������������ ������ �������
	  }

	  for (int j = columns/2; j < columns; j++)		// ������������ ������� �������(2-�� ��������) �������� �� �������
	  {
	    //map[0][j] = letters[j-columns/2-1] + 63;	  // j-columns/2-1 ����� ��� �� ������ � ����� �
	  }

	  map[i][0] = ' ';		  // ������������ ����� ������� (������� ����)
	  map[i][1] = '|';		  // ������������ ����� ������� (������� ����)
	  //map[i][columns/2-1] = '|';	  // ������������ ������ ������� (������� ����)
	  //map[i][columns/2] = ' ';		  // �������������� ����� ����� ������
	  //map[i][columns/2+1] = digits[i] + 47;		  // ������������ ����� ������� (������� ����) �������� ������� �� 1-9
	  //map[i][columns/2+2] = '|';	  // ������������ ����� ������� (������� ����)
	  map[i][columns-1] = '|';		  // ������������ ������ �������
	}
	map[0][0] = ' ';	// ������������ ���� ����
	map[0][1] = ' ';	// ������������ ���� ����
	map[1][0] = ' ';	// ������������ ���� ����
	map[1][1] = '#';	// ������������ ���� ����
	map[strings-1][0] = ' ';	// ������������ ���� ����
	map[strings-1][1] = '#';	// ������������ ���� ����
	map[0][columns-1] = ' ';	// ������������ ���� ����
	map[1][columns-1] = '#';	// ������������ ���� ����
	map[strings-1][columns-1] = '#';	// ������������ ���� ����
	//for (int i = columns/2-1; i <= columns/2+2; i++) 	// ������������ ���� ���� ����������
	//{
	//	map[0][i] = ' '; // ������������ ���� ���� ���������� (������)
	//	map[1][i] = '#'; // ������������ ���� ���� ���������� (������)
	//	map[1][columns/2] = ' '; // ������������ ���� ���� ���������� (������)
	//	map[1][columns/2+1] = ' '; // ������������ ���� ���� ���������� (������)
	//	map[strings-1][i] = '#'; // ������������ ���� ���� ���������� (�����)
	//	map[strings-1][columns/2] = ' '; // ������������ ���� ���� ���������� (�����)
	//	map[strings-1][columns/2+1] = ' '; // ������������ ���� ���� ���������� (�����)
	//}
	display_object(); // ������ ������� �� �����
	return 0; // ������� �� ������� ������������� ������� �����
}
// ������������� ������� ���
int bottom_init() // ������� ���������������� ������ ���
{
	for (int i = 0; i < strings; i++){
		for (int j = 0; j < columns; j++){
			bottom_y[i][j] = 99; // ��������� ������ 99�� - �������
			bottom_y[strings-2][j] = strings-2; // ������ ��� �������� ��� �� y. -2 �������� ������� "-"	
		}
	}
	return 0;
 }
// ������ ������� �� �����
int display_object()
{
	static char symbol_gamer = 'T'; // ������ ������
	static char symbol_warehouse = 'W'; // ������ ������
	map[y][x] = symbol_gamer; // ������ ������
	map[warehouse_y][warehouse_x] = symbol_warehouse; // ������ �����
	square_filling(square_symbol); // ���������� ��������� �������� �������� square_symbol - 0
	return 0;
}
// �������� �� ����� �������� �� ������� ����
int on_limits() // ������� �������� ������ �� ������� ����
{
  beyond = 0; // ������� ��� ������ �� ����
  while (beyond == 0) // ��������� ���� �������� �� ����� �� ������� �����
  {
	  	if (square_y0 < 2) // ��������� ������� �� ����� �������� �� "�������" ������ �����
	{
			map[square_y0][square_x0] = '-';
			map[square_y0][square_x1] = '-';
			square_y0++;
			square_y1++;
			square_filling(square_symbol);
	}
		else if (square_y1 > strings-2) // ��������� ������� �� ����� ������ �� "������" ������ �����
	{
			map[square_y1][square_x0] = '-';
			map[square_y1][square_x1] = '-';
			square_y0--;
			square_y1--;
			square_filling(square_symbol);
	}
		else if (square_x0 < 2) // ��������� ������� �� ����� ������ �� "�����" ������ ������� ����
	{
			map[square_y0][square_x0] = '|';
			map[square_y1][square_x0] = '|';
			square_x0++;
			square_x1++;
			square_filling(square_symbol);
	}
		else if (square_x1 > columns-2) // ��������� ������� �� ����� ������ �� "������" ������ ����
	{
			map[square_y0][square_x1] = '|';
			map[square_y1][square_x1] = '|';
			square_x0--;
			square_x1--;
			square_filling(square_symbol);
	}
		else if (square_y0-1 == bottom_y[square_y0-1][square_x1]) // ��������� ������� �� ������� ������ ����� �������� �� ���������� y1
	{
			map[square_y1][square_x1] = post_step; // ���� ��� ������ �� ���� ������� ����������� ��������
			if (square_y1-1 == bottom_y[square_y1-1][square_x1]){ // ������������� ���������� ���������� �� �1 ����� ���������� 0 (���� ��� ������ ����� � �� ������)
				map[square_y1][square_x1] = square_symbol;
			}
			square_x0--;
			square_x1--;
			square_filling(square_symbol);
	}
		else if (square_y1-1 == bottom_y[square_y1-1][square_x1]) // ��������� ������� �� ������� ������ ����� �������� �� ���������� y0
	{
			map[square_y0][square_x1] = post_step; // ���� ��� ������ �� ���� ������� ����������� ��������
			if (square_y0-1 == bottom_y[square_y0-1][square_x1]){ // ������������� ���������� ���������� �� �0 ����� ���������� 0 (���� ��� ������ ����� � �� ������)
				map[square_y0][square_x1] = square_symbol;
			}
			square_x0--;
			square_x1--;
			square_filling(square_symbol);
	}
		else if (square_y0-1 == bottom_y[square_y0-1][square_x0]) // ��������� ������� �� ������� ����� ����� �������� �� ���������� y1
	{
			map[square_y1][square_x0] = post_step; // ���� ��� ������ �� ���� ������� ����������� ��������
			if (square_y1-1 == bottom_y[square_y1-1][square_x0]){ // ������������� ���������� ���������� �� �1 ����� ���������� 0 (���� ��� ������ ����� � �� ������)
				map[square_y1][square_x0] = square_symbol;
			}
			square_x0++;
			square_x1++;
			square_filling(square_symbol);
	}
		else if (square_y1-1 == bottom_y[square_y1-1][square_x0]) // ��������� ������� �� ������� ����� ����� �������� �� ���������� y0
	{
			map[square_y0][square_x0] = post_step; // ���� ��� ������ �� ���� ������� ����������� ��������
			if (square_y0-1 == bottom_y[square_y0-1][square_x0]){ // ������������� ���������� ���������� �� �0 ����� ���������� 0 (���� ��� ������ ����� � �� ������)
				map[square_y0][square_x0] = square_symbol;
			}
			square_x0++;
			square_x1++;
			square_filling(square_symbol);
	}
		else // ���� ����� �� ����� �� ������� ����� ������� �� �������
	{
			return beyond = 1; // ������� �� ����� ������� ������ �� ������� �����
	}
  }
}
// �������� �� ������� ��������� ���
void on_bottom() // ������� �������� �� ������� ��������� ���
{
  //����� ��������� ������!
	  	if (square_y1 >= bottom_y[square_y1][square_x0] ||
			square_y1 >= bottom_y[square_y1][square_x1]) // ��������� ������� �� ������� ��������� ��� � ������������ � ������������ x
	{
			square_filling(square_symbol); // ��� ������� ���, �� ��� �������� �������
			bottom_y[square_y0-1][square_x0] = square_y0-1; // ��� ����������� �.�. � ���� �������� ���������� � �� ����������� x
			bottom_y[square_y0-1][square_x1] = square_y0-1;
			bottom_y[square_y1-1][square_x0] = square_y1-1; // ��� ����������� �.�. � ���� �������� ���������� � �� ����������� x
			bottom_y[square_y1-1][square_x1] = square_y1-1;
			square_x0 = 5;				// ��� ������� ��� ���������� �������� ������������ �� �����
			square_y0 = 14;				// ��� ������� ��� ���������� �������� ������������ �� �����
			square_x1 = square_x0 + 1; // ������ ���������� �������� �� x ������������ �� �����
			square_y1 = square_y0 + 1; // ������ ���������� �������� �� y ������������ �� �����
			square_filling(square_symbol); // ��� ������� ��� ������� ������������ �� ����� � ���������������
			
	}
}
// ������� ��� �������������� � ��������� �� ����� (�����, �������)
int interaction(int& warehouse_count, int fuel, int full_fuel)
{
  bool warehouse_par = 0; // �������� ����������� ��� '������' �� ������
  char post_step = ' ';   // ���������� ����� ������ ������� �������� ����� ���� ��� ����� "����" �� ������
		if (x == warehouse_x && y == warehouse_y && warehouse_par == 0) // ��������� ������� �� ��������� ������ �� �����
	{
		map[warehouse_y][warehouse_x] = 'V'; // ���� ����� ���������� �� ������ �� ������ ������ �������� � 'W' �� 'V'
		warehouse_par = 1; // �������� ����������� ��� '������' �� ������
		post_step = 'W'; // ���� ����� ������� ����� �� ������ ������� ��������� ��� �� ' ' � 'V'
		rand_gener(); //  ���� ����� ������� ����� �� ������������� ����� ���������� ������
		map[warehouse_y][warehouse_x] = 'W'; // �������������� �����
		fuel += full_fuel; // ��������� ������� �� ������� ���� ������ �� �����
		warehouse_count += 1; // ������� ���-�� ������� �� �����
		return fuel;
	}
		if (fuel <= 0) // ���� ������� ����� ���� �� ���� ���������
	{
		control = 1; // ���������� ��� ������ �� ����
		//game_over(warehouse_count, fuel); //
		return 0;
	}
		return fuel; // ���� ����� �� ����� �� ����� (������� ��� ����� ���������� ������ ���) ���������� ������� �������� �������
}
// ����� ����� �� �����
void display_map() // ������� ����������� ��������� ������ �� �����
{
	for (int i = 0; i < strings; i++)  // ������� ���� �������� �� ������
	{
		for (int j = 0; j < columns; j++)  // ��������� ���� �������� �� �������
		{
			cout << map[i][j]; // � ������ ����������� ��������� ������
		}
		cout << "\n"; // ������� �� ����� ������ ����� ������� "����"
	}
}
// ���� ��� ��� ���������� �����
int slice(){
	summ = 0;
	for (int k = 1; k <= (strings-3); k++){	// ��������� �� ���� ������� �� 1 �� strings-3 � ������� ��������� ����������
		for (int i = 2; i <= (columns-2); i++){ // ��������� ��� �������� � ������ ����� ������ ����� columns-2
			summ = summ + bottom_y[k][i]; // ��������� ��� �������� � ������
			}
		//cout  << "k: " << k << "summ: " << summ << "bottom_y[k][2]" << bottom_y[k][2] << "\n";
		slice_count = summ/(columns-3); // ������ ��������� �� ������ ������ (columns-3) ��� -3 ��� ������
		summ = 0;

		if (slice_count == k && slice_count < 88){ // ���� ����� ������ �������� ������ �� �������� (� ��� �� 99 - '�����') �� ���������� ��� �������� � ������
			//k = 1;
			square_filling(post_step); // ������� ������� � ������ ����� ���� �� ������� ��� ���� �� ����� �����
			for (int k2 = k; k2 > 1; k2--){ // ���� ��� ������� �� ��������� ������ ����� ���� ������ ����� (������� ������ ��������� ������)
				//cout << "k: " << k << " k2: "<< k2 << " slice_count " << slice_count << " summ " << summ << "\n";
				//_getch();
				for (int j = 2; j <= (columns-2); j++){ 
					map[k2+1][j] = post_step; // ������� ��������� ������ �� ����� ���
					map[k2][j] = map[k2-1][j]; // ��������� ������ ����������� ������� � ������� �����
					bottom_y[k2][j] = bottom_y[k2-1][j]; // ��������� ������ ����������� ������� � ������� ���
					if (bottom_y[k2][j] < 88){
						bottom_y[k2][j] = bottom_y[k2][j] + 1;
					}
				}
			}
		}
		square_filling(square_symbol); // ������ ������� � ����� ��� ��������� ����� ���� ��� ���� �������
		//cout << "k: " << k << "k2: " << "\n";
	}
	return 0;
}
// ���������� ��������� �������� ���������� ���������
char square_filling(char symbol){
	map[square_y0][square_x0] = symbol; // ������ ������� ������ ��������
	map[square_y0][square_x1] = symbol; // ������ ������ ������ ��������
	map[square_y1][square_x0] = symbol; // ������ ������ ������ ��������
	map[square_y1][square_x1] = symbol; // ������ ������ ������ ��������
	return symbol;
}
// �������� ������ ��� ������� ������
int movement_if(int warehouse_count, int& fuel) // ������� ��� �������� ������
{
	char act; // ���������� ��� ���������� ����� ������������
	int ch; // ���������� ��� �������� ����������� �������� ���������� act
	if (control == 1) // ���� ���� ��� ��������� ������� �� �� (��� ���������� ����� ������ ��� �� ���������� � ������� _getch())
	{
		ch = 59;	// ����������� ���������� ������� F1 - �����
	}
	else // ���� ���� ��� �� ��������� ��������� � ������� _getch()
	{
		act = _getch(); // ������� ���� ������� ����� ������� � ��������� �������� ������ ��� string
		ch = static_cast<int>(act); // ��������� ������ �� ����������� � ��������
	}

		if (ch == -32) // ������� ������� ������� ������ ��� ���������
		{}
		else if (ch == 59) // F1 - �����
		{
			return control = 1;
		}
		else if (ch == 60) // F2 - ������������ �� ������ ����
		{
			map[y][x] = post_step; // ������� "�������" ��������� � ����
			if (x < columns/2) // ���� �������� ���������� �� ������ ����
			{
				x = columns/2+3; // ���������� ��������� � ������ ������� ����
				y = 2;
			}
			else // ���� �������� ���������� �� ������ ����
			{
				x = 2; // ���������� ��������� � ������ ������� ����
				y = 2;
			}
			map[y][x] = 'T'; //������ ������
		}
		else if (ch == 61) // F3 - ���������� ����������
		{
			game_over(warehouse_count, fuel); // ������� ��������� ���������� ����
		}
		else if (ch == 75)
		{
			// ��� ��� ������������ ��������� �����
			//cout << "��� �����" << " " << "���: " << act << "(" << static_cast<int>(ch) << ")" << "\n";
			square_filling(post_step); // ���������� ���������� �������� ����������� ���������
			square_x0--;
			square_x1--;
			square_filling(square_symbol); // ������ ������� ������ �������� �� ����� ����������
			//fuel--;
		}
		else if (ch == 77)
		{
			// ��� ��� ������������ ��������� ������
			//cout << "��� ������" << " " << "���: " << act << "(" << static_cast<int>(ch) << ")" << "\n";
			square_filling(post_step); // ���������� ���������� �������� ����������� ���������
			square_x0++;
			square_x1++;
			square_filling(square_symbol); // ������ ������� ������ �������� �� ����� ����������
			//fuel--;
		}
		else if (ch == 72)
		{
			// ��� ��� ������������ ��������� �����
			//cout << "��� �����" << " " << "���: " << act << "(" << static_cast<int>(ch) << ")" << "\n";
			square_filling(post_step); // ���������� ���������� �������� ����������� ���������
			square_y0--;
			square_y1--;
			square_filling(square_symbol); // ������ ������� ������ �������� �� ����� ����������
			//fuel--;
		}
		else if (ch == 80)
		{
			// ��� ��� ������������ ��������� ����
			//cout << "��� ����" << " " << "���: " << act << "(" << static_cast<int>(ch) << ")" << "\n";
			square_filling(post_step); // ���������� ���������� �������� ����������� ���������
			square_y0++;
			square_y1++;
			square_filling(square_symbol); // ������ ������� ������ �������� �� ����� ����������
			//fuel--;
		}
		else // ����� ������ ������� ������� ���������
		{
			cout << "�� ������ �������� �������!" << " " << "���: " << act << "(" << ch << ")" << "\n";
			//_getch();
		}
	return 0;
}
// �������� ��������� �������� �� ���
int clock_down(){
int clock_dwn = clock() / 10;
	cout << "clock_dwn % 10 - " << clock_dwn % 10 << "\n";
	cout << "clock_dwn " << clock_dwn << "\n";
	while (clock_dwn % 3000 == 0)
	{

	//cout << "clock_dwn2 " << clock_dwn2 << "\n";
		square_filling(post_step); // ���������� ���������� �������� ����������� ���������
		square_y0++;
		square_y1++;
		square_filling(square_symbol); // ������ ������� ������ �������� �� ����� ����������
		//system("cls"); // ������� ������
		//display_object();
		//display_map();
		clock_dwn = 0;
	}
	return 0;
}
// ����� ����������� ����
void game_over(int warehouse_count, int& fuel)
{
	//if (fuel <= 0) // ���� ������� ����������� ������������� ������� �����:
	//{
	//	cout << "\n" << "GAME OVER" << "\n";
	//	cout << "� ��� ����������� �������\n";
	//}
	int f = 0;
	cout << "������� ���������� ��������2: " << "x0 = " << square_x0 << " " << "y0 = " << square_y0 << "\n";
	cout << "������ ���������� ��������2: " << "x1 = " << square_x1 << " " << "y0 = " << square_y0 << "\n";
	cout << "������ ���������� ��������2: " << "x0 = " << square_x0 << " " << "y1 = " << square_y1 << "\n"; 
	cout << "������ ���������� ��������2: " << "x1 = " << square_x1 << " " << "y1 = " << square_y1 << "\n"; 
	cout << "clock()/CLOCKS_PER_SEC " << clock()/CLOCKS_PER_SEC << "\n"; 
	cout << "clock_dwn " << clock() << "\n";
  time_t t = time(NULL);
  tm* aTm = localtime(&t);
  printf("%04d/%02d/%02d %02d:%02d:%02d \n",aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);

		for (int i = 0; i < strings; i++)  // ������� ���� �������� �� ������
	{
		for (int j = 0; j < columns; j++)  // ��������� ���� �������� �� �������
		{
			cout << bottom_y[i][j]; // � ������ ����������� ��������� ������
		}
		cout << "\n"; // ������� �� ����� ������ ����� ������� "����"
	}
	_getch(); //������� ��������� ������� ����� �������
	_getch(); //������� ��������� ������� ����� �������
}
