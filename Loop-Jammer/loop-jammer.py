import time
import sys
import threading
import traceback

# Configuration
MAX_ITERATIONS = 100000
MAX_LOOP_TIME = 0.05       # seconds per iteration
MAX_TOTAL_TIME = 15        # seconds total runtime

# Internal state
iteration_count = 0
start_time = time.time()
last_time = start_time

def check_loop_health():
    global iteration_count, last_time
    now = time.time()
    iteration_count += 1

    if iteration_count > MAX_ITERATIONS:
        print(f"\nLoopjammer: iteration count exceeded ({iteration_count})")
        sys.exit(1)

    dt = now - last_time
    if dt > MAX_LOOP_TIME:
        print(f"\nLoopjammer: iteration delay exceeded ({dt:.3f}s)")
        sys.exit(1)

    if now - start_time > MAX_TOTAL_TIME:
        print(f"\nLoopjammer: total runtime exceeded ({MAX_TOTAL_TIME}s)")
        sys.exit(1)

    last_time = now

# Example usage
if __name__ == "__main__":
    print("Loopjammer running. Simulating risky loop...\n")
    try:
        while True:
            check_loop_health()
            # Simulated task (can be replaced with real logic)
            time.sleep(0.01)
    except KeyboardInterrupt:
        print("\nStopped manually.")
