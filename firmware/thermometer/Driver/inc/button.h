#pragma once

#include "Input.h"
#include "button_data.h"

class Button : public Input<button_state_t>
{
public:
    virtual bool Read(button_state_t& state) override;
    static Button& GetInstance(button_t button);
private:
    button_t button;
    Button(button_t button);
};
