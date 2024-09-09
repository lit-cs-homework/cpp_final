

#include "ftxui/component/event.hpp"
#include "ftxui/component/loop.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include <iostream>
#include <thread>

#include "cfg.h"
#include "game.h"
#include "map.h"
#include "combat.h"


using namespace ftxui;


const std::vector<int> g_prize = {
    2000,   //
    4000,   //
    8000,   //
    16000,  //
    32000,  //
    64000,  //
};

void ExecuteMap(GameConfig config,
                  std::function<void()> win,
                  std::function<void()> lose,
                  std::function<void()> quit) {



    //config.map.load();  loaded before this function

    while (true) {
        config.map.showMap();
        config.map.showMenu();
        try{
          if(!config.map.action()) break;
        }catch(FailCombat e) {
          lose();
        }
    }

}

void ExecuteWinScreen(int coins) {
  auto screen = ScreenInteractive::Fullscreen();
  auto component = WinScreen(coins, screen.ExitLoopClosure());
  screen.Loop(component);
}

void ExecuteLoseScreen() {
  auto screen = ScreenInteractive::Fullscreen();
  auto component = LoseScreen(screen.ExitLoopClosure());
  screen.Loop(component);
}

void ExecuteMainMenu(GameConfig& config,
                     std::function<void(int)> play,
                     std::function<void()> quit,
                     std::function<void()> on_restart_game) {
  auto screen = ScreenInteractive::Fullscreen();
  auto exit = screen.ExitLoopClosure();

  auto quit_and_exit = [quit, exit]() {
    quit();
    exit();
  };
  auto menu = MainMenu(config, exit, quit_and_exit, on_restart_game);
  screen.Loop(menu);
}

void ExecuteIntro(bool* enable_audio) {
  auto screen = ScreenInteractive::Fullscreen();
  auto component = Intro(enable_audio, screen.ExitLoopClosure());
  screen.Loop(component);
}


// The component responsible for renderering the game board.

// ftxui::Component GameScreen(Page& page,
//                             ScreenInteractive& screen,
//                             std::function<void()> lose,
//                             std::function<void()> quit) {
//   auto button_back = Button("Back", lose, ButtonOption::Animated(Color::Blue));
//   auto button_quit = Button("Quit", quit, ButtonOption::Animated(Color::Red));

//   auto layout = Container::Vertical({
//       button_back,
//       button_quit,
//   });

//   //auto component = page.Render(screen, button_back, button_quit);

//   auto layout = Container::Vertical({
//       button_back,
//       button_quit,
//   });

//   /*
//   auto component = Renderer(layout, [&, button_back, button_quit] {
//     return board.Draw(button_back->Render(), button_quit->Render());
//   });
//   component |= CatchEvent([&](Event event) {  // NOLINT
//     if (event == Event::Custom) {
//       page.Step();
//       return true;
//     }

//     return page.OnEvent(event);
//   });*/
//   auto component = layout->;

//   return component;
// }


// The main logic, moving the players in between the various screens.

void StartGame() {

  bool enable_audio = false;
  ExecuteIntro(&enable_audio);


  Map map;
  GameConfig config{map};

  int level_to_play = -1;

  bool quit = false;
  auto on_quit = [&] { quit = true; };

  int iterations = 0;

  bool restart_game = false; // If start a new game.  out-var, init below
  // we must init in loop body in case ExecuteMainMenu abort because user press ctrl-C

  // NOTE: cannot make on_restart_game directly call config.map.enterFirstScenario(),
  // whcich makes it called in too inner stacks
  auto on_restart_game = [&] { restart_game = true; };

  auto gameStatus = gsUndue;
  auto on_win =  [&] { gameStatus = gsWin;  };
  auto on_lose = [&] { gameStatus = gsLose; };

  while (!quit) {
    iterations++;
    auto select_level = [&](int level) {
      level_to_play = level;
    };

    // do not skip the first menu to choose backup
    ExecuteMainMenu(config, select_level, on_quit, on_restart_game);

    if (quit) {
      break;
    }
    if (restart_game) {
        config.map.enterFirstScenario();
        restart_game = false;  // prevent loop
    }

    config.difficulty = level_to_play;
    ExecuteMap(config, on_win, on_lose, on_quit);

    if (quit) {
      break;
    }

    if (gameStatus == gsWin) {
      ExecuteWinScreen(g_prize.at(size_t(level_to_play)));
      config.coins += g_prize.at(size_t(level_to_play));
    } else if (gameStatus == gsLose) {
      ExecuteLoseScreen();
    }
  }
}

