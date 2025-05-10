# edgesight  

Tools for catching what your runtime won't.

This is a small, focused collection of standalone developer tools. Each one is built to spot quiet failures, runtime ghosts, and edge-case bugs that normal toolchains ignore.

No dependencies. No setup. Just code that watches back.

---

## Included Tools

#### ▸ [BuildWatcher](./BuildWatcher)
Monitors a build folder in real time. Tells you if nothing is happening — which is sometimes worse than errors.

#### ▸ [GhostEnv](./GhostEnv)
Scans your Python environment for contamination. Flags dangerous overrides, poisoned paths, and shadowed modules.

#### ▸ [Loop-Jammer](./Loop-Jammer)
Detects infinite or slow-burning loops based on real-time behavior. Insert into any loop to force runtime awareness.

#### ▸ [StackWhisper](./StackWhisper)
Scans your program's active stack for known memory markers and reveals residual stack state. Great for low-level memory layout analysis and forensic-style inspection.

---

## Philosophy

Each tool in this collection:

- Solves a real-world dev issue that isn't obvious or easy to trace
- Requires no external libraries or setup
- Is self-contained, surgical, and readable
- Is designed to act fast and fail clean

Use them if you’ve ever thought:

> “Why is this working… but still wrong?”

---

## Author

Built by [`@dotdotdotpy`](https://github.com/dotdotdotpy)  
Each file stands alone. Together, they form a surface monitor for real software.
