

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/screen.hpp"
#include <functional>
#include "dialog.h"
#include "cfg.h"

class Page{
public:
  explicit Page(GameConfig config,
                 std::function<void()> win,
                 std::function<void()> lose);

  bool OnEvent(ftxui::Event event);
  void Step();
  DialogPage Render(ftxui::ScreenInteractive&, ftxui::Component back_btn, ftxui::Component quit_btn);


private:
  const GameConfig config_;
  std::function<void()> win_;
  std::function<void()> lose_;
};
