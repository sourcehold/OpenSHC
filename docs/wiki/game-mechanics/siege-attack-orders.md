# Siege engines and attack orders

Catapults and trebuchets use a special branch when their group receives an order
to attack an enemy unit. The branch turns that order into an attack at the
target's location. Unlike the adjacent ground and wall attack branches, it does
not call `UnitsState::makeUnitStopWalkingByClearingPathProgressState` first.
If an engine was already walking, its old path can therefore remain active after
the new attack order.

Other tested ranged unit types use different command branches. An attack on
ground, an attack on a wall, and a stop order do call the existing path cleanup.
The cleanup clears path progress; the normal movement update still decides when
the current step ends. Aiming, ammunition and projectile release belong to later
unit behavior, not to the group command itself.

This describes the **original** game. Calling the cleanup in the catapult and
trebuchet enemy-unit branch would be a gameplay correction, not a faithful
reconstruction of that branch.

## Existing names and evidence

The relevant names already exist in `TribesState.hpp`, `UnitInstructionType.hpp`
and `UnitsState.hpp`. `TribesState::giveTribeAnInstruction` handles
`UIT_UNIT_ATTACK_UNIT` (4), `UIT_ATTACK_LAND` (5) and `UIT_STOP` (31). The path
cleanup is `UnitsState::makeUnitStopWalkingByClearingPathProgressState`.
No generated headers, function implementations or address mappings change here.

The command dispatcher and its adjacent branches were inspected in the original
SHC 1.41 executable (SHA-256
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`).
The corresponding Crusader Extreme binary and EFIGS/Polish executable variants
have the same checked branch behavior. Native instruction tests executed 144
paired original and corrected group commands across those six fixtures,
including catapult, trebuchet and other-unit controls. They check the path
cleanup call count, affected unit-record fields and command ABI. These are
instruction observations; they are not a claim of in-game aiming or firing
validation, a full OpenSHC build or a reccmp match.
