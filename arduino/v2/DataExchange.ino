#include "Time.h"
#include "State.h"
#include "Network.h"
#include "debug.h"

void setup()
{
    init_debug();
    network_init();
    DEBUGLN(F("Startup done!"));
}

void loop()
{
    download_config();

    DEBUGLN(millis());
}
