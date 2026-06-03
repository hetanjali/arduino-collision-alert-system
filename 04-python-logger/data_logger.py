import serial
import csv
import time
from datetime import datetime

def get_alert_status(distance):
    if distance < 10:
        return "CRITICAL"
    elif distance < 20:
        return "DANGER"
    elif distance < 40:
        return "WARNING"
    else:
        return "SAFE"

def log_serial_data(port='/dev/ttyUSB0', 
                    baud=9600, 
                    filename="sensor_log.csv"):
    """
    Reads real Arduino serial data and logs to CSV
    port = your Arduino's USB port
    baud = must match Serial.begin(9600) in Arduino code
    """
    print(f"Connecting to Arduino on {port}...")
    
    try:
        ser = serial.Serial(port, baud, timeout=1)
        print("Connected! Logging data...")
        
        with open(filename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Timestamp", 
                           "Distance_cm", 
                           "Alert_Status"])
            
            while True:
                line = ser.readline().decode('utf-8').strip()
                
                if "Distance:" in line:
                    # Parse "Distance: 25 cm"
                    distance = float(line.split(":")[1]
                                   .replace("cm","").strip())
                    timestamp = datetime.now().strftime(
                                "%Y-%m-%d %H:%M:%S")
                    status = get_alert_status(distance)
                    
                    writer.writerow([timestamp, 
                                   distance, 
                                   status])
                    print(f"{timestamp} | "
                          f"{distance}cm | {status}")
                    
    except KeyboardInterrupt:
        print("\nLogging stopped!")
    except serial.SerialException:
        print(f"Could not connect to {port}")
        print("Run simulate_arduino.py instead!")

if __name__ == "__main__":
    log_serial_data()