#include "renderer.h"

#include "../game.h"
#include "../lib/log.h"
#include <ncurses.h>
#include <stdlib.h>

#include "interfaceelement.h"
#include "userinterface.h"



// TEMP ?
int colornum(int fg, int bg)
{
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}


int rendMinX=INT_MAX,
    rendMaxX=0,
    rendMinY=INT_MAX,
    rendMaxY=0;
void Renderer::RenderText(int __x, int __y, const char* __text, Color __colorF, Color __colorB)
{
    std::lock_guard ncurses_locker(UserInterface::ncurses_lock);

    // update borders
    if (rendMinX > __x) rendMinX = __x;
    if (rendMaxX < __x) rendMaxX = __x;
    if (rendMinY > __y) rendMinY = __y;
    if (rendMaxY < __y) rendMaxY = __y;

    // set color
    attron(COLOR_PAIR(colornum(__colorF, __colorB)));
    if (__colorF / 8 == 1) attron(A_BOLD);
    else attroff(A_BOLD);

    // print
    mvprintw(__y, __x, __text);
}


void Renderer::Init()
{
    std::lock_guard ncurses_locker(UserInterface::ncurses_lock);

    // init rendering
    initscr();
    curs_set(0);
    clear();

    // init colors
    use_default_colors();
    start_color();
    for (int _iF = 0; _iF < 8; _iF ++)
        for (int _iB = 0; _iB < 8; _iB ++)
            init_pair(colornum(_iF, _iB), _iF, _iB);
}


void Renderer::Run()
{
    while (true)
    {
        // clear
        {
            std::lock_guard ncurses_locker(UserInterface::ncurses_lock);
            clear();
        }

        // render layers
        {
            std::lock_guard layers_locker(InterfaceElement::layers_lock);
            for (int _il = 0; _il < INTERFACE_ELEMENT_LAYERS_AMOUNT; _il ++)
                for (auto &_el : InterfaceElement::layers[_il])
                {
                    std::lock_guard el_locker(_el->lock);
                    for (auto &_rule : _el->visualComponent.rules)
                        Renderer::RenderText(
                            _el->x + _rule.x,
                            _el->y + _rule.y,
                            _rule.ch,
                            _rule.colorF,
                            _rule.colorB
                        );
                }
        }

        // refresh
        {
            std::lock_guard ncurses_locker(UserInterface::ncurses_lock);
            refresh();
        }
    }
}