

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

Element Trophy() {
  return vbox({
      text(R"(                 ___________                        )"),
      text(R"(            .---'::'        `---.                   )"),
      text(R"(           (::::::'              )                  )"),
      text(R"(           |`-----._______.-----'|                  )"),
      text(R"(           |              :::::::|                  )"),
      text(R"(          .|               ::::::!-.                )"),
      text(R"(          \|               :::::/|/                 )"),
      text(R"(           |               ::::::|                  )"),
      text(R"(           |                :::::|                  )"),
      text(R"(           |                 ::::|                  )"),
      text(R"(           |               ::::::|                  )"),
      text(R"(           |              .::::::|                  )"),
      text(R"(           \              :::::::/                  )"),
      text(R"(            \            :::::::/                   )"),
      text(R"(             `.        .:::::::'                    )"),
      text(R"(               `-._  .::::::-'                      )"),
      text(R"(___________________|  """|"_________________________)"),
      text(R"(                   |  :::|                          )"),
      text(R"(                   /   ::\                          )"),
      text(R"(                  /     ::\                         )"),
      text(R"(             __.-'      :::`-.__                    )"),
      text(R"(            (_           ::::::_)                   )"),
      text(R"(              `"""---------"""'                     )"),
  });
};

Decorator Render(int coins) {
  return [=](Element continue_button) {
    return vbox({
        Trophy(),
        text(""),
        text("Congratulations! You won!"),
        text(""),
        text("You have collected " + std::to_string(coins) + " coins."),
        continue_button,
    });
  };
}

Component WinScreen(int coins, std::function<void()> continuation) {
  auto component = Button("Continue", continuation, ButtonOption::Animated());
  return component | Render(coins);
}
