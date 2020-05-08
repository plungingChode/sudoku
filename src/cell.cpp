#include "cell.hpp"
#include "sudoku.hpp"

using namespace Controls;
using namespace genv;

bool Cell::SHOW_INVALID = false;

Cell::Cell(Scene *s, int x_, int y_, int col_, int row_, cell_callback f)
    : Spinner(s, x_, y_, CELL_SIDE, CELL_SIDE, 0, 0, 9), 
      col(col_), row(row_), is_preset(false), on_change(f)
{
    border = BLACK;
}

void Cell::initialize(int init_value)
{
    Spinner::set_value(init_value);
    row_invalid = col_invalid = segment_invalid = false;
    is_preset = (value != 0);
}

void Cell::update()
{
    if (Cell::SHOW_INVALID && 
       (row_invalid || col_invalid || segment_invalid))
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
    on_change(col, row, value);
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
        if (ev.keycode == genv::key_delete || key_held == genv::key_delete)
        {
            set_value(0);
        }
    }
}
