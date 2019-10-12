#include "Time.h"
#include "State.h"
#include "Network.h"

void setup()
{
    Serial.begin(115200);
    Serial.println(F("Starting..."));
    network_init();
    Serial.println(F("Startup done!"));
}

void loop()
{
    download_config();

}
