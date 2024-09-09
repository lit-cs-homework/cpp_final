
#pragma once

#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/screen_interactive.hpp" // for ScreenInterative
#include "ftxui/dom/elements.hpp"
#include <functional>
#include "cfg.h"
#include "page.h"
#include "dialog.h"


enum BoolStatus {
  bsUndue = -1,
  bsTrue,
  bsFalse
};


void StartGame();

// Exposed for testing.
ftxui::Component Intro(bool* enable_audio, std::function<void()> quit);  // in intro.cpp
ftxui::Component WinScreen(int coins, std::function<void()> continuation);  // in win.cpp
ftxui::Component LoseScreen(std::function<void()> continuation); // in lose.cpp
ftxui::Component GameScreen(Page& page,
                            ftxui::ScreenInteractive& screen,
                            std::function<void()> lose,
                            std::function<void()> quit);
ftxui::Component MainMenu(GameConfig& config,
                          std::function<void(int)> play,
                          std::function<void()> quitThisPage,
                          std::function<void()> quit,
                          std::function<void()>  on_start_new_game);  // in main_menu.cpp
void ExecuteMainMenu(GameConfig& config,
                     std::function<void()> play,
                     std::function<void()> quit,
                     std::function<void()> on_start_new_game);

