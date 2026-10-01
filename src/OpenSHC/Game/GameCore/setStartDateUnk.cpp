#include "../GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BD50
    void GameCore::setStartDateUnk(int trailNumber)
    {
        // trailNumber 0 resets all trails, otherwise 1 = skirmish, 2 = warchest, 3 = extreme
        if (trailNumber == 0 || trailNumber == 1) {
            this->skirmishTrailYearReached = 1100 * 12;
        }
        if (trailNumber == 0 || trailNumber == 2) {
            this->warchestTrailYearReached = 1130 * 12;
        }
        if (trailNumber == 0 || trailNumber == 3) {
            this->extremeTrailYearReached = 1130 * 12;
        }

        if (trailNumber == 0 || trailNumber == 1) {
            int mission;
            for (mission = 0; mission < 50; ++mission) {
                if (this->skirmishTrailMonthsTakenOrChicken[mission] == -1200) {
                    this->skirmishTrailStartDateInMonths[mission] = this->skirmishTrailYearReached;
                    this->skirmishTrailYearReached += 1200;
                    continue;
                }
                if (this->skirmishTrailMonthsTakenOrChicken[mission] < 0) {
                    break;
                }
                this->skirmishTrailStartDateInMonths[mission] = this->skirmishTrailYearReached;
                this->skirmishTrailYearReached += this->skirmishTrailMonthsTakenOrChicken[mission];
            }
            if (mission != 50) {
                this->skirmishTrailStartDateInMonths[mission] = this->skirmishTrailYearReached;
            }
        }

        if (trailNumber == 0 || trailNumber == 2) {
            int mission;
            for (mission = 0; mission < 30; ++mission) {
                if (this->warchestTrailMonthsTakenOrChicken[mission] == -1200) {
                    this->warchestTrailStartDatesInMonths[mission] = this->warchestTrailYearReached;
                    this->warchestTrailYearReached += 1200;
                    continue;
                }
                if (this->warchestTrailMonthsTakenOrChicken[mission] < 0) {
                    break;
                }
                this->warchestTrailStartDatesInMonths[mission] = this->warchestTrailYearReached;
                this->warchestTrailYearReached += this->warchestTrailMonthsTakenOrChicken[mission];
            }
            if (mission != 30) {
                this->warchestTrailStartDatesInMonths[mission] = this->warchestTrailYearReached;
            }
        }

        if (trailNumber == 0 || trailNumber == 3) {
            int mission;
            for (mission = 0; mission < 20; ++mission) {
                if (this->extremeTrailMonthsTakenOrChicken[mission] == -1200) {
                    this->extremeTrailStartDatesInMonths[mission] = this->extremeTrailYearReached;
                    this->extremeTrailYearReached += 1200;
                    continue;
                }
                if (this->extremeTrailMonthsTakenOrChicken[mission] < 0) {
                    break;
                }
                this->extremeTrailStartDatesInMonths[mission] = this->extremeTrailYearReached;
                this->extremeTrailYearReached += this->extremeTrailMonthsTakenOrChicken[mission];
            }
            if (mission != 20) {
                this->extremeTrailStartDatesInMonths[mission] = this->extremeTrailYearReached;
            }
        }
    }

}
}
