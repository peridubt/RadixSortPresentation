#include <iostream>
#include <string>

const size_t SIZE = 5;

template <typename T>
void print(T arr[], size_t size) // печать всего массива
{
	for (size_t i = 0; i < size; ++i)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

std::string to_binary(int number, int bits_count) // перевод целого числа в двоичную систему (представимо в виде строки)
{
	std::string result = "";
	while (number > 0)
	{
		result = std::to_string(number % 2) + result;
		number /= 2;
		bits_count--;
	}

	while (bits_count > 0) // дописываются дополнительные разряды, чтобы все числа массива имели одинаковую длину
	{
		result = "0" + result;
		bits_count--;
	}
	return result;
}

int to_integer(std::string binary_num) // перевод из двоичной системы в десятичную
{
	size_t size = binary_num.length();
	int result = 0;
	for (size_t i = 0; i < size; ++i)
		result += (binary_num[size - i - 1] - '0') * std::pow(2, i);
	return result;
}

int max_bits(int arr[], size_t size) // подсчёт максимального количества битов для выравнивания чисел в массиве по длине
{
	int maxm = arr[0];
	for (size_t i = 0; i < size; ++i)
		if (arr[i] > maxm)
			maxm = arr[i];
	return to_binary(maxm, 0).length();
}

std::string* arr_to_bin(int arr[], size_t size, int bits_count) // перевод массива десятичных чисел в массив бинарных чисел
{
	std::string* result = new std::string[size];
	for (size_t i = 0; i < size; ++i)
		result[i] = to_binary(arr[i], bits_count);
	return result;
}

int* arr_to_int(std::string arr[], size_t size) // обратный перевод
{
	int* result = new int[size];
	for (size_t i = 0; i < size; ++i)
		result[i] = to_integer(arr[i]);
	return result;
}

void radix_sort_rec(std::string* array, size_t start, size_t end, int digit) // поразрядная сортировка
{
	if (start < end && digit < array[0].length()) // идём до тех пор, пока начало массива != конец 
		// и пока мы не дошли до последнего разряда
	{
		size_t i = start, j = end; // идём по выделенной области [start;end) с двух концов (с левой и правой стороны)
		while (i <= j) // будем менять индексы, пока они не пересекутся (когда i > j)
		{
			while (i <= end && array[i][digit] == '0') // двигаемся слева, пока не дошли до конца либо текущий разряд != 0
				++i;
			while (j >= start && array[j][digit] == '1') // двигаемся справа, пока не дошли до начала либо текущий разряд != 1
				--j;
			if (i <= j)
			{
				std::swap(array[i], array[j]); // производим обмен таким образом, что в левой части находятся числа с текущим разрядом == 0,
				// а в правой части - с текущим разрядом == 1
				++i; --j;
			}
		}
		// рекурсия вызывается для разных частей массива, 
		// при этом сортировка идёт по следующему разряду (и так до самого старшего)
		radix_sort_rec(array, start, j, digit + 1); 
		radix_sort_rec(array, i, end, digit + 1);
	}
}

void radix_sort(int*& arr, size_t size)
{
	int bits_count = max_bits(arr, size);
	std::string* bin_arr = arr_to_bin(arr, size, bits_count);
	radix_sort_rec(bin_arr, 0, size - 1, 0);
	arr = arr_to_int(bin_arr, size);
}

int main()
{
	int* arr = new int[SIZE];
	arr[0] = 543; arr[1] = 986; arr[2] = 217; arr[3] = 765; arr[4] = 329;
	print<int>(arr, SIZE);
	radix_sort(arr, SIZE);
	print<int>(arr, SIZE);
	std::cin.get();
	return 0;
}
