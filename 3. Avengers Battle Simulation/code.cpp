#include <bits/stdc++.h>
using namespace std;

class QNS{

    private:

    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;

    public:

    QNS(int P, int D, int E, int H):powerLevel(P),durability(D),energyStorage(E),heatLevel(H){
        constrains();
    };
    QNS():powerLevel(1000),durability(500),energyStorage(300),heatLevel(0){};
    void constrains()
    {
        if(powerLevel>5000)
        {
            powerLevel = 5000;
        }
        if(heatLevel<0)
        {
            heatLevel = 0;
        }
    }
    QNS(const QNS& q)
    {
        powerLevel = q.powerLevel;
        durability = q.durability;
        energyStorage = q.energyStorage;
        heatLevel = q.heatLevel;
    }

    QNS operator+(QNS q)
    {
        powerLevel+= q.energyStorage;
        durability += q.durability;
        energyStorage += q.powerLevel;
        constrains();
        return *this;
    }

    QNS operator-(int x)
    {
        
            durability -= x;
            energyStorage += x;
            heatLevel+=x;

        return *this;
    }

    QNS operator*(int x)
    {
        powerLevel = (powerLevel+((powerLevel*x)/100));
        energyStorage = energyStorage +5*x;
        heatLevel+=x;
        constrains();
        return *this;
    }

    QNS operator/(int x)
    {
        durability+=x;
        heatLevel-=x;
        constrains();
        return *this;
    }


    void boostPower(int factor)
    {
        *this=(*this)*(factor);
    }

    void boostPower(QNS otherSuit)
    {
        *this= *this + otherSuit;
    }
 

    bool operator ==(QNS s1)
    {
        return(powerLevel==s1.powerLevel && durability==s1.durability);
    }

    bool operator <(QNS s1)
    {
        int x = powerLevel;
        int y = durability;
        x=x+y;
        int a = s1.durability;
        int b = s1.powerLevel;
        a= a+b;

        return(x<a);
        
    }

    int getpower()
    {
        return powerLevel;
    }
    int getdurability()
    {
        return durability;
    }
    int getenergy()
    {
        return energyStorage;
    }
    int getheat()
    {
        return heatLevel;
    }

    void setpower(int x)
    {
        powerLevel =x;
    }
    void setdurability(int x)
    {
        durability =x;
    }
    void setenergy(int x)
    {
        energyStorage=x;
    }
    void setHeat(int x)
    {
        heatLevel =x;
    }
};

class Avenger{

    private:

    string name;
    QNS suit;
    int attackStrength;

    public:

    Avenger(string aName, QNS aSuit, int astrength): name(aName),suit(aSuit),attackStrength(astrength){};
    Avenger(const Avenger& av){
        name = av.name;
        suit = av.suit;
        attackStrength = av.attackStrength;
    }

    void attack(Avenger & enemy)
    {
        enemy.suit = enemy.suit - attackStrength;
    }

    void upgradeSuit(QNS otherSuit)
    {
        suit = suit+otherSuit;
    }

    void repair(int x)
    {
        suit= suit/x;
    }

    void printStatus()
    {
        cout<< name<<" "<<suit.getpower()<<" "<<suit.getdurability()<<" "<<suit.getenergy()<<" "<<suit.getheat()<<endl;
    }

    int Avgetpower()
    {
        return suit.getpower();
    }

    int Avgetdurability()
    {
        return suit.getdurability();
    }

    int AvgetHeatlevel()
    {
        return suit.getheat();
    }

    string getName()
    {
        return name;
    }
    int getAttackS()
    {
        return attackStrength;
    }
    int current_situation()
    {
        int d = Avgetdurability();
        int h = AvgetHeatlevel();

        if(d<=0){return -1;}
        else if(h>500){return 0;}
        else{return 1;}

    }

    void bostby(int x)
    {
        suit.boostPower(x);
    }

    void boostbysuit(QNS q)
    {
        suit.boostPower(q);
    }

};

class Battle{

    private:

    vector<Avenger> heros;
    vector<Avenger> enemies;
    vector<string> battleLog;
    queue<QNS> suits;

    public:

    void startBattle()
    {
        string str;
        while(true)
        {
            cin>>str;
            if(str=="Attack")
            {
                string name1,name2;
                cin>>name1>>name2;
                Avenger *A1=nullptr;
                Avenger *A2=nullptr;
                for(int i=0;i<heros.size();i++){
                    if(name1==heros[i].getName())
                    {
                        A1 = &heros[i];
                    }
                    if(name2==heros[i].getName())
                    {
                        A2 = &heros[i];
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(name1==enemies[i].getName())
                    {
                        A1 = &enemies[i];
                    }
                    if(name2==enemies[i].getName())
                    {
                        A2 = &enemies[i];
                    }
                }
                if(A1&&A2)
                {
                    int a1 = A1->current_situation();
                    int a2 = A2->current_situation();
                    if(a1==1 && a2!=-1)
                    {
                        A1->attack(*A2);
                        battleLog.push_back(name1+" attacks "+name2);
                        int a3 = A2->current_situation();
                        if(a3==-1)
                        {
                            battleLog.push_back(name2+" suit destroyed");
                        }
                        else if(a3==0)
                        {
                            battleLog.push_back(name2+" suit overheated");
                        }

                    }
                }
            }
            else if(str=="Repair")
            {
                string name;
                int x;
                cin>>name>>x;
                bool flag = false;
                for(int i=0;i<heros.size();i++){
                    if(name==heros[i].getName())
                    {
                        heros[i].repair(x);
                        battleLog.push_back(name+" repaired");flag = true;break;
                    }
                }
                if(!flag)
                {
                    for(int i=0;i<enemies.size();i++){
                        if(name==enemies[i].getName())
                        {
                            enemies[i].repair(x);
                            battleLog.push_back(name+" repaired");break;
                        }
                    }
                }
                
            }
            else if(str=="BoostPowerByFactor")
            {
                string name;
                int x;
                cin>>name>>x;
                bool flag = false;
                for(int i=0;i<heros.size();i++){
                    if(name==heros[i].getName())
                    {
                        heros[i].bostby(x);
                        battleLog.push_back(name+" boosted");
                        int x =heros[i].AvgetHeatlevel() ;
                        if(x>500)
                        {
                            battleLog.push_back(name+" suit overheated");
                        }
                        flag = true;break;
                    }
                }
                if(!flag)
                {
                    for(int i=0;i<enemies.size();i++){
                        if(name==enemies[i].getName())
                        {
                            enemies[i].bostby(x);
                            battleLog.push_back(name+" boosted");
                            int x =enemies[i].AvgetHeatlevel() ;
                            if(x>500)
                            {
                                battleLog.push_back(name+" suit overheated");
                            }
                            break;
                        }
                    }
                }
                
            }
            else if(str=="BoostPower")
            {
                string name;
                int p,d,e,h;
                cin>>name>>p>>d>>e>>h;
                QNS q2(p,d,e,h);
                bool flag = false;
                for(int i=0;i<heros.size();i++){
                    if(name==heros[i].getName())
                    {
                        heros[i].boostbysuit(q2);
                        battleLog.push_back(name+" boosted");
                        int x =heros[i].AvgetHeatlevel() ;
                        if(x>500)
                        {
                            battleLog.push_back(name+" suit overheated");
                        }
                        flag=true;break;
                    }
                }
                if(!flag)
                {
                    for(int i=0;i<enemies.size();i++){
                        if(name==enemies[i].getName())
                        {
                            enemies[i].boostbysuit(q2);
                            battleLog.push_back(name+" boosted");
                            int x =enemies[i].AvgetHeatlevel() ;
                            if(x>500)
                            {
                                battleLog.push_back(name+" suit overheated");
                            }
                            break;
                            break;
                        }
                    }
                }

            }
            else if(str=="AvengerStatus")
            {
                string name;
                cin>>name;
                bool flag =false;
                for(int i=0;i<heros.size();i++){
                    if(name==heros[i].getName())
                    {
                        heros[i].printStatus();flag=true;break;
                    }
                }

                if(!flag)
                {
                    for(int i=0;i<enemies.size();i++){
                        if(name==enemies[i].getName())
                        {
                            enemies[i].printStatus();break;
                        }
                    }
                }
            }
            else if(str=="Upgrade")
            {
                string name;
                cin>>name;
                bool flag = false;
                if(suits.empty())
                {
                    battleLog.push_back(name+" upgrade Fail");
                }
                else
                {
                    for(int i=0;i<heros.size();i++){
                        if(name==heros[i].getName())
                        {
                            if(heros[i].current_situation()!=-1)
                            {
                                QNS q = suits.front(); suits.pop();
                                heros[i].upgradeSuit(q);
                                battleLog.push_back(name+" upgraded");
                            }
                            else
                            {
                                battleLog.push_back(name+" upgrade Fail");
                            } flag =true;
                        }
                    }
                    if(!flag)
                    {
                        for(int i=0;i<enemies.size();i++){
                            if(name==enemies[i].getName())
                            {
                                if(enemies[i].current_situation()!=-1)
                                {
                                    QNS q = suits.front(); suits.pop();
                                    enemies[i].upgradeSuit(q);
                                    battleLog.push_back(name+" upgraded");
                                }
                                else
                                {
                                    battleLog.push_back(name+" upgrade Fail");
                                }break;
                            }
                        } 
                    }
                }
            }
            else if(str=="PrintBattleLog")
            {
                for(int i=0;i<battleLog.size();i++){
                    cout<<battleLog[i]<<'\n';
                }
            }
            else if(str=="BattleStatus")
            {
                int x = Result();
                if(x==1)
                {
                    cout<<"heroes are winning"<<'\n';
                }
                else if(x==-1)
                {
                    cout<<"enemies are winning"<<'\n';
                }
                else{cout<<"tie"<<'\n';}
            }
            else
            {
                break;
            }
        }
    }
    void printBattleLog()
    {
        int n = battleLog.size();

        for(int i=0;i<n;i++){
            cout<<battleLog[i]<<'\n';
        }
    }

    int Result()
    {
        int Whero=0;
        int Wenemies =0;
        for(int i=0;i<heros.size();i++){
            if(heros[i].Avgetdurability()>0)
            {
                Whero= Whero + heros[i].Avgetpower() + heros[i].Avgetdurability();
            }
        }

        for(int i=0;i<enemies.size();i++){
            if(enemies[i].Avgetdurability()>0){
                Wenemies = Wenemies + enemies[i].Avgetpower() + enemies[i].Avgetdurability();
            }
        }

        if(Whero>Wenemies)
        {
            return 1;
        }
        else if(Wenemies>Whero)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }   

    void addSuit(QNS q)
    {
        suits.push(q);
    }
    void addHeros(string name , int attack_Strength)
    {   
        if(!suits.empty())
        {
            QNS q = suits.front();suits.pop();
            Avenger A(name,q,attack_Strength);
            heros.push_back(A);
        }
        else
        {
            cout<<name<<" is out of fight"<<'\n';
        }
    }
    void addEnemies(string name,int attack_Strength)
    {
        if(!suits.empty())
        {
            QNS q = suits.front();suits.pop();
            Avenger A(name,q,attack_Strength);
            enemies.push_back(A);
        }
        else
        {
            cout<<name<<" is out of fight"<<'\n';
        }
    }


};

int main()
{
    Battle B;

    int k,n,m;

    cin>>k>>n>>m;

    for(int i=0;i<k;i++){
        int P,D,E,H;
        cin>>P>>D>>E>>H;
        QNS q(P,D,E,H);
        B.addSuit(q);
    }
    for(int i=0;i<n;i++){
        string name;
        int attack_Strength;
        cin>>name>>attack_Strength;
        B.addHeros(name,attack_Strength);
    }
    for(int i=0;i<m;i++){
        string name;
        int attack_Strength;
        cin>>name>>attack_Strength;
        B.addEnemies(name,attack_Strength);
    }

    string str;
    cin>>str;

    if(str=="BattleBegin")
    {
        B.startBattle();
    }
}




