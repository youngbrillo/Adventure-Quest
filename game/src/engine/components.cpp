#include "components.h"
#include <raymath.h>

void engine::Panel::Draw(Color* color) const
{
    DrawTextureNPatch(
        texture,
        npatch,
        destination,
        origin,
        angle,
        color ? *color : tint
    );

}

void engine::Text::Draw(Vector2 offset, float angleOffset, Color* color) const
{
    DrawTextPro(
        font,
        text.c_str(),
        Vector2Add(position, offset),
        origin,
        angle + angleOffset,
        fontSize,
        fontSpacing,
        color ? *color : tint
    );
}

Vector2 engine::Text::Size() const
{
    return MeasureTextEx(font, text.c_str(), fontSize, fontSpacing);
}

Rectangle engine::Text::bounds() const
{
    return Rectangle();
}

bool engine::Button::Draw()
{
    bool hovered = CheckCollisionPointRec(GetMousePosition(), panel.destination);

    panel.Draw(hovered ? &altPanelColor : &panel.tint);
    text.Draw({ panel.destination.x, panel.destination.y }, panel.angle, hovered ? &altTextColor : &text.tint);
    

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return true;
    }

    return false;
}

void engine::Button::resize()
{
    Vector2 size = text.Size();

    panel.destination.width = size.x + (panel.npatch.left + panel.npatch.right)/2;
    panel.destination.height = size.y + (panel.npatch.top + panel.npatch.bottom)/2;

    panel.origin.x = (panel.npatch.left)/2;
    panel.origin.y = (panel.npatch.top)/2;
}
