import re
from collections import deque, defaultdict, namedtuple

class Valve:
    def __init__(self, flow_rate, tunnels):
        self.flow_rate = flow_rate
        self.tunnels = tunnels

def parse_input(filename):
    valves = {}
    with open(filename, 'r') as file:
        for line in file:
            match = re.match(r"Valve (\w\w) has flow rate=(\d+); tunnels? leads? to valves? (.+)", line)
            if match:
                valve_id = match.group(1)
                flow_rate = int(match.group(2))
                tunnels = match.group(3).split(", ")
                valves[valve_id] = Valve(flow_rate, tunnels)
    return valves

def bfs(valves, start_valve, total_minutes):
    State = namedtuple('State', ['current_valve', 'minutes_remaining', 'opened', 'pressure_released'])
    initial_state = State(current_valve=start_valve, minutes_remaining=total_minutes, opened=frozenset(), pressure_released=0)
    
    queue = deque([initial_state])
    visited = set()
    max_pressure = 0
    
    while queue:
        state = queue.popleft()
        
        if (state.current_valve, state.minutes_remaining, state.opened) in visited:
            continue
        
        visited.add((state.current_valve, state.minutes_remaining, state.opened))
        
        max_pressure = max(max_pressure, state.pressure_released)
        
        if state.minutes_remaining <= 0:
            continue
        
        valve = valves[state.current_valve]
        
        # Option to open the valve
        if state.current_valve not in state.opened and valve.flow_rate > 0:
            new_opened = state.opened | {state.current_valve}
            new_pressure_released = state.pressure_released + valve.flow_rate * (state.minutes_remaining - 1)
            new_state = State(state.current_valve, state.minutes_remaining - 1, new_opened, new_pressure_released)
            queue.append(new_state)
        
        # Option to move to a connected valve
        for next_valve in valve.tunnels:
            new_state = State(next_valve, state.minutes_remaining - 1, state.opened, state.pressure_released)
            queue.append(new_state)
    
    return max_pressure

def main():
    valves = parse_input('input.txt')
    max_pressure = bfs(valves, "AA", 30)
    print(f"The most pressure you can release in 30 minutes is: {max_pressure}")

if __name__ == "__main__":
    main()
