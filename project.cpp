//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cmath>
using namespace std;

//NO LEER
bool validDate(int num1,int num2,int num3){
    bool leapYear;
        if(num1>0 && num2>0 && num2<=12 && num3>0){
            leapYear=(num3%400==0?1:num3%100==0?0:num3%4==0?1:0);
            if(num2==2 && ((leapYear==1 && num1>29) || (leapYear==0 && num1>28))){
                return 0;
            }else if((num2==1 || num2==3 || num2==5 || num2==7 || num2==8 || num2==10 || num2==12) && num1>31){
                return 0;
            }else if((num2==4 || num2==6 || num2==9 || num2==11) && num1>30){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 0;
        }
}
//cortesía de pruebas.cpp
class Date{
    private:
    int day,month,year;
    public:
    Date(){day=month=year=1;}
    Date(int num1,int num2,int num3){
        if(validDate(num1,num2,num3)==1){
            day=num1;
            month=num2;
            year=num3;
        }else{
            cout <<"invalid date" <<endl;
            day=month=year=1;
        }
    }
    void setDay(int num){
        if(validDate(num,month,year)){day=num;}
        else{cout <<"invalid date" <<endl;}
    }
    void setMonth(int num){
        if(validDate(day,num,year)){month=num;}
        else{cout <<"invalid date" <<endl;}
    }
    void setYear(int num){
        if(validDate(day,month,num)){year=num;}
        else{cout <<"invalid date" <<endl;}
    }
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
    bool operator <(Date input){
        long long int a,b;
        //y0000+m00+d=y/mm/dd
        a=day+month*100+year*10000;
        b=input.day+input.month*100+input.year*10000;
        return a<b;
    }
    bool operator >(Date input){
        long long int a,b;
        a=day+month*100+year*10000;
        b=input.day+input.month*100+input.year*10000;
        return a>b;
    }
    
    void printDate(){
        cout <<(day<10?"0":"") << day << ":" <<(month<10?"0":"") << month << ":";
        for(int i=1;i<4-floor(log10(year));i++){cout <<"0";}    //añadimos ceros al año
        cout << year << endl;
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
        for(int w=0; w<wagonsvect.size(); w++){
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
        for(int w=0; w<wagonsvect.size(); w++){
            if(wagonsvect[w].getSeat(myid)!= -1){
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
    vector <Trip> getTrips(){return travels;}
    
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
        for(int i=0; i<travels.size(); i++){
            if(travels[i].getTripDate()==dia && travels[i].getTrain()==t && travels[i].getWagon()==w && travels[i].getSeat()==s){
                travels.erase(travels.begin()+i);
                break;
            } 
        }
    }
};

//para poder buscar objetos dado un "atributo"
static vector <Train> trenes;
static vector <Passenger> gentezuela;

void readInitialData(list<Train>initialLstOfTrains, map<int,Passenger>initialMapIDPass){
    

}

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
            if (trenes[t].findPassenger(myid).first != -1 && trenes[t].findPassenger(myid).second != -1){
                found = 1;
                cout <<"Passenger " <<myid <<" already registered in train " << t <<", wagon " << trenes[t].findPassenger(myid).first <<", seat " <<trenes[t].findPassenger(myid).second <<endl;
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
                auto w = trenes[t].findPassenger(myid);
                if(w.first != -1 && w.second != -1){
                    cout <<"Passenger " << myid <<" added to train " << t <<", wagon " << w.first <<", seat " << w.second << endl;
                    //También hay que añadirle el viaje al pasajero
                    gentezuela[position].addTrip(dia,t,w.first,w.second);
                    added=1;
                    break;
                }
            }
        }
        if(added==0){
            cout <<"All trains " << station1 << "-" <<station2 <<" are full" <<endl;
        }else if (added==1){
            cout << "Trip added succesfully!" << endl;
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
                    gentezuela[position].removeTrip(dia,t,trenes[t].findPassenger(myid).first,trenes[t].findPassenger(myid).second);
                    trenes[t].removePassengerT(myid);
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

void showTripsOfPassenger(){
    string idPass;
    cout << "Introduce the ID of the passenger: ";
    cin >> idPass;
    int position=-1;
    vector <Trip> travelsPass;
    for(int i=0; i<gentezuela.size(); i++){
        if(gentezuela[i].getID() == idPass){
            position = i;
            travelsPass = gentezuela[i].getTrips();
            break;
        }
    }
    if(position != -1){
        if(travelsPass.size()>0){
            cout << "This is the list of trips for passenger " << idPass << ":" << endl;
            int count = 1;
            for (Trip tr:travelsPass){
                cout << "\n----------Information Trip " << count << "----------" << endl;
                cout << "Date: ";
                tr.getTripDate().printDate();
                cout << "Train: " << tr.getTrain() << " Wagon: " << tr.getWagon()  << " Seat: " << tr.getSeat() << endl;
            }
        }else{
            cout <<"The passenger " <<idPass <<" has no trips" <<endl;
        }
    }else{
        cout << "The passenger you introduced was not found!" << endl;
    }
}

void showListOfPassengers(int t){
    if(trenes.size()<t){
        cout <<"Train doesnt exist" <<endl;
    }else{
        for(int i=0;i<trenes[t].getWagons().size();i++){
            cout <<"  ~~~ Vagón " <<i <<" ~~~" <<endl;
            if(trenes[t].getWagons()[i].getSeatVector().size()==0){
                cout <<"vacío" <<endl;
            }else{
                for(int j=0;j<trenes[t].getWagons()[i].getSeatVector().size();j++){
                    cout <<trenes[t].getWagons()[i].getSeatVector()[j].second <<endl;
                }
            }
        }
    }
}

//TEMPORAL
//Porque necesitamos algo parecido a Trip pero incluyendo origen-destino
struct pseudotrip{
    Date tripDate;
    int wagon,seat;
    //cambiamos el numero de tren por las estaciones
    string origin,destination;
};

list <pair <string,vector <pseudotrip>>> showOrderedListOfPassengers(){
    //nombre-vector(dia,origen,destino,vagon,sitio)
    list <pair <string,vector <pseudotrip>>> output;
    pair <string,vector <pseudotrip>> bigAux;
    pseudotrip smolAux;
    for(auto p:gentezuela){
        //nombre
        bigAux.first=p.getname();
        for(auto t:p.getTrips()){
            //el resto (menos origen y destino destino)
            smolAux.tripDate=t.getTripDate();
            smolAux.wagon=t.getWagon();
            smolAux.seat=t.getSeat();
            //origen y destino
            smolAux.origin=trenes[t.getTrain()].getOrigin();
            smolAux.destination=trenes[t.getTrain()].getDestination();
            bigAux.second.push_back(smolAux);
        }
        auto it=output.begin();
        int preInsertionSize=output.size();
        while(it!=output.end()){
            if((*it).first>bigAux.first){
                output.insert(it,bigAux);
                break;
            }else{it++;}
        }
        //no se ha insertado porque el iterador no llega al final asi que se mete al final ´\(º_º)/`
        if(preInsertionSize==output.size()){
            output.push_back(bigAux);
        }
        //limpiamos bigAux
        bigAux.first="";
        bigAux.second.clear();
    }
    bool printedSomething;
    for(auto p:output){
        printedSomething=0;
        cout <<p.first <<":" <<endl;
        for(auto viajes:p.second){
            printedSomething=1;
            cout <<"    " <<viajes.origin <<"-" <<viajes.destination <<" Date ";
            viajes.tripDate.printDate();
            cout <<"    Wagon " <<viajes.wagon <<" sitio " <<viajes.seat <<endl <<endl;
        }
        if(printedSomething==0){
            cout <<"    no trips" <<endl;
        }
    }
    return output;
}

int main(){
    /*int selection;
    string origin,destination,myid;
    Date d;
    int num;            
    while(selection!=7){
        selection=mainMenu();
        switch (selection){
            case 0:
                cout <<"Please, choose a valid option" <<endl;
                break;
            case 7:
                cout <<"Goodbye";
                break;
            case 1:
                cout <<"Introduce your ID: ";
                cin >>myid;
                cout <<"Introduce the origin: ";
                cin >>origin;
                cout <<"Introduce the destination: ";
                cin >>destination;
                cout <<"Introduce the day: ";
                cin >>num;
                d.setDay(num);
                cout <<"Introduce the month: ";
                cin >>num;
                d.setMonth(num);
                cout <<"Introduce the year: ";
                cin >>num;
                d.setYear(num);
                addNewPassengerTrip(d,origin,destination,myid);
                break;
            case 2:
                cout <<"Introduce your ID: ";
                cin >>myid;
                cout <<"Introduce the origin: ";
                cin >>origin;
                cout <<"Introduce the destination: ";
                cin >>destination;
                cout <<"Introduce the day: ";
                cin >>num;
                d.setDay(num);
                cout <<"Introduce the month: ";
                cin >>num;
                d.setMonth(num);
                cout <<"Introduce the year: ";
                cin >>num;
                d.setYear(num);
                removePassengerTrip(d,origin,destination,myid);
                break;
        }
    }
*/

    //TESTEO

    Date dia(1,1,10);
    string estacion1 = "Leganes", estacion2 = "Madrid", ID[11]={"FFF","GGG","HHH","III","AAA","BBB","CCC","DDD","EEE","JJJ","KKK"};
    Train trenPrueba(estacion1, estacion2 , 5 , dia);
    trenes.push_back(trenPrueba);
    //tren extra
    trenes.push_back(trenPrueba);
    for(int i=0;i<11;i++){
        addNewPassengerTrip(dia,estacion1,estacion2,ID[i]);
        gentezuela[i].setName(ID[i]);
    }
    removePassengerTrip(dia,estacion1,estacion2,"III");
    
    cout << endl <<"----- Tren 0 -----" << endl;
    cout <<" Vagon 0 tiene " <<trenes[0].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" Vagon 1 tiene " <<trenes[0].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
    showListOfPassengers(0);
    cout <<"----- Tren 1 -----" <<endl;
    cout <<" Vagon 0 tiene " <<trenes[1].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" Vagon 1 tiene " <<trenes[1].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
    showListOfPassengers(1);
    showOrderedListOfPassengers();
}