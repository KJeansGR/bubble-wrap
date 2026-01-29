#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_items_dot.h>
#include <bn_sprite_items_heart.h>
#include <bn_log.h>
#include <bn_vector.h>

int main()
{
    bn::core::init();

    // bn::sprite_ptr myCircle = bn::sprite_items::dot.create_sprite(40, -40);
    // bn::sprite_ptr myCircle1 = bn::sprite_items::dot.create_sprite(-40, -40);
    // bn::sprite_ptr myCircle2 = bn::sprite_items::dot.create_sprite(40, 40);
    // bn::sprite_ptr myCircle3 = bn::sprite_items::dot.create_sprite(-40, 40);

    bn::vector<bn::sprite_ptr, 30> circles = {};

    for (int x = -40; x <= 40; x += 20)
    {
        circles.push_back(bn::sprite_items::heart.create_sprite(x, -40));
        BN_LOG("x value", x);
    }
    for (int x = -40; x <= 40; x += 20)
    {
        circles.push_back(bn::sprite_items::heart.create_sprite(x, -20));
        BN_LOG("x value", x);
    }
    for (int x = -40; x <= 40; x += 20)
    {
        circles.push_back(bn::sprite_items::heart.create_sprite(x, 0));
        BN_LOG("x value", x);
    }
    for (int x = -40; x <= 40; x += 20)
    {
        circles.push_back(bn::sprite_items::heart.create_sprite(x, 20));
        BN_LOG("x value", x);
    }
    for (int x = -40; x <= 40; x += 20)
    {
        circles.push_back(bn::sprite_items::heart.create_sprite(x, 40));
        BN_LOG("x value", x);
    }

    // original
    float r = 20;
    float g = 20;
    float b = 31;

    // a button
    float x = 0;
    float y = 31;
    float z = 0;

    // b button
    float i = 31;
    float j = 0;
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
            bn::backdrop::set_color(bn::color(
                std::min((int)rT, 31),
                std::min((int)gT, 31),
                std::min((int)bT, 31)));
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

        if (bn::keypad::any_pressed() || bn::keypad::any_held())
        {
            for (int o = 0; o < circles.size(); o++)
            {
                auto xPos = circles[o].position().x();
                auto yPos = circles[o].position().y();

                auto nyPos = circles[o].position().y(); // made this auto because i dont know how to declare a position/vector variable

                yPos + 10 > 70 ? nyPos = -70 : nyPos = yPos + 10; // this should make it stay in the screen bounds

                circles[o].set_position(xPos, nyPos);
            }
            for (int o = 0; o < circles.size(); o++)
            {

                circles[o].set_rotation_angle(circles[0].rotation_angle() + 10 * o);
            }
        }

        bn::core::update();
    }
}