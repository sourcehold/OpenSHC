#include "../GameStateStructures.func.hpp"

#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    using UI::Enums::DisplayElementID;
    using WindowsHelper::Enums::BOOLEnum;

    // NOTE: currentTick is a value in 0-199 used for load balancing

    // FUNCTION: STRONGHOLDCRUSADER 0x00456670
    void GameStateStructures::updateDateAndTime(BOOLEnum startOfWeekAsCurrentTickIs0, int currentTick)
    {
        this->mapAndTime.weekChanged = 0;
        this->mapAndTime.monthChanged = 0;
        this->mapAndTime.yearChanged = 0;
        this->mapAndTime.startOfDay = 0;
        // synchronized with currentTick but it counts until 50 instead of 200
        this->mapAndTime.dayTicks++;
        this->mapAndTime.weekTicks++;
        this->mapAndTime.monthTicks++;
        // if currentTick is 0, 50, 100, 150
        if (currentTick % 50 == 0) {
            this->mapAndTime.startOfDay = 1;
            this->mapAndTime.dayTicks = 0;
        }
        // key "H" in scenario editor mode for example
        if (DAT_GameCore::instance.isTimeHalted) {
            return;
        }
        // we are at the start of Castle Builder mode or in a tutorial
        if (MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
            return;
        }
        if (!startOfWeekAsCurrentTickIs0) {
            return;
        }
        ++this->mapAndTime.week;
        this->mapAndTime.weekChanged = 1;
        this->mapAndTime.weekTicks = 0;
        if (this->mapAndTime.week >= 4) {
            ++this->mapAndTime.month;
            this->mapAndTime.week = 0;
            this->mapAndTime.monthChanged = 1;
            this->mapAndTime.monthTicks = 0;
            if (this->mapAndTime.month >= 12) {
                ++this->mapAndTime.year;
                this->mapAndTime.month = 0;
                this->mapAndTime.yearChanged = 1;
            }
        }
    }

}
}
