#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_core.h>
#include <bn_keypad.h>

int main()
{
    bn::core::init();
    // original
    float r = 20;
    float g = 20;
    float b = 31;

    // a button
    float x = 0;
    float y = 0;
    float z = 31;

    // b button
    float i = 0;
    float j = 31;
    float k = 0;

    bn::backdrop::set_color(bn::color(r, g, b));

    while (true)
    {
        // blend colors if a and b are pressed, limts the max value to 31
        if ((bn::keypad::a_pressed() && bn::keypad::b_pressed()) ||
            (bn::keypad::a_held() && bn::keypad::b_held()))
        {
            float rT = x + i;
            float gT = y + j;
            float bT = z + k;
            bn::backdrop::set_color(bn::color(std::min((int)rT, 31), std::min((int)gT, 31), std::min((int)bT, 31)));
        }
        // sets to defined a color
        else if (bn::keypad::a_pressed() || bn::keypad::a_held())
        {
            bn::backdrop::set_color(bn::color(x, y, z));
        }
        // sets to defined b color
        else if (bn::keypad::b_pressed() || bn::keypad::b_held())
        {
            bn::backdrop::set_color(bn::color(i, j, k));
        }
        // revert to original color if nothing is pressed
        else if (!bn::keypad::a_pressed() && !bn::keypad::b_pressed())
        {
            bn::backdrop::set_color(bn::color(r, g, b));
        }
        bn::core::update();
    }
}