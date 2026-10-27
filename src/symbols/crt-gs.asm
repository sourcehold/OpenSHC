; Point MSVC's /GS machinery at the game's own stack cookie.
;
; With /GS every protected function emits `mov eax, [__security_cookie]` in its prologue and
; `call __security_check_cookie` in its epilogue. The original binary reads its cookie from
; 0x00B94220, so as long as our DLL links the CRT's own `__security_cookie` variable, every
; single /GS-protected function differs from the original in its very first instruction.
;
; Declaring the symbol as an absolute here makes the reference assemble to the literal
; address 0x00B94220 instead of a relocation into our own .data, which reproduces the
; original instruction exactly. It also means the value we check against is the cookie the
; game itself is already using - which is required for correctness, not only for matching,
; because our frames are unwound by the same process.
;
; `__security_init_cookie` must be stubbed out along with it. It lives in the same CRT object
; as `__security_cookie` (LIBCMT's gs_cookie.obj), so defining only the cookie gives
; LNK2005; and if the real one did run it would generate a fresh random cookie and store it
; to 0x00B94220, destroying the value every already-live game stack frame will check on
; return. The game initialises the cookie in its own startup long before we are injected, so
; for us the correct initialisation is to do nothing.

; `__security_cookie_complement` has to come along as the third symbol in that same CRT
; object - leaving it undefined pulls gs_cookie.obj back in on its own and the duplicate
; definition returns. 0x00B94224 is where the game keeps it, directly after the cookie.
;
; `__security_check_cookie` is deliberately NOT redirected. The game's copy lives at
; 0x0057F755, but the epilogue reference is a relative call, and a relative displacement
; computed at link time into a fixed foreign address is only correct while our DLL loads
; at its preferred base - it cannot be relocated. Our own copy is functionally identical,
; and a differing call target is what reccmp's normalized percentage already forgives.

.386
.model flat

PUBLIC ___security_cookie

___security_cookie EQU 00B94220h

PUBLIC ___security_cookie_complement

___security_cookie_complement EQU 00B94224h

_TEXT SEGMENT

PUBLIC ___security_init_cookie

___security_init_cookie PROC
    ret
___security_init_cookie ENDP

_TEXT ENDS

END
