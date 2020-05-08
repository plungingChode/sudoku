#include "holdbtn.hpp"
#include "scene.hpp"

using namespace Controls;
using namespace genv;

HoldButton::HoldButton(Scene *s, int x_, int y_, int w_, const std::string &text_, std::function<void()> a, const genv::font *f)
    : Button(s, x_, y_, w_, text_, a, f)
{
}

void HoldButton::on_mouse_ev(const genv::event &ev, bool btn_held)
{
    if (ev.button == btn_left && hovered)
    {
        action();
    }
    if (ev.button == -btn_left && held)
    {
        action();
    }
    Label::on_mouse_ev(ev, btn_held);
}