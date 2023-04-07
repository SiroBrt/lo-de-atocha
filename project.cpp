//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <fstream>

using namespace std;


int counter(string s, char x){
    int count = 0;
    for (int i=0; i<s.length(); i++){
        if (s.at(i) == x){
            count = count + 1;
        }
    }
    return count;
}

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
    Wagon(int numseats, int numofwaagon, vector <pair <int,string>> reserv_seats){
        if(numseats>=5){
            capacity=numseats;
        }else{
            cout <<"\nThe minimum number of seats in a wagon is 5" <<endl;
            capacity = 5;
        }
        wagonNumber = numofwaagon;
        reservedSeats = reserv_seats;

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
    int getSeatfromID(string id){
        int output=-1;
        for(auto i:reservedSeats){
            if(id==i.second){
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
    int train, wagon, seat, prize, distance;
    public:
    Trip(){
        train = wagon = seat = 0;
        tripDate = Date(1,1,1);
        prize = 0;
    }

    Trip(Date dateoftrip, int numtrain, int numwagon, int numseat, int tripprize){
        tripDate = dateoftrip;
        train = numtrain;
        wagon = numwagon;
        seat = numseat;
        prize = tripprize;
    }

    Date getTripDate(){return tripDate;}
    int getTrain(){return train;}
    int getWagon(){return wagon;}
    int getSeat(){return seat;}
    int getPrize(){return prize;}
    
    void setDate(Date dateoftrip){tripDate = dateoftrip;}
    void setTrain(int num){train = num;}
    void setWagon(int num){wagon = num;}
    void setSeat(int num){seat = num;}
    void setPrize(int myprize){prize = myprize;}
    void setDistance(int tripdistanceinkm){distance = tripdistanceinkm;}    
};

class Train{
private:
    int trainnum; 
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
        trainnum = 0;
    }
    Train(int numoftrain, string orgn, string dest, float dist, Date tripdate, vector <Wagon> vectorofwagons){
        trainnum = numoftrain;
        origin = orgn;
        destination = dest;
        distance = dist;
        dateoftrip = tripdate;
        wagonsvect = vectorofwagons;
    }
    void setOrigin(string originst){origin = originst;}
    void setDest(string destst){destination = destst;}
    void setDist(float mydist){distance = mydist;}
    void setDate(Date input){dateoftrip=input;}
    string getOrigin(){return origin;}
    string getDestination(){return destination;}
    float getDistance(){return distance;}
    Date getDate(){return dateoftrip;}
    int getTrainNum(){return trainnum;}
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
            if(wagonsvect[w].getSeatfromID(myid)!=-1){
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
            if(wagonsvect[w].getSeatfromID(myid)!= -1){
                found.first=w+1;
                found.second=wagonsvect[w].getSeatfromID(myid);
                break;
            }
        }
        return found;
    }
    
    //solo consulta (igual que el de Wagon)
    vector <Wagon> getWagons(){return wagonsvect;}
};

Train getTrainfromNum(list <Train> mytrenecitos, int n){
    for (auto t:mytrenecitos){
        if (t.getTrainNum()==n){
            return t;
        }
    }
}

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
    void addTrip(Date dia,int t,int w,int s, int p){
        Trip newTrip(dia,t,w,s,p);
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



void readInitialData(list <Train> &initialLstOfTrains, map <string,Passenger> &initialMapIDPass){
    //haber si sale bien
    ifstream trainfi;
    trainfi.open("trenes.txt");
    if (!trainfi){
        cout << "\nFile not found!" << endl;
        exit(1);
    }
    string title;
    getline(trainfi, title);
    string input;
    int traincounter = 0;
    while (getline(trainfi, input)){
        traincounter = traincounter+1;
        int pos = input.find(" | ");
        int trainNumber = stoi(input.substr(0, pos));

        // Extract the date
        input = input.substr(pos + 3);
        pos = input.find("-");
        int year = stoi(input.substr(0, pos));
        input = input.substr(pos + 1);
        pos = input.find("-");
        int month = stoi(input.substr(0, pos));
        input = input.substr(pos + 1);
        pos = input.find(" | ");
        int day = stoi(input.substr(0, pos));

        // Extract the origin and destination stations
        input = input.substr(pos + 3);
        pos = input.find(" | ");
        string originStation = input.substr(0, pos);
        input = input.substr(pos + 3);
        pos = input.find(" | ");
        string destStation = input.substr(0, pos);

        // Extract the distance in kilometers and the number of wagons in the train
        input = input.substr(pos + 3);
        pos = input.find(" | ");
        int distanceInKm = stoi(input.substr(0, pos));
        input = input.substr(pos + 3);
        pos = input.find(" | ");
        int numWagons = stoi(input.substr(0, pos));

        // Extract the number of seats per wagon
        vector <int> seatsperwagon;
        input = input.substr(pos + 3);
        for (int i=1; i<numWagons; i++){
            int pos2 = input.find(", ");
            int seatsinwagon = stoi(input.substr(0, pos2));
            seatsperwagon.push_back(seatsinwagon);
            input = input.substr(pos2 + 2);            
        }
        pos = input.find(" | ");
        int seatsinlastwagon = stoi(input.substr(0, pos));
        seatsperwagon.push_back(seatsinlastwagon);
        input = input.substr(pos + 3);

        // Extract the IDs of the passengers in each wagon
        vector <vector <int>> idsintrain;
        idsintrain.clear();
        int numofwagonswithpeople;
        numofwagonswithpeople = counter(input, '-')+1;
        for (int k=1; k<=numofwagonswithpeople; k++){
            vector <int> idsinwagon;
            idsinwagon.clear();
            pos = input.find(" - ");
            string id_substr = input.substr(0, pos);
            int occupiedseats = counter(id_substr, ',');
            for (int j=1; j<=occupiedseats; j++){
                int pos2 = id_substr.find(", ");
                int id = stoi(id_substr.substr(0, pos2));
                idsinwagon.push_back(id);
                id_substr = id_substr.substr(pos2+2);            
            }
            int lastid = stoi(id_substr);
            idsinwagon.push_back(lastid);
            idsintrain.push_back(idsinwagon);
            input = input.substr(pos+3);
        }
        // Prints the info so we know its working correctly
        cout << "\nTrain " << trainNumber << " goes from: " << originStation << " to " << destStation << ", covering " << distanceInKm <<" km.\n";
        cout << "The date of the trip is " << day << ":" << month << ":" << year;
        cout << "\nThis train has " << numWagons << " wagons.\n";
        int count = 1;
        for (auto p:seatsperwagon){
            cout << "Wagon " << count << " has " << p << " seats\n";
            count++;
        }
        int c1 = 1, c2 = 1;
        cout << "These are the IDs of the people in each train per wagon: \n";
        for(auto idsinwag:idsintrain){
            cout << "Wagon " << c1 << ":\n";
            for (int i = 0; i<idsinwag.size(); i++){
                cout << idsinwag[i] << endl;
            }
            c1++;
        }

        Date mydate{day, month, year};
        vector <Wagon> myWagons;
        myWagons.clear();
        for (int q=0; q < idsintrain.size(); q++){
            int numofWagon = q+1;
            vector <int> mywagids = idsintrain[q];
            vector <pair <int,string>> myreservedSeats;
            for (int s=0; s<mywagids.size(); s++){
                pair <int, string> myseat;
                myseat.first = s+1;
                int id = mywagids[s];
                myseat.second = to_string(id);
                myreservedSeats.push_back(myseat);
            }
            int capaci = seatsperwagon[q];
            Wagon wag{capaci, numofWagon, myreservedSeats};
            myWagons.push_back(wag);
        }
        Train mytrain{traincounter, originStation, destStation, (float)distanceInKm, mydate, myWagons}; 
        initialLstOfTrains.push_back(mytrain);
    }
}

int mainMenu(){
    //usamos string para aceptar cualquier input
    string output;
    cout <<"---------- Choose an option ----------\n1. Add new passenger's trip to a train\n2. Remove a passenger's trip from a train\n3. Show trips of a passenger \n4. Show list of passengers in a specific train\n5. Show an alphabetically ordered list of passengers in all the trains\n6. Show passengers of cities\n7. End program \n";
    cin >>output;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1 : output=="2"? 2 : output=="3"? 3 : output=="4"? 4 : output=="5"? 5 : output=="6" ? 6 :output=="7"? 7 : 0);
}

void addNewPassengerTrip(list <Train> &trenes, map <string, Passenger> &passes){
    string origin,destination,myid;
    Date dia;
    int num, prizeofthetrip;
    cout <<"Introduce your ID: ";
    cin >> myid;
    cout <<"Introduce the origin: ";
    cin >> origin;
    cout <<"Introduce the destination: ";
    cin >> destination;
    cout <<"Introduce the day: ";
    cin >> num;
    dia.setDay(num);
    cout <<"Introduce the month: ";
    cin >>num;
    dia.setMonth(num);
    cout <<"Introduce the year: ";
    cin >>num;
    dia.setYear(num);
    cout<<"Introduce the prize of the trip: ";
    cin >> prizeofthetrip;

    //comprobar si el pasajero existe
    string foundID = "0";
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).second.getID()==myid){
            foundID = (*it).first;
            break;
        }
    }
    if(foundID=="0"){
        Passenger unregistered;
        unregistered.setID(myid);
        passes[myid] = unregistered;
        cout << "Passenger was not found in the data base";
    }
    //comprobar trenes que coincidan en fecha e itinerario
    bool personfound=0;
    bool trainfound=0;
    for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
        if((*train_it).getDate()==dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
            //este tren coincide
            cout << "There is a train that fits this description";
            trainfound = 1;
            if ((*train_it).findPassenger(myid).first != -1 && (*train_it).findPassenger(myid).second != -1){
                personfound = 1;
                cout <<"Passenger " << myid <<" already registered in train " << (*train_it).getTrainNum() <<", wagon " << (*train_it).findPassenger(myid).first <<", seat " <<(*train_it).findPassenger(myid).second <<endl;
                break;
            }
        }
        if(personfound==1){break;}
    }
    //si no está lo añadimos
    if(personfound==0 && trainfound==1){
        bool added=0;
        //mismo sistema para trenes y vagones
        for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
            if((*train_it).getDate()==dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
                //este tren coincide
                (*train_it).addPassengerT(myid);
                auto w = (*train_it).findPassenger(myid);
                if(w.first != -1 && w.second != -1){
                    cout <<"Passenger " << myid <<" added to train " << (*train_it).getTrainNum() <<", wagon " << w.first <<", seat " << w.second << endl;
                    //También hay que añadirle el viaje al pasajero
                    passes[myid].addTrip(dia,(*train_it).getTrainNum(),w.first,w.second, prizeofthetrip);
                    added=1;
                    break;
                }
            }
        }
        if(added==0){
            cout <<"The train from " << origin << "" << destination <<" is already full" <<endl;
        }else if (added==1){
            cout << "Trip added succesfully!" << endl;
        }
    }else if(trainfound==0){
        cout << "\nThere are no trains fitting this description";
    }
}

void removePassengerTrip(list <Train> &trenes, map <string, Passenger> &passes){
    int num;
    string myid, origin, destination;
    Date d;
    cout <<"Introduce your ID: ";
    cin >> myid;
    cout <<"Introduce the origin: ";
    cin >> origin;
    cout <<"Introduce the destination: ";
    cin >> destination;
    cout <<"Introduce the day: ";
    cin >>num;
    d.setDay(num);
    cout <<"Introduce the month: ";
    cin >>num;
    d.setMonth(num);
    cout <<"Introduce the year: ";
    cin >>num;
    d.setYear(num);

    //comprobar si el pasajero existe
    string foundID = "0";
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).second.getID()==myid){
            foundID = (*it).first;
            break;
        }
    }
    bool foundtrip=0;
    if(foundID != "0"){
        for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
            if((*train_it).getDate()== d && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
                //tren coincide con la ruta
                if((*train_it).findPassenger(myid).first !=-1 && (*train_it).findPassenger(myid).second!=-1){
                    cout <<"\nPassenger " << myid <<" has been removed from train " << (*train_it).getTrainNum() << ", wagon " << (*train_it).findPassenger(myid).first << ", seat " << (*train_it).findPassenger(myid).second <<endl;
                    passes[myid].removeTrip(d,(*train_it).getTrainNum(), (*train_it).findPassenger(myid).first, (*train_it).findPassenger(myid).second);
                    (*train_it).removePassengerT(myid);
                    foundtrip=1;
                    break;
                }
            }
        }
    }else{
        cout <<"\nThe trip you are trying to remove could not be found!" <<endl;
    }
}

void showTripsOfPassenger(map <string, Passenger> &passes){
    string idPass;
    cout << "Introduce the ID of the passenger: ";
    cin >> idPass;
    int position=-1;
    vector <Trip> travelsPass;
    bool foundID = 0;
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).first == idPass){
            travelsPass = (*it).second.getTrips();
            foundID = 1;
            break;
        }
    }
    if(foundID){
        if(travelsPass.size()>0){
            cout << "This is the list of trips for passenger " << idPass << ":" << endl;
            int count = 1;
            for (Trip tr:travelsPass){
                cout << "\n----------Information Trip " << count << "----------" << endl;
                cout << "Date: ";
                tr.getTripDate().printDate();
                cout << "\nTrain: " << tr.getTrain() << " \nWagon: " << tr.getWagon()  << " \nSeat: " << tr.getSeat() << endl;
            }
        }else{
            cout <<"The passenger " <<idPass <<" has no trips" <<endl;
        }
    }else{
        cout << "\nThe passenger you introduced was not found!" << endl;
    }
}

void showListOfPassengers(list <Train> &trenes, map <string, Passenger> &passes){
    int t;
    cout << "\nIntroduce the number of the train: ";
    cin >> t;
    if(trenes.size()<t){
        cout <<"\nThis train does not exist!" <<endl;
    }else{
        Train mytrain = getTrainfromNum(trenes, t);
        for(int i=0;i<mytrain.getWagons().size();i++){
            cout <<"  ~~~ Wagon " << i+1 <<" ~~~" <<endl;
            if(mytrain.getWagons()[i].getSeatVector().size()==0){
                cout <<"This wagon is empty" <<endl;
            }else{
                for(int j=0;j<mytrain.getWagons()[i].getSeatVector().size();j++){
                    string idofpass = mytrain.getWagons()[i].getSeatVector()[j].second;
                    string name = passes[idofpass].getname();
                    cout << "Seat " << j+1 << " - " << name << " with ID: " << idofpass << endl;
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

//Esto hay que cambiarlo
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
    cout << "Mis pruebecillas:" << endl;
    list <Train> mytrains;
    map <string, Passenger> mypasses;
    readInitialData(mytrains, mypasses);
    cout << endl << "FIN VIR\n\n\n";
    int selection;
    
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
                addNewPassengerTrip(mytrains, mypasses);
                break;
            case 2:
                removePassengerTrip(mytrains, mypasses);
                break;
            case 3:
                showTripsOfPassenger(mypasses);
                break;
            case 4:
                showListOfPassengers(mytrains, mypasses);
                break;
        }
    }


    //TESTEO

    Date dia(2,5,2023);
    string estacion1 = "Madrid", estacion2 = "Lisbon", ID[11]={"92","119","216","69","34","BBB","CCC","DDD","EEE","JJJ","KKK"};
    
    //cout << endl <<"----- Tren 0 -----" << endl;
    //cout <<" Vagon 0 tiene " <<trenes[0].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" Vagon 1 tiene " <<trenes[0].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
    //showListOfPassengers(0);
    //cout <<"----- Tren 1 -----" <<endl;
    //cout <<" Vagon 0 tiene " <<trenes[1].getWagons()[0].getSeatVector().size() <<" pasajeros" <<endl <<" Vagon 1 tiene " <<trenes[1].getWagons()[1].getSeatVector().size() <<" pasajeros" <<endl;
    //showListOfPassengers(1);
    //showOrderedListOfPassengers();
}