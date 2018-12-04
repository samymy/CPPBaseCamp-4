#ifndef PROCESS_MYDATE_H
#define PROCESS_MYDATE_H

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

class MyDate {

	std::vector<uint8_t>    months_ = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	std::regex              format1_ { R"((\d\d).(\d\d).(\d\d\d\d))" };
	std::regex              format2_ { R"((\d\d)-(\d\d)-(\d\d\d\d))" };
	std::regex              format3_ { R"((\d\d\d\d).(\d\d).(\d\d))" };

	std::string date_;

	uint8_t     day_;
	uint8_t     month_;
	uint16_t    year_;

	bool        isDay() const;
	bool        isMonth() const;
	bool        isYear() const;
	bool        IsValidDate() const;

	void        subDay(uint8_t day);
	void        subMonth(uint8_t month);
	void        subYear(uint16_t year);

public:

	MyDate&                 operator-(const MyDate&);

	friend std::ostream&    operator<<(std::ostream&, const MyDate&);
	friend std::istream&    operator>>(std::istream&, MyDate&);

class InvalidDateException : public std::exception {

	std::string     details_;

public:
	explicit InvalidDateException(const std::string &);
	const char * what() const noexcept override;
};

};

#endif //PROCESS_MYDATE_H
