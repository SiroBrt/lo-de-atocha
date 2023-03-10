#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

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
    //cosas clasicas de clases
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

class Juego{
    private:
    vector <pair<int,string>> players;
    public:
    void addPlayer(int id,string password){
        pair <int,string> input;
        input.first=id;
        input.second=password;
        players.push_back(input);
    }
    string getPassword(int id){
        string output;
        for(int i=0;i<players.size();i++){
            if(players[i].first==id){
                output=players[i].second;
                break;
            }
        }
        return output;
        /*for(auto i:players){
            cout <<i.first <<"->" <<i.second <<endl;
        }
        return "done";*/
    }
};

class Persona{
    private:
    Date cumple;
    int ID;
    list <pair <Juego,string>> registradoEn;
    public:
    static int poblacion;
    Persona(){
        poblacion++;
        ID=poblacion;
    }
    void setBirthday(int num1,int num2, int num3){
        cumple.setDay(num1);
        cumple.setMonth(num2);
        cumple.setYear(num3);
    }
    int getID(){
        return ID;
    }
    void addGame(Juego &game,string password){ //aquí es importante pasarlo por referencia para cambiarlo fuera de la función 
        pair <Juego,string> input;
        input.first=game;
        input.second=password;
        registradoEn.push_back(input);
        game.addPlayer(ID,password);
    }
    void showPassword(Juego game){
        string password;
        cout <<ID <<" is ";
        password=game.getPassword(ID);
        cout <<password;
    }    
    void printBirthday(){
        int day=cumple.getDay();
        int month=cumple.getMonth();
        int year=cumple.getYear();
        cout <<(day>=10? "":"0") <<day <<":";
        cout <<(month>=10? "":"0") <<month <<":";
        cout <<(year>=1000? "":year>=100? "0":year>=10?"00":"000") <<year;      //if else pero con mas "clase" :)
    }
};

int Persona::poblacion=0;

int main(){
    Persona yo,tu;
    Juego amongUs;
    //pruebas fechas
    /*cout <<"yo=" <<yo.getID() <<" tu=" <<tu.getID() <<endl;
    yo.printBirthday();*/
    yo.addGame(amongUs,"something");
    tu.addGame(amongUs,"another thing");
    tu.showPassword(amongUs);
}
