import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import re


# Function to parse the data from a file
def parse_data_from_file(filename):
    with open(filename, 'r') as file:
        input_data = file.read()

    # Regular expression to match the relevant lines
    pattern = r'(\d+): Philo (\d+) is (\w+)'

    # Find all matches in the input data
    matches = re.findall(pattern, input_data)

    # Convert the matches into the desired format
    data = [(int(timestamp), int(philo), action) for timestamp, philo, action in matches]

    return data

filename = '../../out'  # Replace with the actual filename
data = parse_data_from_file(filename)

# Define colors for each state
state_colors = {
    "thinking": "blue",
    "eating": "green",
    "sleeping": "orange",
}

# Prepare data for visualization
philosophers = {ph: [] for ph in range(1, 6)}
for timestamp, philo, state in data:
    philosophers[philo].append((timestamp, state))

# Plot the data
fig, ax = plt.subplots(figsize=(10, 6))

for philo, events in philosophers.items():
    for i in range(len(events) - 1):
        start_time = events[i][0]
        end_time = events[i + 1][0]
        state = events[i][1]
        ax.barh(philo, end_time - start_time, left=start_time, color=state_colors[state], edgecolor="black")

# Add legend
legend_patches = [mpatches.Patch(color=color, label=state) for state, color in state_colors.items()]
ax.legend(handles=legend_patches, title="State", loc="upper right")

# Formatting the plot
ax.set_xlabel("Time (ms)")
ax.set_ylabel("Philosophers")
ax.set_title("Dining Philosophers Problem Visualization")
ax.set_yticks(range(1, 6))
ax.set_yticklabels([f"Philo {i}" for i in range(1, 6)])
ax.grid(True, axis="x", linestyle="--", alpha=0.7)

# Show the plot
plt.tight_layout()
plt.show()
