#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // travelledDistance is compared as a signed short (orig `cmp cx, imm; jge` from 0x406FE2).
    // FUNCTION: STRONGHOLDCRUSADER 0x00406FD0
    void Entities::UpdateEntityType8()
    {
        short travelledDistance
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].travelledDistance;
        if (travelledDistance < 14) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 8;
        } else if (travelledDistance < 16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 9;
        } else if (travelledDistance < 18) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 10;
        } else if (travelledDistance < 20) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 11;
        } else if (travelledDistance < 22) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 12;
        } else if (travelledDistance < 24) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 13;
        } else if (travelledDistance < 26) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 14;
        } else if (travelledDistance < 28) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 15;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 16;
        }
        if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 3) == 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += 16;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            MACRO_CALL(OpenSHC::Map::Entities_Func::SomeFireSpreadFunction)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                DAT_TileMapState::instance
                        .HeightLayer[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]
                    + 8,
                5);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition,
                OpenSHC::DE::SHCDE::FX_FIRE_START);
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 76) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 60;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
    }

}
}
