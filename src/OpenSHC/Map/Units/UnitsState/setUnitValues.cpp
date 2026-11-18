#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053B8E0
        void UnitsState::setUnitValues(int unitID, UnitType unitType)
        {
            this->units[unitID].unitType = unitType;
            this->units[unitID].field_0x90 = DAT_UnitPropertiesDefinedData::instance.field_0x7634[unitType];
            this->units[unitID].isStalked = DAT_UnitPropertiesDefinedData::instance.field_0x7774[unitType];
            this->units[unitID].gmIDUnk = DAT_UnitPropertiesDefinedData::instance.SPRITE_ID[unitType];
            this->units[unitID].spriteID = this->units[unitID].gmIDUnk;
            this->units[unitID].gfxNumber = 1;
            this->units[unitID].field_0x2a = DAT_TextureRenderCoreObject::instance
                                                 .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                                 .originX;
            this->units[unitID].unknownV = DAT_TextureRenderCoreObject::instance
                                               .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                               .originY;
            this->units[unitID].spriteWidthUnk
                = DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][0];
            this->units[unitID].spriteHeightUnk
                = DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][1];
            this->units[unitID].drawXOffset = this->units[unitID].field_0x2a - this->units[unitID].spriteWidthUnk / 2;
            this->units[unitID].someDrawYOffset
                = (this->units[unitID].unknownV - this->units[unitID].spriteHeightUnk) + 3;
            this->units[unitID].movementSpeed
                = DAT_UnitPropertiesDefinedData::instance.UNIT_MOVEMENT_SPEED_ARRAY[unitType];
            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            this->units[unitID].field_0x354 = 0;
            this->units[unitID].field_0x350 = 0;
            this->units[unitID].maxHealth = DAT_UnitPropertiesDefinedData::instance.BASE_HP[unitType];
            this->units[unitID].health = this->units[unitID].maxHealth;
            this->units[unitID].healthPercentage = this->units[unitID].maxHealth == 0
                ? 100
                : this->units[unitID].health * 100 / this->units[unitID].maxHealth;
            this->units[unitID].healthbar = this->units[unitID].healthPercentage / 10;
            this->units[unitID].unitCanClimb = DAT_UnitPropertiesDefinedData::instance.UNIT_CLIMB[unitType];
            this->units[unitID].someUnitStat4 = DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix4[unitType];
            this->units[unitID].graphicSize = DAT_UnitPropertiesDefinedData::instance.GRAPHIC_SIZE[unitType];
            this->units[unitID].someUnitStat2_meleeDamageUnk
                = DAT_UnitPropertiesDefinedData::instance.UNIT_CAN_MELEE[unitType];
            this->units[unitID].enemyNoticeFrequencyUnk
                = DAT_UnitPropertiesDefinedData::instance.UNIT_ENEMY_NOTICE_RANGE[unitType];
            this->units[unitID].moveableUnk = DAT_UnitPropertiesDefinedData::instance.UNIT_MOVABLE[unitType];
            if (this->units[unitID].firstNameIndex <= 0 || unitType == OpenSHC::Map::Units::UT_BREWER
                || unitType == OpenSHC::Map::Units::UT_TANNER || unitType == OpenSHC::Map::Units::UT_LADY
                || unitType == OpenSHC::Map::Units::UT_MOTHER || unitType == OpenSHC::Map::Units::UT_JUGGLER
                || unitType == OpenSHC::Map::Units::UT_FIREEATER || unitType == OpenSHC::Map::Units::UT_PRIEST) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(unitID);
            }
            short _owner = this->units[unitID].owner;
            if (_owner > 0) {
                this->units[unitID].occupancyOrFlag = 1 << (_owner - 1);
                this->units[unitID].field_0x3d1 = ~this->units[unitID].occupancyOrFlag;
            } else {
                this->units[unitID].occupancyOrFlag = 255;
                this->units[unitID].field_0x3d1 = 255;
            }
            this->units[unitID].isSelectable_OR_matchTime = 0;
            this->units[unitID].field_0x430 = 0;
            if (unitType != OpenSHC::Map::Units::UT_CAGEDOG) {
                this->units[unitID].unknownBool01 = 500;
            }
            if (unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                this->units[unitID].assassinsMicroDistanceToEnemyUnk = 32000;
            }
        }

    }
}
}
