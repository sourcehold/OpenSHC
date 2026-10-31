#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B3E0
    void Version::UpgradeMapUnitsTo_UnknownVersion1()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType != Units::UT_CHILD) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].spriteID
                        = (short)DAT_UnitPropertiesDefinedData::instance
                              .SPRITE_ID[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitCanClimb
                    = (short)DAT_UnitPropertiesDefinedData::instance
                          .UNIT_CLIMB[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].someUnitStat4
                    = (short)DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix4
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field22_0x2a
                    = (short)DAT_TextureRenderCoreObject::instance
                          .gmFileHeaderColorpaletteArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .spriteID]
                          .originX;
                // Only the lower half of unknownV is written
                *(short*)&DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV
                    = (short)DAT_TextureRenderCoreObject::instance
                          .gmFileHeaderColorpaletteArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .spriteID]
                          .originY;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].drawXOffset
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field22_0x2a
                    - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].spriteWidthUnk / 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                    = *(short*)&DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV
                    - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].spriteHeightUnk + 3;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].graphicSize
                    = (short)DAT_UnitPropertiesDefinedData::instance
                          .GRAPHIC_SIZE[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].enemyNoticeFrequencyUnk
                    = DAT_UnitPropertiesDefinedData::instance.UNIT_ENEMY_NOTICE_RANGE
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveableUnk
                    = (short)DAT_UnitPropertiesDefinedData::instance
                          .UNIT_MOVABLE[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
            }
        }
    }

}
}
