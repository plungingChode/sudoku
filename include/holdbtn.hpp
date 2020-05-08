#ifndef HOLDBTN_HPP_INCLUDED
#define HOLDBTN_HPP_INCLUDED

#include "button.hpp"

class HoldButton : public Controls::Button
{
public:
    HoldButton(Controls::Scene *owner, int x, int y, int width, const std::string &text, std::function<void()> toggle_action, const genv::font *font = nullptr);

    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override;   
};

#endif