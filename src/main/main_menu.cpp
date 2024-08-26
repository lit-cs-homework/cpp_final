
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

Component PlayTab(std::function<void(int)> play) {
  struct Impl : public ComponentBase {
   public:
    Impl(std::function<void(int)> play) {
      auto on_click = [&, play] { play(index_); };
      menu_ = Menu(&g_levels_name, &index_);
      play_button_ = Button("Play", on_click,
                            ButtonOption::Animated(Color::Red, Color::White));

      auto layout = Container::Horizontal({
          menu_,
          play_button_,
      });

      auto renderer = Renderer(layout, [&] {
        return hbox({
            menu_->Render() | borderEmpty,
            vbox({
                text("Title: " + g_levels_name.at(size_t(index_))),
                text("Prize: " + std::to_string(g_prize.at(size_t(index_)))),
            }) | size(WIDTH, GREATER_THAN, 25) |
                border,
            play_button_->Render() | size(WIDTH, GREATER_THAN, 7) | borderEmpty,
        });
      });

      Add(renderer);
    }

   private:
    Component menu_;
    Component play_button_;
    int index_ = 0;
  };
  return Make<Impl>(play);
}

int LifeCost(const GameConfig& config){
    return config.difficulty;
}
Component ShopTab(GameConfig& config) {

  auto button = Button("[TODO] Buy 5 life values", [&] {
    if (config.coins >= LifeCost(config)) {
      config.coins -= LifeCost(config);
      config.life += 5;
    }
  });

  return button | [&](Element button_element) {
    auto description = vbox({
        //text("balls: " + std::to_string(config.balls)),
        text("coins: " + std::to_string(config.coins)),
        text("cost 5 life value: " + std::to_string(LifeCost(config)) + " coins"),
    });

    description |= border;

    if (config.coins < LifeCost(config)) {
      return vbox({
          description,
          text("You don't have enough coins"),
      });
    }

    return vbox({
        description,
        button_element,
    });
  };

}


Component MainMenu(GameConfig& config,
                   std::function<void(int)> play,
                   std::function<void()> quit) {
  static const std::vector<std::string> tab_entries_ = {
      "Play",
      "Shop",
      "Quit",
  };

  class Impl : public ComponentBase {
   private:
    int tab_index_ = 0;
    GameConfig& config_;

   public:
    Impl(GameConfig& config,
         std::function<void(int)> play,
         std::function<void()> quit)
        : config_(config) {
      auto menu = Menu(&tab_entries_, &tab_index_, CustomMenuOption());
      auto tab_content = Container::Tab(
          {
              PlayTab(play),
              ShopTab(config_),
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

  return Make<Impl>(config, std::move(play), std::move(quit));
}
