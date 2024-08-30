
#include "../../include/equip.h"

#include<memory>

// void fun()
// {
    // BlueMedicine bluemedicine;
    // RedMedicine redMedicine;
    // Stonesword a(0,0,0,10,10);
    // Ironsword b(0,0,0,30,30);
    // Bronzesword c(0,0,0,20,20);
    // Shoes d(5,5,5,10);
    // Armhour e(10,10,20,30);
    // std::vector<Equip> equipstore = {a,b,c};
    // std::vector<Medicine> medicinestore = {redMedicine,bluemedicine};
    // Store store(equipstore,medicinestore);
    // Hero hero;
    // Bag bag;
// }

int main()
{
    std::shared_ptr<BlueMedicine> bluemedicine = std::make_shared<BlueMedicine>() ;
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    std::shared_ptr<StoneSword> a = std::make_shared<StoneSword> (0,0,0,10,10);
    std::shared_ptr<IronSword> b = std::make_shared<IronSword> (0,0,0,30,30);
    std::shared_ptr<BronzeSword> c= std::make_shared<BronzeSword> (0,0,0,20,20);
    std::shared_ptr<Shoes> d = std::make_shared<Shoes> (5,5,5,10);
    std::shared_ptr<Armhour> e = std::make_shared<Armhour> (10,10,20,30);
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {redMedicine,bluemedicine};
    Store store(equipstore,medicinestore);
    Hero hero;
    hero.getBag().get(redMedicine,10);
    hero.getBag().display();
}