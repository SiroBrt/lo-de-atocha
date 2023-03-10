/*Nombres y nias
TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
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

class Wagon{
    private:
    int number,seats;
    vector <string> IDs;
};

class Trip{
    private:
    Date trainDate;
    string departureStation,arrivalStation;
    int distance;
};

class Train{
private:
    Trip viaje;
    vector <Wagon> part;
};

class Passenger{
private:
    string ID,name,adress;
    int age,baggage;
    char gender;
    vector <Trip> travels;
};

int main(){
    cout <<"hello world";
}