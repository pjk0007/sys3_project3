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

		int seat_time_limit;
		int room;	// already borrowed 1, no borrowed 0
		int room_num;
		int seat;	// already borrowd 1, no borrowed 0
		int seat_num;
		int room_time;
		int seat_time;
		int empty_time;

		
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

		int getTimeLimit();
		
		int getRoom();
		int getRoom_num();
		int getSeat();
		int getSeat_num();
		int getRoom_Time();
		int getSeat_Time();
		void Borrow(string Space_type, int Space_number, int return_time);
		void Return(string Space_type);
		void Empty(string Space_type, int hour);
		void Comeback(string Spce_type);
		void Reset();
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
