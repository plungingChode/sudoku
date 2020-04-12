#include "sudoku.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace Controls;
using namespace std;

Sudoku::Sudoku(std::string boards_file) 
    : Scene(640, 480), boards_file(boards_file), show_invalid(false)
{
    board = vector<vector<int>>(9, vector<int>(9));
    cells = vector<vector<Cell*>>(9, vector<Cell*>(9));

    vector<ListBoxItem*> boards;
    std::ifstream f(boards_file);
    while (f.good())
    {
        std::string line;
        std::getline(f, line, '\n');

        if(!std::isdigit(line[0]))
        {
            boards.push_back(new BoardItem(line));
        }
    }
    boards_list = new ListBox(vec2(400, 23), 150, 6, boards, FONT);
    boards_list->set_hover_bg(0xffffff);
    boards_list->set_hold_bg(0xffffff);
    boards_list->set_focus_bg(0xffffff);
    boards_list->set_border_color(0x999999);
    add_control(boards_list);

    action_t load_action = std::bind(&Sudoku::load_selected, this);
    Button *loader = new Button(vec2(400, 140), load_action, "Load", 150, FONT);
    add_control(loader);

    action_t peek_action = std::bind(&Sudoku::toggle_invalid, this);
    HoldButton *peek = new HoldButton(vec2(23, 390), peek_action, "Peek invalid", 160, FONT);
    add_control(peek);

    action_t toggle_action = std::bind(&Sudoku::toggle_invalid_perm, this);
    toggle_inv = new Button(vec2(23, 420), toggle_action, "Show invalid", 160, FONT);
    add_control(toggle_inv);

    for (int x = 0; x < 9; x++)
    {
        int x_gap = (x%3 == 0) ? 2 : 0;
        for (int y = 0; y < 9; y++)
        {
            int y_gap = (y%3 == 0) ? 2 : 0;
            cells[x][y] = new Cell(vec2(20+x*(CELL_SIDE-1)+x_gap, 20+y*(CELL_SIDE-1)+y_gap), x, y, this);          

            add_control(cells[x][y]);
        }
    }

    load_board(boards[0]->to_string());
}

void Sudoku::toggle_invalid()
{
    show_invalid = !show_invalid;
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
    if (show_invalid)
    {
        toggle_inv->set_text("Hide invalid");
    }
    else
    {
        toggle_inv->set_text("Show invalid");
    }
}

void Sudoku::load_selected()
{
    string brd = boards_list->get_selected_item()->to_string();
    load_board(brd);
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
}

void Sudoku::on_cell_change(int x, int y, int value)
{
    board[x][y] = value;
    check_conflicts(x, y);
}

void Sudoku::check_conflicts(int x, int y)
{
    int occ[10] = {0};

    // check rows
    bool invalid = false;
    for (int col = 0; col < 9; col++)
    {
        int val = board[col][y];

        occ[val]++;
        if (val > 0 && occ[val] > 1)
        {
            invalid = true;
            break;
        }
    }
    for (int col = 0; col < 9; col++)
    {
        cells[col][y]->row_invalid = invalid;
        cells[col][y]->schedule_update();
    }
    std::fill(occ, occ+10, 0);

    //check columns
    invalid = false;
    for (int row = 0; row < 9; row++)
    {
        int val = board[x][row];
        occ[val]++;
        if (val > 0 && occ[val] > 1)
        {
            invalid = true;
            break;
        }
    }
    for (int row = 0; row < 9; row++)
    {
        cells[x][row]->col_invalid = invalid;
        cells[x][row]->schedule_update();
    }
    std::fill(occ, occ+10, 0);

    // check 3x3 segments
    invalid = false;
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
                invalid = true;
                break;
            }
        }
    }
    for (int row = sy; row < sy+3; row++)
    {
        for (int col = sx; col < sx+3; col++)
        {
            cells[col][row]->segment_invalid = invalid;
            cells[col][row]->schedule_update();
        }
    }
}

bool Sudoku::on_key_event(const genv::event &ev)
{
    bool is_cell = false;

    vector<vector<Cell*>>::const_iterator col;
    for (col = cells.begin(); col != cells.end(); col++)
    {
        if (find(col->begin(), col->end(), focused) != col->end())
        {
            is_cell = true;
            break;
        }
    }

    if (is_cell)
    {
        vec2 pos = ((Cell*)focused)->pos();

        int kc = key_held ? key_held : ev.keycode;

        switch(kc)
        {
        case 'w': pos.y = std::max(pos.y-1, 0); break;
        case 'a': pos.x = std::max(pos.x-1, 0); break;
        case 's': pos.y = std::min(pos.y+1, 8); break;
        case 'd': pos.x = std::min(pos.x+1, 8); break;
        default: return Scene::on_key_event(ev); break;
        }

        focus(cells[pos.x][pos.y]);
        return true;
    }
    return Scene::on_key_event(ev);
}