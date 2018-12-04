#include <iostream>
#include "MyDate.h"

int main() {

	MyDate  date1;
	MyDate  date2;

	try {
		std::cin >> date1;
		std::cin >> date2;
	}
	catch (const std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
	std::cout << date1;
	std::cout << date2;

	std::cout << date1 - date2;

	return 0;
}