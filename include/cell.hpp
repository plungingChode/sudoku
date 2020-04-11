#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include "spinner.hpp"
#include <vector>

static const int CELL_SIDE = 40;
static const genv::color CELL_INVALID = Controls::hex_to_color("ff5555");
static const genv::color CELL_BG = Controls::hex_to_color("ffffff");
static const genv::color CELL_FOCUS = Controls::hex_to_color("dddddd");
static const genv::color CELL_TEXT = Controls::BLACK;

class Cell : public Controls::Spinner
{
protected:
    void update() override;

    int x, y;
    std::vector<Cell*> row, col, segment;

    bool row_valid, col_valid, segment_valid;

    void set_value(int val) override;

public:
    static std::vector<std::vector<int>> board;
    static bool show_invalid;

    bool is_preset;

    Cell(Controls::vec2 pos, int x, int y);

    void set_row(std::vector<Cell*> row) { this->row = row; }
    void set_col(std::vector<Cell*> col) { this->col = col; }
    void set_segment(std::vector<Cell*> segment) { this->segment = segment; }

    void set_row_validity(bool val);
    void set_col_validity(bool val);
    void set_segment_validity(bool val);

    void check_conflicts();
    void reload_board();

    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held = false) override;
};

#endif