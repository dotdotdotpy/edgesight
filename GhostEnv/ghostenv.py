import os
import sys
import site
import platform
import subprocess
from pathlib import Path

print("Checking Python environment...\n")

# Step 1: Python executable and version
print("Python Executable:", sys.executable)
print("Python Version:", sys.version.split()[0])

# Step 2: Detect virtual environment status
in_venv = (
    hasattr(sys, 'real_prefix') or
    (hasattr(sys, 'base_prefix') and sys.base_prefix != sys.prefix)
)

if in_venv:
    print("Virtual environment: active")
else:
    print("Virtual environment: not detected")

# Step 3: Site-packages source
print("\nSite-packages directories:")
for d in site.getsitepackages():
    print(" -", d)

# Step 4: Check for .env file in current dir
env_path = Path(".env")
if env_path.exists():
    print("\n.env file found in current directory:")
    with env_path.open() as f:
        for line in f:
            if "=" in line:
                print(" ", line.strip())
else:
    print("\nNo .env file in current directory.")

# Step 5: Check key environment variables
print("\nEnvironment variables of interest:")
for var in ['PYTHONPATH', 'VIRTUAL_ENV', 'PIP_REQUIRE_VIRTUALENV']:
    val = os.environ.get(var)
    if val:
        print(f"{var} = {val}")

# Step 6: Shadowed module detection
print("\nScanning for shadowed standard modules:")
shadowed = []
std_libs = ['json', 'random', 'os', 'sys']
for lib in std_libs:
    try:
        mod = __import__(lib)
        mod_path = getattr(mod, '__file__', None)
        if mod_path and not mod_path.startswith(sys.prefix):
            shadowed.append((lib, mod_path))
    except Exception:
        continue

if shadowed:
    print("Potential shadowing detected:")
    for lib, path in shadowed:
        print(f" - {lib}: {path}")
else:
    print("No shadowed core modules found.")

print("\nDone.")
