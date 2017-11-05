#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
	string message;
	cout << "Enter your message: ";
	getline(cin, message); // считываем строку для получения сообщения для кодирования
	cout << endl;

	string code = "";
	int newBits = 0; // количество добавленных бит в сообщение

	// bit - текуший номер бита, в который заносится значения (из сообщения или 0 для кода хэмминга)
	// i - индекс символа в сообщении
	for (size_t i = 0, bit = 1; i < message.length(); bit++) {
		if ((bit & (bit - 1)) == 0) {
			code += '0';
			newBits++; // увеличиваем число новых бит кода Хэмминга
		}
		else
			code += message[i++];

		cout << '|' << code[bit - 1]; // выводим текущее значение сообщения вместе с нулевыми битами кода Хэмминга
	}

	cout << '|' << endl;

	string *matrix = new string[newBits]; // матрица для нахождения кода Хэминга

	// заполняем матрицу Хэмминга значениями (0 и 1)
	for (int i = 0; i < newBits; i++) {
		size_t start_j = (1 << i) - 1; // (1 << i) - 1 = 2^i - 1, число нулей, с которого начинается матрица

		matrix[i] = string(start_j, '0'); // матрица всегда начинается с 2^i-1 нулей

		int count = 1 << i; // число повторяющихся нулей и единиц
		int v = 1; // текущее добавляемое значение к строке

		for (size_t j = start_j; j < code.length(); j++) {
			matrix[i] += ('0' + v); // добавляем символ-цифру, которую нужно приписать к кожду Хэмминга
			count--; // уменьшаем текущее значение количества нулей или единиц

			if (!count) {
				count = 1 << i; // восстанавливаем число повторяющихся нулей и единиц
				v = !v; // меняем значение прибавляемой цифры
			}
		}

		int res = 0; // переменная для хранения итогового значения бита
		for (size_t j = 0; j < code.length(); j++) {
			res ^= (code[j] - '0') * (matrix[i][j] - '0'); // производим сложение по модуля два произведений бит сообщения на бит строки из матрицы

			cout << '|' << (matrix[i][j] - '0' ? 'X' : ' ');
		}

		cout << "|" << endl;

		matrix[i] = res + '0';
	}

	for (size_t i = 0, bit = 0; i < code.length(); i++)
		if ((i & (i + 1)) == 0)
			code[i] = matrix[bit++][0];

	cout << endl;
	cout << "Message: " << message << endl;
	cout << "Code: " << code << endl << endl;
}