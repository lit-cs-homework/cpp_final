# *装备类*
首先创建一个基本装备类 `class BaseEquip` 然后再分成`class Equip` 和 `class Medicine` 然后最后由这两个类 分出各种子类


# *商店类*
主要思路是用两个`unoder_map`容器分别管理`class Equip`和`class Medicine` 
```cpp
        std::unordered_map<std::shared_ptr<Equip>, int, hashBaseEquip, eqOnObj> equipCommodities;
        std::unordered_map<std::shared_ptr<Medicine>, int, hashBaseEquip, eqOnObj> medicineCommodities;
```
主要的函数有：
```cpp
    //商店UI交互
    void trade(Bag& bag,Hero& hero);
    // 纯 CLI 交互
    void tradeCli(Bag& bag,Hero& hero);
    bool sold(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero);//角色买装备，商店卖装备
    bool sold(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero);///角色买药水，商店卖药水
    bool buy(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero);//角色卖装备，商店买
    bool buy(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero);//角色卖药水


    核心是靠几个个 unordered_map 容器 存储类名以及一个返回类型的函数 靠类名找到对应类型，并调用该类型的各种功能
    std::unordered_map<std::string,std::function<void(std::shared_ptr<Equip>&> equipbagmap;
```

# *背包类*
跟商店类似，主要思路是用两个`unoder_map`容器分别管理`class Equip`和`class Medicine` ,用`array`容器管理装备栏
```cpp
        std::unordered_map<std::shared_ptr<Equip>, int, hashBaseEquip, eqOnObj> equipBag;//未装备的装备
        std::unordered_map<std::shared_ptr<Medicine>, int, hashBaseEquip, eqOnObj> medicineBag;//药水
        std::array<std::shared_ptr<Equip>, EquipTypCount> equipColumn;//已装备的装备 武器栏
```

主要的函数有：
```cpp
        //角色获得装备
        void get(std::shared_ptr<Equip> equip, int n);
        //角色获得药水
        void get(std::shared_ptr<Medicine> Medicine, int n);
        void display() const;
        // 展示装备栏
        void displayEquipColumnCil(Hero& hero);
        void displayEquipColumnAndChange(Hero& hero);
        //角色使用药水
        bool use(std::shared_ptr<Medicine> medicine, int n, Hero& hero);
        //角色更换装备
        void changeequip(std::shared_ptr<Equip> equip, Hero& hero);

        核心的实现方式跟商店类似
```

# *背包/商店的序列化和反序列化*
```cpp
    核心是靠几个unordered_map容器 存储类名以及一个返回类型的函数 靠类名找到对应类型
    std::unordered_map<std::string,std::function<void(std::shared_ptr<Equip>&> equipbagmap;

    序列化时 将背包/商店中的物品名字存入 完成序列化
    
    反序列化时 将名字一一读出，然后靠这个容器，找到对应的类，从而完成反序列化
```






