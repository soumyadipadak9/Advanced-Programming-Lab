import random
import time
import plotly.graph_objects as go

# ---------------- Linear Search ----------------
def linear_search(arr, key):
    for i in range(len(arr)):
        if arr[i] == key:
            return i
    return -1

# ---------------- Binary Search ----------------
def binary_search(arr, key):
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == key:
            return mid

        elif arr[mid] < key:
            low = mid + 1

        else:
            high = mid - 1

    return -1


# Input Sizes
sizes = [100, 500, 1000, 5000, 10000]

linear_best = []
linear_avg = []
linear_worst = []

binary_best = []
binary_avg = []
binary_worst = []

REPEAT = 1000

for n in sizes:

    arr = list(range(1, n + 1))

    # ---------------- Linear Best ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        linear_search(arr, 1)

    end = time.perf_counter()

    linear_best.append((end - start) * 1000)

    # ---------------- Linear Average ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        linear_search(arr, arr[n // 2])

    end = time.perf_counter()

    linear_avg.append((end - start) * 1000)

    # ---------------- Linear Worst ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        linear_search(arr, -1)

    end = time.perf_counter()

    linear_worst.append((end - start) * 1000)

    # ---------------- Binary Best ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        binary_search(arr, arr[(n - 1) // 2])

    end = time.perf_counter()

    binary_best.append((end - start) * 1000)

    # ---------------- Binary Average ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        binary_search(arr, arr[random.randint(0, n - 1)])

    end = time.perf_counter()

    binary_avg.append((end - start) * 1000)

    # ---------------- Binary Worst ----------------
    start = time.perf_counter()

    for _ in range(REPEAT):
        binary_search(arr, -1)

    end = time.perf_counter()

    binary_worst.append((end - start) * 1000)

# ---------------- Result Table ----------------

print("\nExecution Time (Milliseconds)\n")

print("Input\tLinear Best\tLinear Avg\tLinear Worst\tBinary Best\tBinary Avg\tBinary Worst")

for i in range(len(sizes)):
    print(
        f"{sizes[i]}\t"
        f"{linear_best[i]:.4f}\t\t"
        f"{linear_avg[i]:.4f}\t\t"
        f"{linear_worst[i]:.4f}\t\t"
        f"{binary_best[i]:.4f}\t\t"
        f"{binary_avg[i]:.4f}\t\t"
        f"{binary_worst[i]:.4f}"
    )

# ---------------- Plotly Graph ----------------

fig = go.Figure()

fig.add_trace(go.Scatter(
    x=sizes,
    y=linear_best,
    mode='lines+markers',
    name='Linear Best'
))

fig.add_trace(go.Scatter(
    x=sizes,
    y=linear_avg,
    mode='lines+markers',
    name='Linear Average'
))

fig.add_trace(go.Scatter(
    x=sizes,
    y=linear_worst,
    mode='lines+markers',
    name='Linear Worst'
))

fig.add_trace(go.Scatter(
    x=sizes,
    y=binary_best,
    mode='lines+markers',
    name='Binary Best'
))

fig.add_trace(go.Scatter(
    x=sizes,
    y=binary_avg,
    mode='lines+markers',
    name='Binary Average'
))

fig.add_trace(go.Scatter(
    x=sizes,
    y=binary_worst,
    mode='lines+markers',
    name='Binary Worst'
))

fig.update_layout(
    title="Linear Search vs Binary Search",
    xaxis_title="Input Size",
    yaxis_title="Execution Time (Milliseconds)",
    template="plotly_white"
)

fig.show()