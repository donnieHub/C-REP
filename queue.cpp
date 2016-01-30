#include <iostream> // cin, out
#include <conio.h>  // _getch()
#include <stdlib.h> // поддержка функции очистки экрана system("cls")
#include <clocale>  // поддержка русского языка
using namespace std;

class queue
{
private:
	int head, tail; // переменные хранящие начальный и конечный индексы
	int q [10]; // очередь содержащая десять элементов
public:
	queue() : head(0), tail(0)
	{}
	void enqueue (int number){ // добавление в очередь
		q[tail] = number;
		tail = (tail + 1) % 10;
	}
	int dequeue (){ // удаление из очереди
		int temp = q[head];
		head = (head+1) % 10;
		return temp;
	}
};

void main(){
	setlocale(LC_CTYPE,"Russian"); // установка русского языка
	queue queue1; // создаем объект класса - очередь

	int i = 0;
	while (i < 5){
		queue1.enqueue(i); // добавляем элементы в очередь
		i++;
	}

	int j = 0;
	while (j < 5){
		cout << queue1.dequeue() << "\n"; // удаляем элементы из очереди
		j++;
	}
	cout << "putin" << "\n";
	system("pause");
};