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
    void addPassengerW(string id){
        pair <int,string> info;
        info.first=reservedSeats.size()+1;
        info.second=id;
        reservedSeats.push_back(info);
    }
    void removePassengerW(string myid){
        int found=-1,count=0;
        for(auto i:reservedSeats){
            if(myid==i.second){
                found=count;
                break;
            }
            count++;
        }
        if(found>=0){
            reservedSeats.erase(reservedSeats.begin()+found);
        }
    }
    //solo para consultar, si editas el vetor devuelto el original no cambia
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
    void addPassengerT(string myid){
        for(int w=0;w<wagonsvect.size();w++){
            if(wagonsvect[w].getCapacity()>wagonsvect[w].getSeatVector().size()){
                //aquí hay sitio
                wagonsvect[w].addPassengerW(myid);
                break;
            }
        }
    }
    void removePassengerT(string myid){
        bool found=0;
        for(int w=0;w<wagonsvect.size();w++){
            if(wagonsvect[w].getSeat(myid)!=-1){
                wagonsvect[w].removePassengerW(myid);
                found=1;
                break;
            }
        }
        if(found==0){
            cout <<"passenger not found" <<endl;
        }
    }
    pair <int,int> findPassenger(string myid){
        pair <int,int> found;   //wagon-seat
        found.first=-1;
        found.second=-1;
        for(int w=0;w<wagonsvect.size();w++){
            if(wagonsvect[w].getSeat(myid)!=-1){
                found.first=w;
                found.second=wagonsvect[w].getSeat(myid);
                break;
            }
        }
        return found;
    }
    
    //solo consulta (igual que el de Wagon)
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
    void removeTrip(Date dia,int t,int w,int s){
        for(int i=0;i<travels.size();i++){
            if(travels[i].getTripDate()==dia && travels[i].getTrain()==t && travels[i].getWagon()==w && travels[i].getSeat()==s){
                travels.erase(travels.begin()+i);
            } 
        }
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

void addNewPassengerTrip(Date dia,string station1,string station2,string myid){
    //comprobar si el pasajero existe
    int position=-1;
    for(int i=0;i<gentezuela.size();i++){
        if(gentezuela[i].getID()==myid){
            position=i;
            break;
        }
    }
    if(position==-1){
        Passenger unregistered;
        unregistered.setID(myid);
        gentezuela.push_back(unregistered);
        position=gentezuela.size()-1;
    }
    //comprobar trenes que coindcidan en fecha e itinerario
    bool found=0;
    for(int t=0;t<trenes.size();t++){
        if(trenes[t].getDate()==dia && trenes[t].getOrigin()==station1 && trenes[t].getDestination()==station2){
            //este tren coincide
            if (trenes[t].findPassenger(myid).first!=-1 && trenes[t].findPassenger(myid).second!=-1){
                found=1;
                cout <<"Passenger " <<myid <<" already registered in train " <<t <<", wagon " <<trenes[t].findPassenger(myid).first <<", seat " <<trenes[t].findPassenger(myid).second <<endl;
                break;
            }
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
                trenes[t].addPassengerT(myid);
                auto w=trenes[t].findPassenger(myid);
                if(w.first!=-1 && w.second!=-1){
                    cout <<"Passenger " <<myid <<" added to train " <<t <<", wagon " <<w.first <<", seat " <<w.second <<endl;
                    //También hay que añadirle el viaje al pasajero
                    gentezuela[position].addTrip(dia,t,w.first,w.second);
                    added=1;
                    break;
                }
            }
        }
        if(added==0){
            cout <<"All trains " <<station1 <<"-" <<station2 <<" are full" <<endl;
        }
    }
}

void removePassengerTrip(Date dia,string station1,string station2,string myid){
    //comprobar si el pasajero existe
    int position=-1;
    bool found=0;
    for(int i=0;i<gentezuela.size();i++){
        if(gentezuela[i].getID()==myid){
            position=i;
            break;
        }
    }
    if(position!=-1){
        for(int t=0;t<trenes.size();t++){
            if(trenes[t].getDate()==dia && trenes[t].getOrigin()==station1 && trenes[t].getDestination()==station2){
                //tren coincide con la ruta
                if(trenes[t].findPassenger(myid).first!=-1 && trenes[t].findPassenger(myid).second!=-1){
                    cout <<"Passenger " <<myid <<" removed from train " <<t <<", wagon " <<trenes[t].findPassenger(myid).first <<", seat " <<trenes[t].findPassenger(myid).second <<endl;
                    trenes[t].removePassengerT(myid);
                    gentezuela[position].removeTrip(dia,t,trenes[t].findPassenger(myid).first,trenes[t].findPassenger(myid).second);
                    found=1;
                    break;
                }
            }
        }
    }
    
    if(found==0 || position==-1){
        cout <<"Not found" <<endl;
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


    //TESTEO

    Date dia;
    string estacion1="leganes",estacion2="madrid",ID[11]={"AAA","BBB","CCC","DDD","EEE","FFF","GGG","HHH","III","JJJ","KKK"};
    Train trenPrueba(estacion1,estacion2,5,dia);
    trenes.push_back(trenPrueba);
    //tren extra
    trenes.push_back(trenPrueba);
    for(int i=0;i<11;i++){
        addNewPassengerTrip(dia,estacion1,estacion2,ID[i]);
    }
    removePassengerTrip(dia,estacion1,estacion2,"III");
    removePassengerTrip(dia,"king's cross",estacion2,"AAA");
    
    cout <<endl <<"----- Tren 0 -----" <<endl;
    cout <<" ·vagon 0 tiene " <<trenes[0].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" ·vagon 1 tiene " <<trenes[0].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
    cout <<"----- Tren 1 -----" <<endl;
    cout <<" ·vagon 0 tiene " <<trenes[1].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" ·vagon 1 tiene " <<trenes[1].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
}