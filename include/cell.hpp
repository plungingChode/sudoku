#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include "spinner.hpp"
#include <vector>
#include <functional>

static const int CELL_SIDE = 40;
static const genv::color CELL_INVALID = Controls::hex_to_color(0xff5555);
static const genv::color CELL_INVALID_FOCUS = Controls::change_tint(CELL_INVALID, 0.5);
static const genv::color CELL_BG = Controls::hex_to_color(0xffffff);
static const genv::color CELL_FOCUS = Controls::hex_to_color(0xdddddd);
static const genv::color CELL_TEXT = Controls::BLACK;

typedef std::function<void(int, int, int)> cell_callback;
typedef std::function<void(int, int)> move_callback;

enum cell_flag
{
    row_invalid = 0,
    col_invalid = 1,
    seg_invalid = 2
};

class Cell : public Controls::Spinner
{
protected:
    int col, row;
    int invalid_flags;
    void update() override;

    bool is_preset;
    cell_callback on_change;
    move_callback move_focus;

public:
    static bool SHOW_INVALID;

    Cell(Controls::Scene *owner, int x, int y, int col, int row, cell_callback on_change, move_callback move_focus);

    void initialize(int value);
    void set_flag(cell_flag f, bool val);

    virtual void set_value(int val) override;
    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override;
    virtual void on_key_ev(const genv::event &key_ev, int key_held) override;
};

#endif