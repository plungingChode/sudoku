#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "frame.hpp"

namespace Controls
{
    class Label : public Frame
    {
    protected:
        genv::color text_fill_normal = DEFAULT_TEXT_NORMAL;
        genv::color text_fill_focused = DEFAULT_TEXT_FOCUS;

        std::string text;

        virtual void update() override;

    public:
        Label(Scene *owner, int x, int y, int width, int height, const std::string &text, const genv::font *font = nullptr);
        Label(Scene *owner, int x, int y, int width, const std::string &text, const genv::font *font = nullptr);

        void set_text(const std::string &text);
        void set_text_fill_normal(int hex) { set_color(text_fill_normal, hex); }
        void set_text_fill_focused(int hex) { set_color(text_fill_focused, hex); }
    };
}

#endif