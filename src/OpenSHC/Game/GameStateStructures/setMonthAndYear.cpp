#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456750
    void GameStateStructures::setMonthAndYear(int month, int year)
    {
        this->mapAndTime.weekChanged = 0;
        this->mapAndTime.monthChanged = 0;
        this->mapAndTime.yearChanged = 0;
        this->mapAndTime.week = 0;
        this->mapAndTime.month = month;
        this->mapAndTime.year = year;
        this->mapAndTime.dayTicks = 100;
        this->mapAndTime.weekTicks = 100;
        this->mapAndTime.monthTicks = 100;
    }

}
}
