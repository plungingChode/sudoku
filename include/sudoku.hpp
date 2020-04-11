#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include "scene.hpp"
#include "cell.hpp"
#include <vector>

class Sudoku : public Controls::Scene
{
protected:
    std::vector<std::vector<Cell*>> cells;
    std::vector<std::vector<int>> board;

    std::string board_name;

    void load_board(std::string fname);
    void check_conflicts(int x, int y);
    
    bool on_key_event(const genv::event &ev) override;
    
public:
    bool show_invalid;

    Sudoku(std::string board_file);

    void on_cell_change(int x, int y, int new_val);
};

#endif