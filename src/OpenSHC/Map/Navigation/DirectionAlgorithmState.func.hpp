/**
  path: 'OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp'
*/

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.hpp"
namespace OpenSHC {
namespace Map {
    namespace Navigation {
        namespace DirectionAlgorithmState_Func {

            MACRO_FUNCTION_RESOLVER(int (DirectionAlgorithmState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004092C0,
                &DirectionAlgorithmState::computeHealthPercentage)
            computeHealthPercentage;

            MACRO_FUNCTION_RESOLVER(void (DirectionAlgorithmState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0046C920, &DirectionAlgorithmState::calculateOrientation)
            calculateOrientation;

            MACRO_FUNCTION_RESOLVER(void (DirectionAlgorithmState::*)(int, int), false,
                Address::SHC_3BB0A8C1_0x0046C9A0, &DirectionAlgorithmState::calculateOrientationBetweenTiles)
            calculateOrientationBetweenTiles;

            MACRO_FUNCTION_RESOLVER(void (DirectionAlgorithmState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0046C9E0, &DirectionAlgorithmState::calculatePreferredRelativeOrientation)
            calculatePreferredRelativeOrientation;

            MACRO_FUNCTION_RESOLVER(void (DirectionAlgorithmState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0046CAA0, &DirectionAlgorithmState::computeOrientationToTarget)
            computeOrientationToTarget;

            MACRO_FUNCTION_RESOLVER(int (DirectionAlgorithmState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0046CC80, &DirectionAlgorithmState::setAxisBasedDistanceResult)
            setAxisBasedDistanceResult;

            MACRO_FUNCTION_RESOLVER(undefined (DirectionAlgorithmState::*)(), false, Address::SHC_3BB0A8C1_0x0046CCD0,
                &DirectionAlgorithmState::getMouseVectorLengthBasedOnDirection)
            getMouseVectorLengthBasedOnDirection;

            MACRO_FUNCTION_RESOLVER(uint (DirectionAlgorithmState::*)(int, int*), false,
                Address::SHC_3BB0A8C1_0x0046CD30, &DirectionAlgorithmState::computeHash)
            computeHash;

            MACRO_FUNCTION_RESOLVER(uint (DirectionAlgorithmState::*)(int, uint*, uint), false,
                Address::SHC_3BB0A8C1_0x0046CDF0, &DirectionAlgorithmState::computeMaskedRotatingHash)
            computeMaskedRotatingHash;

        } // namespace DirectionAlgorithmState_Func
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
