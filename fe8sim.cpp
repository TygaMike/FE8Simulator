/*
fe8sim.cpp - Mike Price
 This program allows users to input
 the stats of a character and their weapon
 and will simulate a battle between 2 characters
 using the engine of Fire Emblem 8 - Sacred Stones.
 It uses arena rules, so only one weapon and no terrain.
*/

#include <iostream> //for UI
#include <cstdlib> //for rand()
#include <string>
using namespace std;

class Weapon
{
    int mt,hit,wt,crit,tri,attr,phys;
    /*
    For tri:
    0: Sword/Anima
    1: Lance/Dark
    2: Axe/Light
    3: Other (No weapon triangle.)

    For attr:
    0: Normal
    1: Bow - 3x damage to fliers.
    2: Armorslayer - 3x damage to armored units.
    3: Wyrmslayer - 3x damage to maneketes and dragons.
    4: Slayer - 3x damage to monsters.

    For phys:
    0: Physical
    1: Magic
    */
}

class Unit
{
    string name;
    int lvl,hp,str,skl,spd,luk,def,res,con,pskill,type,srank,bcrit; //Base stats
    bool gs; //determines if great shield is active
    int atk,df,ats,acc,avo,crt; //Combat stats
    Weapon wpn;
    /*
    For pskill:
    0: No skill
    1: Great Shield - Nullifies Damage - lvl%
    2: Pierce - Ignores Defense - lvl%
    3: Silencer - Instant Kill - 50% chance on crit
    4: Sure Strike - 100% hit chance - level%

    For type:
    0: Normal unit
    1: Flier - Weak to bows
    2: Armor - Weak to Hammer/Armorslayer/etc.
    3: Manakete/Dragon - Weak to Wyrmslayer.
    4: Monster - Weak to Slayer.
    */
}

Unit createfighter()
{
    Unit u;
    Weapon w;
    cout<<"Please enter unit's name: ";
    cin>>u.name;
    cout<<"Please enter unit's level: ";
    cin>>u.lvl;
    cout<<"Please enter unit's HP: ";
    cin>>u.hp;
    cout<<"Please enter unit's strength/magic: ";
    cin>>u.str;
    cout<<"Please enter unit's skill: ";
    cin>>u.skl;
    cout<<"Please enter unit's speed: ";
    cin>>u.spd;
    cout<<"Please enter unit's luck: ";
    cin>>u.luk;
    cout<<"Please enter unit's defense: ";
    cin>>u.def;
    cout<<"Please enter unit's resistance: ";
    cin>>u.res;
    cout<<"Please enter unit's constitution: ";
    cin>>u.con;
    cout<<"Please enter unit's personal skill, if any."<<endl
    <<"0: No skill."<<endl<<"1: Great Shield"<<endl<<"2: Pierce"<<endl
    <<"3: Silencer"<<endl<<"4: Sure Strike"<<endl;
    cin>>u.pskill;
    while(u.pskill < 0 || u.pskill > 4)
    {
        cout<<"Bad input, enter a valid skill."<<endl;
        cin>>u.pskill;
    }
    cout<<"Please enter unit's typing, if any."<<endl
    <<"0: No type."<<endl<<"1: Flier"<<endl<<"2: Armor"<<endl
    <<"3: Dragon/Manakete"<<endl<<"4: Monster"<<endl;
    cin>>u.type;
    while(u.type < 0 || u.type > 4)
    {
        cout<<"Bad input, enter a valid type."<<endl;
        cin>>u.type;
    }
    cout<<"Does your unit have an S rank in their weapon?"<<endl<<"0: Yes"<<endl<<"1: No"<<endl;
    cin>>s.srank;
    while(u.srank < 0 || u.srank > 1)
    {
        cout<<"Bad input, enter a valid answer."<<endl;
        cin>>u.srank;
    }
    cout<<"Please enter the unit's base crit rate: ";
    cin>>u.bcrit;
    cout<<"Now we will make the unit's weapon."<<endl<<"Please enter the weapon's might: ";
    cin>>w.mt;
    cout<<"Please enter the weapon's hit rate: ";
    cin>>w.hit;
    cout<<"Please enter the weapon's weight: ";
    cin>>w.wt;
    cout<<"Please enter the weapon's crit rate: ";
    cin>>w.crit;
    cout<<"Please enter the weapon's type."<<endl
    <<"0: Sword/Anima"<<endl<<"1: Lance/Dark"<<endl<<"2: Axe/Light"<<endl<<"3: Other"<<endl;
    cin>>w.tri;
    while(w.tri < 0 || w.tri > 3)
    {
        cout<<"Bad input, enter a valid type."<<endl;
        cin>>w.tri;
    }
    cout<<"What does the weapon slay?"<<endl
    <<"0: Nothing"<<endl<<"1: Fliers"<<endl<<"2: Armor"<<endl<<"3: Wyrm"<<endl<<"4: Monsters"<<endl;
    cin>>w.attr;
    while(w.attr < 0 || w.attr > 4)
    {
        cout<<"Bad input, enter a valid input."<<endl;
        cin>>w.attr;
    }
    cout<<"Is this a physical or magic weapon?"<<endl<<"0: Physical"<<endl<<"1: Magic"<<endl;
    cin>>s.phys;
    while(u.phys < 0 || u.phys > 1)
    {
        cout<<"Bad input, enter a valid answer."<<endl;
        cin>>u.phys;
    }
    u.wpn = w;   
    return u;
}

bool checkhp(Unit u)//returns true if unit is alive
{
    if(u.hp >= 0) return true;
    else return false;
}

int attack(Unit u[2])//Simulates an attack where u[0] attacks u[1] and returns damage dealt.
{
    int rng[3]; //Random numbers for hits, crits, and skill procs. An array so they can all be rolled at once, just like in the games.    
    int i;
    int bdamage, bacc, bcrit; //Damage done, battle accuracy and battle crit rate, dependent on both unit's stats.
    bool pc,ss; //Bool for pierce and sure strike proc
    int math; //hold value for math

    pc = false;
    ss = false;
    for(i = 0; i < 2; i++)//The games calculate this every time. It's useful if weapons can change between rounds of combat.
    {
        bdamage = u[i].atk - u[(i+1)%2].df;
        bacc = u[i].acc - u[(i+1)%2].avo;
        bcrit = u[i].crt - u[(i+1)%2].luk;
    }
    rng[0] = rand()%100;
    rng[1] = rand()%100;
    rng[2] = rand()%100;
    if(rng[2] < u[0].lvl)//Skill proc
    {
        switch(u[0].pskill)
        {
            case 1: u[0].gs = true;
            case 2: pc = true;
            case 4: ss = true;
            default: 
        }
    }
    if(rng[0] < bacc || ss == true)//Hit
    {
        if(u[1].gs == true)//Enemy Great Shield Proc
        {
            math = 0;
        }
        else if(pc == true)//Pierce proc
        {
            math = u[0].atk;
        }
        else math = bdamage;
        if(rng[1] < bcrit)//Crit
        {
            if(u[0].pskill == 3 && rand[2] < 50)//Silencer proc
            {
                math = u[1].hp;
            }
            else math *= 3;
        }
        return math;
    }
}

void displayhp(Unit u[2])
{
    cout<<u[0].name<<": "<<u[0].hp<<" HP"<<endl;
    cout<<u[1].name<<": "<<u[1].hp<<" HP"<<endl;    
}

void victor(Unit u)
{
    cout<<u.name<<" is victorious!"<<endl;
    cin.ignore();
    exit(1);
}

main()
{
    int i;
    int damage;
    Unit[2] u;
    Unit ur[2];//Has them indexed in reverse for having 1 attack 0    
    int wta[2], eff[2]; //Bool for weapon triangle advantage and Effective damage multiplier
    cout<<"Creating Unit 1."<<endl;
    u[0] = createfighter();
    cout<<"Creating Unit 2."<<endl;
    u[1] = createfighter();
    cout<<"From here on out, just press enter to advance the text, okay?"<<endl<<"You can type stuff, but it doesn't matter."<<endl;
    cin.ignore();
    //Determine weapon triangle advantage and effective damage.
    if((u[0].w.tri == 0 && u[1].w.tri == 1) || (u[0].w.tri == 1 && u[1].w.tri == 2) || (u[0].w.tri == 2 && u[1].w.tri == 3))
    {
        wta[0] = 1;
        wta[1] = -1;
    }
    if((u[1].w.tri == 0 && u[0].w.tri == 1) || (u[1].w.tri == 1 && u[0].w.tri == 2) || (u[1].w.tri == 2 && u[0].w.tri == 3))
    {
        wta[1] = 1;
        wta[0] = -1;
    }
    if(u[0].w.attr == u[1].type)
    {
        eff[0] = 3;
        eff[1] = 1;
    }
    if(u[1].w.attr == u[0].type)
    {
        eff[0] = 1;
        eff[1] = 3;
    }
    //Calculate combat stats. Not done in creation due to needing to know weapon triangle and enemy weapon type.
    for(i = 0; i<2; i++)
    {
        u[i].atk = u[i].str + ((u.w.mt + wta[i])*eff[i]);//attack
        if(u[(i+1)%2].w.phys == 0) u[i].df = u[i].def;//defense
        else u[i]df = u[i].res;
        u[i].ats = u[i].spd - (u[i].w.wt - u[i].con);//attack speed
        u[i].acc = u[i].w.hit + u[i].skl*2 + u[i].luk/2 + wta[i]*15 + u[i].srank*5;//accuracy
        u[i].avo = u[i].spd*2 + u[i].luk;//avoid
        u[i].crt = u[i].bcrit + u[i].w.crit + u[i].skl/2 + u[i].srank*5;//crit rate
        // Crit evade == Luck
    }
    ur[0] = u[1];
    ur[1] = u[0];
    //Now the battle begins.
    while(1)
    {
        cout<<u[0].name<<" attacks!"<<endl;
        cin.ignore();
        u[0].gs = false;
        damage = attack(u);
        u[1].hp -= damage;
        cout<<u[0].name<<" dealt "<<damage<<" damage!"<<endl;
        displayhp(u);
        cin.ignore();
        if(!checkhp(u[1])) victor(u[0]);//End fight and display winner if unit is dead.

        cout<<u[1].name<<" attacks!"<<endl;
        cin.ignore();
        u[1].gs = false;
        damage = attack(ur);
        u[0].hp -= damage;
        cout<<u[1].name<<" dealt "<<damage<<" damage!"<<endl;
        displayhp(u);
        cin.ignore();
        if(!checkhp(u[0])) victor(u[0]);//End fight and display winner if unit is dead.

        //Check for double attacks.
        if(u[0].ats - u[1].ats >= 4)
        {
            cout<<u[0].name<<" attacks again!"<<endl;
            cin.ignore();
            damage = attack(u);
            u[1].hp -= damage;
            cout<<u[0].name<<" dealt "<<damage<<" damage!"<<endl;
            displayhp(u);
            cin.ignore();
            if(!checkhp(u[1])) victor(u[0]);//End fight and display winner if unit is dead.
        }
        if(u[1].ats - u[0].ats >= 4)
        {
            cout<<u[1].name<<" attacks again!"<<endl;
            cin.ignore();
            damage = attack(ur);
            u[0].hp -= damage;
            cout<<u[1].name<<" dealt "<<damage<<" damage!"<<endl;
            displayhp(u);
            cin.ignore();
            if(!checkhp(u[0])) victor(u[0]);//End fight and display winner if unit is dead.
        }
    }
    return;
}