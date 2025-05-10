# ghostenv.py  

*Find the weirdness in your Python environment.*

This script scans for signs of a "contaminated" or misconfigured Python environment — the kind that causes bugs without throwing errors.

 What It Checks

- Whether you're inside a virtual environment
- Where your `site-packages` are coming from
- If there's a `.env` file quietly altering variables
- Suspicious or dangerous environment variables like `PYTHONPATH`
- Shadowed core modules (`json`, `random`, `os`, `sys`, etc.)

 How to Use

1. Drop `ghostenv.py` into any Python project folder.
2. Open the script and run it:
   ```bash
   python ghostenv.py
   ```
3. Read the output. It'll tell you if you're pulling packages from global Python, overriding core imports, or running without a proper `venv`.

---

Typical Clean Output

- Python executable and version info
- Confirms virtualenv usage
- Lists where `site-packages` are loaded from
- Warns about `.env` files or shadowed modules
- Flags `PYTHONPATH` if it's set

---

 Why Use This?

Python environments fail in subtle ways.  
You don’t need a bug to have a broken setup — you just need a rogue path, a shadowed file, or one global install leaking into another.

Run `ghostenv.py` when:
- Things act weird and nothing makes sense
- You're about to deploy something
- You’re cloning someone else’s repo and want to know what you're standing on

---

💻 Author

Part of the `edgesight` collection.  


— [`@dotdotdotpy`](https://github.com/dotdotdotpy)
