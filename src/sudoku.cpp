#include "sudoku.hpp"
#include <fstream>
#include <map>

using namespace Controls;
using namespace std;

Sudoku::Sudoku(string fname) : Scene(640, 480)
{
    board = vector<vector<int>>(9, vector<int>(9));
    cells = vector<vector<Cell*>>(9, vector<Cell*>(9));

    for (int x = 0; x < 9; x++)
    {
        int x_gap = (x%3 == 0) ? 3 : 0;
        for (int y = 0; y < 9; y++)
        {
            int y_gap = (y%3 == 0) ? 3 : 0;
            cells[x][y] = new Cell(vec2(20+x*CELL_SIDE+x_gap, 20+y*CELL_SIDE+y_gap), x, y, this);          

            add_control(cells[x][y]);
        }
    }

    load_board(fname);
}

void Sudoku::load_board(string fname)
{
    board_name = fname;

    ifstream f(fname);
    if (f.good())
    {
        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                f >> board[x][y];
                cells[x][y]->initialize(board[x][y]);
            }  
        }
    }
}

void Sudoku::on_cell_change(int x, int y, int value)
{
    board[x][y] = value;
    check_conflicts(x, y);
}

void Sudoku::check_conflicts(int x, int y)
{
    map<int, int> occ;

    bool row_invalid = false;
    for (int col = 0; col < 9; col++)
    {
        int val = board[col][y];
        if (val > 0)
        {
            occ[val]++;
            if (occ[val] > 1)
            {
                row_invalid = true;
                break;
            }
        }
    }
    for (int col = 0; col < 9; col++)
    {
        cells[col][y]->row_invalid = row_invalid;
        cells[col][y]->schedule_update();
    }

    occ.clear();

    bool col_invalid = false;
    for (int row = 0; row < 9; row++)
    {
        int val = board[x][row];
        if (val > 0)
        {
            occ[val]++;
            if (occ[val] > 1)
            {
                col_invalid = true;
                break;
            }
        }
    }
    for (int row = 0; row < 9; row++)
    {
        cells[x][row]->col_invalid = col_invalid;
        cells[x][row]->schedule_update();
    }

    occ.clear();

    bool segment_invalid = false;
    int sx = (x/3)*3;
    int sy = (y/3)*3;
    for (int row = sy; row < sy+3; row++)
    {
        for (int col = sx; col < sx+3; col++)
        {
            int val = board[col][row];
            if (val > 0)
            {
                occ[val]++;
                if (occ[val] > 1)
                {
                    segment_invalid = true;
                    break;
                }
            }
        }
    }
    for (int row = sy; row < sy+3; row++)
    {
        for (int col = sx; col < sx+3; col++)
        {
            cells[col][row]->segment_invalid = segment_invalid;
            cells[col][row]->schedule_update();
        }
    }
}

bool Sudoku::on_key_event(const genv::event &ev)
{
    vec2 pos = ((Cell*)focused)->pos();

    int kc = key_held ? key_held : ev.keycode;

    switch(kc)
    {
    case 'w': pos.y = std::max(pos.y-1, 0); break;
    case 'a': pos.x = std::max(pos.x-1, 0); break;
    case 's': pos.y = std::min(pos.y+1, 8); break;
    case 'd': pos.x = std::min(pos.x+1, 8); break;
    default: return Scene::on_key_event(ev);
    }

    focus(cells[pos.x][pos.y]);
    return true;
}