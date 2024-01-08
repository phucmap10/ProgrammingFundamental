#include "knight2.h"

bool Phoenixdown::canUse(BaseKnight* knight)
{
    int HP= knight->getHp() ;
    int maxHP= knight->getMaxHp() ;
    switch (typeOfPhoenix)
    {
    case 1:
        if (HP <= 0) return true;
        else return false;
    case 2:
        if (HP < (maxHP / 4)) return true;
        else return false;
    case 3:
        if (HP < (maxHP / 3)) return true;
        else return false;
    case 4:
        if (HP < (maxHP / 2)) return true;
        else return false;
    }
    return false;
};

void Phoenixdown::use(BaseKnight* knight)
{
    int HP{ knight->getHp() };
    int maxHP{ knight->getMaxHp() };
    switch (typeOfPhoenix)
    {
    case 1:
    case 2:
        knight->setHp(maxHP);
        return;
    case 3:
        if (HP <= 0) knight->setHp((maxHP / 3));
        else knight->setHp((maxHP / 4) + HP);
        return;
    case 4:
        if (HP <= 0) knight->setHp((maxHP / 2));
        else knight->setHp((maxHP / 5) + HP);
        return;
    }
}

bool Pythago(int n)
{
    int a = n % 10;
    int b = (n / 10) % 10;
    int c = n / 100;
    if (a * b * c == 0) return false;
    else if (a * a + b * b == c * c || b * b + c * c == a * a ||c * c + a * a == b * b) return true;
    return false;
}
bool Prime(int n)
{
    if (n <= 1) {
        return false;
    }
    
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}
/* * * BEGIN implementation of class BaseBag * * */

bool BaseBag::insertFirst(BaseItem* item) {
    if (count == 0)
    {
        head = new BagNode(item);
        ++count;
        return true;
    }
    else if (maxSlot == -1 || count < maxSlot)
    {
        BagNode* tmp = new BagNode(item, head);
        head = tmp;
        ++count;
        return true;
    }
    else return false;
}

BaseItem* BaseBag::get(ItemType itemType) {
    BagNode* tmp= head ;
    while (tmp)
    {
        if (tmp->item->getType() == itemType)
        {
            BaseItem* tmpItem{ tmp->item };
            return tmpItem;
        }
        tmp = tmp->next;
    }
    return nullptr;
}
string BaseBag::toString() const {
    string res{ "Bag[count=" };
    res = res + to_string(count) + ';';
    BagNode* tmp{ head };
    while (tmp)
    {
        res = res + tmp->item->toString() + ',';
        tmp = tmp->next;
    }
    if (res[res.length() - 1] == ',') res[res.length() - 1] = ']';
    else res += ']';
    return res;
}

BaseItem* BaseBag::checkItem(ItemType itemType, BaseKnight* knight) {
    BagNode* tmp= head;
    while (tmp != nullptr)
    {
        if (tmp->item->getType() == itemType && tmp->item->canUse(knight))
        {
            BaseItem* tmpItem = tmp->item ;
            tmp->item = head->item;
            head->item = tmpItem;
            return tmpItem;
        }
        tmp = tmp->next;
    }
    return nullptr;
}
bool BaseBag::useItem(ItemType itemType, BaseKnight* knight) {
    BaseItem* itemToUse = checkItem(itemType, knight);
    if (itemToUse!=nullptr)
    {
        itemToUse->use(knight);
        BagNode* tmp = head;
        head = head->next;
        --count;
        delete tmp;
        return true;
    }
    return false;
}

void BaseBag::dropItem()
{
    if (count>0)
    {
        BagNode* tmp = head;
        head = head->next;
        --count;
    }
}

void BaseBag::setmax(){
    BaseKnight* Knight;
    if(Knight->knightType == PALADIN){
        this->maxSlot = -1;
    }
    else if(Knight->knightType == LANCELOT){
        this->maxSlot = 16;
    }
    else if(Knight->knightType == DRAGON){
        this->maxSlot = 14;
    }
    else if(Knight->knightType == NORMAL){
        this->maxSlot = 19;
    }
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}
/* * * END implementation of class BaseKnight * * */
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight* khoitao= nullptr;
    if (maxhp == 888)
    {
        khoitao = new hsLancelot(id, maxhp, level, gil, antidote, phoenixdownI);
       
    }
    else if (Prime(maxhp) == true)
    {
        khoitao = new hsPaladin(id, maxhp, level, gil, antidote, phoenixdownI);
        
    }
    else if (maxhp > 99 && maxhp <= 999 && Pythago(maxhp))
    {

        khoitao = new hsrong(id, maxhp, level, gil, 0, phoenixdownI);
       
    }
    else
    {
        khoitao = new hs(id, maxhp, level, gil, antidote, phoenixdownI);
        
    }
    return khoitao;
}
bool BaseKnight::Arise()
{
    if (bag->useItem(PHOENIX, this)) return true;
    else if (this->hp <= 0 && this->gil >= 100)
    {
        this->hp = this->maxhp / 2;
        this->gil -= 100;
        return true;
    }
    return false;
}

void hsPaladin::fight(BaseOpponent* opponent)
{
    int monsterType = opponent->getType();
    if (monsterType <= 5)
    {
        winningMinor(opponent);
    }
    else if (this->level >= opponent->getlv())
    {
        if (monsterType == 6)
        {
            winTornbery();
        }
        else winQueen();
    }
    else if (monsterType==6)
    {
        loseTornbery();
    }
}

void hsLancelot::fight(BaseOpponent* opponent)
{
    int monsterType = opponent->getType();
    if (monsterType <= 5)
    {
        winningMinor(opponent);
    }
    else if (this->level >= opponent->getlv())
    {
        if (monsterType == 6)
        {
            winTornbery();
        }
        else winQueen();
    }
    else if (monsterType == 6)
    {
        loseTornbery();
    }
    else loseQueen();
}
void hsrong::fight(BaseOpponent* opponent)
{
    int monsterType = opponent->getType();
    if (this->level >= opponent->getlv())

    {
        if (monsterType <= 5) winningMinor(opponent);
        else if (monsterType == 6)
        {
            winTornbery();
        }
        else winQueen();
    }
    else if (monsterType <= 5)
    {
        losingMinor(opponent);
    }
    else if (monsterType == 7) loseQueen();
}
void hs::fight(BaseOpponent* opponent)
{   
    int monsterType = opponent->getType();
    if (this->level >= opponent->getlv())
    {
        if (monsterType <= 5) winningMinor(opponent);
        else if (monsterType == 6)
        {
            winTornbery();
        }
        else winQueen();
    }
    else if (monsterType <= 5)
    {
        losingMinor(opponent);
    }
    else if (monsterType == 6) loseTornbery();
    else loseQueen();
}
/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights): dieukien{}
{
    ifstream inf{ file_armyknights };
    army = nullptr;
    hslucdau = 0;
    sohs = 0;
    inf >> sohs;
    hslucdau = sohs;
    army = new BaseKnight*[sohs];
    for (int i=0; i<sohs; ++i)
    {
        int hp, level, phoenix, gil, antidote;
        inf >> hp >> level >> phoenix >> gil >>antidote;
        army[i] = BaseKnight::create(i+1,hp,level,gil,antidote,phoenix);
    }
    inf.close();
}
ArmyKnights::~ArmyKnights() 
{
    for (int i= 0 ; i < hslucdau; ++i)
    {
        if (army[i]) delete army[i];
    }
    delete[] army;
    army = nullptr;
    sohs = 0;
}

bool ArmyKnights::adventure(Events* events) {
    int numOfEvents= events->count() ;
    bool result= true ;
    for (int i = 0 ; i < numOfEvents; ++i)
    {
        int eventNumber{ events->get(i) };
        if (sohs <= 0)
        {
            printInfo();
            continue;
        }
        bool res = eventHandle(i, eventNumber);

        printInfo();
        if (!res) result = false;
    }
    return result;
}
int ArmyKnights::count() const {
    return sohs;
}

BaseKnight* ArmyKnights::lastKnight() const {
    return army[sohs - 1];
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}


void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

void ArmyKnights::deleteKnight(int index)
{
    if (army != nullptr && index >= 0 && index < sohs)
    {
        delete army[index];
        army[index] = nullptr;
        sohs--;
    }
}

void ArmyKnights::passGil(int numOfGil, int startIdx)
{
    while (startIdx>=0 && numOfGil>0)
    {
        int curGil = army[startIdx]->getGil();
        curGil += numOfGil;
        numOfGil = 0;
        if (curGil > 999)
        {
            numOfGil = curGil - 999;
            curGil = 999;
        }
        army[startIdx]->setGil(curGil);
        --startIdx;
    }
}

bool ArmyKnights::fightMinorMonster(int eventOrder, int monsterType)
{
    int gilOfMonster[5]{ 100,150,450,750,800 };
    int bdOfMonster[5]{ 10,15,45,75,95 };
    int monsterLevel = (eventOrder + monsterType) % 10 + 1;
    BaseOpponent* monster = new BaseOpponent(monsterLevel, gilOfMonster[monsterType - 1], bdOfMonster[monsterType - 1], monsterType);
    for (int i= sohs - 1 ; i >= 0; --i)
    {
        army[i]->fight(monster);
        if (army[i]->getHp() <= 0) deleteKnight(i);
        else
        {
            int gil = army[i]->getGil();
            if (gil > 999)
            {
                army[i]->setGil(999);
                passGil(gil - 999, i - 1);
            }
            break;
        }
        
    }
    delete monster;
    if (sohs <= 0) return false;
    return true;
}
bool ArmyKnights::fightTornbery(int eventOrder)
{
    int monsterLevel = (eventOrder + 6) % 10 + 1;
    BaseOpponent* monster = new BaseOpponent(monsterLevel, 0, 0, 6);
    for (int i = sohs - 1 ; i >= 0; --i)
    {
        army[i]->fight(monster);
        if (army[i]->getHp() <= 0) deleteKnight(i);
        else break;
    }
    delete monster;
    if (sohs <= 0) return false;
    return true;
}
bool ArmyKnights::QueenOfCards(int eventOrder)
{
    int monsterLevel = (eventOrder + 7) % 10 + 1;
    BaseOpponent* monster = new BaseOpponent(monsterLevel, 0, 0, 7);
    BaseKnight* lastknight = this->lastKnight();
    lastknight->fight(monster);
    int gil = lastknight->getGil();
    if (gil > 999)
    {
        lastknight->setGil(999);
        passGil(gil - 999, sohs - 2);
    }
    delete monster;
    return true;
}
void ArmyKnights::Nina()
{
    for (int i=0; i < sohs; ++i)
    {
        BaseKnight* tmp = this->army[i];
        //BaseKnight* tmp = this->lastKnight();
        int curGil = tmp->getGil();
        int curHp = tmp->getHp();
        int maxHp = tmp->getMaxHp();
        if (tmp->getType() == PALADIN && curHp < (maxHp / 3))
        {
            tmp->setHp(curHp + maxHp / 5);
        }
        else if (curGil >= 50 && curHp < (maxHp / 3))
        {
            tmp->setGil(curGil - 50);
            tmp->setHp(curHp + maxHp / 5);
        }
    }
}
bool ArmyKnights::fightOmegaWeapon()
{
    if (dieukien.DefeatedOmega) return true;
    for (int i= sohs - 1 ; i >= 0; --i)
    {
        if (army[i]->getType() == DRAGON ||
            army[i]->getLv()==10 && (army[i]->getHp() == army[i]->getMaxHp()))
        {
            dieukien.DefeatedOmega = true;
            army[i]->setLv(10);
            army[i]->setGil(999);
            return true;
        }
        else
        {
            army[i]->setHp(0);
            army[i]->Arise();
            if (army[i]->getHp() <= 0) deleteKnight(i);
            else return true;
        }
    }
    if (sohs <= 0) return false;
    return true;
}


bool ArmyKnights::fightHades()
{
    if (dieukien.DefeatedHades) return true;
    for (int i= sohs - 1 ; i >= 0; --i)
    {
        if (army[i]->getLv() == 10 ||
            army[i]->getType() == PALADIN && army[i]->getLv() > 7 )
        {
            dieukien.DefeatedHades = true;
            dieukien.gotShield = true;
            return true;
        }
        else
        {
            army[i]->setHp(0);
            army[i]->Arise();
            if (army[i]->getHp() <= 0) deleteKnight(i);
            else return true;
        }
    }
    if (sohs <= 0) return false;
    return true;
}

bool ArmyKnights::fightUltimecia()
{
    if (dieukien.gotSword) return true;
    if (!hasPaladinShield() || !hasLancelotSpear() || !hasGuinevereHair()) return false;
    int BossHP{ 5000 };
    for (int i= sohs-1 ; i >= 0; --i)
    {
        if (army[i]->getType() != NORMAL)
        {
            int damage = (int)(army[i]->getLv() * army[i]->getHp() * army[i]->knightbasedmg);
            BossHP -= damage;
            if (BossHP <= 0) return true;
            deleteKnight(i);
        }
        else deleteKnight(i);
    }
    
    return false;
}
void ArmyKnights::durian()
{
    for (int i= 0 ; i < sohs; ++i)
    {
        BaseKnight* tmp = this->army[i];
        tmp->setHp(tmp->getMaxHp());
    }
}

void ArmyKnights::takePhoenix(int type)
{
    BaseItem* tmp = new Phoenixdown(type);
    for (int i= sohs - 1 ; i >= 0; --i)
    {
        if (army[i]->getBag()->insertFirst(tmp)) return;
    }
    delete tmp;
    return;
}
void ArmyKnights::compulItem(int eventNumber)
{
    switch (eventNumber)
    {
    case 95: 
        dieukien.gotShield = true;
        return;
    case 96:
        dieukien.gotSpear = true;
        return;
    case 97:
        dieukien.gotHair = true;
        return;
    }
}
void ArmyKnights::takeExcalibur()
{
    dieukien.gotSword = dieukien.gotShield && dieukien.gotSpear && dieukien.gotHair;
}

bool ArmyKnights::eventHandle(int eventOrder, int eventNumber)
{
    if (eventNumber <= 5)
    {
        return fightMinorMonster(eventOrder, eventNumber);
    }
    else if (eventNumber == 6) return fightTornbery(eventOrder);
    else if (eventNumber == 7) return QueenOfCards(eventOrder);
    else if (eventNumber == 8)
    {
        Nina();
        return true;
    }
    else if (eventNumber == 9)
    {
        durian();
        return true;
    }
    else if (eventNumber == 10) return fightOmegaWeapon();
    else if (eventNumber == 11) return fightHades();
    else if (eventNumber == 95 ||eventNumber == 96 ||eventNumber == 97 )
    {
        compulItem(eventNumber);
        return true;
    }
    else if (eventNumber == 98)
    {
        takeExcalibur();
        return dieukien.gotSword;
    }
    else if (eventNumber == 99) return fightUltimecia();
    else
    {
        takePhoenix(eventNumber - 110);
        return true;
    }
    return true;
}


/* * * END implementation of class ArmyKnights * * */

Events::Events(const string& file_events) {
    ifstream inf{ file_events };
    numOfEvent = 0;
    event = nullptr;
    inf >> numOfEvent;
    event = new int[numOfEvent];
    for (int i= 0 ; i < numOfEvent; ++i)
    {
        inf >> event[i];
    }
    inf.close();
}
Events::~Events() {
    delete[] this->event;
    this->event = nullptr;
    numOfEvent = 0;
}
int Events::count() const {
    return numOfEvent;
}

int Events::get(int i) const {
    return this->event[i];
}
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure() {
    if (armyKnights!=nullptr) delete armyKnights;
    if (events!=nullptr) delete events;
}

void KnightAdventure::loadArmyKnights(const string& inf)
{
    armyKnights = new ArmyKnights(inf);
}

void KnightAdventure::loadEvents(const string& inf)
{
    events = new Events(inf);
}

void KnightAdventure::run()
{
    if (armyKnights!=nullptr && events!=nullptr)
    {
        bool res = armyKnights->adventure(events);
        armyKnights->printResult(res);
    }
}


/* * * END implementation of class KnightAdventure * * */