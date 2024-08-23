
#include "dialog.h"
#include <fstream>

int main() {
    std::ofstream f("t.txt");
    auto onOptionOne = [&]() {
        f << "Option one selected." << std::endl;
        f.flush();
    };

    auto onOptionTwo = [&]() {
        f << "Option two selected." << std::endl;
        f.flush();
    };
    // ::TerminalOutput() will just be inline
    // ::FullScreen() is like what full-screen editor does like vim
    auto screen = ScreenInteractive::
        Fullscreen();
        //TerminalOutput();
        // the same but shorter:

    if (false){
        // one example using long notation:
        DialogPage page;
        page.add("Tom", "Hello, here is Tom.",{
            {"Option One", onOptionOne},
            {"Option Two", onOptionTwo},
        });
        page.add("Me", "Hello, here is Tom.",{
            {"2", onOptionTwo},
            {"1", onOptionOne},
        });
        //page.addNext(myPage);

        page.mainloop(screen);
    } else if(false) {
        DialogPage().add("Tom", "hi", {
            {"1", onOptionOne},
            {"2", onOptionTwo}
        }).add("me", "hi", {
                {"2", onOptionTwo},
                {"1", onOptionOne},
                }
        ).mainloop(screen);
    } else {
        auto p = DialogPage(
         ).add("鹅峨峨", "hi, 奥斯丁不 爱鸟哦爬上哦奥法奥法熬", {
            {"1", onOptionOne},
            {"2", onOptionTwo}
        }, OneDialogPage::NextOption("here", false, true)).add("me", "hi", {
                {"2", onOptionTwo},
                {"1", onOptionOne},
                }, OneDialogPage::NextOption(true)
        ).add("me", "bye", {
                {"One", onOptionOne},
                {"Two", onOptionTwo},
                }
        );
        screen.Loop(p.asComponent());
    }

}
