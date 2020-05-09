#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include "scene.hpp"
#include "holdbtn.hpp"
#include "listbox.hpp"
#include "cell.hpp"
#include <vector>

class Sudoku : public Controls::Scene
{
protected:
    const genv::font FONT = genv::font("LiberationSans-Regular.ttf", 16);
    const int win_hex = 0x32cd32;
    const int bg_hex = 0x3c3c3c;
    

    std::string boards_file;
    std::vector<std::string> boards;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<Cell*>> cells;
    bool show_invalid;
    bool win_state;

    void toggle_invalid();
    void toggle_invalid_perm();

    Controls::Button *loader;
    Controls::Button *toggle_inv;
    Controls::ListBox *boards_list;
    Controls::Label *win_label;
    HoldButton *peek_inv;
    
    void on_request_move_focus(int new_x, int new_y);
    void on_cell_change(int x, int y, int new_val);
    void check_conflicts(int x, int y);
    void set_win_state(bool w);

    void parse_boards();  
    void load_board(const std::string &board_name);
public:

    Sudoku(std::string boards_file);
};

#endif