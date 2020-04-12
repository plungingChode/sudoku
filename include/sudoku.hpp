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
    const std::string FONT = "LiberationSans-Regular.ttf";
    
    std::string boards_file;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<Cell*>> cells;

    void toggle_invalid();
    void toggle_invalid_perm();

    Controls::Button *toggle_inv;
    Controls::ListBox *boards_list;
    
    void load_selected();

    void load_board(const std::string &fname);
    void check_conflicts(int x, int y);
    
    bool on_key_event(const genv::event &ev) override;
    
public:
    bool show_invalid;

    Sudoku(std::string boards_file);

    void on_cell_change(int x, int y, int new_val);
};

#endif