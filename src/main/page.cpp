
#include "page.h"
#include "dialog.h"

Page::Page(GameConfig config,
                 std::function<void()> win,
                 std::function<void()> lose): config_(config), win_(win), lose_(lose) {
}

bool Page::OnEvent(ftxui::Event event){
    // TODO
    return true;
}
void Page::Step(){

    // TODO
}

DialogPage Page::Render(ftxui::ScreenInteractive& screen,
                          ftxui::Component back_btn,
                          ftxui::Component quit_btn) {
  using namespace ftxui;
  auto f1 = []{};
  auto f2 = f1;
  return
      DialogPage().add("Tom", "hi", {
          {"1", f1},
          {"2", f2}
      }).add("me", "hi", {
          {"2", f2},
          {"1", f1},
      }).add("me", "bye", {
                {"One", f1},
                {"Two", f2}
                }
      );
  ;
  /*
  auto c = Canvas(g_board_width, g_board_height);

  for (const Ball& ball : balls_) {
    ball->Draw(c);
  }
  for (const Brick& brick : bricks_) {
    brick->Draw(c);
  }

  DrawShootingLine(c);

  std::string balls_remaining = std::to_string(remaining_balls_to_shoot_) +
                                "/" + std::to_string(config_.balls);

  auto frame = hbox({
      canvas(std::move(c)) | reflect(box_),
      separator(),
      vbox({
          window(text("bricks:"), text(std::to_string(bricks_.size()))),
          window(text("balls:"), text(balls_remaining)),
          back_btn,
          quit_btn,
          filler(),
      }),
  });

  frame |= border;
  frame = vbox(frame, filler());
  frame = hbox(frame, filler());
  return frame;
  */
 // TODO
  
}