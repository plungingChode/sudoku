#include "controls.hpp"
#include "cell.hpp"
#include "holdbtn.hpp"
#include <vector>
#include <fstream>

using namespace Controls;
using namespace std;

const std::string FONT = "LiberationSans-Regular.ttf";

vector<vector<Cell*>> cells;

Button *show_inv;
void toggle_invalid()
{
    Cell::show_invalid = !Cell::show_invalid;
    for (const vector<Cell*> &col : cells)
    {
        for (Cell* c : col)
        {
            c->schedule_update();
        }
    }
}
void show_invalid_action()
{
    toggle_invalid();
    if (Cell::show_invalid)
    {
        show_inv->set_text("Hibák elrejtése");
    }
    else
    {
        show_inv->set_text("Hibák mutatása");
    }
}

void load_board(const string &fname)
{
    ifstream f(fname);
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            f >> Cell::board[x][y];
        }
    }
    for (const vector<Cell*> col : cells)
    {
        for (Cell *c : col)
        {
            c->reload_board();
        }
    }
}

int main()
{
    Scene s(640, 480);

    cells = vector<vector<Cell*>>(9, vector<Cell*>(9));
    for (int x = 0; x < 9; x++)
    {
        int x_gap = (x%3 == 0) ? 3 : 0;
        for (int y = 0; y < 9; y++)
        {
            int y_gap = (y%3 == 0) ? 3 : 0;
            cells[x][y] = new Cell(vec2(20+x*CELL_SIDE+x_gap, 20+y*CELL_SIDE+y_gap), x, y);          

            s.add_control(cells[x][y]);
        }
    }

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            vector<Cell*> row = {
                cells[0][y], cells[1][y], cells[2][y],
                cells[3][y], cells[4][y], cells[5][y],
                cells[6][y], cells[7][y], cells[8][y]
            };

            int sx = (x/3)*3;
            int sy = (y/3)*3;
            vector<Cell*> segment = {
                cells[sx+0][sy+0], cells[sx+1][sy+0], cells[sx+2][sy+0],
                cells[sx+0][sy+1], cells[sx+1][sy+1], cells[sx+2][sy+1],
                cells[sx+0][sy+2], cells[sx+1][sy+2], cells[sx+2][sy+2],
            };

            cells[x][y]->set_col(cells[x]);
            cells[x][y]->set_row(row);
            cells[x][y]->set_segment(segment);
        }
    }

    Cell::show_invalid = false;
    load_board("board1.txt");

    show_inv = new Button(vec2(23, 390), show_invalid_action, "Hibák mutatása", 150, FONT);
    s.add_control(show_inv);

    HoldButton *peek_inv = new HoldButton(vec2(23, 420), toggle_invalid, "Peek invalid", 150, FONT);
    s.add_control(peek_inv);

    s.run();

    return 0;
}