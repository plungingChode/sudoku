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

class Cell : public Controls::Spinner
{
protected:
    int col, row;
    void update() override;

public:
    static bool SHOW_INVALID;

    bool is_preset;
    bool row_invalid, col_invalid, segment_invalid;
    cell_callback on_change;

    Cell(Controls::Scene *owner, int x, int y, int col, int row, cell_callback on_change);

    void initialize(int value);
    Controls::vec2 pos() const { return Controls::vec2(col, row); }

    virtual void set_value(int val) override;
    virtual void on_mouse_ev(const genv::event &mouse_ev, bool btn_held) override;
    virtual void on_key_ev(const genv::event &key_ev, int key_held) override;
};

#endif