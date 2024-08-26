#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
using namespace ftxui;

Element IntroDecorator(Element buttons) {
  auto description = vbox({
    filler(),
        paragraphAlignCenter("Welcome to this game!"),
        paragraphAlignCenter("This game was made by @litlighilit"), filler(),
        paragraphAlignCenter(""),
        paragraphAlignCenter("Please press any key to start") | blink, filler(),
        paragraphAlignCenter(
            "More info on https://github.com/litlighilit/cpp_final"),
        filler(),
  });

  auto document = vbox({
      //Logo() | flex_shrink,
      separator(),
      description | flex_grow,
      buttons | center,
  });

  return document | border;
}


ftxui::Component Intro(bool* enable_audio, std::function<void()> quit) {
  // Depending on the configuration and platform, we might or might not be able
  // to play audio. If we can, we let the player decide, except when running
  // inside the browser.
#if defined(__EMSCRIPTEN__)
  *enable_audio = true;
  auto buttons = Button("Start", quit, ButtonOption::Animated(Color::Green));
#elif ENABLE_AUDIO
  auto start_with_audio = [=] {
    *enable_audio = true;
    quit();
  };
  auto start_without_audio = [=] {
    *enable_audio = false;
    quit();
  };
  auto btn_option_audio = ButtonOption::Animated(Color::Blue);
  auto btn_option_asan = ButtonOption::Animated(Color::Red);

  auto buttons = Container::Horizontal({
      Button("Start with Audio", start_with_audio, btn_option_audio),
      Button("Start without Audio", start_without_audio, btn_option_asan),
  });
#else
  *enable_audio = false;
  auto buttons = Button("Start", quit, ButtonOption::Animated(Color::Yellow));
#endif  // ENABLE_AUDIO

  return buttons | IntroDecorator;
}
