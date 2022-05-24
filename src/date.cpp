#include "date.h"

#include <iomanip>

using namespace std;

Date::Date() : year_(0), month_(0), day_(0) {}

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

void Date::SetYear(int year) {
    year_ = year;
}

void Date::SetMonth(int month) {
    month_ = month;
}

void Date::SetDay(int day) {
    day_ = day;
}

ostream& operator<<(ostream& out, const Date& date) {
    out << setfill('0') << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
    return out;
}

istream& operator>>(istream& in, Date& date) {
    char delimiter;
    int day, month, year;
    if(in >> year >> delimiter >> month >> delimiter >> day) {
        if(month < 1 || month > 12) throw invalid_argument("Month value is invalid: " + to_string(month));
        if(day < 1 || day > 31) throw invalid_argument("Day value is invalid: " + to_string(day));

        date.SetDay(abs(day));
        date.SetMonth(abs(month));
        date.SetYear(abs(year));
        return in;
    }
    throw invalid_argument("Invalid date");
}

Date ParseDate(istream& in) {
    Date date;
    in >> date;
    return date;
}

// (12*31=372)
int GetTotalDays(const Date& date) {
    return date.GetYear() * 372 + date.GetMonth() * 31 + date.GetDay();
}

bool operator<(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) < GetTotalDays(rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) <= GetTotalDays(rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) > GetTotalDays(rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) >= GetTotalDays(rhs);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) == GetTotalDays(rhs);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return GetTotalDays(lhs) != GetTotalDays(rhs);
}