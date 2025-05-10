 buildwatcher.py  

Watches a build folder in real time. Tells you when something changes — or when absolutely nothing is happening (which is sometimes worse).

---

 What It’s For

Build systems break in weird ways:
- No output, no errors, just quiet failure.
- Files stop changing but the compiler says "done".
- Output shows success, but no files were actually touched.

This catches that. It watches for file activity and lets you know what’s really going on.

---
 How to Use It

1. Make a folder you want to monitor.  
   Example:
   ```
   C:\Users\YourName\Desktop\build
   ```

2. Open `buildwatcher.py` and change this line at the top:
   ```python
   WATCH_DIR = r"C:\your\folder\path\here"
   ```

3. Save and run it:
   ```bash
   python buildwatcher.py
   ```

---

 How to Test It

Once it's running:

- Add a file → `[+] New files: 1`
- Delete a file → `[-] Deleted files: 1`
- Modify a file → `[~] Modified files: 1`

If the folder goes quiet for too long:
```
No changes detected for 20 seconds. Build may be stalled.
```

You can tweak that interval if you want. It's just a counter.

---

 Notes

- No dependencies  
- One file  
- Doesn’t care what your toolchain is  
- Works on Windows, macOS, Linux

You can drop it in any CI environment or just keep it running while you're building weird things locally.

---

Author

Part of the `edgesight` collection  


– [`@dotdotdotpy`](https://github.com/dotdotdotpy)
