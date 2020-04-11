#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include "spinner.hpp"
#include <vector>

static const int CELL_SIDE = 40;
static const genv::color CELL_INVALID = Controls::hex_to_color("ff5555");
static const genv::color CELL_INVALID_FOCUS = Controls::change_tint(CELL_INVALID, 0.5);
static const genv::color CELL_BG = Controls::hex_to_color("ffffff");
static const genv::color CELL_FOCUS = Controls::hex_to_color("dddddd");
static const genv::color CELL_TEXT = Controls::BLACK;

class Sudoku;

class Cell : public Controls::Spinner
{
protected:
    int x, y;
    Sudoku *owner;

    void update() override;

public:
    bool is_preset;
    bool row_invalid, col_invalid, segment_invalid;

    Cell(Controls::vec2 pos, int x, int y, Sudoku *owner);

    void initialize(int value);
    Controls::vec2 pos() const { return Controls::vec2(x, y); }

    virtual void set_value(int val) override;
    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override;
    virtual void on_key_ev(const genv::event &key_ev, int key_held) override;
};

#endif