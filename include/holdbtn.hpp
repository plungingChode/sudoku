#ifndef HOLDBTN_HPP_INCLUDED
#define HOLDBTN_HPP_INCLUDED

#include "button.hpp"

class HoldButton : public Controls::Button
{
protected:
    Controls::action_t press_action;

public:
    HoldButton(Controls::vec2 start, Controls::action_t on_press, Controls::action_t on_release, std::string text, int width, std::string font = "", int font_size = 16);
    HoldButton(Controls::vec2 start, Controls::action_t toggle, std::string text, int width, std::string font = "", int font_size = 16);

    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;   
};

#endif