//Siro Brotón 
//Virginia Herce
//TRAIN MANAGEMENT

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
    bool done=0, error=0;
    do {
        try {
            cout <<question;
            cin >> aux;
            num=stoi(aux);
            done=1;
        }
        catch (...) {
            cout <<"\033[31;1m" <<"invalid input" <<"\033[0m\033[A\033[2K";
            for (int i=0; i<13; i++){cout <<"\033[D";}      //13 since "invalid input".size()=13
            error=1;
        }
    }while(!done);
    if(error==1){cout <<"\033[2K";}
    return num;
}

bool validDate(int day,int month,int year){
    bool leapYear;
        if(day>0 && month>0 && month<=12 && year>0){
            leapYear=(year%400==0?1:year%100==0?0:year%4==0?1:0);
            if(month==2 && ((leapYear==1 && day>29) || (leapYear==0 && day>28))){
                return 0;
            }else if((month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) && day>31){
                return 0;
            }else if((month==4 || month==6 || month==9 || month==11) && day>30){
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
    Date(int myday,int mymonth,int myyear){
        if(validDate(myday,mymonth,myyear)==1){
            day=myday;
            month=mymonth;
            year=myyear;
        }else{
            cout <<"invalid date" <<endl;
            day=month=year=1;
        }
    }
    
    int getDay(){return day;}
    int getMonth(){return month;}
    int getYear(){return year;}
    
    void setDay(int myday){
        if(validDate(myday,month,year)){day=myday;}
        else{cout <<"invalid date" <<endl;}
    }
    void setMonth(int mymonth){
        if(validDate(day,mymonth,year)){month=mymonth;}
        else{cout <<"invalid date" <<endl;}
    }
    void setYear(int myyear){
        if(validDate(day,month,myyear)){year=myyear;}
        else{cout <<"invalid date" <<endl;}
    }
    
    bool operator ==(Date input){
        if(input.day==day && input.month==month && input.year==year){
            return 1;
        }else{
            return 0;
        }
    }
    
    void printDate(){
        cout <<(day<10?"0":"") << day << ":" <<(month<10?"0":"") << month << ":";
        for(int i=1;i<4-floor(log10(year));i++){cout <<"0";}    //we add zeros to the year
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
    Wagon(int numseats, int numofwagon, vector <pair <int,string>> reserv_seats){
        if(numseats>=5){
            capacity=numseats;
        }else{
            cout <<"\nThe minimum number of seats in a wagon is 5" <<endl;
            capacity = 5;
        }
        wagonNumber = numofwagon;
        reservedSeats = reserv_seats;

    }
    
    int getCapacity(){return capacity;}
    int getWagonNum(){return wagonNumber;}
    //returns the ID corresponding to the seat. if it is not found it returns a -1
    string getPassenger(int seat){
        string output="-1";
        for(auto i:reservedSeats){
            if(seat==i.first){
                output=i.second;
                break;
            }
        }
        return output;
    }
    //returns the seat corresponding to a given ID. if it is not found it returns a -1
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
    
    void setCapacity(int mycapacity){
        if(reservedSeats.size()>mycapacity){
            cout <<"The wagon is full!" <<endl;
        }else{
            capacity=mycapacity;
        }
    }
    void setNumber(int mynumber){
        if(mynumber>0){
            wagonNumber=mynumber;
        }else{
            cout <<"introduce a valid wagon number" <<endl;
        }
    }
    
    void addPassengerW(string myid){
        pair <int,string> info;
        info.first=reservedSeats.size()+1;
        info.second=myid;
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
    //only for consulting, if you edit the vector, the original does not change
    vector <pair <int,string>> getSeatVector(){return reservedSeats;}
};

class Trip{
    private:
    Date tripDate;
    int train, wagon, seat, price;
    int distance;
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
    float getDistance(){return distance;}

    void setDate(Date dateoftrip){tripDate = dateoftrip;}
    void setTrain(int mytrain){train = mytrain;}
    void setWagon(int mywagon){wagon = mywagon;}
    void setSeat(int myseat){seat = myseat;}
    void setprice(int myprice){price = myprice;}
    void setDistance(float tripdistanceinkm){distance = tripdistanceinkm;}    
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
        //minimum of two wagons
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
    
    string getOrigin(){return origin;}
    string getDestination(){return destination;}
    float getDistance(){return distance;}
    Date getDate(){return dateoftrip;}
    int getTrainNum(){return trainnum;}
    //only for consulting (the same as Wagon)
    vector <Wagon> getWagons(){return wagonsvect;}

    void setTrainNum(int mytrainnum){trainnum = mytrainnum;}
    void setOrigin(string originst){origin = originst;}
    void setDest(string destst){destination = destst;}
    void setDist(int mydist){distance = mydist;}
    void setDate(Date day){dateoftrip=day;}
    
    void addPassengerT(string myid){
        for(int w=0; w<wagonsvect.size(); w++){
            if(wagonsvect[w].getCapacity()>wagonsvect[w].getSeatVector().size()){
                //there is space
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
            cout <<"\nThis passenger not found" <<endl;
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
};

Train getTrainfromNum(list <Train> mytrenecitos, int n){
    for (auto t:mytrenecitos){
        if (t.getTrainNum()==n){
            return t;
        }
    }
    //only for avoiding problems if the train is not found
    Train problemas;
    problemas.setTrainNum(-1);
    cout <<"The train was not found" <<endl;
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
    void setAge(int myage){age = myage;}
    void setBaggage(float mybag){
        if (mybag<0 || mybag>25){
            cout << "The weight of the baggage isnt valid!";
        }else{
            baggage = mybag;
        }
    }
    void setGender(char mygender){
        if (mygender != 'F' && mygender != 'M'){
            cout << "The gender you introduced isnt valid!";
        }else{
            gender = mygender;
        }
    }
    void clear(){
        ID,name,adress="";
        age=baggage=0;
        gender=' ';
        travels.clear();
    };

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
    try{
        ifstream passengersfi;
        passengersfi.open("passengers.txt");
        if (!passengersfi){
            cout <<"\033[1;31m" << "File not found \033[0m" << endl;
            exit(1);
        }
        string title;
        getline(passengersfi, title);
        string input2;
        Passenger persona;
        while (getline(passengersfi, input2)){
            persona.clear();
            // Extract the ID of the passenger
            int pos = input2.find(" | ");
            string id = input2.substr(0, pos);
            persona.setID(id);
            input2 = input2.substr(pos + 3);
            // Extract the name of the passenger
            pos = input2.find(" | ");
            string pname = input2.substr(0, pos);
            persona.setName(pname);
            input2 = input2.substr(pos + 3);
            // Extract the address of the passenger
            pos = input2.find(" | ");
            string paddress = input2.substr(0, pos);
            persona.setAddress(paddress);
            input2 = input2.substr(pos + 3);
            // Extract the age of the passenger
            pos = input2.find(" | ");
            int page = stoi(input2.substr(0, pos));
            persona.setAge(page);
            input2 = input2.substr(pos + 3);
            // Extract the gender of the passenger
            pos = input2.find(" | ");
            char pgender = input2.substr(0, pos)[0];
            persona.setGender(pgender);
            input2 = input2.substr(pos + 3);
            float pbag = (float) stoi(input2);
            persona.setBaggage(pbag);
            initialMapIDPass[id]=persona;
        }
        passengersfi.close();
        
        ifstream trainfi;
        trainfi.open("trenes.txt");
        if (!trainfi){
            cout <<"\033[1;31m" << "File not found \033[0m" << endl;
            exit(1);
        }
        string aux;
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
            Date mydate{day, month, year};

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
            for (int i=1; i<numWagons; i++){    //last one is counted separately
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
                    cout <<"\033[1;31m" <<"limit of passengers exceeded in train " <<trainNumber <<" \033[0m" <<endl;
                    exit(1);
                }
                for (int j=1; j<occupiedseats; j++){
                    int posSpace = id_substr.find(" ");
                    int posComa = id_substr.find(", ");
                    string idString=id_substr.substr(0, posSpace);
                    int id = stoi(idString);
                    int money = stoi(id_substr.substr(posSpace+1, posComa));
                    idsinwagon.push_back(id);
                    initialMapIDPass[idString].addTrip(mydate,trainNumber,k,idsinwagon.size(),money);
                    id_substr = id_substr.substr(posComa+2);            
                }
                int posSpace = id_substr.find(" ");
                string idString=id_substr.substr(0,posSpace);
                int lastid = stoi(idString);
                int lastmoney = stoi(id_substr.substr(posSpace+1));
                idsinwagon.push_back(lastid);
                initialMapIDPass[idString].addTrip(mydate,trainNumber,k,idsinwagon.size(),lastmoney);
                idsintrain.push_back(idsinwagon);
                input = input.substr(pos+3);
            }
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
    }catch(...){
        cout <<"\033[1;31m" <<"Error reading files" <<"\033[0m" <<endl;
        exit(1);
    }
}

int mainMenu(){
    //we use string to accept any input
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
    //go from string to int without using stoi (we only want from 1 to 7) if it is not found it returns 0
    return (output=="1"? 1 : output=="2"? 2 : output=="3"? 3 : output=="4"? 4 : output=="5"? 5 : output=="6" ? 6 :output=="7"? 7 : 0);
}

void addNewPassengerTrip(list <Train> &trenes, map <string, Passenger> &passes){
    string origin, destination, myid;
    int day, month, year, priceofthetrip;
    Date dia;
    cout << "Introduce your ID: ";
    cin >> myid;
    cout << "Introduce the origin: ";
    cin >> origin;
    cout << "Introduce the destination: ";
    cin >> destination;
    bool done = 0, error = 0;
    do{
        day = inputInt("Introduce the day: ");
        month = inputInt("Introduce the month: ");
        year=inputInt("Introduce the year: ");
        dia.setYear(year);
        dia.setMonth(month);
        dia.setDay(day);
        if(dia.getDay()!=day || dia.getMonth()!=month || dia.getYear()!=year){
            cout <<"\033[A\033[A\033[2K\033[A\033[2K\033[A\033[2K";
            error=1;
        }else{
            done=1;
        }
    } while (!done);
    if(error==1){cout <<"\033[2K";}
    priceofthetrip=inputInt("Introduce the price of the trip: ");
    //we check if the passenger exists
    string foundID = "0";
    for (auto it = passes.begin(); it != passes.end(); ++it){
        if((*it).first==myid){
            foundID = (*it).first;
            break;
        }
    }
    if(foundID=="0"){
        Passenger unregistered;
        string auxS;
        int auxI;
        unregistered.setID(myid);
        cout <<"Passenger not registered, please introduce the their data" <<endl <<"Name: ";
        cin >>auxS;
        unregistered.setName(auxS);
        cout <<"Adress(substitute spaces by .): ";
        cin >>auxS;
        int dots=counter(auxS,'.'),pos;
        for(int i=0;i<dots;i++){
            pos=auxS.find('.');
            auxS[pos]=' ';
        }
        auxI=inputInt("Age: ");
        unregistered.setAge(auxI);
        bool correct=0,error=0;
        do{
            cout <<"Gender(F/M): ";
            cin >>auxS;
            if(auxS!="F" && auxS!="M" && auxS!="f" && auxS!="m"){
                cout <<"\033[31;1m" <<"invalid input" <<"\033[0m\033[A\033[2K";
                for (int i=0; i<13; i++){cout <<"\033[D";}
                error=1;
            }else{
                correct=1;
            }
        }while(correct==0);
        if(error==1){cout <<"\033[2K";}
        //we take input as string and only accept F and M
        unregistered.setGender(((auxS=="F" || auxS=="f")?'F':'M'));
        correct=0,error=0;
        do{
            auxI=inputInt("Baggage: ");
            if(auxI>25||auxI<0){
                //we try to avoid the same error as in inputInt
                cout <<"\033[31;1m" <<"invalid input" <<"\033[0m\033[A\033[2K";
                for (int i=0; i<13; i++){cout <<"\033[D";}
                error=1;
            }else{
                correct=1;
            }
        }while(correct==0);
        if(error==1){cout <<"\033[2K";}
        unregistered.setBaggage(auxI);
        passes[myid] = unregistered;
    }
    //check trains that coincide on date and itenerary
    bool personfound=0;
    bool trainfound=0;
    for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
        if((*train_it).getDate()==dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
            //this train matches the requirements
            trainfound = 1;
            if ((*train_it).findPassenger(myid).first != -1 && (*train_it).findPassenger(myid).second != -1){
                personfound = 1;
                cout <<"Passenger " << myid <<" already registered in train " << (*train_it).getTrainNum() <<", wagon " << (*train_it).findPassenger(myid).first <<", seat " <<(*train_it).findPassenger(myid).second <<endl;
                break;
            }
        }
        if(personfound==1){break;}
    }
    //if the passenger is not found we add it to the train
    if(personfound==0 && trainfound==1){
        bool added=0;
        //same system for trains and wagons
        for(auto train_it = trenes.begin(); train_it != trenes.end(); train_it++){
            if((*train_it).getDate()==dia && (*train_it).getOrigin()==origin && (*train_it).getDestination()==destination){
                //este tren coincide
                (*train_it).addPassengerT(myid);
                auto w = (*train_it).findPassenger(myid);
                if(w.first != -1 && w.second != -1){
                    cout <<"Passenger " << myid <<" added to train " << (*train_it).getTrainNum() <<", wagon " << w.first <<", seat " << w.second << endl;
                    //We also have to add the trip to the passenger
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
    string origin, destination, myid;
    int day, month, year;
    Date dia;
    cout << "Introduce your ID: ";
    cin >> myid;
    cout << "Introduce the origin: ";
    cin >> origin;
    cout << "Introduce the destination: ";
    cin >> destination;
    bool done = 0, error = 0;
    do{
        day = inputInt("Introduce the day: ");
        month = inputInt("Introduce the month: ");
        year=inputInt("Introduce the year: ");
        dia.setYear(year);
        dia.setMonth(month);
        dia.setDay(day);
        if(dia.getDay()!=day || dia.getMonth()!=month || dia.getYear()!=year){
            cout <<"\033[A\033[A\033[2K\033[A\033[2K\033[A\033[2K";
            error=1;
        }else{
            done=1;
        }
    } while (!done);
    if(error==1){cout <<"\033[2K";}
    //check that the passenger exists
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
                //this train meets our criteria
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

void showTripsOfPassenger(map <string, Passenger> &passes, list <Train> &trenes){
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
            cout << "\nThis is the list of trips for passenger " << idPass << ":" << endl;
            int count = 1;
            for (Trip tr:travelsPass){
                cout << "\n----------Information Trip " << count << "----------" << endl;
                cout << "Origin: " << getTrainfromNum(trenes, tr.getTrain()).getOrigin() <<"\nDestination: " << getTrainfromNum(trenes, tr.getTrain()).getDestination() <<"\nDistance: " << tr.getDistance() << "\nDate: ";
                tr.getTripDate().printDate();
                cout << "Prize of the trip: " << tr.getprice();
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

void showListOfPassengers(list <Train> &trenes, map <string, Passenger> &passes){
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

list <Passenger> showOrderedListOfPassengers(map <string,Passenger> &input){
    list <Passenger> output;
    //Insertion sort
    for(auto inserting:input){
        auto it=output.begin();
        int preInsertionSize=output.size();
        while(it!=output.end()){
            if((*it).getname()>inserting.second.getname()){
                output.insert(it,inserting.second);
                break;
            }else{it++;}
        }
        //If the new passenger is going to be last the while doesn't reach and it's not added, so we add it last
        if(preInsertionSize==output.size()){
            output.push_back(inserting.second);
        }
    }
    
    return output;
}

map <string,list<string>> showPassengersCities(list <Train> &trenes, map <string, Passenger> &passes){
    map <string,list<string>> output;
    for(auto t:trenes){
        for(auto w:t.getWagons()){
            for(auto p:w.getSeatVector()){
                //We add the passengers to the city they are traveling from
                output[t.getOrigin()].push_back(passes[p.second].getname());
                //and to the city they are arriving to
                output[t.getDestination()].push_back(passes[p.second].getname());
            }
        }
    }
    return output;
}

void endProgram(list <Train> trenes, map <string, Passenger> passes){
    ofstream outfi;
    outfi.open("output.txt");
    outfi << "\n~~~~~~~~~~~~~~~~~~~~~~~~ "<< "INFORMATION ABOUT TRAINS" << " ~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (Train t : trenes){
        outfi << "\n~~~~~~~~ "<< "TRAIN "<< t.getTrainNum() <<" ~~~~~~~~" << endl << endl;
        for(int i=0;i<t.getWagons().size();i++){
            outfi <<"  ~~~ Wagon " << i+1 <<" ~~~" <<endl;
            if(t.getWagons()[i].getSeatVector().size()==0){
                outfi <<"This wagon is empty" <<endl;
            }else{
                for(int j=0;j<t.getWagons()[i].getSeatVector().size();j++){
                    string idofpass = t.getWagons()[i].getSeatVector()[j].second;
                    string name = passes[idofpass].getname();
                    outfi << "Seat " << j+1 << " - " << name << " with ID: " << idofpass << endl;
                }
            }
        }
    }
    outfi << "\n~~~~~~~~~~~~~~~~~~~~~~~~ "<< "INFORMATION ABOUT PASSENGERS" << " ~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (auto p:passes){
        outfi << "\nPassenger with ID: " << p.second.getID() << "\nName: "<<p.second.getname() << "\nAge: "<<p.second.getage() << "\nAddress: "<<p.second.getaddress() << "\nGender: "<<p.second.getgender();
        if(p.second.getTrips().size()>0){
            outfi << "\n-------------------- List of trips: --------------------" << endl;
            int count = 1;
            for (Trip tr:p.second.getTrips()){
                outfi << "----------Information Trip " << count << "----------" << endl;
                outfi << "Origin: " << getTrainfromNum(trenes, tr.getTrain()).getOrigin() <<"\nDestination: " << getTrainfromNum(trenes, tr.getTrain()).getDestination() <<"\nDistance: " << tr.getDistance() << "km\nDate: ";
                outfi <<(tr.getTripDate().getDay()<10?"0":"") << tr.getTripDate().getDay() << ":" <<(tr.getTripDate().getMonth()<10?"0":"") << tr.getTripDate().getMonth() << ":";
                for(int i=1;i<4-floor(log10(tr.getTripDate().getYear()));i++){outfi <<"0";}
                outfi << tr.getTripDate().getYear() << endl;
                outfi << "Prize of the trip: " << tr.getprice();
                outfi << "\nTrain: " << tr.getTrain() << " \nWagon: " << tr.getWagon()  << " \nSeat: " << tr.getSeat() << endl;
                count++;
                outfi << "\n";
            }
        }else{
            outfi <<"Passenger "<< p.first <<" has no trips" <<endl;
        }
        outfi << endl;
    }
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
        switch (selection) {
            case 0: 
                cout <<"Please, choose a valid option";
                for(int i=0;i<11;i++){cout <<"\033[A";}
                for(int i=0;i<29;i++){cout <<"\033[D";}
                borrar=1;
                break;
            case 7:{
                cout <<"Goodbye";
                endProgram(mytrains, mypasses);
                break;
                }
            case 1:{
                addNewPassengerTrip(mytrains, mypasses);
                break;
                }
            case 2:{
                removePassengerTrip(mytrains, mypasses);
                break;
                }
            case 3:{
                showTripsOfPassenger(mypasses, mytrains);
                break;
                }
            case 4:{
                showListOfPassengers(mytrains, mypasses);
                break;
                }
            case 5:{
                list <Passenger> orderedpasses = showOrderedListOfPassengers(mypasses);
                if(orderedpasses.size()==0){
                    cout <<"No passenger registered" <<endl;
                }else{
                    for(auto p:orderedpasses){
                        cout <<p.getID() <<" " <<p.getname() <<endl;
                    }
                }
                break;
                }
            case 6: {
                map <string,list<string>> mymap = showPassengersCities(mytrains,mypasses);
                for(auto i:mymap){
                    cout <<"\n\033[1m ~~~~~~~~ " << i.first <<" ~~~~~~~~ \033[0m" <<endl;
                    for(auto p:i.second){
                        cout <<"    " << p <<endl;
                    }
                }
                }
        }
    }
}