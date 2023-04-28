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

//Original idea: Yan
int inputInt(string question){
    string aux;
    int num;
    bool done=0,error=0;
    do {
        try {
            cout <<question;
            cin >> aux;
            num=stoi(aux);
            done=1;
        }
        catch (...) {
            cout <<"\033[31;1m" <<"invalid input" <<"\033[0m\033[A\033[2K";
            for (int i=0; i<13; i++){cout <<"\033[D";}      //13 porque "invalid input".size()=13
            error=1;
        }
    }while(!done);
    if(error==1){cout <<"\033[2K";}
    return num;
}

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
    //solo para consultar, si editas el vector devuelto el original no cambia
    vector <pair <int,string>> getSeatVector(){return reservedSeats;}
};

class Trip{
    private:
    Date tripDate;
    int train, wagon, seat, price, distance;
    public:
    Trip(){
        train = wagon = seat = 0;
        tripDate = Date(1,1,1);
        price = 0;
    }

    Trip(Date dateoftrip, int numtrain, int numwagon, int numseat, int tripprice){
        tripDate = dateoftrip;
        train = numtrain;
        wagon = numwagon;
        seat = numseat;
        price = tripprice;
    }

    Date getTripDate(){return tripDate;}
    int getTrain(){return train;}
    int getWagon(){return wagon;}
    int getSeat(){return seat;}
    int getprice(){return price;}
    
    void setDate(Date dateoftrip){tripDate = dateoftrip;}
    void setTrain(int num){train = num;}
    void setWagon(int num){wagon = num;}
    void setSeat(int num){seat = num;}
    void setprice(int myprice){price = myprice;}
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
    void setTrainNum(int input){trainnum=input;}
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
    bool checkTrain(){
        //go through the train comparing all ids so nobody is twice
        string currentId;
        int counter;
        for(auto w1:wagonsvect){
            for(auto p1:w1.getSeatVector()){
                counter=0;
                //now go through all wagons comparing
                for(auto w2:wagonsvect){
                    for(auto p2:w2.getSeatVector()){
                        if(p1.second==p2.second){
                            counter++;
                        }

                    }
                }
                if(counter>1){
                    return 0;
                }
            }
        }
        return 1;
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
    //si ha hecho return no llega hasta aqui, solo para evitar posibles errores
    Train problemas;
    problemas.setTrainNum(-1);
    cout <<"train not found" <<endl;
    return problemas;
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

Train gettrainfromnum(int t, list <Train> &trenes){
    Train mytrain{};
    for (auto tr:trenes){
        if (tr.getTrainNum()==t){
            mytrain = tr;
            break;
        }
    }
    return mytrain;
}

void readInitialData(list <Train> &initialLstOfTrains, map <string,Passenger> &initialMapIDPass){
    try{
        ifstream trainfi;
        trainfi.open("trenes.txt");
        if (!trainfi){
            cout <<"\033[1;31m" << "File not found \033[0m" << endl;
            exit(1);
        }
        string title,aux;
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

            // Extract the number of seats per wagon
            vector <int> seatsperwagon;
            pos = input.find(" | ");
            aux=input.substr(0,pos);
            int numWagons;
            numWagons=counter(aux,',')+1;
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
                int occupiedseats = counter(id_substr, ',')+1;
                if(occupiedseats>seatsperwagon[k-1]){
                    cout <<"\033[1;31m" <<"limit of passengers exceeded" <<"\033[0m" <<endl;
                    exit(1);
                }
                for (int j=1; j<occupiedseats; j++){
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
            /*cout << "\nTrain " << trainNumber << " goes from: " << originStation << " to " << destStation << ", covering " << distanceInKm <<" km.\n";
            cout << "The date of the trip is " << day << ":" << month << ":" << year;
            cout << "\nThis train has " << numWagons << " wagons.\n";
            int count = 1;
            for (auto p:seatsperwagon){
                cout << "Wagon " << count << " has " << p << " seats\n";
                count++;
            }
            int c1 = 1;
            cout << "These are the IDs of the people in each train per wagon: \n";
            for(auto idsinwag:idsintrain){
                cout << "Wagon " << c1 << ":\n";
                for (int i = 0; i<idsinwag.size(); i++){
                    cout << idsinwag[i] << endl;
                }
                c1++;
            }*/

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
            if(!mytrain.checkTrain()){
                cout <<"\033[1;31m" <<"Train " <<traincounter <<" has repeated passengers" <<"\033[0m" <<endl;
                exit(1);
            }
            initialLstOfTrains.push_back(mytrain);
        }
        trainfi.close();
        ifstream passengersfi;
        passengersfi.open("passengers.txt");
        if (!passengersfi){
            cout <<"\033[1;31m" << "File not found \033[0m" << endl;
            exit(1);
        }
        string title2;
        getline(passengersfi, title);
        string input2;
        while (getline(passengersfi, input2)){
            // Extract the ID of the passenger
            int pos = input2.find(" | ");
            string id = input2.substr(0, pos);
            input2 = input2.substr(pos + 3);
            // Extract the name of the passenger
            pos = input2.find(" | ");
            string pname = input2.substr(0, pos);
            input2 = input2.substr(pos + 3);
            // Extract the address of the passenger
            pos = input2.find(" | ");
            string paddress = input2.substr(0, pos);
            input2 = input2.substr(pos + 3);
            // Extract the age of the passenger
            pos = input2.find(" | ");
            int page = stoi(input2.substr(0, pos));
            input2 = input2.substr(pos + 3);
            // Extract the gender of the passenger
            pos = input2.find(" | ");
            char pgender = input2.substr(0, pos)[0];
            input2 = input2.substr(pos + 3);
            // Extract the baggage weight of the passenger
            pos = input2.find(" | ");
            float pbag = (float) stoi(input2.substr(0, pos));
            input2 = input2.substr(pos + 3);
            // Extract the number of the train in which the passenger is
            pos = input2.find(" | ");
            int trainnum = stoi(input2.substr(0, pos));
            input2 = input2.substr(pos + 3);
            // Extract the price of the trip
            pos = input2.find(" | ");
            int tripprice = stoi(input2.substr(0, pos));

            bool passfound = 0;
            for (auto p:initialMapIDPass){
                if (p.first==id){
                    passfound = 1;
                    break;
                }
            }
            Passenger mypas(id, pname, paddress, page, pbag, pgender);
            Train mytrain = getTrainfromNum(initialLstOfTrains, trainnum);
            if(mytrain.getTrainNum()==-1){
                cout <<"\033[1;31m" <<"There has been an error with passenger " <<id <<"\033[0m" <<endl;
            }else{
                // We need two different options
                if (!passfound){
                    mypas.addTrip(mytrain.getDate(), trainnum, mytrain.findPassenger(id).first, mytrain.findPassenger(id).second, tripprice);
                    initialMapIDPass[id] = mypas;
                }else{
                    initialMapIDPass[id].addTrip(mytrain.getDate(), trainnum, mytrain.findPassenger(id).first, mytrain.findPassenger(id).second, tripprice);
                }
            }
        }
    }catch(...){
        cout <<"\033[1;31m" <<"error reading files" <<"\033[0m" <<endl;
        exit(1);
    }
}

int mainMenu(){
    //usamos string para aceptar cualquier input
    string output;
    cout <<"\033[32m"
    <<"+--------------------- Choose an option ---------------------+" <<endl
    <<"|     1. Add new passenger's trip to a train                 |" <<endl
    <<"|     2. Remove a passenger's trip from a train              |" <<endl
    <<"|     3. Show trips of a passenger                           |" <<endl
    <<"|     4. Show list of passengers in a specific train         |" <<endl
    <<"|     5. Show an alphabetically ordered list of passengers   |" <<endl
    <<"|        in all the trains                                   |" <<endl
    <<"|     6. Show passengers of cities                           |" <<endl
    <<"|     7. End program                                         |" <<endl
    <<"|                              *                             |" <<endl
    <<"+------------------------------------------------------------+\033[0m\033[A";
    for(int i=0;i<31;i++){cout <<"\033[D";}
    cin >>output;
    cout <<endl;
    //pasar string a int sin stoi (solo queremos del 1 al 7) y si no se puede devuelve 0
    return (output=="1"? 1 : output=="2"? 2 : output=="3"? 3 : output=="4"? 4 : output=="5"? 5 : output=="6" ? 6 :output=="7"? 7 : 0);
}

void addNewPassengerTrip(list <Train> &trenes, map <string, Passenger> &passes){
    string origin,destination,myid;
    Date dia;
    int num, priceofthetrip;
    cout <<"Introduce your ID: ";
    cin >> myid;
    cout <<"Introduce the origin: ";
    cin >> origin;
    cout <<"Introduce the destination: ";
    cin >> destination;
    num=inputInt("Introduce the day: ");
    dia.setDay(num);
    num=inputInt("Introduce the month: ");
    dia.setMonth(num);
    num=inputInt("Introduce the year: ");
    dia.setYear(num);
    priceofthetrip=inputInt("Introduce the price of the trip: ");
    //comprobar si el pasajero existe
    string foundID = "0";
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).first==myid){
            foundID = (*it).first;
            break;
        }
    }
    if(foundID=="0"){
        Passenger unregistered;
        unregistered.setID(myid);
        passes[myid] = unregistered;
    }
    //comprobar trenes que coincidan en fecha e itinerario
    bool personfound=0;
    bool trainfound=0;
    for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
        if((*train_it).getDate()==dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
            //este tren coincide
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
                    passes[myid].addTrip(dia,(*train_it).getTrainNum(),w.first,w.second, priceofthetrip);
                    added=1;
                    break;
                }
            }
        }
        if(added==0){
            cout <<"The train from " << origin << "" << destination <<" is already full" <<endl;
        }else if (added==1){
            cout << "Trip added succesfully" << endl;
        }
    }else if(trainfound==0){
        cout <<"\033[1;31m" <<"Train not found" <<"\033[0m" <<endl;
    }
}

void removePassengerTrip(list <Train> &trenes, map <string, Passenger> &passes){
    int num;
    string myid, origin, destination;
    Date dia;
    cout <<"Introduce your ID: ";
    cin >> myid;
    cout <<"Introduce the origin: ";
    cin >> origin;
    cout <<"Introduce the destination: ";
    cin >> destination;
    num=inputInt("Introduce the day: ");
    dia.setDay(num);
    num=inputInt("Introduce the month: ");
    dia.setMonth(num);
    num=inputInt("Introduce the year: ");
    dia.setYear(num);
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
            if((*train_it).getDate()== dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
                //tren coincide con la ruta
                if((*train_it).findPassenger(myid).first !=-1 && (*train_it).findPassenger(myid).second!=-1){
                    cout <<"\nPassenger " << myid <<" has been removed from train " << (*train_it).getTrainNum() << ", wagon " << (*train_it).findPassenger(myid).first << ", seat " << (*train_it).findPassenger(myid).second <<endl;
                    passes[myid].removeTrip(dia,(*train_it).getTrainNum(), (*train_it).findPassenger(myid).first, (*train_it).findPassenger(myid).second);
                    (*train_it).removePassengerT(myid);
                    foundtrip=1;
                    break;
                }
            }
        }
        if(foundtrip==0){
            cout <<"\033[1;31m" <<"Trip not found" <<"\033[0m" <<endl;
        }
    }else{
        cout <<"\033[1;31m" <<"Passenger not found" <<"\033[0m" <<endl;
    }
}

void showTripsOfPassenger(map <string, Passenger> passes){
    string idPass;
    cout << "Introduce the ID of the passenger: ";
    cin >> idPass;
    int position=-1;
    vector <Trip> travelsPass;
    bool foundID = 0;
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).first == idPass){
            cout <<(*it).second.getname();
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
                count++;
            }
        }else{
            cout <<"The passenger " <<idPass <<" has no trips" <<endl;
        }
    }else{
        cout <<"\033[1;31m" <<"Passenger not found" <<"\033[0m" << endl;
    }
}

void showListOfPassengers(list <Train> trenes, map <string, Passenger> passes){
    int t;
    bool found=0;
    t=inputInt("Introduce the number of the train: ");
    for(auto i:trenes){
        if(i.getTrainNum()==t){
            found=1;
            break;
        }
    }
    if(found==0){
        cout <<"\033[1;31m" <<"This train does not exist" <<"\033[0m" <<endl;
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

list <Passenger> showOrderedListOfPassengers(map <string,Passenger> input){
    list <Passenger> output;
    for(auto inserting:input){
        auto it=output.begin();
        int preInsertionSize=output.size();
        //Un poquito de insertion sort en su estado mas lamentable
        //se puede optimizar partiendo la lista a la mitad, comparando y repitiendo
        while(it!=output.end()){
            if((*it).getname()>inserting.second.getname()){
                output.insert(it,inserting.second);
                break;
            }else{it++;}
        }
        if(preInsertionSize==output.size()){
            output.push_back(inserting.second);
        }
    }
    if(output.size()==0){
        cout <<"No passenger registered" <<endl;
    }else{
        for(auto p:output){
            cout <<p.getID() <<" " <<p.getname() <<endl;
        }
    }
    cout <<endl;
    return output;
}

map <string,list<string>> showPassengersCities(list <Train> trenes, map <string, Passenger> passes){
    map <string,list<string>> output;
    for(auto t:trenes){
        for(auto w:t.getWagons()){
            for(auto p:w.getSeatVector()){
                //primero añadimos pasajeros a la ciudad de donde salen
                output[t.getOrigin()].push_back(passes[p.second].getname());
                //y ahora a la que llegan
                output[t.getDestination()].push_back(passes[p.second].getname());
            }
        }
    }
    for(auto i:output){
        cout <<"\n\033[1m ~~~~~~~~ " <<i.first <<" ~~~~~~~~ \033[0m" <<endl;
        for(auto p:i.second){
            cout <<"    " <<p <<endl;
        }
    }
    return output;
}

int main(){
    list <Train> mytrains;
    map <string, Passenger> mypasses;
    readInitialData(mytrains, mypasses);
    int selection;
    bool borrar=0;
    while(selection!=7){
        selection=mainMenu();
        if(borrar){cout <<"\033[2K";borrar=0;}
        switch (selection){
            case 0: 
                cout <<"Please, choose a valid option";
                for(int i=0;i<11;i++){cout <<"\033[A";}
                for(int i=0;i<29;i++){cout <<"\033[D";}
                borrar=1;
                break;
            case 7:
                cout <<"Goodbye";
                //funcion de imprimir
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
            case 5:
                showOrderedListOfPassengers(mypasses);
                break;
            case 6:
                showPassengersCities(mytrains,mypasses);
                break;
        }
    }
}