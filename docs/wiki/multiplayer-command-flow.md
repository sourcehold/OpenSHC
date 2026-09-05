# Multiplayer command ownership and replay boundaries

This note records original-code evidence from Crusader 1.41, SHA-256
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`.
Addresses refer to that executable. Generated names help navigation; the original
instructions establish behavior. No multiplayer match was run for this analysis.

## From transport to simulation

1. `queueCommand` (`0x489100`) builds a command in a 200-entry ring. Each entry is
   `0x4F8` bytes, with tick at offset 0, sender handle at 4, category at 8, state
   at 9 and parameters at 10. The handler participates in both serialization
   and execution; invoking it does not necessarily mean the command executed.
2. `transmitCommand` (`0x487C50`) serializes the low **three bytes** of the tick
   after the category byte. The generated `Packet` labels divide this into
   `short time` and `byte unknown`, but the native copy at `0x46A830` writes all
   three bytes of the timestamp. Payloads above 200 bytes normally use envelope
   category 125; category 65 has a separate exception. Most commands use
   guaranteed DirectPlay delivery; categories 12 and 117 have special handling.
3. `receiveAllTransmittedCommands` (`0x490690`) unwraps category 125 and zeroes a
   32-bit tick before copying those three bytes into it. DirectPlay system
   messages, synchronization packets and ordinary commands take different paths.
   Host migration and player removal are processed here, outside timed dispatch.
4. `scheduleReceivedCommand` (`0x480210`) invokes the handler in receive/parse
   mode. Timed payloads go into the ring. Commands with signed time <= 0 copy to
   the fixed parameter area and execute immediately at `0x480425`, then clear
   their temporary ring entry. They never reach `processWaitingCommands`.
5. `getCommandIDFromCommandSelectionStuff` (`0x480440`) selects due, unprocessed
   entries, with a batch cap of 100. It translates sender handles and stably
   orders the selected entries by logical player slot. A recorder must observe
   actual dispatch order; transport arrival order is insufficient.
6. `processWaitingCommands` (`0x4892F0`) translates each sender again, sets the
   execution action/parameter state, calls the handler and marks the entry
   processed. The translator is `0x47EAF0`, reimplemented by this contribution.

The timestamp is thus 24-bit on the wire and 32-bit in the ring. The examined
receive routine does not reconstruct a higher epoch. Long-duration recording
and replay must preserve that distinction rather than assuming identical wire
and internal formats. This observation does not establish a reproduced wrap bug.

## Why one save and a timed-command log are insufficient

The original save section table does not cover active mode or the full network
handle array. It does cover a saved mode copy, AI-slot values and local player
slot. The single-player load-dialog path (`0x4950B0`) clears network handles and
recreates the local entry. Multiplayer playback therefore needs explicit roster
restoration and command ownership, not merely a changed mode flag or slot zero.

`queueSynchronizedAutosaveProtocol` (`0x48C660`) uses host wall-clock elapsed time,
then queues a save command carrying the simulation tick and a unit checksum.
`checkGameSync` (`0x48CB00`) compares peer evidence and starts the resync state
machine. `recomputeHashesAndSendResync` (`0x48CC90`) hashes selected game arrays;
`sendPendingResyncCommandsInBudget` (`0x48E680`) sends mismatching sections in
bounded batches, retaining its category/item position between calls. These
include units, buildings, player data and tile-map regions. Resync replaces
simulation data; treating every immediate command as presentation-only is wrong.

A useful recorder must account separately for timed command execution, immediate
state-changing commands, roster/host transitions and resync transfers. Reliable
transport delivery alone cannot restore missing replay state or make
frame/audio-driven RNG calls deterministic. An extension's ordinary save
integration also does not demonstrate integration with native resync transfers.

## Validation scope

The accompanying player-identity checker compiles and executes the actual C++
function against the originals in both variants. It covers last-match semantics,
sentinels, missing handles, relocated receivers and the retained ECX value.
Other routines in this note were inspected in the named Ghidra project and
original assembly; they are not newly reimplemented or live-validated here.
See [reproduction instructions](../../tools/reimplementation-tests/PLAYER-IDENTITY.md).
