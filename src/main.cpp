#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_core.h>
#include <bn_keypad.h>

int main()
{
    bn::core::init();
    bn::backdrop::set_color(bn::color(20, 20, 31));

    while (true)
    {
        if (bn::keypad::a_pressed())
        {
            bn::backdrop::set_color(bn::color(0, 0, 0));
        }
        if (bn::keypad::b_held())
        {
            bn::backdrop::set_color(bn::color(255, 255, 255));
        }

        bn::core::update();
    }
}