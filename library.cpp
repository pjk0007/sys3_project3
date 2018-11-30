#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "library.h"
#include "member.h"
#include "resource.h"
#include "space.h"
using namespace std;


library::library()
{
	resource* tempRes;
	member* tempMem;
	study_room study_rooms[11];
	seat seat1 = seat(0, 24);
	seat seat2 = seat(9, 21);
	seat seat3 = seat(9, 18);

	char input1[100], input2[100];
	char buf1[100], buf2[100], buf3[100], buf4[100];
	FILE* fp;
	FILE* fq;
	int year1, month1, day1, year2, month2, day2, hour;
	int year, month, day, i;
	int cnt=1, exist=0;
	int b_year, b_month, b_day;
	string resName, resType, memName, memType;
	char BorR[3];

	int result;
	int mag_y, mag_m;

	string Space_type;
	int Space_number;
	char Operation;
	int Number_of_member;
	int Time;

	int file_end1, file_end2;
	

	fp = fopen("resource.dat", "r");
	fscanf(fp, "%s", buf1);
	fscanf(fp, "%s", buf2);


	
	while(fscanf(fp, "%s", buf1)!=EOF)
	{
		resType = buf1;
		fscanf(fp, "%s", buf2);
		if(resType=="Book"){
			RESLIST.push_back(new book(buf2, buf1));
		}
		else if(resType=="Magazine"){
			RESLIST.push_back(new magazine(buf2, buf1));
		}
		else if(resType=="E-book"){
			char tmp_buf[100];
			int len_size=0;
			int buf2_size;
			int flag=0;
			for(int i=0;;i++){
				if(buf2[i]==']'){
					tmp_buf[len_size]='\0';
					break;
				}
				if(flag==1){
					tmp_buf[len_size]=buf2[i];
					len_size++;
				}
				if(buf2[i]=='['){
					flag=1;
					buf2_size=i;
				}
			}
			buf2[buf2_size]='\0';
			RESLIST.push_back(new e_book(buf2,buf1,atoi(tmp_buf)));
		}
	}
	fclose(fp);

	fp = fopen("input.dat", "r");
	for(i=0;i<6;i++){
		fscanf(fp, "%s", buf1);
	}

	fq = fopen("space.dat", "r");
	for(i=0;i<8;i++){
		fscanf(fq, "%s", buf3);
	}

	cout << "Op_#	Return_code	Description"<<endl;
	while(1)
	{
		cout << cnt << "	";
		
		if(file_end1=fscanf(fp, "%s", buf1)!=EOF)
		{
			buf2[0]=buf1[0];
			buf2[1]=buf1[1];
			buf2[2]='\0';
			year1 = atoi(buf2);
			
			buf2[0]=buf1[3];
			buf2[1]=buf1[4];
			buf2[2]='\0';
			month1 = atoi(buf2);
				
			buf2[0]=buf1[6];
			buf2[1]=buf1[7];
			buf2[2]='\0';
			day1 = atoi(buf2);
		}
	
		if(file_end2=fscanf(fq, "%s", buf3)!=EOF)
		{
			buf4[0]=buf3[0];
			buf4[1]=buf3[1];
			buf4[2]=buf3[2];
			buf4[3]=buf3[3];
			buf4[4]='\0';
			year2 = atoi(buf4);
			
			buf4[0]=buf3[5];
			buf4[1]=buf3[6];
			buf4[2]='\0';
			month2 = atoi(buf4);
			
			buf4[0]=buf3[8];
			buf4[1]=buf3[9];
			buf4[2]='\0';
			day2 = atoi(buf4);
		}
	
		if(file_end1<1 && file_end2<1) break;
		else if(year1*360+month1*12+day1 <= year2*360+month2*12+day2 || file_end2<1){ 
			year = year1;
			month = month1;
			day = day1;
			if(file_end2>0) fseek(fq, -13, SEEK_CUR);
			fscanf(fp, "%s", buf1);
			fscanf(fp, "%s", buf2);
			resName = buf2;
			resType = buf1;
			exist = 0;
		
			for(i=0;i<RESLIST.size();i++){
				if(RESLIST.at(i)->getName() == resName){
					tempRes = RESLIST.at(i);
					exist++;
					break;
				}
			}
	
			if(resType=="Magazine"){
				char tmp_buf[10];
				int len_size=0;
				int buf2_size;
				int flag=0;
				string temp_name;
	
	
				if(exist==0){
					for(i=0;;i++){
						if(buf2[i]==']'){
							tmp_buf[len_size]='\0';
							break;
						}
						if(flag==1){
							tmp_buf[len_size]=buf2[i];
						len_size++;
							}
						if(buf2[i]=='['){
							flag=1;
							buf2_size=i;
						}
					}
					buf2[buf2_size]='\0';
					temp_name=buf2;
					buf1[0]=tmp_buf[0];
					buf1[1]=tmp_buf[1];
					buf1[2]='\0';
					buf2[0]=tmp_buf[3];
					buf2[1]=tmp_buf[4];
					buf2[2]='\0';
					mag_y=atoi(buf1);	
					mag_m=atoi(buf2);
	
					for(i=0;i<RESLIST.size();i++){
						if(RESLIST.at(i)->getName() == temp_name){
							exist++;
							break;
						}
					}
					if(exist==1 && mag_y*12+mag_m>year*12+month-12 && mag_y*12+mag_m<=year*12+month){
						RESLIST.push_back(new magazine_y_m(resName, resType, mag_y, mag_m));
						tempRes = RESLIST.back();
					}
					else exist=0;
				}
				else if(exist==1){
					if(mag_y*12+mag_m>year*12+month-12 && mag_y*12+mag_m<=year*12+month) exist==1;
					else exist=0;
				}
			}
	
			fscanf(fp, "%s", BorR);
	
			fscanf(fp, "%s", buf1);
			fscanf(fp, "%s", buf2);
			memName = buf2;
			memType = buf1;
	
			if(MEMLIST.size()==0){
				if(memType=="Undergraduate"){
					MEMLIST.push_back(new undergraduate(buf2, buf1));
				}
				else if(memType=="Graduate"){
					MEMLIST.push_back(new graduate(buf2, buf1));
				}
				else if(memType=="Faculty"){
					MEMLIST.push_back(new faculty(buf2, buf1));
				}
				tempMem = MEMLIST.back();
				exist = 0;
			}
			else{
				for(i=0;i<MEMLIST.size();i++){
					if(MEMLIST.at(i)->getName() == memName){
						tempMem = MEMLIST.at(i);
						break;
					}
					else if(i==MEMLIST.size()-1){
						if(memType=="Undergraduate"){
							MEMLIST.push_back(new undergraduate(buf2, buf1));
						}
						else if(memType=="Graduate"){
							MEMLIST.push_back(new graduate(buf2, buf1));
						}
						else if(memType=="Faculty"){
							MEMLIST.push_back(new faculty(buf2, buf1));
						}
						tempMem = MEMLIST.back();
					}
				}
			}
	
			if(BorR[0]=='B'){
				if(exist==0){
					cout << "1	";	// return code 1
					cout << "Non exist resource." <<endl;
				}
				else if(tempRes->getType()!="e-book" && tempMem->borrow(year, month, day)==2){
					cout << "2	";
					cout << "Exceeds your possible number of borrow. Possible # of borrows: ";
					cout << tempMem->getBorrow() << endl;
				}
				else if(tempMem->borrow(year, month, day)==0){
					b_year = (year*360+month*30+day + tempMem->getTerm()) / 360;
					b_month = ((year*360+month*30+day + tempMem->getTerm()) - b_year*360) / 30;
					b_day = ((year*360+month*30+day + tempMem->getTerm()) - b_year*360 - b_month*30);
					if(tempRes->borrow(tempMem->getName(), year, month, day, b_year, b_month, b_day)==1){
						cout << "4	";
						cout << "You already borrowed this ";
						cout << setw(2) << setfill('0') << tempRes->getB_year() <<"/";
						cout << setw(2) << setfill('0') << tempRes->getB_month() <<"/";
						cout << setw(2) << setfill('0') << tempRes->getB_day() << endl;
					}
					else if(tempRes->getType()!="e-book" && tempRes->borrow(tempMem->getName(), year, month, day, b_year, b_month, b_day)==2){
						cout << "5	";
						cout << "Other member already borrowed this ";
						cout << tempRes->getType()<<". This " << tempRes->getType() <<" will be returned at ";
						cout << setw(2) << setfill('0') << tempRes->getR_year() <<"/";
						cout <<	setw(2) << setfill('0') << tempRes->getR_month()<<"/";
						cout <<	setw(2) << setfill('0') << tempRes->getR_day() <<endl;
					}
					else if(tempRes->getType()=="e-book" && tempMem->getLimitSize() < (tempMem->getSize()+tempRes->getSize())){
						cout << "15	Exceeds your storage capacity." << endl;
					}
					else {
						if(tempRes->getType()!="e-book"){
							tempMem->setBorrow(tempMem->getBorrow()+1);
						}
						else{
							tempMem->setSize(tempMem->getSize()+tempRes->getSize());
						}
						cout << "0	Success." <<endl;
					}
				
				}
				else if(tempMem->borrow(year, month, day)==1){
					cout << "6	";
					cout << "Restricted member until ";
					cout << setw(2) << setfill('0') << tempMem->getYear()<<"/";
					cout << setw(2) << setfill('0') << tempMem->getMonth()<<"/";
					cout << setw(2) << setfill('0') << tempMem->getDay()<<endl;
				}
			}
			else if(BorR[0]=='R'){
				if(tempRes->giveBack(tempMem->getName(), year, month, day) == 0){
					tempMem->giveBack();
					cout << "0	Success." <<endl;
				}
				else if(tempRes->giveBack(tempMem->getName(), year, month, day) == 2){
					cout << "3	You did not borrow this "<< tempRes->getType() <<"."<<endl;
				}
				else{
					result = year*360 + month*30 + day - tempRes->getR_year()*360 - tempRes->getR_month()*30 - tempRes->getR_day();
					b_year = (year*360+month*30+day + result) / 360;
					b_month = ((year*360+month*30+day + result) - b_year*360) / 30;
					b_day = ((year*360+month*30+day + result) - b_year*360 - b_month*30);
	
					tempMem->setYear(b_year);
					tempMem->setMonth(b_month);
					tempMem->setDay(b_day);
					tempMem->giveBack();
	
					cout << "7	Delayed return. You'll be restricted until ";
					cout << setw(2) << setfill('0') << tempMem->getYear() <<"/";	
					cout << setw(2) << setfill('0') << tempMem->getMonth() <<"/";	
					cout << setw(2) << setfill('0') << tempMem->getDay()<<endl;
				}
			}
		}
		else if(year1*360+month1*12+day1 > year2*360+month2*12+day2 || file_end1<1){ 
			year = year2;
			month = month2;
			day = day2;

			if(file_end1>0) fseek(fp, -8, SEEK_CUR);

			fscanf(fq, "%s", buf3);
			Space_type = buf3;
			fscanf(fq, "%s", buf3);
			Space_number = atoi(buf3);
			fscanf(fq, "%s", buf3);
			Operation = buf3[0];
			fscanf(fq, "%s", buf3);
			memType = buf3;
			fscanf(fq, "%s", buf3);
			memName = buf3;

			if(Operation=='B'){
				fscanf(fq, "%s", buf3);
				Number_of_member = atoi(buf3);
				fscanf(fq, "%s", buf3);
				Time = atoi(buf3);
			}

			if(MEMLIST.size()==0){
				if(memType=="Undergraduate"){
					MEMLIST.push_back(new undergraduate(memName, memType));
				}
				tempMem = MEMLIST.back();
			}
			else{
				for(i=0;i<MEMLIST.size();i++){
					if(MEMLIST.at(i)->getName() == memName){
						tempMem = MEMLIST.at(i);
						break;
					}
					else if(i==MEMLIST.size()-1){
						if(memType=="Undergraduate"){
							MEMLIST.push_back(new undergraduate(memName, memType));
						}
						tempMem = MEMLIST.back();
					}
				}
			}

			if(Operation=='B'){
			}
			else if(Operation=='R'){
			}
			else if(Operation=='E'){
			}
			else if(Operation=='C'){
			}
		}

		cnt++;
	}
	fclose(fp);
	fclose(fq);
}
