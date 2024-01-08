#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE= 0, PHOENIX};

class BaseItem;
class Phoenixdown;
class Antidote;
class BaseKnight;
class Events;

class BaseItem {
protected:
    ItemType itemType;
public:
    virtual ItemType getType() { return itemType; }
    virtual string toString() = 0;
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    virtual  ~BaseItem(){};
};

class Antidote : public BaseItem{
    public:
        Antidote() {
            this-> itemType = ANTIDOTE;
    }

    ~Antidote() {}

    string toString() { return "Antidote"; }

    bool canUse(BaseKnight* knight)
    {
        return true;
    }

    void use(BaseKnight* knight)
    {
        return;
    }
};
class Phoenixdown : public BaseItem
{
protected:
    int typeOfPhoenix;
public:
    Phoenixdown(int num = 1)
    {
        this->itemType = PHOENIX;
        typeOfPhoenix = num;
    }
    ~Phoenixdown() {}
    
    string toString() {
        string arr[4]{ "I", "II", "III", "IV" };
        return "Phoenix" + arr[typeOfPhoenix - 1];
    }

    bool canUse(BaseKnight* knight);

    void use(BaseKnight* knight);

};



class BaseBag {
    struct BagNode {
        BaseItem* item;
        BagNode* next;
        BagNode(BaseItem* input = nullptr, BagNode* nextptr = nullptr){
            item = input;
            next = nextptr;
        }
        ~BagNode()
        {
            if (item!= nullptr) delete item;
        }
    };
    BagNode* head;
    int count;
    int maxSlot;
public:
    BaseBag(int phoenixdown, int antidote, int max = -1) {
        maxSlot = max;
        count = 0;
        head = nullptr;
        for (int i = 0; i < phoenixdown; ++i)
        {
            //insert phoenix1 in bag
            BaseItem* tmp = new Phoenixdown();
            this->insertFirst(tmp);
        }

        for (int i= 0 ; i < antidote; ++i)
        {
            BaseItem* tmp = new Antidote();
            this->insertFirst(tmp);
        }
    }
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;

    ///student's method
    ~BaseBag()
    {
        while (head != nullptr)
        {
            BagNode* tmp= head ;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
        count = 0;
    }
protected:
    virtual BaseItem* checkItem(ItemType itemType, BaseKnight* knight);
public:
    virtual bool useItem(ItemType itemType, BaseKnight* knight);
    virtual void dropItem();
    virtual void setmax();
    int getmax(){return maxSlot;};
};


class BaseOpponent{
    protected:
        int level;
        int gil;
        int basedmg;
        int type;
    public:
        BaseOpponent(int level, int gil, int basedmg, int type){
            this->level = level;
            this->gil = gil;
            this->basedmg = basedmg;
            this->type = type;
        }
        int getType(){
            return type;
        }
        int getgil(){
            return gil;
        }
        int getlv(){
            return level;
        }
        int getbasedmg(){
            return basedmg;
        }
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;

public:
    KnightType knightType;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    double knightbasedmg;
    virtual void fight(BaseOpponent * opponent) = 0;
    virtual ~BaseKnight(){
        if(bag != NULL)
        {delete bag;}
        bag = nullptr;
     }  
    void setHp(int HP) { this->hp = HP; }
    int getHp() const { return hp; }
    int getMaxHp() const{ return maxhp; }
    int getLv() const { return level; }
    void setLv(int lv) { level = lv; }
    KnightType getType() const { return knightType; }
    int getGil() const { return gil; }
    void setGil(int gil) { this->gil = gil; }
    BaseBag* getBag() { return bag; }
    virtual bool Arise();
    protected:
    virtual void winningMinor(BaseOpponent* opponent) {
        this->gil += opponent->getgil();
    }
    virtual void losingMinor(BaseOpponent* opponent)
    {
        int damage = opponent->getbasedmg() * (opponent->getlv() - this->level);
        this->hp -= damage;
        Arise();
    }
    virtual void winTornbery()
    {
        if(this->level < 10){
            this->level +=1;
        }else this->level = this->level;
    }
    virtual void loseTornbery()
    {
        if (antidote > 0)
        {
            --antidote;
            bag->useItem(ANTIDOTE, this);
        }
        else
        {
            for (int i=0 ; i < 3; ++i) bag->dropItem();
            this->hp -= 10;
            Arise();
        }
    }
    virtual void winQueen()
    {
        this->gil *= 2;
    }
    virtual void loseQueen()
    {
        this->gil /= 2;
    }
};

class hsPaladin : public BaseKnight{
    public:
    hsPaladin(int id, int maxhp, int level, int gil, int antidote, int phoenixI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        bag = new BaseBag(phoenixI, antidote);
        this->knightType = PALADIN;
        knightbasedmg = 0.06;}

    ~hsPaladin(){if(bag != NULL)
        {delete bag;}
        bag = nullptr;
     }
     void fight(BaseOpponent* opponent);
};
class hsLancelot : public BaseKnight{
    public:
    hsLancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        bag = new BaseBag(phoenixI, antidote);
        this->knightType = LANCELOT;
        knightbasedmg = 0.06;}

    ~hsLancelot(){if(bag != NULL)
        {delete bag;}
        bag = nullptr;
     }
     void fight(BaseOpponent* opponent);
};
class hsrong : public BaseKnight {
public:
    hsrong(int id, int maxhp, int level, int gil, int antidote, int phoenixI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        bag = new BaseBag(phoenixI, antidote,14);
        this->knightType = DRAGON;
        knightbasedmg = 0.075;
    }
    ~hsrong()
    {
        if (bag) delete bag;
        bag = nullptr;
    }
    void fight(BaseOpponent* opponent);
};
class hs : public BaseKnight {
public:
    hs(int id, int maxhp, int level, int gil, int antidote, int phoenixI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        bag = new BaseBag(phoenixI, antidote,14);
        this->knightType = NORMAL;
        knightbasedmg = 0;
    }
    ~hs()
    {
        if (bag) delete bag;
        bag = nullptr;
    }
    void fight(BaseOpponent* opponent);
};


struct setinfo{
    bool gotShield = false;
    bool gotSpear = false;
    bool gotHair = false;
    bool gotSword = false;
    bool DefeatedOmega = false;
    bool DefeatedHades = false;
};

class ArmyKnights {
    BaseKnight** army;
    int hslucdau;
    int sohs;
    setinfo dieukien;


public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const { return dieukien.gotShield; }
    bool hasLancelotSpear() const { return dieukien.gotSpear; }
    bool hasGuinevereHair() const { return dieukien.gotHair; }
    bool hasExcaliburSword() const { return dieukien.gotSword; }

    void printInfo() const;
    void printResult(bool win) const;

    //student's method
private:
    void deleteKnight(int index);

    void passGil(int, int);

    bool eventHandle(int eventOrder, int eventNumber);

    bool fightMinorMonster(int eventOrder, int monsterType);

    bool fightTornbery(int eventOrder);

    bool QueenOfCards(int eventOrder);

    void Nina();

    void durian();

    bool fightOmegaWeapon();

    bool fightHades();

    bool fightUltimecia();

    void takePhoenix(int type);

    void compulItem(int eventNumber);

    void takeExcalibur();

    
};


class Events {
    int* event;
    int numOfEvent;
public:
    Events(const string& file);
    ~Events();
    int count() const;
    int get(int i) const;
};


class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__