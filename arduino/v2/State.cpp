#include "State.h"

void item::setLoose()
{
    State.successPostedEnabled = false;
    isEnabled = false;
    looseWarning = false;
}

void item::setEnabledFromServer(bool enabled)
{
    isEnabled = State.successPostedEnabled && enabled;
    looseWarning &= !isEnabled;
}

state State;
