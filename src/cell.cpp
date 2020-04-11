#include "cell.hpp"
#include "sudoku.hpp"
#include <map>

using namespace Controls;
using namespace genv;

Cell::Cell(vec2 pos, int x, int y, Sudoku *owner)
    : Spinner(pos, 0, 0, 9, CELL_SIDE, CELL_SIDE, vec2(7, 10)), 
      x(x), y(y), is_preset(false), owner(owner)
{
    border = BLACK;
}

void Cell::initialize(int value)
{
    Spinner::set_value(value);
    row_invalid = col_invalid = segment_invalid = false;
    is_preset = (value != 0);
}

void Cell::update()
{
    if (owner->show_invalid && (row_invalid || col_invalid || segment_invalid))
    {
        normal_bg = CELL_INVALID;
        focus_bg = CELL_INVALID_FOCUS;
        hover_bg = CELL_INVALID;
        hold_bg = CELL_INVALID_FOCUS;
    } 
    else
    {
        normal_bg = CELL_BG;
        hover_bg = CELL_BG;
        focus_bg = CELL_FOCUS;
        hold_bg = CELL_FOCUS;
    }
    if (value == 0)
    {
        text_fill_normal = normal_bg;
        text_fill_focused = focus_bg;
    } 
    else
    {
        text_fill_normal = CELL_TEXT;
        text_fill_focused = CELL_TEXT;
    }
    if (is_preset)
    {
        Label::update();
    }
    else
    {
        Spinner::update();
    }
}

void Cell::set_value(int val)
{
    Spinner::set_value(val);
    owner->on_cell_change(x, y, value);
}

void Cell::on_mouse_ev(const event &ev, bool btn_held)
{
    if (is_preset)
    {
        Label::on_mouse_ev(ev, btn_held);
    }
    else
    {
        Spinner::on_mouse_ev(ev, btn_held);
    }
}

void Cell::on_key_ev(const event &ev, int key_held)
{
    if (is_preset)
    {
        Label::on_key_ev(ev, key_held);
    }
    else
    {
        Spinner::on_key_ev(ev, key_held);
        if (ev.keycode == key_delete || key_held == key_delete)
        {
            set_value(0);
        }
    }
}
