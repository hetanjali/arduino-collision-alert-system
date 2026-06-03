import random
import time
import csv
from datetime import datetime
import matplotlib.pyplot as plt
import pandas as pd

def simulate_distance():
    """Simulate ultrasonic sensor readings"""
    # Randomly vary distance between 5-60cm
    return round(random.uniform(5, 60), 2)

def get_alert_status(distance):
    """Same logic as Arduino code"""
    if distance < 10:
        return "CRITICAL"
    elif distance < 20:
        return "DANGER"
    elif distance < 40:
        return "WARNING"
    else:
        return "SAFE"

def log_data(filename="sensor_log.csv", duration=10):
    """
    Log simulated sensor data to CSV
    duration = how many seconds to log
    """
    print("Starting data logger...")
    print("Timestamp | Distance | Status")
    print("-" * 40)
    
    # Create CSV file with headers
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Timestamp", "Distance_cm", "Alert_Status"])
        
        start_time = time.time()
        
        while time.time() - start_time < duration:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            distance = simulate_distance()
            status = get_alert_status(distance)
            
            # Write to CSV
            writer.writerow([timestamp, distance, status])
            
            # Print to terminal
            print(f"{timestamp} | {distance}cm | {status}")
            
            time.sleep(0.5)  # Read every 500ms like Arduino
    
    print(f"\nData saved to {filename}")
    return filename

def plot_data(filename="sensor_log.csv"):
    """Generate a graph from logged data"""
    df = pd.read_csv(filename)
    
    plt.figure(figsize=(10, 6))
    plt.plot(df.index, df['Distance_cm'], 
             color='blue', linewidth=2, label='Distance')
    
    # Add alert zone lines
    plt.axhline(y=10, color='red', 
                linestyle='--', label='CRITICAL (<10cm)')
    plt.axhline(y=20, color='orange', 
                linestyle='--', label='DANGER (<20cm)')
    plt.axhline(y=40, color='yellow', 
                linestyle='--', label='WARNING (<40cm)')
    
    plt.title('Collision Alert System — Distance Log')
    plt.xlabel('Reading Number')
    plt.ylabel('Distance (cm)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('distance_graph.png')
    plt.show()
    print("Graph saved as distance_graph.png")

if __name__ == "__main__":
    # Step 1: Log data for 10 seconds
    filename = log_data(duration=10)
    
    # Step 2: Plot the data
    plot_data(filename)