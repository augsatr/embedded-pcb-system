import sys
import random
import math
import time
import json
import os
from datetime import datetime

os.system('')

class SensorSimulator:
    def __init__(self):
        self.base_temp = 25.0
        self.base_pressure = 101325.0
        self.base_humidity = 45.0
        self.tick = 0
        self.history = []

    def simulate_temperature(self):
        noise = random.uniform(-0.5, 0.5)
        drift = math.sin(self.tick / 10.0) * 0.5
        return self.base_temp + noise + drift

    def simulate_pressure(self):
        noise = random.uniform(-1.0, 1.0)
        return self.base_pressure + noise

    def simulate_humidity(self):
        noise = random.uniform(-0.25, 0.25)
        drift = math.sin(self.tick / 15.0) * 2.0
        return max(0, min(100, self.base_humidity + noise + drift))

    def simulate_accel(self):
        return (
            204 + random.randint(-10, 10),
            -102 + random.randint(-10, 10),
            16384 + random.randint(-50, 50)
        )

    def simulate_gyro(self):
        return (
            128 + random.randint(-20, 20),
            -64 + random.randint(-20, 20),
            32 + random.randint(-20, 20)
        )

    def read_sensors(self):
        self.tick += 1
        data = {
            'timestamp': self.tick,
            'time': datetime.now().strftime('%H:%M:%S'),
            'bme280': {
                'temperature': round(self.simulate_temperature(), 2),
                'pressure': round(self.simulate_pressure(), 1),
                'humidity': round(self.simulate_humidity(), 1)
            },
            'lsm6ds3': {
                'accel': self.simulate_accel(),
                'gyro': self.simulate_gyro()
            }
        }
        self.history.append(data)
        return data

    def print_header(self):
        print("\033[2J\033[H")
        print("=" * 75)
        print("        EMBEDDED PCB SYSTEM - VIRTUAL SENSOR MONITOR")
        print("=" * 75)
        print("  BME280 (I2C)              |  LSM6DS3 (SPI)")
        print("  Temp   |  Pres   |  Hum   |  Accel XYZ       |  Gyro XYZ")
        print("-" * 75)

    def print_data(self, data):
        bme = data['bme280']
        lsm = data['lsm6ds3']

        if 20 <= bme['temperature'] <= 30:
            temp_color = "\033[92m"
        else:
            temp_color = "\033[93m"
        reset = "\033[0m"

        print("  %s | %s%6.2f C%s | %7.1f Pa | %5.1f %% | %+6d,%+6d,%+6d | %+4d,%+4d,%+4d" % (
            data['time'],
            temp_color, bme['temperature'], reset,
            bme['pressure'],
            bme['humidity'],
            lsm['accel'][0], lsm['accel'][1], lsm['accel'][2],
            lsm['gyro'][0], lsm['gyro'][1], lsm['gyro'][2]
        ))

    def print_stats(self):
        if len(self.history) < 2:
            return

        temps = [d['bme280']['temperature'] for d in self.history]
        pres = [d['bme280']['pressure'] for d in self.history]
        hum = [d['bme280']['humidity'] for d in self.history]

        print("-" * 75)
        print("  AVG: T=%.2f C  P=%.1f Pa  H=%.1f %%  |  Samples: %d" % (
            sum(temps)/len(temps), sum(pres)/len(pres), sum(hum)/len(hum), len(self.history)))
        print("  MIN: T=%.2f C  P=%.1f Pa  H=%.1f %%  |  Rate: ~10 Hz" % (
            min(temps), min(pres), min(hum)))
        print("  MAX: T=%.2f C  P=%.1f Pa  H=%.1f %%  |  Status: ACTIVE" % (
            max(temps), max(pres), max(hum)))
        print("=" * 75)

    def export_json(self, filename):
        with open(filename, 'w') as f:
            json.dump(self.history, f, indent=2)
        print("\nData exported to %s" % filename)

    def run(self, duration=30):
        self.print_header()
        try:
            for i in range(duration * 10):
                data = self.read_sensors()
                if i % 10 == 0:
                    self.print_header()
                    for d in self.history[-20:]:
                        self.print_data(d)
                    self.print_stats()
                time.sleep(0.1)
        except KeyboardInterrupt:
            pass

        self.export_json('sensor_data.json')
        print("\nSimulation stopped.")

if __name__ == "__main__":
    sim = SensorSimulator()
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 30
    print("Starting virtual sensor simulation for %d seconds..." % duration)
    print("Press Ctrl+C to stop early.\n")
    time.sleep(1)
    sim.run(duration)
