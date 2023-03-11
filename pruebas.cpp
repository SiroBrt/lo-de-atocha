#include <iostream>
#include <vector>
#include <string>

class Date{
    private:
    int day,month,year;
    public:
    Date(){
        day=1;
        month=1;
        year=1;

    }
    Date(int num1,int num2,int num3){
        day=num1;
        month=num2;
        year=num3;
    }
    //cosas clasicas de clases
    void setDay(int num){
        day=num;
    }
    void setMonth(int num){
        month=num;
    }
    void setYear(int num){
        year=num;
    }
    int getDay(){
        return day;
    }
    int getMonth(){
        return month;
    }
    int getYear(){
        return year;
    }
};

class Persona{
    private:
    Date cumple;
    int ID;
    public:
    void setID(int input){
        ID=input;
    }
    void setBirthday(int num1,int num2, int num3){
        cumple.setDay(num1);
        cumple.setMonth(num2);
        cumple.setYear(num3);
    }
    static void printBirthday(Persona input){
        cout <<input.cumple.getDay() <<"/" <<input.cumple.getMonth() <<"/" <<input.cumple.getYear();
    }

};

int main(){
    Persona yo;
    yo.setBirthday(23,8,2004);
    Persona::printBirthday(yo);

}