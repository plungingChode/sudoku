#include "holdbtn.hpp"
#include "scene.hpp"

using namespace Controls;
using namespace std;
using namespace genv;

HoldButton::HoldButton(Scene *s, int x, int y, int press_action, int release_action, string text, int width, const genv::font *f)
    : Button(s, x, y, release_action, text, width, f), press_action(press_action)
{
}

HoldButton::HoldButton(Scene *s, int x, int y, int toggle_action, string text, int width, const genv::font *f)
    : Button(s, x, y, toggle_action, text, width, f), press_action(toggle_action)
{
}

void HoldButton::on_mouse_ev(const event &ev, bool btn_held)
{
    if (ev.button == btn_left && hovered)
    {
        owner->action(press_action);
    }
    if (ev.button == -btn_left && held)
    {
        owner->action(action);
    }
    Label::on_mouse_ev(ev, btn_held);
}