#ifndef HOLDBTN_HPP_INCLUDED
#define HOLDBTN_HPP_INCLUDED

#include "button.hpp"

class HoldButton : public Controls::Button
{
protected:
    int press_action;

public:
    HoldButton(Controls::Scene *owner, int x, int y, int on_press, int on_release, std::string text, int width, const genv::font *font = nullptr);
    HoldButton(Controls::Scene *owner, int x, int y, int toggle, std::string text, int width, const genv::font *font = nullptr);

    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;   
};

#endif