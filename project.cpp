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
    bool operator ==(Date input){
        if(input.day==day && input.month==month && input.year==year){
            return 1;
        }else{
            return 0;
        }
    }
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
                cout <<"Passenger added" <<endl;
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
    vector <pair <int,string>> getSeatVector(){return reservedSeats;}
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
        //mínimo de dos vagones
        Wagon vacio;
        wagonsvect.push_back(vacio);
        vacio.setNumber(2);
        wagonsvect.push_back(vacio);
    }
    Train(string orgn, string dest, float dist, Date tripdate){
        origin = orgn;
        destination = dest;
        distance = dist;
        dateoftrip = tripdate;
        Wagon vacio;
        wagonsvect.push_back(vacio);
        vacio.setNumber(2);
        wagonsvect.push_back(vacio);
    }
    void setOrigin(string originst){origin = originst;}
    void setDest(string destst){destination = destst;}
    void setDist(float mydist){distance = mydist;}
    void setDate(Date input){dateoftrip=input;}
    string getOrigin(){return origin;}
    string getDestination(){return destination;}
    float getDistance(){return distance;}
    Date getDate(){return dateoftrip;}
    vector <Wagon> getWagons(){return wagonsvect;}
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
        if (num<0 || num>=25){
            cout << "The weight of the baggage isnt valid!";
        }else{
            baggage = num;
        }
    }
    void setGender(char mygender){
        if (mygender != 'F' && mygender != 'M'){
            cout << "The gender you introduced isnt valid!";
        }else{
            gender = mygender;
        }
    }
    void addTrip(Date dia,int t,int w,int s){
        Trip newTrip(dia,t,w,s);
        travels.push_back(newTrip);
    }
};

//para poder buscar objetos dado un "atributo"
static vector <Train> trenes;
static vector <Passenger> gentezuela;

int mainMenu(){
    //usamos string para aceptar cualquier input
    string output;
    cout <<"---------- Choose an option ----------\n1. Add new passenger's trip to a train\n2. Remove a passenger's trip from a train\n3. Show trips of a passenger \n4. Show list of passengers in a specific train\n5. Show an alphabetically ordered list of passengers in all the trains\n6. Show passengers of cities\n7. End program \n";
    cin >>output;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1:output=="2"? 2:output=="3"? 3:output=="4"? 4:output=="5"? 5:output=="6"? 6:output=="7"? 7:0);
}

void addNewPassengerTrip(Date dia,string station1,string station2,string id){
    //comprobar si el pasajero existe
    int position=-1;
    for(int i=0;i<gentezuela.size();i++){
        if(gentezuela[i].getID()==id){
            position=i;
            break;
        }
    }
    if(position==-1){
        Passenger unregistered;
        unregistered.setID(id);
        gentezuela.push_back(unregistered);
        position=gentezuela.size()-1;
    }
    
    //comprobar trenes que coindcidan en fecha e itinerario
    bool found=0;
    for(int t=0;t<trenes.size();t++){
        if(trenes[t].getDate()==dia && trenes[t].getOrigin()==station1 && trenes[t].getDestination()==station2){
            //este tren coincide
            for(int w=0;w<trenes[t].getWagons().size();w++){
                //vamos vagón por vagón
                for(int s=0;s<trenes[t].getWagons()[w].getSeatVector().size();s++){
                    if(trenes[t].getWagons()[w].getSeatVector()[s].second==id){
                        found=1;
                        cout <<"Passenger already registered in train " <<t <<", wagon " <<w <<", seat " <<s <<endl;
                        break;
                    }
                }
                if(found==1){break;}
            }
            if(found==1){break;}
        }
        if(found==1){break;}
    }
    //si no está lo añadimos
    if(found==0){
        bool added=0;
        //mismo sistema para trenes y vagones
        for(int t=0;t<trenes.size();t++){
            if(trenes[t].getDate()==dia && trenes[t].getOrigin()==station1 && trenes[t].getDestination()==station2){
                //este tren coincide
                for(int w=0;w<trenes[t].getWagons().size();w++){
                    //vamos vagón por vagón
                    if(trenes[t].getWagons()[w].getCapacity()>trenes[t].getWagons()[w].getSeatVector().size()){
                        //añadimos el pasajero al vagón correspondiente
                        pair <int,string> info;
                        info.first=trenes[t].getWagons()[w].getSeatVector().size()+1;
                        info.second=id;
                        trenes[t].getWagons()[w].addPassenger(info);
                        cout <<"Passenger added to train " <<t <<", wagon " <<w <<", seat " <<info.first <<endl;
                        

                        //
                        cout <<"sentado en " <<trenes[t].getWagons()[w].getSeat(id) <<endl;
                        auto aux1=trenes[t].getWagons()[w].getSeatVector();
                        cout <<trenes[t].getWagons().size() <<" vagones, " <<aux1.size() <<" pasajeros de " <<trenes[t].getWagons()[w].getCapacity() <<endl;
                        //


                        //También hay que añadirle el viaje al pasajero
                        gentezuela[position].addTrip(dia,t,w,info.first);
                        added=1;
                        break;
                    }
                    if(added==1){break;}
                }
                if(added==1){break;}
            }
            if(added==1){break;}
        }
    }
}

int main(){
    /*int selection;
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
    }*/
    Date dia;
    string estacion1="leganes",estacion2="madrid",ID="AAA";
    Train barco(estacion1,estacion2,5,dia);
    trenes.push_back(barco);
    auto aux1=trenes[0].getWagons()[0].getSeatVector();
    auto aux2=trenes[0].getWagons()[1].getSeatVector();
    cout <<trenes[0].getWagons().size() <<" vagones, " <<aux1.size()+aux2.size() <<" pasajeros" <<endl;
    //añadimos pasajero
    addNewPassengerTrip(dia,estacion1,estacion2,ID);
}