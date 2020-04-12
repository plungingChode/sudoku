#include "holdbtn.hpp"

using namespace Controls;
using namespace std;
using namespace genv;

HoldButton::HoldButton(vec2 start, action_t press_action, action_t release_action, string text, int width, string font, int font_size)
    : Button(start, release_action, text, width, font, font_size), press_action(press_action)
{
}

HoldButton::HoldButton(vec2 start, action_t toggle_action, string text, int width, string font, int font_size)
    : Button(start, toggle_action, text, width, font, font_size), press_action(toggle_action)
{
}

void HoldButton::on_mouse_ev(const event &ev, bool btn_held)
{
    if (ev.button == btn_left && hovered)
    {
        press_action();
    }
    if (ev.button == -btn_left && held)
    {
        Button::action();
    }
    Label::on_mouse_ev(ev, btn_held);
}