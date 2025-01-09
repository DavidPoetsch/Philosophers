import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import re

# Define colors for each state
state_colors = {
    "thinking": "blue",
    "took fork": "grey",
    "eating": "green",
    "sleeping": "orange",
    "died": "red",
}

show_times = True

def on_key(event):
	global show_times
	if event.key == 'escape':  # Check if the pressed key is 'ESC'
			plt.close(event.canvas.figure)  # Close the figure
	elif event.key == 't':  # Toggle time deltas on 'T'
			show_times = not show_times
			plt.close(event.canvas.figure)  # Close the figure
			draw_plot()

def line_contains_keyword(line):
	if "thinking" in line :
		return True
	if "fork" in line :
		return True
	if "eating" in line :
		return True
	if "sleeping" in line :
		return True
	if "died" in line :
		return True
	return False

def parse_action(line):
	if "thinking" in line :
		return "thinking"
	if "fork" in line :
		return "took fork"
	if "eating" in line :
		return "eating"
	if "sleeping" in line :
		return "sleeping"
	if "died" in line :
		return "died"

def parse_data(filename):
	results = []
	with open(filename, 'r') as file:
			lines = file.readlines()
	for line in lines:
			line = line.strip()
			if line_contains_keyword(line):
					parts = line.split()
					ms = int(parts[0])
					philo_id = int(parts[1])
					action = parse_action(parts[-1].strip('.'))
					results.append([ms, philo_id, action])
	return results

def get_max_philo(data):
	max_philos = 0
	for timestamp, philo, state in data:
		if (philo > max_philos):
			max_philos = philo
	return int(max_philos)

def prepare_data(data, max_philos):
	philosophers = {ph: [] for ph in range(1, max_philos + 1)}
	for timestamp, philo, state in data:
		philosophers[philo].append((timestamp, state))
	for philo, events in philosophers.items():
		timestamp_end = int(events[-1][0])
		timestamp_end += 100
		end_event = (timestamp_end, events[-1][1])
		philosophers[philo].append(end_event)
	return philosophers

def format_plot(ax, max_philos):
	# Add legend
	legend_patches = [mpatches.Patch(color=color, label=state) for state, color in state_colors.items()]
	ax.legend(handles=legend_patches, title="State", loc="upper right")

	# Formatting the plot
	ax.set_xlabel("Time (ms)")
	ax.set_ylabel("Philosophers")
	ax.set_title("Dining Philosophers Problem Visualization")
	ax.set_yticks(range(1, max_philos + 1))
	ax.set_yticklabels([f"Philo {i}" for i in range(1, max_philos + 1)])
	ax.grid(True, axis="x", linestyle="--", alpha=0.7)

def show_plot():
	plt.tight_layout()
	plt.show()

def plot_data(philosophers, max_philos):
	global show_times
	# Define maximum figure size in inches
	max_width_in_inches = 10
	max_height_in_inches = 8

	# Ensure the figure size does not exceed the max dimensions
	fig, ax = plt.subplots(figsize=(min(10, max_width_in_inches), 
																	min(max_philos + 1, max_height_in_inches)), dpi=100)
	for philo, events in philosophers.items():
		for i in range(len(events) - 1):
			start_time = events[i][0]
			end_time = events[i + 1][0]
			state = events[i][1]
			duration = end_time - start_time

			ax.barh(philo, end_time - start_time, left=start_time,
							color=state_colors[state], edgecolor="black")
			if show_times:
				ax.text(start_time + duration / 2, philo, f"{duration}ms", 
								ha='center', va='center', fontsize=8, 
								color="white" if state != "thinking" else "black")

	format_plot(ax, max_philos)
	fig.canvas.mpl_connect('key_press_event', on_key)

def draw_plot():
	filename = 'out'
	data = parse_data(filename)
	max_philos = get_max_philo(data)
	philosophers = prepare_data(data, max_philos)
	plot_data(philosophers, max_philos)
	show_plot()

draw_plot()
