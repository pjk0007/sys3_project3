#include <iostream>
#include <string>
#ifndef _MEMBER_H
#define _MEMBER_H
using namespace std;

class member
{
	protected:
		string mem_Name;
		string Type;
		int canBorrow;
		int nowBorrow;
		int ban_year;
		int ban_month;
		int ban_day;
		int term;
		int size;
		int limit_size;

		int room_time_limit;
		int seat_time_limit;
		int room;	// already borrowed 1, no borrowed 0
		int room_num;	// if you borrowed room,you borrowed this room
		int seat;	// already borrowd 1, no borrowed 0
		int seat_num;	// if you borrowed seat,you borrowed this seat

		
	public:
		member(string mn, string T);
		string getName();
		int getBorrow();
		int getYear();
		int getMonth();
		int getDay();
		int getTerm();
		void setBorrow(int b);
		void setYear(int y);
		void setMonth(int m);
		void setDay(int d);
		int borrow(int n_y, int n_m, int n_d);
		void giveBack(string RT, int sz);
		int getSize();
		int getLimitSize();
		void setSize(int sz);

		
		int getRoom();
		int getSeat();
		int borrow(string Space_type);
		int getBack(string Space_type, int Space_number);
};

class undergraduate : public member
{
	public :
		undergraduate(string rn, string T) : member(rn, T){
			canBorrow = 1;
			term = 13;
			limit_size = 100;
			seat_time_limit = 3;
		}
};

class graduate : public member
{
	public :
		graduate(string rn, string T) : member(rn, T){
			canBorrow = 5;
			term = 29;
			limit_size = 500;
		}
};


class faculty : public member
{
	public :
		faculty(string rn, string T) : member(rn, T){
			canBorrow = 10;
			term = 29;
			limit_size = 1000;
		}
};
#endif
