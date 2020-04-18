#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include "scene.hpp"
#include "holdbtn.hpp"
#include "listbox.hpp"
#include "cell.hpp"
#include <vector>

class BoardItem : public Controls::ListBoxItem
{
public:
    std::string name;

    BoardItem(std::string name) : name(name) { }

    std::string to_string() override { return name; };
};

class Sudoku : public Controls::Scene
{
protected:
    enum action_t
    {
        a_toggle_inv = 0,
        a_peek_inv,
        a_load,
    };

    const genv::font FONT = genv::font("LiberationSans-Regular.ttf", 16);
    
    std::string boards_file;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<Cell*>> cells;

    void toggle_invalid();
    void toggle_invalid_perm();

    Controls::Button *loader;
    Controls::Button *toggle_inv;
    Controls::ListBox *boards_list;
    HoldButton *peek_inv;
    
    void on_cell_change(int x, int y, int new_val);
    void load_board(const std::string &fname);
    void check_conflicts(int x, int y);
        
public:
    bool show_invalid;

    Sudoku(std::string boards_file);

    void action(int a) override;
};

#endif