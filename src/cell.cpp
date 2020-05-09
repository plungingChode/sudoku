#include "cell.hpp"
#include "sudoku.hpp"

using namespace Controls;
using namespace genv;

bool Cell::SHOW_INVALID = false;

Cell::Cell(Scene *s, int x_, int y_, int col_, int row_, cell_callback change_f, move_callback move_f)
    : Spinner(s, x_, y_, CELL_SIDE, CELL_SIDE, 0, 0, 9), 
      col(col_), row(row_), is_preset(false), on_change(change_f), move_focus(move_f)
{
    border = BLACK;
}

void Cell::initialize(int init_value)
{
    Spinner::set_value(init_value);
    invalid_flags = 0;
    is_preset = (value != 0);
}

void Cell::update()
{
    if (Cell::SHOW_INVALID && invalid_flags)
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

void Cell::set_flag(cell_flag flag, bool val)
{
    invalid_flags = (invalid_flags & ~(1<<flag)) | (val<<flag);
    schedule_update();
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
    switch(ev.keycode)
    {
    case 'w': move_focus(col, row-1); break;
    case 'a': move_focus(col-1, row); break;
    case 's': move_focus(col, row+1); break;
    case 'd': move_focus(col+1, row); break;
    default: break;
    }
    
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
