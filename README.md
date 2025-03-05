# Jak Dojade? (How Do I Get There?)

> Efficient city navigation system with road and air travel options

## Overview

The "Jak Dojade?" project is an implementation of a navigation system that calculates the shortest path between cities. The system operates on a rectangular grid-based map where each field can be:
- Empty (impassable) represented by `.`
- Road (passable in all directions) represented by `#`
- City (passable like a road) represented by `*`
- City name (impassable) represented by letters/numbers

Additionally, certain cities are connected by one-way air routes with specific travel times.

## Features

- **Grid-based Navigation**: Calculate routes between cities on a grid map
- **Multi-modal Transportation**: Support for both road travel (1 minute per field) and air travel
- **Shortest Path Algorithm**: Find the optimal route between any two cities
- **Detailed Route Information**: Optionally display all intermediate cities along the route

## Implementation Requirements

- **No Standard Library Containers**: STL containers, including `string`, cannot be used
- **Custom Data Structures**: All data structures must be implemented from scratch
- **Memory Management**: Proper memory handling required (no memory leaks)
- **No Smart Pointers**: Standard library smart pointers are forbidden (custom implementations allowed)
- **Code Readability**: Emphasis on clean, readable code structure

## Map Representation

The map is a grid where:
- `.` represents empty (impassable) fields
- `#` represents roads (passable in all directions)
- `*` represents cities (passable like roads)
- Letters/numbers represent city names (impassable)

### City Names
- Every city name must be adjacent (by side or corner) to the city marker (`*`) with its first or last letter
- Names are unambiguously assigned to cities
- No numbers or letters appear before or after a city's name (if such a field exists)

## Air Connections

Selected cities have one-way air connections with specified travel times. These connections provide alternative routes between cities.

## Input Format

```
w h                    # Width and height of the map
[map description]      # h lines with w characters each
k                      # Number of flight connections
[flight descriptions]  # k lines of "source destination time"
q                      # Number of queries
[queries]              # q lines of "source destination type"
```

### Query Types
- **Type 0**: Show only travel time
- **Type 1**: Show travel time and route (intermediate cities)

## Output Format

For each query, the program outputs one line:
- For Type 0: The shortest travel time
- For Type 1: The shortest travel time, followed by all intermediate cities (excluding start and end)

## Example

### Input

```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```

### Output

```
5
40
40 KIELCE SZCZECIN
```

## Testing

The project includes various test cases:
- Example tests
- Minimum functionality tests
- Correctness tests
- Grid tests
- Large map tests
- Performance tests
