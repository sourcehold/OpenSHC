#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::IO::Graphics::GmID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00539BE0
        GmID UnitsState::getPeasantGmID(int unitID)
        {
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_BURNINGMAN:
                return OpenSHC::IO::Graphics::GID_BODY_MAN_BURNING;
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                return OpenSHC::IO::Graphics::GID_BODY_WOODCUTTER;
            case OpenSHC::Map::Units::UT_FLETCHER:
                return OpenSHC::IO::Graphics::GID_BODY_FLETCHER;
            case OpenSHC::Map::Units::UT_TUNNELER:
                return OpenSHC::IO::Graphics::GID_BODY_TUNNELOR;
            case OpenSHC::Map::Units::UT_HUNTER:
                return OpenSHC::IO::Graphics::GID_BODY_HUNTER;
            case OpenSHC::Map::Units::UT_QUARRYOX:
                return OpenSHC::IO::Graphics::GID_BODY_OX;
            case OpenSHC::Map::Units::UT_PITCHMAN:
                return OpenSHC::IO::Graphics::GID_BODY_PITCH_WORKER;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
            case OpenSHC::Map::Units::UT_HOPSFARMER:
            case OpenSHC::Map::Units::UT_APPLEFARMER:
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                return OpenSHC::IO::Graphics::GID_BODY_FARMER;
            case OpenSHC::Map::Units::UT_MILLER:
                return OpenSHC::IO::Graphics::GID_BODY_MILLER;
            case OpenSHC::Map::Units::UT_BAKER:
                return OpenSHC::IO::Graphics::GID_BODY_BAKER;
            case OpenSHC::Map::Units::UT_BREWER:
                return OpenSHC::IO::Graphics::GID_BODY_BREWER;
            case OpenSHC::Map::Units::UT_POLETURNER:
                return OpenSHC::IO::Graphics::GID_BODY_POLETURNER;
            case OpenSHC::Map::Units::UT_SMITH:
                return OpenSHC::IO::Graphics::GID_BODY_BLACKSMITH;
            case OpenSHC::Map::Units::UT_ARMORER:
                return OpenSHC::IO::Graphics::GID_BODY_ARMOURER;
            case OpenSHC::Map::Units::UT_TANNER:
                return OpenSHC::IO::Graphics::GID_BODY_TANNER;
            case OpenSHC::Map::Units::UT_MINER:
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                return OpenSHC::IO::Graphics::GID_BODY_IRON_MINER;
            case OpenSHC::Map::Units::UT_PRIEST:
                return OpenSHC::IO::Graphics::GID_BODY_PRIEST;
            case OpenSHC::Map::Units::UT_HEALER:
                return OpenSHC::IO::Graphics::GID_BODY_HEALER;
            case OpenSHC::Map::Units::UT_DRUNK:
                return OpenSHC::IO::Graphics::GID_BODY_DRUNKARD;
            case OpenSHC::Map::Units::UT_TRADER:
                return OpenSHC::IO::Graphics::GID_BODY_TRADER;
            case OpenSHC::Map::Units::UT_TRADERHORSE:
                return OpenSHC::IO::Graphics::GID_BODY_HORSE_TRADER;
            case OpenSHC::Map::Units::UT_COW:
                return OpenSHC::IO::Graphics::GID_BODY_COW;
            case OpenSHC::Map::Units::UT_HUNTERDOG:
                return OpenSHC::IO::Graphics::GID_BODY_DOG;
            case OpenSHC::Map::Units::UT_LORD:
                return OpenSHC::IO::Graphics::GID_BODY_LORD;
            case OpenSHC::Map::Units::UT_LADY:
                return OpenSHC::IO::Graphics::GID_BODY_LADY;
            case OpenSHC::Map::Units::UT_JESTER:
                return OpenSHC::IO::Graphics::GID_BODY_JESTER;
            case OpenSHC::Map::Units::UT_CHICKEN:
                return OpenSHC::IO::Graphics::GID_BODY_CHICKEN;
            case OpenSHC::Map::Units::UT_MOTHER:
                return OpenSHC::IO::Graphics::GID_BODY_MOTHER;
            case OpenSHC::Map::Units::UT_CHILD:
                return OpenSHC::IO::Graphics::GID_BODY_BOY;
            case OpenSHC::Map::Units::UT_JUGGLER:
                return OpenSHC::IO::Graphics::GID_BODY_JUGGLER;
            case OpenSHC::Map::Units::UT_FIREEATER:
                return OpenSHC::IO::Graphics::GID_BODY_FIRE_EATER;
            case OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG:
                return OpenSHC::IO::Graphics::GID_BODY_ANIMAL_BURNING_BIG;
            case OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL:
                return OpenSHC::IO::Graphics::GID_BODY_ANIMAL_BURNING_SMALL;
            default:
                return OpenSHC::IO::Graphics::GID_BODY_PEASANT;
            }
        }

    }
}
}
