#!/usr/bin/env bash
# Initialise or repair a wine prefix so the bundled MSVC 2005 toolchain can compile with /Zi.
#
# cl.exe /Zi talks to mspdbsrv.exe over RPC with NTLM authentication. Under wine that needs
# samba's ntlm_auth and the SamSs service (lsass.exe) registered in the prefix. Without SamSs,
# every /Zi compile fails with the misleading
#   fatal error C1902: Program database manager mismatch; please check your installation
#
# SamSs is registered by wine.inf's DefaultInstall, which wineboot runs *after* the
# "install Wine Mono?" prompt. When that dialog never appears (seen on Wayland), wineboot
# hangs and SamSs is never registered. Disabling mscoree/mshtml skips the Mono/Gecko prompts.
#
# Usage: tools/wine-prefix-setup.sh        (honours WINEPREFIX, default ~/.wine)

set -u

PREFIX="${WINEPREFIX:-$HOME/.wine}"
export WINEPREFIX="$PREFIX"
export WINEDEBUG="${WINEDEBUG:--all}"

if ! command -v wine >/dev/null 2>&1; then
    echo "[ERROR] wine not found in PATH." >&2
    exit 1
fi
if ! command -v ntlm_auth >/dev/null 2>&1; then
    echo "[WARN] ntlm_auth not found: install samba (it provides ntlm_auth), /Zi compiles need it." >&2
fi

echo "[INFO] Prefix: $PREFIX"

# A stuck wineboot leaves orphaned processes (rundll32 setupapi, control.exe install_mono,
# services.exe, ...) that survive even after their wineserver is gone. Clear them first.
echo "[INFO] Stopping wineserver and orphaned wine processes..."
wineserver -k 2>/dev/null
sleep 2
pkill -9 -f 'C:\\windows\\system32\\' 2>/dev/null
pkill -9 -f 'C:\\windows\\syswow64\\' 2>/dev/null
sleep 1

echo "[INFO] Running wineboot -u with Mono/Gecko prompts disabled..."
LOG="$(mktemp -t wineboot.XXXXXX.log)"
if ! WINEDLLOVERRIDES="mscoree=;mshtml=" timeout 300 wineboot -u >"$LOG" 2>&1; then
    echo "[ERROR] wineboot -u failed or timed out after 300s. Last output ($LOG):" >&2
    tail -n 20 "$LOG" >&2
    wineserver -k 2>/dev/null
    exit 1
fi
wineserver -k 2>/dev/null
sleep 2

if grep -q -i '\\Services\\\\SamSs\]' "$PREFIX/system.reg" 2>/dev/null; then
    echo "[OK] SamSs service is registered. /Zi compiles should work."
else
    echo "[ERROR] SamSs service is still missing from $PREFIX/system.reg." >&2
    exit 1
fi
