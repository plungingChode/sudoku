#include "cell.hpp"
#include <map>

using namespace Controls;
using namespace std;
using namespace genv;

vector<vector<int>> Cell::board = vector<vector<int>>(9, vector<int>(9));
bool Cell::show_invalid = true;

Cell::Cell(vec2 pos, int x, int y)
    : Spinner(pos, 0, 0, 9, CELL_SIDE, CELL_SIDE, vec2(7, 10)), 
      x(x), y(y), row_valid(true), col_valid(true), segment_valid(true), is_preset(false)
{
    border = Controls::BLACK;
}

void Cell::set_value(int val)
{
    Spinner::set_value(val);
    Cell::board[x][y] = value;
    check_conflicts();
}

void Cell::check_conflicts()
{
    map<int, int> occ;

    set_row_validity(true);
    for (int rx = 0; rx < 9; rx++)
    {
        int val = board[rx][y];
        if (val > 0)
        {
            occ[val]++;
        }
        if (occ[val] > 1)
        {
            set_row_validity(false);
            break;
        }
    }

    occ.clear();
    set_col_validity(true);
    for (int ry = 0; ry < 9; ry++)
    {
        int val = board[x][ry];
        if (val > 0)
        {
            occ[val]++;
        }
        if (occ[val] > 1)
        {
            set_col_validity(false);
            break;
        }
    }

    occ.clear();
    set_segment_validity(true);
    int sx = (x/3)*3;
    int sy = (y/3)*3;
    for (int rx = sx; rx < sx+3; rx++)
    {
        for (int ry = sy; ry < sy+3; ry++)
        {
            int val = board[rx][ry];
            if (val > 0)
            {
                occ[val]++;
            }
            if (occ[val] > 1)
            {
                set_segment_validity(false);
                break;
            }
        }
    }
}

void Cell::update()
{
    if (show_invalid && 
       (!row_valid || !col_valid || !segment_valid))
    {
        normal_bg = CELL_INVALID;
        focus_bg = CELL_INVALID;
        hover_bg = CELL_INVALID;
        hold_bg = CELL_INVALID;
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

void Cell::set_row_validity(bool val)
{
    for (Cell *c : row)
    {
        c->row_valid = val;
        c->schedule_update();
    }
}

void Cell::set_col_validity(bool val)
{
    for (Cell *c : col)
    {
        c->col_valid = val;
        c->schedule_update();
    }
}

void Cell::set_segment_validity(bool val)
{
    for (Cell *c : segment)
    {
        c->segment_valid = val;
        c->schedule_update();
    }
}

void Cell::reload_board()
{
    Spinner::set_value(Cell::board[x][y]);
    is_preset = (value != 0);
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