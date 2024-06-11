#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;

class xe{
    private:
        string plate;
        string timein;
    public:
        xe(string timein, string plate){
            this->plate = plate;
            this->timein = timein;
        }
        string getTimein(){
            return timein;
        }
        string getPlate(){
            return plate;
        }
        void inxe(){
            cout<<plate<<endl;
            cout<<timein<<endl;
        }
};

class baidoxe{
    private:
        vector<xe> baidoxe;
        int totalEarning;
    public:
        void setTotalEarning(){
            this->totalEarning = 0;
        }
        void addxe(string timein, string plate){
            baidoxe.push_back(xe(timein,plate));
        }

        void list(){
            for(int i = 0; i < baidoxe.size(); i++){
                cout<<baidoxe[i].getPlate()<<endl;
            }
        }

        int find(string plate){
            for(int i = 0; i < baidoxe.size(); i++){
                if(baidoxe[i].getPlate() == plate){
                    return i;
                }
            }
            return -1;
        }

        bool isDaytime(string time){
            return (time >= "06:00:00" && time <= "18:00:00");
        }

        bool isNighttime(string time){
            return (time < "06:00:00" || time > "18:00:00");
        }

        int in(string timein, string plate){
            int p = 0;
            for(int i = 0; i < baidoxe.size();i++){
                if(baidoxe[i].getPlate() == plate){
                    p = 1;
                }
            }
            if(p == 1){
                return 0;
            }
            else{
                    addxe(timein, plate);
                    return 1;
                }
        }
        int out(string timeout, string plate){
            for(int i = 0; i < baidoxe.size(); i++){
                if(baidoxe[i].getPlate() == plate){
                    int fee = calculateFee(plate,baidoxe[i].getTimein(),timeout);
                    totalEarning += fee;
                    baidoxe.erase(baidoxe.begin() + i);
                    return 1;
                }
            }
            return 0;
        }

        int cnt_moto(){
            int count = 0;
            for(int i = 0; i < baidoxe.size(); i++){
                if(baidoxe[i].getPlate().substr(0,4) != "xxxx"){
                    count++;
                }
            }
            return count;
        }

        bool isBike(string plate){
            return (plate.substr(0,4) == "xxxx");
        }

        int calculateFee(string plate, string timein, string timeout){
           if(isDaytime(timein) && isDaytime(timeout)){
                return isBike(plate) ? 1 : 3;
            }
            else if(isNighttime(timein) && isNighttime(timeout)){
                return isBike(plate) ? 2 : 5;
            }
            else if(isNighttime(timein) && isDaytime(timeout)){
                return isBike(plate) ? 3 : 8;
            }
            else if(isNighttime(timeout) && isDaytime(timein)){
                return isBike(plate) ? 3 : 8;
            }
            else{
                return isBike(plate) ? 5 : 13;
            } 
        }
        int bill(string timeout, string plate){
            for(int i = 0; i < baidoxe.size(); i++){
                if(baidoxe[i].getPlate() == plate){
                    return calculateFee(plate,baidoxe[i].getTimein(),timeout);
                }
            }
            return -1;
        }

        int billall(){
            return totalEarning;
        }
};

int main(){
    baidoxe bdx;
    string line;

    while(getline(cin,line) && line != "*"){
        int spacePos = line.find(' '); //Tim kiem vi tri khoang trang dau tien
        if(spacePos != string::npos){ //Neu tim thay khoang trang
            string timein = line.substr(0, spacePos);
            string plate = line.substr(spacePos + 1);
            bdx.addxe(timein, plate);
        }
    }

    vector<pair<string,string>> commands;
    while (getline(cin,line) && line != "***"){
        int spacePos = line.find(' ');
        string lenh = line.substr(0,spacePos);
        string solieu = line.substr(spacePos + 1);
        commands.push_back({lenh, solieu});
    }
    
    for(pair<string,string> x : commands){ //Vong lap cua tung doi tuong thuoc commands
    //x.first la phan tu dau tien cua mot cap pair<a,b> hay mot vector
    //x.first la phan tu thu hai cua mot cap pair<a,b> hay mot vector
        if(x.first == "list"){
            bdx.list();
        }
        else if(x.first == "find"){
            cout<<bdx.find(x.second)<<endl;
        }
        else if(x.first == "in"){
            int spacePos = x.second.find(' ');
            if(spacePos != string::npos){
                string timein = x.second.substr(0,spacePos);
                string plate = x.second.substr(spacePos + 1);
                cout<<bdx.in(timein,plate)<<endl;
            }
        }
        else if(x.first == "out"){
            int spacePos = x.second.find(' ');
            if(spacePos != string::npos){
                string timeout = x.second.substr(0,spacePos);
                string plate = x.second.substr(spacePos + 1);
                cout<<bdx.out(timeout,plate)<<endl;
            }
        }
        else if(x.first == "cnt-moto"){
            cout<<bdx.cnt_moto()<<endl;
        }
        else if(x.first == "bill"){
            int spacePos = x.second.find(' ');
            if(spacePos != string::npos){
                string timeout = x.second.substr(0,spacePos);
                string plate = x.second.substr(spacePos + 1);
                cout<<bdx.bill(timeout,plate)<<endl;
            }
        }
        else if(x.first == "billall"){
            cout<<bdx.billall()<<endl;
        }
    }

}
