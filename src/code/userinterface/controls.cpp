#include "controls.h"

#include <ncurses.h>

#include "interfaceelement.h"
#include "userinterface.h"

#include "../lib/log.h"

void Controls::Init()
{
    noecho();
    nodelay(stdscr, TRUE);
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    // printf("\033[?1003l\n");
    printf("\033[?1003h\n");
}


bool Controls::is_running = false;
void Controls::Run() 
{
    is_running = true;
    while (is_running) 
    {
        int c;
        {
            std::lock_guard ncurses_locker(UserInterface::ncurses_lock);
            c = getch();
        }
        MEVENT event;
        switch(c)
        {
            case KEY_UP:
                Renderer::is_running = false;
                is_running = false;
                break;
            case KEY_DOWN:
                break;
            case KEY_MOUSE:
                if(getmouse(&event) == OK)
                {
                    HandleMouseMovement(event.x, event.y);
                    if(event.bstate & BUTTON1_PRESSED)
                        HandleMouseButton1(event.x, event.y);
                    else if(event.bstate & BUTTON2_PRESSED)
                        Log::Out("CON: b2");
                    else {}
                        // Log::Out("CON: b3");
                }
                break;
            default:
                break;
        }
    }
}

bool PointWithinBorders(int __px, int __py, int __bx, int __by, int __bw, int __bh)
{
    return __bx <= __px 
        && __bx + __bw > __px
        && __by <= __py 
        && __by + __bh > __py;
}

void Controls::HandleMouseButton1(int __x, int __y)
{
    for (int _il = 0; _il < INTERFACE_ELEMENT_LAYERS_AMOUNT; _il ++)
        for (auto &_el : InterfaceElement::layers[_il])
        {
            std::lock_guard<std::recursive_mutex> locker(_el->lock);
            if (PointWithinBorders(__x, __y, _el->x, _el->y, _el->w, _el->h))
            {
                _el->OnClick(true);
                return;
            }
        }
}

InterfaceElement *hashed_el=nullptr;
void Controls::HandleMouseMovement(int __x, int __y)
{
    for (int _il = 0; _il < INTERFACE_ELEMENT_LAYERS_AMOUNT; _il ++)
        for (auto &_el : InterfaceElement::layers[_il])
        {
            std::lock_guard<std::recursive_mutex> locker(_el->lock);
            if (PointWithinBorders(__x, __y, _el->x, _el->y, _el->w, _el->h))
            {
                if (hashed_el != _el)
                {
                    if (hashed_el != nullptr)
                    {
                        std::lock_guard<std::recursive_mutex> locker(hashed_el->lock);
                        hashed_el->OnHover(false);
                    }
                    _el->OnHover(true);
                    hashed_el = _el;
                }
                return;
            }
        }

    if (hashed_el != nullptr)
    {
        std::lock_guard<std::recursive_mutex> locker(hashed_el->lock);
        hashed_el->OnHover(false);
        hashed_el = nullptr;
    }
}