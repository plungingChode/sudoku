#include "sudoku.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace Controls;
using namespace std;

Sudoku::Sudoku(std::string boards_file_) 
    : Scene(640, 480), boards_file(boards_file_), show_invalid(false), win_state(false)
{
    board = vector<vector<int>>(9, vector<int>(9, 0));
    cells = vector<vector<Cell*>>(9, vector<Cell*>(9));
    parse_boards();

    boards_list = new ListBox(this, 400, 23, 150, 6, boards, &FONT);
    boards_list->set_hover_bg(0xffffff);
    boards_list->set_hold_bg(0xffffff);
    boards_list->set_focus_bg(0xffffff);
    boards_list->set_border_color(0x999999);

    win_label = new Label(this, 400, 200, 150, "Helyes megoldás", &FONT);
    win_label->set_text_fill_normal(bg_hex);
    win_label->set_border_color(bg_hex);
    win_label->set_normal_bg(bg_hex);

    std::function<void()> load_f = [&]() 
    {
        if (boards_list->get_selected_index() != -1)
        {
            load_board(boards_list->get_selected_item());
        }
    };
    loader = new Button(this, 400, 140, 150, "Load", load_f, &FONT);
    peek_inv = new HoldButton(this, 23, 390, 160, "Peek invalid", [&](){ toggle_invalid(); }, &FONT);
    toggle_inv = new Button(this, 23, 420, 160, "Show invalid", [&](){ toggle_invalid_perm(); }, &FONT);

    for (int x = 0; x < 9; x++)
    {
        int x_gap = (x%3 == 0) ? 2 : 0;
        for (int y = 0; y < 9; y++)
        {
            int y_gap = (y%3 == 0) ? 2 : 0;
            cells[x][y] = new Cell(
                this, 
                20+x*(CELL_SIDE-1)+x_gap, 
                20+y*(CELL_SIDE-1)+y_gap, 
                x, y,
                [&](int col, int row, int val_) { on_cell_change(col, row, val_); },
                [&](int x_, int y_) { on_request_move_focus(x_, y_); }
            );          
        }
    }

    load_board(boards[0]);
}

void Sudoku::toggle_invalid()
{
    Cell::SHOW_INVALID = !Cell::SHOW_INVALID;
    for (const vector<Cell*> &col : cells)
    {
        for (Cell *c : col)
        {
            c->schedule_update();
        }
    }
}

void Sudoku::toggle_invalid_perm()
{
    toggle_invalid();
    if (Cell::SHOW_INVALID)
    {
        toggle_inv->set_text("Hide invalid");
    }
    else
    {
        toggle_inv->set_text("Show invalid");
    }
}

void Sudoku::parse_boards()
{
    std::ifstream f(boards_file);
    while (f.good())
    {
        std::string line;
        std::getline(f, line, '\n');

        if(!std::isdigit(line[0]))
        {
            boards.push_back(line);
        }
    }
}

void Sudoku::load_board(const string &name)
{
    ifstream f(boards_file);
    while (f.good())
    {
        std::string line;
        std::getline(f, line, '\n');
        
        if (line == name)
        {
            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    f >> board[x][y];
                    cells[x][y]->initialize(board[x][y]);
                }  
            }
            break;
        }
    }
    set_win_state(false);
}

void Sudoku::on_request_move_focus(int x, int y)
{
    x = std::min(std::max(x, 0), 8);
    y = std::min(std::max(y, 0), 8);
    focus(cells[x][y]);
}

void Sudoku::on_cell_change(int x, int y, int value)
{
    board[x][y] = value;
    check_conflicts(x, y);
}

void Sudoku::set_win_state(bool w)
{
    win_state = w;
    if (w)
    {
        win_label->set_text_fill_normal(win_hex);
    }
    else
    {
        win_label->set_text_fill_normal(bg_hex);
    }
}

void Sudoku::check_conflicts(int x, int y)
{
    int occ[10] = {0};
    bool any_invalid = false;

    // check rows
    bool is_invalid = false;
    for (int col = 0; col < 9; col++)
    {
        int val = board[col][y];

        occ[val]++;
        if (val > 0 && occ[val] > 1)
        {
            is_invalid = true;
            any_invalid = true;
            break;
        }
    }
    for (int col = 0; col < 9; col++)
    {
        cells[col][y]->set_flag(row_invalid, is_invalid);
    }
    std::fill(occ, occ+10, 0);

    //check columns
    is_invalid = false;
    for (int row = 0; row < 9; row++)
    {
        int val = board[x][row];
        occ[val]++;
        if (val > 0 && occ[val] > 1)
        {
            is_invalid = true;
            any_invalid = true;
            break;
        }
    }
    for (int row = 0; row < 9; row++)
    {
        cells[x][row]->set_flag(col_invalid, is_invalid);
    }
    std::fill(occ, occ+10, 0);

    // check 3x3 segments
    is_invalid = false;
    int sx = (x/3)*3;
    int sy = (y/3)*3;
    for (int row = sy; row < sy+3; row++)
    {
        for (int col = sx; col < sx+3; col++)
        {
            int val = board[col][row];

            occ[val]++;
            if (val > 0 && occ[val] > 1)
            {
                is_invalid = true;
                any_invalid = true;
                break;
            }
        }
    }
    for (int row = sy; row < sy+3; row++)
    {
        for (int col = sx; col < sx+3; col++)
        {
            cells[col][row]->set_flag(seg_invalid, is_invalid);
        }
    }

    // check for win
    if (!any_invalid || win_state)
    {
        bool win = !any_invalid;
        for (int col = 0; col < 9; col++)
        {
            for (int row = 0; row < 9; row++)
            {
                if (board[col][row] == 0)
                {
                    win = false;
                    break;
                }
            }
        }
        set_win_state(win);
    }
}