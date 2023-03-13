//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//vector for wagons. Each wagon is the pair of station1-station2 and a vector of pairs seat-ID. The number of the wagon is its position-1
static vector <pair <pair <string,string>,vector <pair <int,string>>>> Wagons;

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

class Trip{
    private:
    Date trainDate;
    int distance,money,seat,wagon;
    map <pair <string,string>,int> registeredTrips;
    public:
    Trip(int w,string station1,string station2,int d,int m,int s,Date day,string ID){
        if(w>Wagons.size()){
            cout <<"That wagon doesnt exist";
            money=0;
            distance=0;

        }else{
            bool occupied=0;
            money=m;
            distance=d;
            if(Wagons[w-1].first.first!=station1 && Wagons[w-1].first.second!=station2){
                cout <<"that wagon doesnt go there" <<endl;
            }else{
                for(int i=0;i<Wagons[w-1].second.size();i++){
                    if(Wagons[w-1].second[i].first==s){
                        cout <<"seat already occupied" <<endl;
                        occupied=1;
                        break;
                    }
                }
                if(occupied=0){
                    pair <int,string> newPassenger;
                    newPassenger.first=s;
                    newPassenger.second=ID;
                    Wagons[w-1].second.push_back(newPassenger);
                }
            }
        }
    }
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
    string output;
    //usamos string para aceptar cualquier input
    cout <<"---------- Choose an option ----------\n1. Add new passenger's trip to a train\n2. Remove a passenger's trip from a train\n3. Show trips of a passenger \n4. Show list of passengers in a specific train\n5. Show an alphabetically ordered list of passengers in all the trains\n6. Show passengers of cities\n7. End program \n";
    cin >>output;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1:output=="2"? 2:output=="3"? 3:output=="4"? 4:output=="5"? 5:output=="6"? 6:output=="7"? 7:0);
}

int main(){
    int selection;
    while(selection!=7){
        selection=mainMenu();
        switch (selection){
            case 0:
            cout <<"Please, choose a valid option" <<endl;
            break;
            case 7:
            cout <<"Goodbye";
            break;
        }
    }
}