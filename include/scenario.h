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
    Scenario(Hero& hero, Store& storem);
    //岩穴 7
    void  Cave();
    //地道 4
    void  Tunnel();
    //地窖 3
    void  Cellar();
    //祸窟 1
    void  DenOfDisaster();
    //石窟 6
    void  Grottoes();
    //地牢 9
    void  Dungeon();
    //鬼门 0
    void ghostdom();
    //地宫 2
    void underPalace();
    //暗室 5
    void darkroom();
    //冥界 10
    void SweatPore();
    //内部使用函数，仅供调试使用
    void adjustScenario(int n);

    void end();
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
    Store& store;
};
