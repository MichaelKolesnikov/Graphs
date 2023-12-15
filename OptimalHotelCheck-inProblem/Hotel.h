#pragma once
#include "Man.h"
#include <vector>
#include <set>

namespace OptimalHotelCheck_inProblem {
	using namespace std;

	class Guest : public Man {
	public:
		Guest(bool gender, const std::string& sur, const std::string& nm, const std::chrono::system_clock::time_point& dob) 
			: Man(gender, sur, nm, dob) {}
	};

	class HotelRoom {
	private:
		size_t number;
		size_t number_of_beds;
		int cost;
		std::multiset<Guest> guests;
	public:
		HotelRoom() : number_of_beds(1), guests() {}
		HotelRoom(size_t number, size_t number_of_beds, int cost) : number(number), number_of_beds(number_of_beds), cost(cost), guests() {}

		size_t get_number() const {
			return this->number;
		}

		int get_cost() const {
			return this->cost;
		}

		size_t get_number_of_beds() const {
			return number_of_beds;
		}

		std::multiset<Guest> get_guests() const {
			return guests;
		}

		bool accommodate_a_guest(Guest guest) {
			if (guests.size() == number_of_beds) {
				return false;
			}
			guests.insert(guest);
			return true;
		}

		bool evict_a_guest(Guest guest) {
			if (!guests.contains(guest)) {
				return false;
			}
			guests.erase(guest);
			return true;
		}
	};

	struct HotelRoomHash {
		std::size_t operator()(const HotelRoom& room) const {
			return std::hash<size_t>()(room.get_number());
		}
	};

	class Hotel {
	private:
		vector<HotelRoom> rooms;
	public:
		Hotel() : rooms(0) {}
		Hotel(size_t count_rooms) : rooms(count_rooms + 1) {}
		Hotel(const vector<HotelRoom>& rooms) {
			this->rooms = rooms;
			std::sort(begin(this->rooms), end(this->rooms), [](const HotelRoom& a, const HotelRoom& b) {
				return a.get_cost() == b.get_cost() ? a.get_cost() < b.get_cost() : a.get_number_of_beds() < b.get_number_of_beds();
			});
		}

		size_t get_number_of_rooms() const {
			return this->rooms.size();
		}

		bool accommodate_a_guest(Guest guest, size_t room_number) {
			if (this->get_number_of_rooms() < room_number) {
				return false;
			}
			return this->rooms[room_number].accommodate_a_guest(guest);
		}

		bool evict_a_guest(Guest guest, size_t room_number) {
			if (this->get_number_of_rooms() < room_number) {
				return false;
			}
			return this->rooms[room_number].evict_a_guest(guest);
		}
	};
}