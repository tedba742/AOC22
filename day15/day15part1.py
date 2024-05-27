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

def count_non_beacon_positions(sensors, row_y):
    covered_positions = set()
    beacon_positions = set()
    
    for (sensor_x, sensor_y), (beacon_x, beacon_y) in sensors:
        distance = manhattan_distance(sensor_x, sensor_y, beacon_x, beacon_y)
        
        # Record beacon positions to exclude them from the final count
        if beacon_y == row_y:
            beacon_positions.add(beacon_x)
        
        if abs(sensor_y - row_y) <= distance:
            reach = distance - abs(sensor_y - row_y)
            for x in range(sensor_x - reach, sensor_x + reach + 1):
                covered_positions.add(x)
    
    # Remove beacon positions from covered positions
    non_beacon_positions = covered_positions - beacon_positions
    
    return len(non_beacon_positions)

if __name__ == "__main__":
    file_path = 'input.txt'
    sensors = parse_input(file_path)
    row_y = 2000000
    result = count_non_beacon_positions(sensors, row_y)
    print(f"The number of positions in row {row_y} that cannot contain a beacon is: {result}")
