#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::ScenarioEvents::IngameEventHeader;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BA7D0
    void MapPropertiesState::sortEventsByDate()
    {
        for (int pass = 0; pass < this->eventsCount - 1; ++pass) {
            for (int i = 0; i < this->eventsCount - pass - 1; ++i) {
                IngameEventHeader const& current = this->scenarioEvents[i].header;
                IngameEventHeader const& next = this->scenarioEvents[i + 1].header;
                if (current.year > next.year
                    || (current.year == next.year
                        && (current.month > next.month
                            || (current.month == next.month && current.tl_type > next.tl_type)))) {
                    // an int buffer: a copy of the event type itself would get a /GS cookie the original does not have
                    int swap[sizeof(InGameEventUnionVersion) / sizeof(int)];
                    memcpy(&swap, &this->scenarioEvents[i], sizeof(swap));
                    memcpy(&this->scenarioEvents[i], &this->scenarioEvents[i + 1], sizeof(swap));
                    memcpy(&this->scenarioEvents[i + 1], &swap, sizeof(swap));
                }
            }
        }
    }

}
}
