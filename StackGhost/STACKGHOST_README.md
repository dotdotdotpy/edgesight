# StackGhost

StackGhost is a diagnostic stack memory scanner that detects embedded runtime markers and reacts to them in real time. It was designed for forensic-style memory inspection, with a twist.

---

## Overview

This tool simulates a scenario where a runtime leaves behind volatile markers in the stack. StackGhost:

- Scans the live stack region for a known signature.
- Validates whether a payload exists after the marker.
- Executes the payload if it matches expectations.

No heap. No globals. No files.  
Everything lives on the **stack**—temporarily.

---

## Why This Matters

Most tools inspect memory *passively*. StackGhost flips the approach:

> If the memory contains something actionable, it acts.

The stack is often considered temporary and volatile. This tool treats it as a dynamic launchpad.

---

## What It Does

1. Plants a marker (`0xDEADBEEF`) and a function pointer onto the stack.
2. Scans memory around it, byte-wise, looking for a match.
3. If found:
   - Triggers a Windows popup (`MessageBoxA`)
   - Writes a file: `hijack_success.txt`
   - Emits a beep
   - Exits abruptly (`ExitProcess(0)`)
4. If not found:
   - Dumps stack memory
   - Logs scan progression
   - Ends gracefully with fallback messaging

---

## How to Test

1. Compile with MinGW:
   ```bash
   gcc stackghost.c -o stackghost -mwindows -g -O0
   ```

2. Run:
   ```bash
   ./stackghost
   ```

3. If the hijack works:
   - A popup appears
   - A text file is created in the current directory
   - You'll hear a beep
   - The app exits early

4. If the hijack fails:
   - You'll see a memory dump
   - The log prints `[✘] Hijack did not trigger. This is a fallback line.`

---

## Files Dropped

If successful, the payload writes:
- `hijack_success.txt` → Contains `"Payload ran."`

---

## Important Notes

- Requires Windows and a terminal that doesn't kill stack data.
- Stack layout is fragile—compiler optimizations may erase or relocate payloads.
- Use `-O0` and `-g` to maintain the memory structure exactly as written.

---

## Author

Built by [`@dotdotdotpy`](https://github.com/dotdotdotpy)  
One stack. One marker. One jump.

---

## Disclaimer

This tool is for educational and diagnostic purposes only.  
You are responsible for how you run or modify this code.
