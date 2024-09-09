
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"

#include <functional>
#include "cfg.h"
using namespace ftxui;

Component QuitTab(std::function<void()> quit) {
  return Button("Quit", quit, ButtonOption::Animated(Color::Cyan1));
}

Element MainMenuDecorator(Element element) {
  return vbox({
      text("Cpp Game") | bold | center,
      element,
  });
}

// A tab menu, with extra wide items.
MenuOption CustomMenuOption() {
  auto option = MenuOption::HorizontalAnimated();

  option.entries_option.transform = [](const EntryState& state) {
    Element e = text(state.label) | borderEmpty;
    if (state.focused) {
      //e |= inverted;
    }
    if (state.active) {
      e |= bold;
    }
    if (!state.focused && !state.active) {
      e |= dim;
    }
    return e;
  };

  return option;
};

const std::vector<std::string> g_levels_name = {
  "1",
  "2",
};
const std::vector<int> g_prize = {
    1,   //
    2,   //
};

//Component PlayTab(std::function<void(int)> play) {}

int LifeCost(const GameConfig& config){
    return config.difficulty;
}

Component RestoreTab(GameConfig& config, ftxui::Closure quitThisPage) {
    struct Impl : public ComponentBase {
      Impl(GameConfig& config, ftxui::Closure quitThisPage): config(config), quitThisPage(quitThisPage) {
          new_game = [this] {
              this->config.map.delBackup();
              this->config.map.load();
              this->quitThisPage();
          };
          obtn = Button("从最近存档开始", [this] {
            if(!this->config.map.load()){
                // no old data
                this->new_game();
            }
          });
            nbtn = Button("开始新游戏", new_game);

          auto buttons = Container::Vertical({
                  obtn,
                  nbtn
          });

          auto renderer = Renderer(buttons, [this] {
                if (this->config.map.hasBackup()) {
                    return vbox({
                      this->obtn->Render(),
                      this->nbtn->Render(),
                    });
                }
                return vbox({
                    text("尚无存档"),
                    this->nbtn->Render()
                });
          });
          Add(renderer);
      }

    private:
      Component obtn;
      Component nbtn;
      GameConfig& config;
      std::function<void()> new_game;
      ftxui::Closure quitThisPage;
    };
    return Make<Impl>(config, std::move(quitThisPage));
}


Component MainMenu(GameConfig& config,
                   std::function<void()>  quitThisPage,
                   std::function<void()> quit) {
  static const std::vector<std::string> tab_entries_ = {
      "Play",
      "Quit",
  };

  class Impl : public ComponentBase {
   private:
    int tab_index_ = 0;
    GameConfig& config_;

   public:
    Impl(GameConfig& config,
         ftxui::Closure quitThisPage,
         ftxui::Closure quit)
        : config_(config) {
      auto menu = Menu(&tab_entries_, &tab_index_, CustomMenuOption());
      auto tab_content = Container::Tab(
          {
              //PlayTab(play),
              RestoreTab(config_, quitThisPage),
              QuitTab(quit),
          },
          &tab_index_);
      auto component = Container::Vertical({
          menu,
          tab_content,
      });
      component |= MainMenuDecorator;
      Add(component);
    }
  };

  return Make<Impl>(config, std::move(quitThisPage), std::move(quit));
}
