#pragma once
#include <string>
#include <chrono>

class Man {
private:
	bool gender; // 0 - woman, 1 - man
	std::string surname;
	std::string name;
	std::string patronymic;
	std::chrono::system_clock::time_point date_of_birth;
public:
	explicit Man() = delete;
	Man(bool gender, const std::string& sur, const std::string& nm, const std::string& patronymic, const std::chrono::system_clock::time_point& dob)
		: gender(gender), surname(sur), name(nm), patronymic(patronymic), date_of_birth(dob) {}

	bool get_gender() const {
		return this->gender;
	}

	std::string get_surname() const {
		return this->surname;
	}
	std::string get_name() const {
		return this->name;
	}
	std::string get_patronymic() const {
		return this->patronymic;
	}

	std::string get_full_name() const {
		return this->surname + " " + this->name + " " + this->patronymic;
	}

	std::chrono::system_clock::time_point get_date_of_birth() const {
		return date_of_birth;
	}

	bool operator==(const Man& other) const {
		return this->gender == other.gender &&
			this->date_of_birth == other.date_of_birth &&
			this->surname == other.surname &&
			this->name == other.name &&
			this->patronymic == other.patronymic;
	}
};
