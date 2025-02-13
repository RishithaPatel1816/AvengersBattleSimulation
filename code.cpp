#include <bits/stdc++.h>
using namespace std;

//Class QNS is for power suitwith p,d,e,h
//Main constraints: h is never negative
//                  p is atmost 5000
//                  d>0
class QNS{
    private:
        int powerLevel;
        int durability;
        int energyStorage;
        int heatLevel;
    public:
        //this is the default constructor
        QNS(){
            powerLevel=1000;
            durability=500;
            energyStorage=300;
            heatLevel=0;
        }
        //CONSTRUNCTOR WITH INPUTS
        QNS(int p,int d,int e,int h){
            //check for any constraints and ssign p,d,e,h
            powerLevel=min(5000,p);
            durability=d;
            energyStorage=e;
            heatLevel=max(h,0);
        }
        //duplicate constructor
        QNS(const QNS & q){
            powerLevel=q.powerLevel;
            durability=q.durability;
            energyStorage=q.energyStorage;
            heatLevel=q.heatLevel;
        }
        void operator+(const QNS &q){
            //Formula: (P1,D1,E1,H1)+(P2,D2,E2,H2)=(P1+E2,D1+D2,E1+P2,H1)
            powerLevel+=q.energyStorage;
            durability+=q.durability;
            energyStorage+=q.powerLevel;
            if(powerLevel>5000){powerLevel=5000;}
            //heat level doesnot change
            return;
        }
        void operator-(int x){
           // Formula: (P,D,E,H)-X=(P,D-X,E+X,H+X)
            durability=durability-x;
            energyStorage=energyStorage+x;
            heatLevel=heatLevel+x;
            return;
        }
        void operator*(int x){
            //Formula: Formula: (P, D, E, H) * X = (P+(P * X)/100), D, E + 5X, H + X)
            powerLevel=powerLevel+((float)(powerLevel*x)/100);
            energyStorage=energyStorage+(5*x);
            heatLevel=heatLevel+x;
            //if(heatLevel>500){return;}
            if(powerLevel>5000){powerLevel=5000;}
            return ;
        }
        void operator/(int x){
            //Formula: (P, D, E, H) / X = (P, D + X, E, H - X)
            durability=durability+x;
            heatLevel=heatLevel-x;
            if(heatLevel<0){heatLevel=0;}
            return;
        }
        void boostPowerbyFactor(int factor){
            (*this)*factor;
            return;
        }
        void boostPower(const QNS & othersuit){
            (*this)+(othersuit);
            return;
        }
        bool operator==(QNS & q){
            if(powerLevel==q.powerLevel && durability==q.durability){return true;}
            return false;
        }
        bool operator<(const QNS & q){
            if(durability+powerLevel<q.durability+q.powerLevel){return true;}
            return false;
        }
        //getters and setters
        int getP(){
            return powerLevel;
        }
        int getD(){
            return durability;
        }
        int getE(){
            return energyStorage;
        }
        int getH(){
            return heatLevel;
        }
    friend class Avenger;
};

class Avenger{
    private:
        string name;
        QNS suit;
        int attackStrength;
    public:
        //Constructor
        Avenger(string avName, QNS avSuit, int strength){
            name=avName;suit=avSuit;attackStrength=strength;
        }
        void attack(Avenger& enemy){
            enemy.damage(attackStrength);
            return;
        }
        void damage(int x){
            suit-x;return;
        }
        void resetDurability(int x){
            suit.durability=suit.durability+x;
        }
        bool upgradeSuit(QNS & q){
            suit+q;
            return true;
        }
        void assignSuit(QNS & q){
            suit=q;
        }
        void repair(int x){
            suit/x;
        }
        //print statues of avenger
        void printStatus(){
            cout<<name<<" "<<suit.powerLevel<<" "<<suit.durability<<" "<<suit.energyStorage<<" "<<suit.heatLevel<<endl;
            return;
        }
        //getters and setters
        int getdur(){
            return suit.getD();
        }
        int getpow(){
            return suit.getP();
        }
        string getName(){
            return name;
        }
        int getHeat(){
            return suit.getH();
        }
    friend class Battle;
};

class Battle{
    private:
        vector<Avenger> heroes;
        vector<Avenger> enemies;
        queue<QNS> weapons; //first come first serve
        vector<string> battleLog;
    public:
        void startBattle(string s, Battle & b){
            //start battle
            while(s!="End"){
                if(s=="Attack"){
                    string n1,n2;
                    cin>>n1>>n2;
                    b.attackof2(n1,n2);
                }
                else if(s=="BoostPower"){
                    string a;
                    cin>>a;
                    int p,d,e,h;
                    cin>>p>>d>>e>>h;
                    b.boostparam(a,p,d,e,h);
                }
                else if(s=="Repair"){
                    string n;
                    int x;
                    cin>>n>>x;
                    b.repair(n,x);
                }
                else if(s=="BoostPowerByFactor"){
                    string s;int n;cin>>s>>n;
                    b.boostpower(s,n);
                }
                else if(s=="AvengerStatus"){
                    string nm;cin>>nm;
                    b.printAvengersuit(nm);
                }
                else if(s=="Upgrade"){
                    string s;cin>>s;
                    b.upgradesuit(s);
                }
                else if(s=="PrintBattleLog"){
                    b.printBattleLog();
                }
                else if(s=="BattleStatus"){
                    int a=b.Result();
                    if(a==1){
                        cout<<"heroes are winning"<<endl;
                    }
                    else if(a==-1){
                        cout<<"enemies are winning"<<endl;
                    }
                    else{
                        cout<<"tie"<<endl;
                    }
                }
                cin>>s;
            }
        }
        void printBattleLog(){
            for(long unsigned int i=0;i<battleLog.size();i++){
                cout<<battleLog[i]<<endl;
            }
        }
        int Result(){
            //determines who won
            int sh=0;
            for(long unsigned int i=0;i<heroes.size();i++){
                if(heroes[i].getdur()>0)sh=sh+heroes[i].getdur()+heroes[i].getpow();
            }
            int se=0;
            for(long unsigned int i=0;i<enemies.size();i++){
                if(enemies[i].getdur()>0)se=se+enemies[i].getdur()+enemies[i].getpow();
            }
            if(sh>se){return 1;}
            if(se>sh){return -1;}
            return 0;
        }
        //creating suit,hero,enemy
        void createsuit(int p,int d,int e,int h){
            QNS q(p,d,e,h);
            weapons.push(q);
        }
        void createhero(){
            string n;int a;
            cin>>n>>a;
            if(!weapons.empty()){
                Avenger h(n,weapons.front(),a);
                weapons.pop();
                heroes.push_back(h);
            }
            else{
                cout<<n<<" is out of fight"<<endl;
            }
            return;
        }
        void createenemy(){
            string n;int a;
            cin>>n>>a;
            if(!weapons.empty()){
                Avenger h(n,weapons.front(),a);
                weapons.pop();
                enemies.push_back(h);
            }
            else{
                cout<<n<<" is out of fight"<<endl;
            }
        }
        void attackof2(string n1,string n2){
            pair<int,int> attacker=getAvenger(n1);
            pair<int,int> papam=getAvenger(n2);
            int h1=attacker.second;
            int index1=attacker.first;
            int h2=papam.second;
            int index2=papam.first;
            //now i have to check 
            if(h1==0 && h2==0){
                if(enemies[index1].getdur()>0 && enemies[index1].getHeat()<=500 && enemies[index2].getdur()>0){
                    //check b durabiltiy too
                    string s=n1+" attacks "+n2;
                    //cout<<s<<endl;
                    battleLog.push_back(s);
                    //now update b's values
                    enemies[index1].attack(enemies[index2]);
                    //if b.durability less than 0 write b got destroyes             
                    if(enemies[index2].getdur()<=0){
                        string s=n2+" suit destroyed";
                        battleLog.push_back(s);
                        if(!weapons.empty()){
                            enemies[index2].assignSuit(weapons.front());
                            weapons.pop();
                        }
                    }
                    else if(enemies[index2].getHeat()>500){
                        string s=n2+" suit overheated";
                        battleLog.push_back(s);
                    }
                }
            }
            else if(h1==0 && h2==1){
                //enemy attacks hero
                if(enemies[index1].getdur()>0 && enemies[index1].getHeat()<=500 && heroes[index2].getdur()>0){
                    //check b durabiltiy too
                    string s=n1+" attacks "+n2;
                    //cout<<s<<endl;
                    battleLog.push_back(s);
                    //now update b's values
                    enemies[index1].attack(heroes[index2]);
                    //if b.durability less than 0 write b got destroyes             
                    if(heroes[index2].getdur()<=0){
                        string s=n2+" suit destroyed";
                        battleLog.push_back(s);
                        if(!weapons.empty()){
                            heroes[index2].assignSuit(weapons.front());
                            weapons.pop();
                        }
                    }
                    else if(heroes[index2].getHeat()>500){
                        string s=n2+" suit overheated";
                        battleLog.push_back(s);
                    }
                }
            }
            else if(h1==1 && h2==0){
                //hero attacks villian
                if(heroes[index1].getdur()>0 && heroes[index1].getHeat()<=500 && enemies[index2].getdur()>0){
                    //check b durabiltiy too
                    string s=n1+" attacks "+n2;
                    battleLog.push_back(s);
                    //now update b's values
                    heroes[index1].attack(enemies[index2]);
                    //if b.durability less than 0 write b got destroyes
                    if(enemies[index2].getdur()<=0){
                        string s=n2+" suit destroyed";
                        battleLog.push_back(s);
                        if(!weapons.empty()){
                            enemies[index2].assignSuit(weapons.front());
                            weapons.pop();
                        }
                    }
                    else if(enemies[index2].getHeat()>500){
                        string s=n2+" suit overheated";
                        battleLog.push_back(s);
                    }
                }
            }
            else{
                //both are heroes
                if(heroes[index1].getdur()>0 && heroes[index1].getHeat()<=500 && heroes[index2].getdur()>0){
                    //check b durabiltiy too
                    string s=n1+" attacks "+n2;
                    battleLog.push_back(s);
                    //now update b's values
                    heroes[index1].attack(heroes[index2]);
                    //if b.durability less than 0 write b got destroyes
                    if(heroes[index2].getdur()<=0){
                        string s=n2+" suit destroyed";
                        battleLog.push_back(s);
                        if(!weapons.empty()){
                            heroes[index2].assignSuit(weapons.front());
                            weapons.pop();
                        }
                    }
                    else if(heroes[index2].getHeat()>500){
                        string s=n2+" suit overheated";
                        battleLog.push_back(s);
                    }
                }
            }   
            return;
        }
        void repair(string n,int x){
            pair<int,int> val=getAvenger(n); 
            
            //h=1 means hero else h==0 means villian
            if(val.second==0){
                enemies[val.first].repair(x);
            }
            else{
                heroes[val.first].repair(x);
            }
            string a=n+" repaired";
            battleLog.push_back(a);
            return;
        }
        pair<int,int> getAvenger(string n){
            long unsigned int i;
            int h=0;
            for(long unsigned int i=0;i<heroes.size();i++){
                if(heroes[i].getName()==n){
                    h=1;
                    return {i,h};
                    break;
                }
            }
            for(i=0;i<enemies.size();i++){
                if(enemies[i].getName()==n){
                    return {i,h};
                    break;
                }
            }
            return {-1,-1};   
        }
        void boostpower(string s,int x){
            pair<int,int> val=getAvenger(s);
            if(val.second==1){
                //hero
                heroes[val.first].suit*x;
                string a=(heroes[val.first].getName()+" boosted");
                battleLog.push_back(a);
                //check over heat
                if(heroes[val.first].suit.getH()>500){
                    string a=(heroes[val.first].getName())+" suit overheated";
                    battleLog.push_back(a);
                }
            }
            else{
                //for villian
                enemies[val.first].suit*x;
                string a=(enemies[val.first].getName()+" boosted");
                battleLog.push_back(a);
                //check over heat
                if(enemies[val.first].suit.getH()>500){
                    string a=(enemies[val.first].getName())+" suit overheated";
                    battleLog.push_back(a);
                }
            }
        }
        void printAvengersuit(string s){
            pair<int,int> val=getAvenger(s);
            if(val.second==1){
                //hero
                heroes[val.first].printStatus();
            }
            else{
                enemies[val.first].printStatus();
            }
            return;
        }
        void upgradesuit(string s){
            if(weapons.empty()){
                string x=s+" upgrade Fail";
                battleLog.push_back(x);return;
            }
            else{
                pair<int,int> val=getAvenger(s);
                if(val.second==1){
                    if(heroes[val.first].upgradeSuit(weapons.front())){
                        weapons.pop();
                        string x=s+" upgraded";
                        battleLog.push_back(x);return;
                    }
                }
                else{
                    if(enemies[val.first].upgradeSuit(weapons.front())){
                        weapons.pop();
                        string x=s+" upgraded";
                        battleLog.push_back(x);return;
                    }
                   
                }
            }
            return;
        }
        void boostparam(string a,int p,int d,int e, int h){
            pair<int,int> vl=getAvenger(a);
            QNS q(p,d,e,h);
            if(vl.second==1){
                //hero
                heroes[vl.first].upgradeSuit(q);
                return;
            }
            enemies[vl.first].upgradeSuit(q);
        }
};

int main(){
    Battle b;
    int k,n,m;
    //k is no of suits
    //n is no of heroes
    //m is no of enemies
    cin>>k>>n>>m;
    for(int i=0;i<k;i++){
        int p,d,e,h;
        cin>>p>>d>>e>>h;
        b.createsuit(p,d,e,h);
    }
    //take heroes and enemies 
    for(int i=0;i<n;i++){
        b.createhero();
    }
    for(int i=0;i<m;i++){
        b.createenemy();
    }
    // b.printAvengersuit("IronMan");
    // cout<<"hi"<<endl;
    string s;
    cin>>s;
    if(s=="BattleBegin"){
        b.startBattle(s,b);
    }
    return 0;
}
