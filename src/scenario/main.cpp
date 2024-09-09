#include "../../include/combat.h"
#include "../../include/equip.h"
#include "../../lib/nterm.h"
#include "../../include/equip.h"
#include "../../include/scenario.h"

#ifdef _WIN32
# include<windows.h>
#else
//#include <unistd.h>
#endif

static
void ms_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec tp = {
		ms / 1000,    // second
		ms % 1000000  // ns
	};
	nanosleep(&tp, NULL);
#endif
}

#include <cstring>
static
void narrationImpl(const char* m, ForegroundColor color)
{
    hideCursor();
    //std::cout<<m;
    for(int i=0;i<strlen(m);i+=3)
    {
        char print[]={m[i],m[i+1],m[i+2], '\0'};
        styledWrite(color, StyleSet{styleBright},print);
        ms_sleep(30);
    }
    std::cout<<std::endl;
    showCursor();
}

void narration(const char* m)
{
    narrationImpl(m, fgYellow);
}

void npcTalk(const char* m)
{
    narrationImpl(m, fgGreen);
}

void heroTalk(const char* m)
{
    narrationImpl(m, fgWhite);
}

Scenario::Scenario(Hero& hero, Store& storem):h(hero),store(storem)
{
    store.refresh();
    scenario = 0;
}

void Scenario::adjustScenario(int n)
{
    scenario = n;
}
int Scenario::getScenario()
{
    return scenario;
}
void Scenario::end()
{
    narration("你来到了另一处墙角，一剑轰出，又是一条通道。你刚要进去，后面传来了熟悉的声音。");
    npcTalk("邓锋魄：真是太麻烦你了，还专门为我打通了一条出去的路。");
    heroTalk("你：你知道的，我从不为别人做事。");
    npcTalk("邓锋魄：我可不这么想。与地灵一战，你已经没多少剩余了吧？我一直存下的魂印都能成为我的助力，你不是我的对手。");
    heroTalk("你：你太自信了，之前和我还有那三巨头对抗你就没什么剩余了。为了防止引起地灵的注意你也不敢大肆屠杀魔物。就算你这段时间把所有人类都杀了，抢了他们身上的所有魂印。杀黑龙去无嗔戒的时候估计也没多少剩余了吧？");
    npcTalk("邓锋魄：那就来试试！我就不信...");
    ms_sleep(1000);
    heroTalk("你突然插口：你以为利用地牢的石碑能骗过我？");
    narration("邓锋魄的脸色闪过一丝慌乱。");
    heroTalk("你：我早就有疑问，我失忆之前为什么会把最多的信息放在最有可能遭破坏的石碑上？看来你有十足的把握，我被你清除的记忆绝对找不回来，这样我就能百分百相信已经被你修改过的内容。让我猜猜，和我打你会立刻示弱然后逃跑消去踪迹，等我进入穴口，然后就会被你这段时间花大代价设下的封印困住是吧？");
    ms_sleep(2000);      
    npcTalk("邓锋魄：你...");
    heroTalk("你：看来你是真的舍不得多花一点力量把石窟打开啊，不然要是石窟石碑也被修改了，我就真的要相信石碑说的话了。又或者说，你根本不敢去石窟，害怕引起黑龙的注意？想来你胆子也没有多大，连尝试吸收石碑下我的力量都不敢，看来是不愿冒一点险啊！");
    ms_sleep(2000);      
    heroTalk("你接着说：你料定我没能力在石窟石碑里刻下记忆。却没想到我留下的装备里恰好有一张地下的地图，里面根本没穴口这个地方！其实你不知道怎么样才能出去，你也不想出去，你只是觉得一直待在这个地方，你就可以获得越来越强大的力量，这样你迟早可以摆脱束缚。但我不一样，我是真受不了这个地方的味道了。");
    ms_sleep(2000);      
    npcTalk("邓锋魄：你要做什么？");
    heroTalk("你举起了鬼玺，高喊道：地灵，想必你也听到了吧！留你一命就是为了这个！我不在乎你最终能达到什么实力，我只想要自己能逃出去！现在，我可以让所有地下怪物全都自杀，你可以汲取到无穷的力量，足以让你恢复状态，然后杀了这个小人！以后你还能达成你的目的！你需要做的，就只是让我逃出去而已。否则，我会除了你的性命，成为地下新的主宰！");
    npcTalk("邓锋魄：等一下！地灵！千万别答应他！");
    narration("地下空间传了沉闷的回响，你的身后出现了一道漆黑的洞口。");
    narration("你迅速来到洞口前，控制一只影魔钻了进去，片刻后，影魔又出来了，身上遍布着黑痕，你一眼就认出是这属于阳光对影魔的伤害。");
    heroTalk("你再次举起鬼玺：杀害所有怪物的事情就交给锋魄兄弟了！");
    narration("地下空间里的怪物几乎全向岩穴涌了过去，向邓锋魄发起了攻击...");
    narration("群攻之下，邓锋魄只能边战边退，根本来不及收集魂印。而落到地上的魂印会被地灵吸收，届时邓锋魄无处可逃。");
    narration("你一剑将邓锋魄逼退，转身跳入黑洞。一眨眼，眼前便是磷光点点的树林，你一剑再出，黑洞瞬间崩溃。");
}
void  Scenario::Cave()
{
    if(getScenario()==0)
    {
    narration("你缓缓地从一片黑暗中苏醒过来，周身弥漫着一股霉味和潮湿的气息。脑袋里一片空白，没有过去的记忆来填补这突如其来的存在感。你的视线逐渐聚焦，发现自己身上仅穿着几件破旧不堪的衣物，似乎已经经历了无数次的磨损和风化。环顾四周，发现自己身处一个昏暗的地穴之中，头顶上是粗糙的岩石，周围零星散落着一些破碎的石头和尘土。当你试图站起来时，一阵眩晕袭来，但你还是坚持着摇晃着站稳了脚跟。这时，你的眼睛被前方的一丝微弱光线所吸引——那是地穴的一个出口。尽管光亮并不强烈，但在这样的环境中，它就像是希望的灯塔一样引人注目。你朝着光源走去，每一步都小心翼翼，生怕惊扰了这份难得的宁静。随着距离的缩短，你发现那光线的背后竟然走进来一个人影。");
    ms_sleep(1000);
    eraseScreen();
    npcTalk("？？？：看来你醒了，别露出一副狼狈的模样，打起精神来！不然在这里会死的！");
    heroTalk("你：这是哪里？你是谁？");
    ms_sleep(1000);
    npcTalk("？？？：别问这些浪费体力的问题，你现在最应该做的是想办法出去！哦我忘了，瞧瞧你，连个武器都没有，还一副要死的样子，真是可怜。这样吧，这些东西送给你，别高兴得太早，外面有很多“家伙”在等着你呢！想要逃出这个鬼地方，就想办法让自己变得更强，拿到鬼玺之后来找我！当然，有金币的话也可以来岩穴和我这换一些东西，你会需要的。");
    narration("你获得了地图，铁剑 ×１，生命药水 ×１，你知道了当前的位置是在“岩穴”");
    ms_sleep(3000);
    adjustScenario(1);
    }
    else if(getScenario()<=4)
    {
        npcTalk("？？？：怎么了？拿到鬼奚了？还是想要与我交换？");
        store.trade(h.getBag(), h);
    }
    else if(getScenario()<=5)
    {
        npcTalk("邓锋魄：怎么了？拿到鬼奚了？还是想要与我交换？");
        store.trade(h.getBag(), h);
    }
    else if(getScenario()==6)
    {
        narration("邓锋魄果然还在这，你抢先一步开口。");
        heroTalk("你：我是怎么来到这里的？");
        npcTalk("邓锋魄：看来你已经知道了些什么。告诉你吧，这里的每一个人，包括怪物，都是被吞到地下来的！这整个地下的空间都是活着的！待在这里迟早会死，所以去找鬼玺吧，找到鬼玺我们就能出去了。");
        heroTalk("你：你要金币做什么？");
        npcTalk("邓锋魄：我喜欢收藏而已，更多的是想给你一些帮助。");
        heroTalk("你：你撒谎！一个食人魔手里的金币提醒了我，那根本不是金币！甚至不是金属！那不是怪物自己的东西，那是在他们身上自然形成的！");
        npcTalk("邓锋魄：...");
        heroTalk("你：为什么我失去了过往的记忆？");
        npcTalk("邓锋魄：相信我，我的朋友，你不会想知道的。");
        heroTalk("你：那可就别怪我了！");
        narration("你冲向邓锋魄，却扑了个空，他已经消失了。");
        adjustScenario(7);
    }
    
}

void  Scenario::Tunnel()
{
    if(getScenario()==1)
    {
        narration("昏暗的地道，你紧绷着神经尽量不发出脚步声，突然一个人影向你冲来。在战斗开始之前，你敏锐的感官看到了他胸前的吊牌，上面写着：裴岭滔。");
        Enemy e{"裴岭滔","迷失在地下的人类",80,80,20,20,20,10,1,10,1};
        Skill s("挥砍","用剑向前全力的劈砍",20,0);
        Skill S[1]={s};
        e.setSkill(S,1);
        Battle(&h,e);

        narration("人影明显已经失去了抵抗能力，在他生命垂危之际，你开了口。");
        heroTalk("你：你是谁？为什么要攻击我？");
        npcTalk("裴岭滔：见鬼！你居然也是清醒的！早知道不打你了！");
        heroTalk("你：什么意思？");
        npcTalk("裴岭滔：你不知道吗？这里可不只有这些怪物！还有好多人类都被困在这个地方！但他们不知道怎么回事都失常了！已经有不下十几个人突然攻击我了，没想到你居然和我一样是清醒的。");
        heroTalk("你：你快死了，我无能为力，抱歉。");
        npcTalk("裴岭滔：死了好！这鬼地方我是一秒也不想多待！我看你比我强多了，不知道有没有希望出去。告诉你吧，越厉害的怪物越聪明，有的甚至可以说话！你想找逃出去的线索的话除了遇到我这样的人外就只有去找怪了。");      
        narration("裴岭滔的生机一点点消逝。你站在他的尸体旁想着：悼念一会吧...");
        ms_sleep(3000);
        narration("3秒后，你把他身上所有的装备物品都扒了下来");
        heroTalk("你：无主之物，不拿白不拿");
        h.adjustGold(100);
        adjustScenario(2);
    }
}
void  Scenario::Cellar()
{
    if(getScenario()==2)
    {
        npcTalk("未知的声音：那边的！站着的人类！我不知道你还能活多久，但还是请你帮我找一把钥匙，他被祸窟里的一只影魔拿去了。");
        heroTalk("你：啊？等等...");
        narration("声音消失了...");
        adjustScenario(3);
    }
    else if(getScenario()==4)
    {
        npcTalk("未知的声音：你拿到钥匙了！请你把它还给我，我会报答你的！只要把钥匙放在地上就好！");
        narration("你犹豫了一下，还是把钥匙扔到了地上。");
        narration("钥匙悬浮了起来，遁入黑暗不见了。");
        npcTalk("未知的声音：人类，你想要什么？");
        heroTalk("你：不想要什么，只是随便走走，顺便看能不能找到关于我的线索。");
        npcTalk("未知的声音：既然如此，我就帮你把通往石窟的路我清理干净好了。另外，小心邓锋魄吧，他和你们这些被吞入到这里的人不一样，他四处收集金币，还想得到鬼玺！肚子里绝对没有好水！虽然他是我的手下败将，但也不是你能对付的。");
        heroTalk("你：等等，什么叫被吞入到这里？他到底想要做什么？");
        narration("声音消失了...");
        adjustScenario(5);
    }
}

//祸窟
void  Scenario::DenOfDisaster()
{
    if(getScenario()==3)
    {
        narration("你遇到一只落单的影魔，它见你独自一个，迅速朝你扑了过来。");
        ms_sleep(2000);
        eraseScreen();
        Enemy e{"影魔","恐怖魔物，潜行于黑暗之中，伺机发动致命一击，遇到阳光会被灼伤。",180,180,100,100,60,30,3,50,30};
        Skill s11("咆哮", "发出尖叫，对周围所有敌人造成音波攻击。", 100, 40);
	    Skill s12("潜袭", "悄无声息地接近目标，并发动突然袭击。", 60, 0);
        Skill S[2]={s11,s12};
        e.setSkill(S,1);
        Battle(&h,e);
        narration("影魔掉落了一把钥匙，你捡起随手别在了腰间。");
        adjustScenario(4);
    }


}
//石窟
void  Scenario::Grottoes()
{
    if(getScenario()==5)
    {
        narration("你看到一面刻着一张怪脸的石碑,其反面刻着一段文字：");
        const char* m="腹胎之饵，杀戮之始。澄粹者，寻三物方可重生。";
        for(int i=0;i<strlen(m);i+=3)
        {
            char print[]={m[i],m[i+1],m[i+2], '\0'};
            styledWrite(fgBlue, StyleSet{styleBright},print);
            ms_sleep(30);
        }
            std::cout<<std::endl;
            m="鬼王之玺 玄冥之石 无嗔之戒 ";
        for(int i=0;i<strlen(m);i+=3)
        {
           char print[]={m[i],m[i+1],m[i+2], '\0'};
           styledWrite(fgRed, StyleSet{styleBright},print);
           ms_sleep(30);
        }
        std::cout<<std::endl;
        narration("有声音从石碑正面传来，是那张怪脸。");
        npcTalk("谁在我后面？");
        heroTalk("你：这文字这说的是什么意思？");
        npcTalk("怪脸：我怎么知道？我又看不见！这是上一个来我这儿的人刻的字，当时可疼死我了！可惜我连他长什么样都不知道。不然我肯定要他好看！");
        heroTalk("你：总感觉这字有点熟悉...鬼王之玺、玄冥之石、无嗔之戒...");
        npcTalk("怪脸：哈！你也是来找那仨宝贝的？这儿但凡有点智商会说话的东西都会想得到它们！");
        heroTalk("你：你知道我是谁吗？");
        npcTalk("怪脸：当然不知道！你是我见过的唯一一个人了！对了！你把我头上那个石子拿了吧！那玩意弄得我痒痒的！");
        heroTalk("你：行吧");
        npcTalk("石碑上果然有一个凸起，是一块小石头。你用手将其拿起，刚想丢去...");
        npcTalk("怪脸：诶诶诶！干什么？它好歹也跟了我这么久，既然我不是普通的石碑，那他也肯定不是普通的石头！");
        narration("你苦笑不得，只好把石头别在了腰间。");
        heroTalk("你：你知道那三个宝贝是干什么的吗？");
        npcTalk("怪脸：我怎么知道？我又没有！");
        heroTalk("你：那你知道我是怎么被吞进来的吗？");
        npcTalk("怪脸：我怎么知道？我又不是被吞进来的！");
        heroTalk("你：那你知道在这鬼地方金币能有什么用吗？");
        npcTalk("怪脸：我怎么知道？我又...");
        narration("叫声吸引来了一只食人魔。怪脸瞬间安静了下来，你只得应战。");
        ms_sleep(2000);
        eraseScreen();
        Enemy e2("食人魔","体型庞大，丑陋贪婪，以掠夺和偷窃为生，偏好食用人类等种族。",360,360,100,100,100,50,4,200,40);
        Skill s21("巨力投掷", "抓起身边的一个大型物体向目标砸去。", 130, 40);
	    Skill s22("贪婪噬咬", "张开巨口吞噬敌人。", 100, 0);
        Skill S2[2] = { s21,s22 };
        e2.setSkill(S2, 2);
        Battle(&h,e2);
    
        npcTalk("食人魔临死之前看向了手里的一抹亮光，嘴里念叨着：我...我的...那是...母亲...留给我的...");
        narration("你走向前拿起了那个东西，端详了许久，仿佛明白了什么...");
        narration("是时候去找邓锋魄了。");
        adjustScenario(6);
    }
    else if(getScenario()<= 8)
    {
        narration("石碑还在那儿，那张怪脸除了制造噪音和废话外没什么价值，还是别去找他了吧。你还记得石碑上写着:");
        const char* m="腹胎之饵，杀戮之始。澄粹者，寻三物方可重生。";
        for(int i=0;i<strlen(m);i+=3)
        {
            char print[]={m[i],m[i+1],m[i+2], '\0'};
            styledWrite(fgBlue, StyleSet{styleBright},print);
            ms_sleep(30);
        }
            std::cout<<std::endl;
            m="鬼王之玺 玄冥之石 无嗔之戒 ";
        for(int i=0;i<strlen(m);i+=3)
        {
           char print[]={m[i],m[i+1],m[i+2], '\0'};
           styledWrite(fgRed, StyleSet{styleBright},print);
           ms_sleep(30);
        }
        std::cout<<std::endl;
    }
    else if(getScenario()== 9)
    {
        narration("你走到了石碑前，怪脸发现了你。");
        heroTalk("你：也许当初创造你的时候真的太虚弱了，把你弄的不伦不类的，真是抱歉了。那段文字也是为我而写的吧！");
        npcTalk("怪脸：啊？什么创造？什么抱歉？");
        heroTalk("你：没什么。");
        narration("你一脚踹在了石碑上，石碑在你这一脚之下直接爆裂。石碑之下，有着点点反光。你伸出了手...感受着异常的温暖...");
        ms_sleep(2000);
        narration("获得尘封的装备");
        adjustScenario(10);
    }
}
// 
void  Scenario::Dungeon()
{
    if(getScenario() == 6)
    {
        npcTalk("邓锋魄的声音从后面传来：劝你别去，地牢里的怪物可不像地道里的那样简单！");
        narration("你想了想，还是停下了脚步。");
    }
    else if(getScenario() == 7)
    {
        narration("又是一面带有怪脸的石碑，你走到了其背后，上面刻着：");
        const char* m="腹胎之饵，杀戮之始。澄粹者，寻三物方可重生。";
        for(int i=0;i<strlen(m);i+=3)
        {
            char print[]={m[i],m[i+1],m[i+2], '\0'};
            styledWrite(fgBlue, StyleSet{styleBright},print);
            ms_sleep(30);
        }
            std::cout<<std::endl;
            heroTalk("你自言自语道：怎么这块没有鬼王之玺、玄冥之石、无嗔之戒？");
            npcTalk("突然怪脸的声音从前方传来：你终于来了。");
            heroTalk("你：你知道我是谁？");
            npcTalk("怪脸：就如你当时所料，他没有杀你，你也失去了记忆。但你比我预想的要弱得多，不知道你是怎么移开石窟入口的石堆的。");
            heroTalk("你：取巧而已。");
            npcTalk("怪脸：如此你想要破开石碑的封印，难矣。收集一千枚魂印到这里来吧，我也只能如此了。");
            adjustScenario(8);
    }
    else if(getScenario() == 8)
    {
        if(h.getGold()<1000)
        {
            narration("石碑没什么反应，去收集一千金币再来吧。");
        }
        else
        {
            narration("你来到沉寂的石碑面前，考虑了一会，把一千金币放到石碑跟前。");
            npcTalk("怪脸睁开了双眼，道：魂印是从生物灵魂之内提炼的结晶，其会为宿主带来的精神层次的影响。而此处实为尘封的提炼之地，地灵将不同的生物强行抓到此处，不断抽离灵魂力量形成魂印，待生物的神智模糊、自相残杀之际，死去的生物便会掉落魂印，被地灵吸取，地灵便会愈加强大。越强大的生物受的影响会越少，但依然避免不了最终的结局。");
            ms_sleep(2000);
            npcTalk("怪脸：此地灵不知已经这般吸取了多少力量，但它从未料到，它会吞入两个不受其影响的人。一者为邓锋魄，另外一个便是你。你与他共同创造了鬼王之玺与玄冥之石。鬼王之玺可用来操控神智模糊的生物，玄冥之石则是破解各处封印的“钥匙”。至于无嗔之戒，那是你们不受灵魂提炼的原因。你们二人不断收集魂印，这样地灵就收集不到充足的力量，此消彼长之下，地灵就会被不断削弱，等解决了地灵，穴口的通道就能打开。可邓锋魄发现了将魂印的力量化为己用的方法，想要独自称雄，于是以玄冥之石为诱惑联合冥王偷袭了你。");
            ms_sleep(2000);
            npcTalk("怪脸：可他低估了冥王，也低估了你。你战败而逃，冥王拿到玄冥之石并不罢休，邓锋魄将冥王击退，却又遇到了冥王的帮手——鬼眼阿比斯和黑龙斯托姆。你感受到鬼王之玺和无嗔之戒都已不在邓锋魄之手，料定他肯定不会想要失去你这样的助力，于是你在此处用手中的魂印创造了我，又在石窟建了另一座石碑，用来保存你的力量，用最后的气力把石窟的路封上，便在岩穴脱力昏了过去。你相信邓锋魄会一直与三巨头周旋，它们四个不会愿意为没什么价值的石窟耗费精力，只有你会在足够强大之后破开石窟，连续见到两面石碑后，你的声音就会唤醒我，我会给你最后的指引。");
            ms_sleep(2000);
            heroTalk("你摸了一下腰间的石头，想着：幸亏没扔。");
            heroTalk("你：石窟那块石碑可比你蠢多了，看来它没有像你一样继承我的意志。");
            npcTalk("怪脸：我本是由魂印创造，这一千枚魂印或许也能摧毁我，你便达成你的目的了。");
            narration("一枚枚“金币”飘起，贴在了石碑上，又渐渐消失，接下来的魂印继续贴上...");
            narration("石碑渐渐消融，一点点光芒升起，进入了你体内。你感受到了前所未有的力量。");
            ms_sleep(800);
            h.addHp(10000);
            h.addMp(2000);
            h.adjustAttack(2000);
            h.adjustDefend(1000);
            narration("接下来该去石窟了...");
            adjustScenario(9);
        }
    }
}
//鬼门 0
void Scenario::ghostdom()
{
    narration("面对眼前的鬼影，你没有丝毫害怕。");
    fightGhostdom(&h);
    narration("你获得了鬼玺，地下所有迷失心智的怪物都听你调遣，不会再攻击你。");
    narration("通过怪物的反馈你知道了暗室的位置。");
    narration("你打算回到地道，前往暗室。");
    adjustScenario(12);
}
//地宫 2
void Scenario::underPalace()
{
    narration("黑龙斯托姆：人类，不知你进来做什么，我无欲无求，只想在这地宫内逍遥快活。你若想求无嗔戒，那你只能杀了我。");
    narration("黑龙身躯巨大无比，你知道现在不是他的对手。");
    ms_sleep(500);
    narration("你打算离开。");

}
//暗室 5
void Scenario::darkroom()
{
    narration("你来到一处墙角，手握剑柄释出全力，墙壁破开，露出了通道。");
    narration("这是地灵灵体的位置。");
    heroTalk("你对地灵说到：放我出去吧，我无意与你决斗。");
    npcTalk("地灵：杀了你，我就能得到无穷的力量...");
    narration("你对着地灵抬起了剑...");
    fightDarkRom(&h);
    narration("战斗威势浩大，整个地下都遍布着余威。");
    ms_sleep(500);
    narration("你走出了暗室，是时候前往穴口了...");
    adjustScenario(13);
}
//冥界 10
void Scenario::SweatPore()
{
    npcTalk("冥王：居然是你？邓锋魄呢？");
    heroTalk("你没有跟他废话，直接冲了上去。");
    ms_sleep(700);
    eraseScreen();
    fightSweatPore(&h);
    npcTalk("冥王：没想到，你还有这么强的力量，看来邓锋魄也活不长了吗，或者说早就死了？");
    heroTalk("你:鬼王之玺和无嗔之戒呢？");
    npcTalk("冥王：当初鬼玺被阿比斯先一步夺去，无嗔戒也被斯托姆抢了，但是，哼！我没拿到的东西，怎么会拱手让给别人！乘着邓锋魄逃走，我封印了阿比斯，和斯托姆大战了一场。之后我再无力动用冥界之石，只能用腐冥锁锁住了地宫，腐冥也不知去向。这段时间我一直再此修养，本想着等恢复全力就出去把他们全解决了，没想到你恢复的这么快！");
    heroTalk("你：谢谢你说这些，我会给你个痛快的。");
    narration("你一剑贯穿了冥王的心口。");
    ms_sleep(500);
    narration("你获得了冥界之石。");
    adjustScenario(11);
}