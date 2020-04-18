#include "State.h"
#include "debug.h"
#include "Time.h"

state State;

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

void state::StartUpdate()
{
    for (auto&& i : Items)
        i.isUpdated = false;
}

void state::ProcessTimestamp(uint32_t ts)
{
    DEBUG("Timestamp: ");
    DEBUGLN(ts);
    setTime(ts);
}

void state::ProcessBucket(long id, long lowlevel)
{
    DEBUG(F("Received bucket "));
    DEBUG(id);
    DEBUG(F(" - lowlevel: "));
    DEBUGLN(lowlevel);
    auto&item = Items[id];
    item.isBucket = true;
    item.isPlant = false;
    item.isEnabled = true;
    item.isUpdated = true;
    item.lowWaterLevel = lowlevel;
}

void state::ProcessPlant(long id, long lowlevel, bool enabled, long bucketid, long pumptime, long filltime)
{
    DEBUG(F("Received plant "));
    DEBUG(id);
    DEBUG(F(" - lowlevel: "));
    DEBUG(lowlevel);
    DEBUG(enabled ? F(" en") : F(" dis"));
    DEBUG(F("abled bucket: "));
    DEBUG(bucketid);
    DEBUG(F(" pump: "));
    DEBUG(pumptime);
    DEBUG(F(" fill: "));
    DEBUGLN(filltime);
    auto&item = Items[id];
    item.isBucket = false;
    item.isPlant = true;
    item.isUpdated = true;
    item.setEnabledFromServer(enabled);
    item.lowWaterLevel = lowlevel;
    item.parentBucket = bucketid;
    item.pumpTime = pumptime;
    item.fillTime = filltime;
}

void state::Confirm()
{
    DEBUGLN("Confirming update");
    for (int8_t i = 0; i < ITEM_COUNT; i++)
    {
        if (!Items[i].isUpdated && Items[i].isEnabled)
        {
            Items[i].isBucket = false;
            Items[i].isPlant = false;
            Items[i].isEnabled = false;
            DEBUG(F("Disabling item "));
            DEBUGLN(i);
        }
    }
}
