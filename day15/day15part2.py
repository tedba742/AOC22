def parse_input(file_path):
    sensors = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(': ')
            sensor_part = parts[0].replace('Sensor at ', '')
            beacon_part = parts[1].replace('closest beacon is at ', '')
            
            sensor_x_str, sensor_y_str = sensor_part.split(', ')
            sensor_x = int(sensor_x_str.replace('x=', ''))
            sensor_y = int(sensor_y_str.replace('y=', ''))
            
            beacon_x_str, beacon_y_str = beacon_part.split(', ')
            beacon_x = int(beacon_x_str.replace('x=', ''))
            beacon_y = int(beacon_y_str.replace('y=', ''))
            
            sensors.append(((sensor_x, sensor_y), (beacon_x, beacon_y)))
    
    return sensors

def manhattan_distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

def is_position_covered(x, y, sensors):
    for (sensor_x, sensor_y), (beacon_x, beacon_y) in sensors:
        distance = manhattan_distance(sensor_x, sensor_y, beacon_x, beacon_y)
        if manhattan_distance(sensor_x, sensor_y, x, y) <= distance:
            return True
    return False

def find_distress_beacon(sensors, max_coord):
    for (sensor_x, sensor_y), (beacon_x, beacon_y) in sensors:
        distance = manhattan_distance(sensor_x, sensor_y, beacon_x, beacon_y)
        # Check the boundary positions
        for dx in range(-distance-1, distance+2):
            for dy in [-distance-1 + abs(dx), distance+1 - abs(dx)]:
                x = sensor_x + dx
                y = sensor_y + dy
                if 0 <= x <= max_coord and 0 <= y <= max_coord:
                    if not is_position_covered(x, y, sensors):
                        tuning_frequency = x * 4000000 + y
                        return (x, y), tuning_frequency

    return None, None  # no valid position is found

if __name__ == "__main__":
    file_path = 'input.txt'
    sensors = parse_input(file_path)
    max_coord = 4000000
    (distress_beacon_position, tuning_frequency) = find_distress_beacon(sensors, max_coord)
    if distress_beacon_position:
        print(f"The tuning frequency for the distress beacon is: {tuning_frequency}")
    else:
        print("No valid position for the distress beacon found.")
