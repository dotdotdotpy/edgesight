# stackwhisper.c  

Scans the active thread’s stack for a known memory pattern and reports residual traces, useful for runtime forensics or testing memory layout behavior.

## What It Does 
 
Places marker values on the stack, then scans the surrounding stack memory region to locate those same values.  
This reveals:

- Whether local data remains intact
- If stack layout changed between function calls
- If memory was overwritten or cleaned by system/runtime

## Why It’s Interesting 
 
Most programs don’t read the stack directly, this one does.  
It treats the local call stack like a raw memory region and inspects it live.

This is **not a debugger**, and doesn’t use external tools.  
It just uses C, pointers, and timing.

## How It Works

1. Defines a known 32-bit pattern (`STACK_MAGIC`)
2. Pushes several markers onto the stack by nesting calls
3. Calculates the rough stack range by taking the highest and lowest address seen
4. Iterates that range in `int`-sized chunks, checking for the marker pattern
5. Reports how many matches were found and whether it was a full match

## How To Compile

If you’re using GCC:

```bash
gcc stackwhisper.c -o stackwhisper
```

## How To Run

```bash
./stackwhisper
```

Example output:
```
=== stackwhisper ===

Marker placed at: 0x0061FEEC
Marker placed at: 0x0061FEDC
Marker placed at: 0x0061FECC
[stackwhisper] Scanning stack region: 0x0061FECC - 0x0061FEEC

Found STACK_MAGIC at: 0x0061FECC
Found STACK_MAGIC at: 0x0061FEDC

Checked 8 memory words, found 2 marker(s).
Partial match. Possible overwrite or movement.
```

## What To Look For

- `Partial match`: Likely a change in layout or overwritten memory
- `No matches`: System cleaned stack space before scan
- `Full match`: Markers are exactly where they were expected

## Notes

- Works best with optimizations **disabled**
- Adding more function layers increases marker spacing
- Only works in single-threaded contexts

---

Crafted for environments where memory layout matters.  
Tested on GCC (MinGW), no external dependencies.
