#include "MyDate.h"

#include <sstream>
#include <iomanip>

void MyDate::subDay(uint8_t day) {

	if (day > day_) {

		subMonth(1);
		day_ = months_[month_ - 1] - ( day - day_ );
		if (month_ == 2 && year_ % 4 == 0)
			++day_;
	}
	else
		day_ -= day;
}

void MyDate::subMonth(uint8_t month) {

	if (month > month_) {

		month_ = (uint8_t)12 - (month - month_);
		try {
			subYear(1);
		}
		catch (...) {
			throw;
		}
	}
	else
		month_ -= month;
}

void MyDate::subYear(uint16_t year) {

	if (year > year_)
		year_ = 0;
	else
		year_ -= year;
}

bool MyDate::isDay() const {

	if (day_ == 0 || day_ > 31)
		return false;

	return true;
}

bool MyDate::isMonth() const {

	if (month_ == 0 || month_ > 12)
		return false;

	return true;
}

bool MyDate::isYear() const {

	if (year_ > 3000)
		return false;

	return true;
}

bool MyDate::IsValidDate() const {

	if (!isDay() || !isMonth() || !isYear())
		return false;

	if (month_ == 2 && year_ % 4 == 0) {
		if (day_ > months_[month_ - 1] + 1)
			return false;
	}
	else
		if (day_ > months_[month_ - 1])
			return false;

	return true;
}

MyDate& MyDate::operator-(const MyDate& date) {

	subYear(date.year_);
	subMonth(date.month_);
	subDay(date.day_);

	std::stringstream   ss;

	ss.fill('0');
	ss << std::setw(2) << static_cast<short>(day_) << ".";
	ss << std::setw(2) << static_cast<short>(month_) << ".";
	ss << std::setw(4) << year_;
	date_ = ss.str();

	return *this;
}

MyDate::InvalidDateException::InvalidDateException(const std::string & details) : details_(details) {}

const char * MyDate::InvalidDateException::what() const noexcept {

	return details_.c_str();
}

std::ostream&    operator<<(std::ostream& o, const MyDate& d) {

	o << d.date_ << std::endl;

	return o;
}

std::istream&    operator>>(std::istream& i, MyDate& d) {

	std::cin >> d.date_;
	if (std::regex_match(d.date_, d.format1_) || std::regex_match(d.date_, d.format2_)) {

		d.day_ = static_cast<uint8_t >(std::stoi(std::regex_replace(d.date_, d.format1_, "$1")));
		d.month_ = static_cast<uint8_t >(std::stoi(std::regex_replace(d.date_, d.format1_, "$2")));
		d.year_ = static_cast<uint16_t >(std::stoi(std::regex_replace(d.date_, d.format1_, "$3")));
	}
	else if (std::regex_match(d.date_, d.format3_)) {

		d.year_ = static_cast<uint16_t >(std::stoi(std::regex_replace(d.date_, d.format3_, "$1")));
		d.month_ = static_cast<uint8_t >(std::stoi(std::regex_replace(d.date_, d.format3_, "$2")));
		d.day_ = static_cast<uint8_t >(std::stoi(std::regex_replace(d.date_, d.format3_, "$3")));
	}
	else {
		throw MyDate::InvalidDateException("Invalid date");
	}
	if (!d.IsValidDate())
		throw MyDate::InvalidDateException("Invalid date");
}
