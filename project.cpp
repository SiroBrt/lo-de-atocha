//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//cortesía de pruebas.cpp
class Date{
    private:
    int day,month,year;
    public:
    Date(){day=month=year=1;}
    Date(int num1,int num2,int num3){
        day=num1;
        month=num2;
        year=num3;
    }
    void setDay(int num){day=num;}
    void setMonth(int num){month=num;}
    void setYear(int num){year=num;}
    int getDay(){return day;}
    int getMonth(){return month;}
    int getYear(){return year;}
};

class Wagon{
    private:
    int capacity, wagonNumber;
    vector <pair <int,string>> reservedSeats;   //seat-ID
    public:
    Wagon(){
        capacity=5;
        wagonNumber=1;
    }
    Wagon(int seats){
        if(seats>=5){
            capacity=seats;
        }else{
            cout <<"The minimum number of seats is 5" <<endl;
            capacity=5;
        }
    }
    int getCapacity(){return capacity;}
    int getWagonNum(){return wagonNumber;}
    //da el ID a partir del sitio. si no está da -1
    string getPassenger(int input){
        string output="-1";
        for(auto i:reservedSeats){
            if(input==i.first){
                output=i.second;
                break;
            }
        }
        return output;
    }
    //el contrario. si no está da -1
    int getSeat(string input){
        int output=-1;
        for(auto i:reservedSeats){
            if(input==i.second){
                output=i.first;
                break;
            }
        }
        return output;
    }
    
    void setCapacity(int input){
        if(reservedSeats.size()>input){
            cout <<"The wagon is full!" <<endl;
        }else{
            capacity=input;
        }
    }
    void setNumber(int input){
        if(input>0){
            wagonNumber=input;
        }else{
            cout <<"introduce a valid wagon number" <<endl;
        }
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
    void removePassenger(string ID){
        int found=-1,count=0;
        for(auto i:reservedSeats){
            if(ID==i.second){
                found=count;
                break;
            }
            count++;
        }
        if(found<0){
            cout <<"That passenger didn't have a seat" <<endl;
        }else{
            reservedSeats.erase(reservedSeats.begin()+found);
            cout <<"The passenger " <<ID <<" has been removed" <<endl;
        }
    }
};

class Trip{
    private:
    Date tripDate;
    int train, wagon, seat;
    public:
    Trip(){
        train = wagon = seat = 0;
        tripDate = Date(1,1,1);
    }

    Trip(Date dateoftrip, int numtrain, int numwagon, int numseat){
        tripDate = dateoftrip;
        train = numtrain;
        wagon = numwagon;
        seat = numseat;
    }

    Date getTripDate(){return tripDate;}
    int getTrain(){return train;}
    int getWagon(){return wagon;}
    int getSeat(){return seat;}
    
    void setDate(Date dateoftrip){tripDate = dateoftrip;}
    void setTrain(int num){train = num;}
    void setWagon(int num){wagon = num;}
    void setSeat(int num){seat = num;}    
};

class Train{
private:
    vector <Wagon> wagonsvect;
    string origin, destination;
    float distance;
    Date dateoftrip;
public:
    Train(){
        origin = destination = "";
    }
    Train(string orgn, string dest, float dist, Date tripdate){
        origin = orgn;
        dest = dest;
        distance = dist;
        dateoftrip = tripdate;
    }
    void setOrigin(string originst){origin = originst;}
    void setDest(string destst){destination = destst;}
    void setDist(float mydist){distance = mydist;}
    string getOrigin(){return origin;}
    string getDestination(){return destination;}
    float getDistance(){return distance;}
};

class Passenger{
private:
    string ID,name,adress;
    int age;
    float baggage;
    char gender;
    vector <Trip> travels;
public:
    Passenger(){
        ID = name = adress = "";
        age = baggage = 0;
        gender = ' ';
    }
    Passenger(string pass_ID, string pass_name, string pass_addres, int pass_age, float pass_baggage, char pass_gender){
        ID = pass_ID;
        name = pass_name;
        adress = pass_addres;
        age = pass_age;
        baggage = pass_baggage;
        gender = pass_gender;
    }
    string getID(){return ID;}
    string getname(){return name;}
    string getaddress(){return adress;}
    int getage(){return age;}
    float getbaggage(){return baggage;}
    char getgender(){return gender;}
    
    void setID(string myid){ID = myid;}
    void setName(string myname){name = myname;}
    void setAddress(string myaddress){adress = myaddress;}
    void setAge(int num){age = num;}
    void setBaggage(float num){
        while (num<0 || num>=25){
            cout << "The weight of the baggage isnt valid!";
            cout << "Introduce a quantity between (0-25): ";
            cin >> num;
        }
        baggage = num;
    }
    void setGender(char mygender){
        while (mygender != 'F' && mygender != 'M'){
            cout << "The gender you introduced isnt valid!";
            cout << "The valid options are either F or M: ";
            cin >> mygender;
        }
        gender = mygender;
    }
};

int mainMenu(){
    //usamos string para aceptar cualquier input
    string output;
    cout <<"---------- Choose an option ----------\n1. Add new passenger's trip to a train\n2. Remove a passenger's trip from a train\n3. Show trips of a passenger \n4. Show list of passengers in a specific train\n5. Show an alphabetically ordered list of passengers in all the trains\n6. Show passengers of cities\n7. End program \n";
    cin >>output;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1:output=="2"? 2:output=="3"? 3:output=="4"? 4:output=="5"? 5:output=="6"? 6:output=="7"? 7:0);
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
    Date dia;
    Trip prueba1(1,"leganes","madrid",10,20,2,dia,"DNI1");
    Trip prueba2(1,"leganes","madrid",10,20,5,dia,"DNI2");

}