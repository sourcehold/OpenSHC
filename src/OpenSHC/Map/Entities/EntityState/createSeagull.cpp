#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00406650
        int EntityState::createSeagull(int x, int y)
        {
            int seagullID = 1;
            for (; seagullID < 100; ++seagullID) {
                if (this->seagullArray[seagullID].field_0x8 == 0) {
                    break;
                }
                if (this->seagullArray[seagullID].entityUID
                    != this->entityArray[this->seagullArray[seagullID].entityID].uid) {
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(this->seagullArray[seagullID]), 0, &this->seagullArray[seagullID]);
                }
                if (seagullID >= 99) {
                    return 0;
                }
            }
            this->seagullArray[seagullID].field_0x8 = 2;
            this->seagullArray[seagullID].field_0xa = 0;
            this->seagullArray[seagullID].someCountDown = 0;
            this->seagullArray[seagullID].x = x;
            this->seagullArray[seagullID].x_2 = x;
            this->seagullArray[seagullID].y = y;
            this->seagullArray[seagullID].y_2 = y;
            this->seagullArray[seagullID].angle = SEC_RNG::instance.currentNumber2 % 360;
            this->seagullArray[seagullID].angle_2 = (char)(SEC_RNG::instance.currentNumber2 >> 8) % 360;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->seagullArray[seagullID].unknownCounter_0x16 = SEC_RNG::instance.currentNumber2 % 16 + 24;
            this->seagullArray[seagullID].numberBetween60And100
                = (char)(SEC_RNG::instance.currentNumber2 >> 8) % 40 + 60;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if (SEC_RNG::instance.currentNumber2 & 1) {
                this->seagullArray[seagullID].someAngle = 1;
            } else {
                this->seagullArray[seagullID].someAngle = -1;
            }
            if (SEC_RNG::instance.currentNumber2 & 2) {
                this->seagullArray[seagullID].angleStep = 1;
            } else {
                this->seagullArray[seagullID].angleStep = -1;
            }
            double const angle = (this->seagullArray[seagullID].angle - 180) * 3.1415926535 / 180.0;
            this->seagullArray[seagullID].angle += this->seagullArray[seagullID].someAngle * 20;
            // fixme: the original adds 360 when the angle is too big and subtracts it when it is negative
            if (this->seagullArray[seagullID].angle >= 360) {
                this->seagullArray[seagullID].angle += 360;
            }
            if (this->seagullArray[seagullID].angle < 0) {
                this->seagullArray[seagullID].angle -= 360;
            }
            this->seagullArray[seagullID].field_0x1a = -20;
            int const offsetX = (int)(sin(angle) * this->seagullArray[seagullID].unknownCounter_0x16);
            int const offsetY = (int)(cos(angle) * this->seagullArray[seagullID].unknownCounter_0x16);
            this->seagullArray[seagullID].rngMax799_countdown = 400;
            this->seagullArray[seagullID].x_3 = x;
            this->seagullArray[seagullID].y_3 = y;
            MACRO_CALL_MEMBER(EntityState_Func::initializeSeagullMovementVector, this)(seagullID,
                this->seagullArray[seagullID].x, this->seagullArray[seagullID].y, this->seagullArray[seagullID].x_3,
                this->seagullArray[seagullID].y_3);
            this->seagullArray[seagullID].pathStepDelay = 5;
            this->seagullArray[seagullID].entityID = MACRO_CALL_MEMBER(EntityState_Func::spawnProjectileEntity, this)(
                seagullID, 0, 0, x, y, 250, x + offsetX, y + offsetY, 250, ET_SEAGULLUnk, 0);
            this->seagullArray[seagullID].entityUID = this->entityArray[this->seagullArray[seagullID].entityID].uid;
            this->seagullArray[seagullID].randomNumber = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return seagullID;
        }

    }
}
}
