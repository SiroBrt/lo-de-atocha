/*Nombres y nias
TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
using namespace std;

class Date{     //done
    private:
    int day,month,year;
    public:
    Date(int num1,int num2, int num3){
        day=num1;
        month=num2;
        year=num3;
    }
    Date(){
        day=1;
        month=1;
        year=1;
    }
};

class Trip{
private:
    
public:
};

class Train{
private:
    Date departureDate;
    string departureStation,arrivalStation;
    int distance;
};

class Passenger{
private:
    string ID,name,adress;
    int age,baggage;
    char gender;
    Trip 
public:
    Passenger(/* args */);
    ~Passenger();
};

Passenger::Passenger(/* args */)
{
}

Passenger::~Passenger()
{
}


int main(){
    cout <<"hello world";
}