//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

static vector <Wagon> Wagons;
//me arrepiento de vector<pair <pair <int,pair <string,string>>,vector <pair <int,string>>>> y reflexionare sobre ello

//cortesía de pruebas.cpp
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

class Wagon{
    private:
    int distance,capacity;
    string departureStation,arrivalStation;
    vector <pair <int,string>> reservedSeats;   //seat-ID
    bool assigned;
    public:
    Wagon(){
        capacity=5;
        distance=0;
        departureStation="";
        arrivalStation="";
    }
    Wagon(int seats,string station1,string station2,int d){
        //seats
        if(seats>=5){
            capacity=seats;
        }else{
            cout <<"the minimum number of seats is 5";
            capacity=5;
        }
        //stations
        departureStation=station1;
        arrivalStation=station2;
        //distances
        distance=d;
        //añadir comprobador de distancia para que un mismo trayecto no tenga 2 distancias
    }
    string getDepartureStation(){
        return departureStation;
    }
    string getArrivalStation(){
        return arrivalStation;
    }
    int getCapacity(){
        return capacity;
    }
    bool assigned(){
        return assigned;
    }
    
    //añadir algo para el vector de pasajeros

    void setDepartureStation(string input){
        departureStation=input;
    }
    void setArrivalStation(string input){
        arrivalStation=input;
    }
    void setCapacity(int input){
        if(reservedSeats.size()>input){
            cout <<"There are already passengers there" <<endl;
        }else{
            capacity=input;
        }
    }
    void changeAssignation(bool input){
        assigned=input;
    }
    void addPassenger(pair <int,string> input){
        if(capacity>reservedSeats.size()){
            bool found=0,occupied=0;
            for(auto i:reservedSeats){
                if(input.first==i.first){
                    found=1;
                    break;
                }else if(input.second==i.second){
                    occupied=1;
                    break;
                }
            }
            if(found==1){
                cout <<"That passenger already has a seat" <<endl;
            }else if(occupied==1){
                cout <<"That seat is already reserved" <<endl;
            }else{
                reservedSeats.push_back(input);
            }
        }else{
            cout <<"The wagon is already full" <<endl;
        }
    }
    void removePassenger(pair <int,string> input){
        bool found=0;
        
    }
};

class Trip{
    private:
    Date trainDate;
    int money,wagon;
    public:
    Trip(int w,,int m,int seat,Date day,string ID){
        
};

class Train{
private:
    Trip viaje;
    //vector <Wagon> part;
};

class Passenger{
private:
    string ID,name,adress;
    int age,baggage;
    char gender;
    vector <Trip> travels;
};

int mainMenu(){
    //usamos string para aceptar cualquier input
    string output;
    cout <<"---------- Choose an option ----------\n1. Add new passenger's trip to a train\n2. Remove a passenger's trip from a train\n3. Show trips of a passenger \n4. Show list of passengers in a specific train\n5. Show an alphabetically ordered list of passengers in all the trains\n6. Show passengers of cities\n7. End program \n";
    cin >>output;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1:output=="2"? 2:output=="3"? 3:output=="4"? 4:output=="5"? 5:output=="6"? 6:output=="7"? 7:0);
}

//TEMPORAL (no es una funcion permitida pero viene bien)
//sin control de errores
void addWagon(){
    pair <pair <int,pair <string,string>>,vector <pair <int,string>>> newWagon;
    cout <<"asientos? ";
    cin >>newWagon.first.first;
    cout <<"salida? ";
    cin >>newWagon.first.second.first;
    cout <<"llegada? ";
    cin >>newWagon.first.second.second;
    Wagons.push_back(newWagon);
}

int main(){
    int selection;
    /*while(selection!=7){
        selection=mainMenu();
        switch (selection){
            case 0:
            cout <<"Please, choose a valid option" <<endl;
            break;
            case 7:
            cout <<"Goodbye";
            break;
        }
    }*/
    addWagon();
    Date dia;
    Trip prueba1(1,"leganes","madrid",10,20,2,dia,"DNI1");
    Trip prueba2(1,"leganes","madrid",10,20,5,dia,"DNI2");

}