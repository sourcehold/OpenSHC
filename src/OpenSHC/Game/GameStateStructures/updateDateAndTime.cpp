#include "../GameStateStructures.func.hpp"

#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      currentTick is a value in 0-199 used for load balancing   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456670
    void GameStateStructures::updateDateAndTime(BOOLEnum startOfWeekAsCurrentTickIs0, int currentTick)
    {
        /*
          synchronized with currentTick but it counts until 50 instead of 200
         */
        this->mapAndTime.dayTicks = this->mapAndTime.dayTicks + 1;
        this->mapAndTime.weekTicks = this->mapAndTime.weekTicks + 1;
        this->mapAndTime.monthTicks = this->mapAndTime.monthTicks + 1;
        /*
          if currentTick is 0, 50, 100, 150
         */
        bool startOfDay = currentTick % 50 == 0;
        this->mapAndTime.weekChanged = 0;
        this->mapAndTime.monthChanged = 0;
        this->mapAndTime.yearChanged = 0;
        if (startOfDay) {
            this->mapAndTime.dayTicks = 0;
        }
        this->mapAndTime.startOfDay = startOfDay;
        /*
          key "H" in scenario editor mode for example
         */
        if (DAT_GameCore::instance.isTimeHalted != FALSE) {
            return;
        }
        /*
          we are at the start of Castle Builder mode or in a tutorial
         */
        if (MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)
            != FALSE) {
            return;
        }
        if (startOfWeekAsCurrentTickIs0 == FALSE) {
            return;
        }
        this->mapAndTime.week = this->mapAndTime.week + 1;
        this->mapAndTime.weekChanged = 1;
        this->mapAndTime.weekTicks = 0;
        if (this->mapAndTime.week >= 4) {
            this->mapAndTime.month = this->mapAndTime.month + 1;
            this->mapAndTime.week = 0;
            this->mapAndTime.monthChanged = 1;
            this->mapAndTime.monthTicks = 0;
            if (this->mapAndTime.month >= 12) {
                this->mapAndTime.year = this->mapAndTime.year + 1;
                this->mapAndTime.month = 0;
                this->mapAndTime.yearChanged = 1;
            }
        }
    }
}
}
