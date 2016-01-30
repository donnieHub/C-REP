#include <iostream> // cin, out
#include <conio.h>  // _getch()
#include <stdlib.h> // ��������� ������� ������� ������ system("cls")
#include <clocale>  // ��������� �������� �����
using namespace std;

class queue
{
private:
	int head, tail; // ���������� �������� ��������� � �������� �������
	int q [10]; // ������� ���������� ������ ���������
public:
	queue() : head(0), tail(0)
	{}
	void enqueue (int number){ // ���������� � �������
		q[tail] = number;
		tail = (tail + 1) % 10;
	}
	int dequeue (){ // �������� �� �������
		int temp = q[head];
		head = (head+1) % 10;
		return temp;
	}
};

void main(){
	setlocale(LC_CTYPE,"Russian"); // ��������� �������� �����
	queue queue1; // ������� ������ ������ - �������

	int i = 0;
	while (i < 5){
		queue1.enqueue(i); // ��������� �������� � �������
		i++;
	}

	int j = 0;
	while (j < 5){
		cout << queue1.dequeue() << "\n"; // ������� �������� �� �������
		j++;
	}
	cout << "putin" << "\n";
	system("pause");
};