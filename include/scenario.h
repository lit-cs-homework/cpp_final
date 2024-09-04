#pragma once


#include <iostream>
#include "./equip.h"
#include "../lib/nterm.h"
#include "./combat.h"


void narration(const char* m);
void npcTalk(const char* m);
void heroTalk(const char* m);

class Scenario {

public:
    Scenario(Hero& hero);
    //岩穴
    void  Cave();
    //地道
    void  Tunnel();
    //地窖
    void  Cellar();
    //祸窟
    void  DenOfDisaster();
    //石窟
    void  Grottoes();
    //地牢
    void  Dungeon();
    //内部使用函数，仅供调试使用
    void adjustScenario(int n);

    int getScenario();
    template <class B>
    void serialize(B& buf) const {
        buf << scenario ;
    }

    template <class B>
    void parse(B& buf) {
        buf >> scenario ;
    }
private:
    Hero& h;
    int scenario;
};
