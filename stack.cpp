#include <iostream> // cin, out
#include <conio.h>  // _getch()
#include <stdlib.h> // ��������� ������� ������� ������ system("cls")
#include <clocale>  // ��������� �������� �����
using namespace std;

class stack
{
private:
	int top; // ������� �����
	int s[10]; // ������ � ������� �������� ����
public:
	stack (): top(0) // ����������� ��� ����������
	{}
	void push(int var); //������� ��� ������������� ��������
	int pop(); // ������� ��� ������������ ��������
	int empty(); // ������� �������� ����������� �����
	int full(); // ������� �������� ������������ �����
};

void stack::push(int var){ // ���������� �������� � ����� �����
	if (full()){ // �������� �� ������������ �����
		top++;			// ����������� ������� �����
		s[top] = var;	// ��������� ������� � ����� ������� �����
	}
	// ���� ���� ���������� ����� �� ��������
}
int stack::pop(){ // ������� ��������� ������� �� �����
	if (empty()){ // �������� �� ����������� �����
		int var = s[top]; // ����� ������� � ������� �����
		top--;	// ��������� ������� �����
		return var; // ���������� ������� � ������� �����
	}
	else{return 0;} // ���� ���� ��������� ���������� 0
}
int stack::empty(){ // �������� �� ����������� �����
	if (top <= 0){ // ���� ������� ������ ��� ����� 0 �� ���� ��������� ������
		cout << "stack is empty" << " ";
		return 0; // ���� ���� ��������� �� ���������� 0
	}
	else {return 1;} // ���� ��� ������ ���������� 1
}
int stack::full(){
	if (top >= 9){ // ���� ������� ������ ��� ����� 9 �� ���� ��������� ������������
		cout << "stack is full" << "\n"; 
		return 0; // ���� ���� ���������� �� ���������� 0
	}
	else {return 1;} // ���� ��� ������ ���������� 1
}

void main(){
	setlocale(LC_CTYPE,"Russian"); // ��������� �������� �����
	stack stack1; // ������� ������ ������ - ����1

	int i = 0;
	while (i < 5){
		stack1.push(i); // ������������ �������� � ����
		i++;
	}

	int j = 0;
	while (j < 5){
		cout << stack1.pop() << "\n"; // ����������� �������� �� �����
		j++;
	}
	cout << "putin" << "\n";
	system("pause");
};