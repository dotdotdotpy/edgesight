# loopjammer.py  

*Watch your loops. Quietly.*

This tool monitors a loop's behavior in real time — and shuts it down if it runs too long, spins too fast, or never ends.

---

 What It Does

- Tracks how long a loop runs
- Tracks how many times it iterates
- Measures the time between each cycle
- If it crosses a threshold, it exits — intentionally

No dependencies. No stacktrace spam. Just control.

---

 How to Use It

1. Drop `loopjammer.py` into your project
2. Import the `check_loop_health()` function, or run it standalone
3. Insert `check_loop_health()` inside any `while` or `for` loop you don’t fully trust

Example:
```python
from loopjammer import check_loop_health

while True:
    check_loop_health()
    run_something()
```

---

 Default Thresholds

Inside the script:

```python
MAX_ITERATIONS = 100000      # Max number of loop passes
MAX_LOOP_TIME = 0.05         # Max seconds allowed per iteration
MAX_TOTAL_TIME = 15          # Max total runtime in seconds
```

You can adjust these at the top of the file.  
If any limit is hit, the script prints a reason and exits with code `1`.

---

 Testing It

You can run the script directly to simulate a risky loop:
```bash
python loopjammer.py
```

After 15 seconds, it will exit:
```
Loopjammer: total runtime exceeded (15s)
```

---

 Why Use This?

Some bugs don’t crash.  
They just loop forever.  
`loopjammer.py` exists to catch those — silently, reliably, and without waiting for your IDE to freeze.

---

 Author

Part of the `edgesight` collection.  


— [`@dotdotdotpy`](https://github.com/dotdotdotpy)
