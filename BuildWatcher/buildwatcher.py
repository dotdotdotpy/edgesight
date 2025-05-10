import os
import time
import hashlib

# 👇 Hardcoded path to the build folder
WATCH_DIR = r"C:\Users\Grant Coding\Desktop\Edge\Edge\BuildWatcher"

if not os.path.exists(WATCH_DIR):
    print(f" Directory does not exist: {WATCH_DIR}")
    exit(1)

print(f"Watching build folder: {WATCH_DIR}")
print("Waiting for changes... (Ctrl+C to stop)\n")

def snapshot_folder(path):
    snap = {}
    for root, _, files in os.walk(path):
        for name in files:
            full_path = os.path.join(root, name)
            try:
                stat = os.stat(full_path)
                snap[full_path] = {
                    "mtime": stat.st_mtime,
                    "size": stat.st_size,
                    "hash": hash_file(full_path)
                }
            except Exception:
                continue
    return snap

def hash_file(path):
    h = hashlib.md5()
    try:
        with open(path, 'rb') as f:
            while True:
                chunk = f.read(8192)
                if not chunk:
                    break
                h.update(chunk)
        return h.hexdigest()
    except Exception:
        return None

def compare_snapshots(prev, curr):
    added = [f for f in curr if f not in prev]
    removed = [f for f in prev if f not in curr]
    modified = [f for f in curr if f in prev and curr[f]['hash'] != prev[f]['hash']]
    return added, removed, modified

prev_snapshot = snapshot_folder(WATCH_DIR)
silent_ticks = 0

try:
    while True:
        time.sleep(2)
        curr_snapshot = snapshot_folder(WATCH_DIR)
        added, removed, modified = compare_snapshots(prev_snapshot, curr_snapshot)

        if not added and not removed and not modified:
            silent_ticks += 1
        else:
            silent_ticks = 0

        if added:
            print(f"[+] New files: {len(added)}")
        if removed:
            print(f"[-] Deleted files: {len(removed)}")
        if modified:
            print(f"[~] Modified files: {len(modified)}")

        if silent_ticks >= 10:
            print("No changes detected for 20 seconds. Build may be stalled.")
            silent_ticks = 0

        prev_snapshot = curr_snapshot

except KeyboardInterrupt:
    print("\n Stopped watching.")
