#include "functions.h"

using namespace std;

void readBoard(myVector<char>& board, BoardDimensions& board_dimensions) {
	cin >> board_dimensions.w >> board_dimensions.h;
	board_dimensions.size = board_dimensions.w * board_dimensions.h;

	char input;
	for (int i = 0; i < board_dimensions.size; i++) {
		cin >> input;
		board.push_back(input);
	}
}

bool isAlphanumeric(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

bool isPositionValid(int rowNumber, int columnNumber, BoardDimensions board_dimensions) {
	return rowNumber >= 0 && rowNumber < board_dimensions.h && columnNumber >= 0 && columnNumber < board_dimensions.w;
}

int findVertexIndexOfCity(const myVector<char>& board, int index, BoardDimensions board_dimensions) {
	int columnNumber = index % board_dimensions.w;
	int rowNumber = index / board_dimensions.w;
	int vertexIndex = UNDEFINED;

	if (board[index] == '*') {
		return index;
	}
	else {
		// searching around the given index for a vertex index of a city
		for (int tempColumnNumber = columnNumber - 1; tempColumnNumber <= columnNumber + 1; tempColumnNumber++) {
			for (int tempRowNumber = rowNumber - 1; tempRowNumber <= rowNumber + 1; tempRowNumber++) {
				if (isPositionValid(tempRowNumber, tempColumnNumber, board_dimensions)) {
					int tempIndex = tempRowNumber * board_dimensions.w + tempColumnNumber;
					if (board[tempIndex] == '*') {
						return tempIndex;
					}
				}
			}
		}
	}
	return vertexIndex;
}

void findCities(const myVector<char>& board, BoardDimensions board_dimensions, myVector<City>& cities) {
	City city;
	bool isReadingCity = false;

	for (int i = 0; i < board_dimensions.size; i++) {
		// if the current character is alphanumeric, it is part of a city name
		if (isAlphanumeric(board[i])) {
			if (!isReadingCity) {
				city.name += board[i];
				city.vertexIndex = findVertexIndexOfCity(board, i, board_dimensions);
				isReadingCity = true;

				// if the last character of the board is part of the city name, push the city to the cities vector
				if (isAlphanumeric(board[board_dimensions.size - 1]) && city.vertexIndex != UNDEFINED) {
					cities.push_back(city);
				}
			}
			else {
				city.name += board[i];
			}
		}
		else if (isReadingCity) {
			// if vertex of the city not found, search around the last letter of the city name
			if (city.vertexIndex == UNDEFINED) {
				city.vertexIndex = findVertexIndexOfCity(board, i - 1, board_dimensions);
			}
			cities.push_back(city);
			city.name = "";
			city.vertexIndex = UNDEFINED;
			isReadingCity = false;
		}
	}
}

void convertMapToGraph(myVector<char>& board, BoardDimensions board_dimensions, myVector<myVector<FieldDistancePair>>& graph) {
	int columnNumber, rowNumber, tempRowNumber, tempColumnNumber, tempIndex;
	const int columnDirections[4] = { 0, -1, 0, 1 };
	const int rowDirections[4] = { -1, 0, 1, 0 };

	for (int i = 0; i < board_dimensions.size; i++) {
		if ((board[i] == '#') || (board[i] == '*')) {
			columnNumber = i % board_dimensions.w;
			rowNumber = i / board_dimensions.w;

			// searching around the given index for a neighbor field in four possible directions (up, left, down, right)
			for (int j = 0; j < 4; j++) {
				tempRowNumber = rowNumber + rowDirections[j];
				tempColumnNumber = columnNumber + columnDirections[j];

				if (isPositionValid(tempRowNumber, tempColumnNumber, board_dimensions)) {
					tempIndex = tempRowNumber * board_dimensions.w + tempColumnNumber;

					// if the neighbor field is a city or a road, push it to the graph with default distance between fields (1)
					if (board[tempIndex] == '#' || board[tempIndex] == '*') {
						graph[i].push_back({ tempIndex, DEFAULT_DISTANCE });
					}
				}
			}
		}
	}
}

void fillCityNamesVector(myVector<City> cities, myVector<myString>& cityNames) {
	for (size_t i = 0; i < cities.size(); i++) {
		cityNames[cities[i].vertexIndex] = cities[i].name;
	}
}

void fillHashTable(int*& hash_table, myVector<City> cities) {
	for (size_t i = 0; i < cities.size(); i++) {
		hash_table[cities[i].name.hash()] = cities[i].vertexIndex;
	}
}

void readFlights(int* hash_table, myVector<myVector<FieldDistancePair>>& graph) {
	int numberOfFlights;
	scanf("%d", &numberOfFlights);
	getchar();

	for (int i = 0; i < numberOfFlights; i++) {
		int distanceBetweenCities, sourceCityIndex, destinationCityIndex, counter;
		char c;
		char* sourceCityName = new char[CITY_NAME_BUFFER];
		char* destinationCityName = new char[CITY_NAME_BUFFER];

		counter = 0;
		distanceBetweenCities = 0;

		// read source city name
		c = getchar();
		while (c != ' ') {
			sourceCityName[counter] = c;
			counter++;
			c = getchar();
		}
		sourceCityName[counter] = '\0';
		counter = 0;

		// read destination city name
		c = getchar();
		while (c != ' ') {
			destinationCityName[counter] = c;
			counter++;
			c = getchar();
		}
		destinationCityName[counter] = '\0';

		scanf("%d", &distanceBetweenCities);
		getchar();

		// convert city names to myString objects
		myString destinationCityNameString(destinationCityName);
		myString sourceCityNameString(sourceCityName);

		// find source and destination city indexes in the graph using hash table
		sourceCityIndex = hash_table[sourceCityNameString.hash()];
		destinationCityIndex = hash_table[destinationCityNameString.hash()];

		// add the destination city index and distance to the source city to the graph
		graph[sourceCityIndex].push_back({ destinationCityIndex, distanceBetweenCities });

		delete[] sourceCityName;
		delete[] destinationCityName;
	}
}

void dijkstraSearch(myVector<myVector<FieldDistancePair>>& graph, myVector<FieldDijkstra>& shortestRoute, int sourceCityIndex) {
	// initialize shortestRoute vector
	for (size_t i = 0; i < shortestRoute.size(); i++) {
		shortestRoute[i].fieldIndex = UNDEFINED;
		shortestRoute[i].distance = INT_MAX;
		shortestRoute[i].previousFieldIndex = UNDEFINED;
		shortestRoute[i].isVisited = false;
	}

	shortestRoute[sourceCityIndex].distance = INITIAL_DISTANCE;

	// initialize priority queue
	PriorityQueue Q;
	Q.push({ sourceCityIndex, INITIAL_DISTANCE });

	// loop until all fields are visited
	while (!Q.isEmpty()) {
		int currentFieldIndex = Q.top().fieldIndex;
		Q.pop();

		if (!shortestRoute[currentFieldIndex].isVisited) {
			shortestRoute[currentFieldIndex].isVisited = true;

			// loop through all neighbors of current field
			for (size_t i = 0; i < graph[currentFieldIndex].size(); i++) {
				int currentNeighborIndex = graph[currentFieldIndex][i].fieldIndex;
				int alternativeDistance = graph[currentFieldIndex][i].neighborFieldDistance;

				// check if alternative route to the neighbor is shorter than current shortest route to the neighbor
				if (shortestRoute[currentFieldIndex].distance + alternativeDistance < shortestRoute[currentNeighborIndex].distance) {
					shortestRoute[currentNeighborIndex].fieldIndex = currentNeighborIndex;
					shortestRoute[currentNeighborIndex].distance = shortestRoute[currentFieldIndex].distance + alternativeDistance;
					shortestRoute[currentNeighborIndex].previousFieldIndex = currentFieldIndex;
					Q.push({ currentNeighborIndex, shortestRoute[currentNeighborIndex].distance });
				}
			}
		}
	}
}

myVector<int> findRouteIndexes(myVector<FieldDijkstra>& shortestRoute, myVector<int>& routeIndexes, int sourceCityIndex, int destinationCityIndex) {
	int currentFieldIndex = destinationCityIndex;

	// loop through shortestRoute vector and find all route indexes from destination city to source city
	while (currentFieldIndex != sourceCityIndex) {
		routeIndexes.push_back(currentFieldIndex);
		currentFieldIndex = shortestRoute[currentFieldIndex].previousFieldIndex;
	}
	return routeIndexes;
}

void printOutput(myVector<FieldDijkstra>& shortestRoute, myVector<myString>& cityNames, int sourceCityIndex, int destinationCityIndex, bool queryType) {
	cout << shortestRoute[destinationCityIndex].distance;

	// if query type is 1, print the route in the output
	if (queryType) {
		myVector<int> routeIndexes;

		findRouteIndexes(shortestRoute, routeIndexes, sourceCityIndex, destinationCityIndex);

		bool firstCity = true;
		for (int i = routeIndexes.size() - 1; i > 0; i--) {
			if ((int)cityNames.size() > routeIndexes[i] && !cityNames[routeIndexes[i]].isEmpty()) {
				if (firstCity) {
					cout << " " << cityNames[routeIndexes[i]];
					firstCity = false;
				} else {
					cout << " " << cityNames[routeIndexes[i]];
				}
			}
		}
	}
	cout << endl;
}

void readQueries(int*& hash_table, myVector<myVector<FieldDistancePair>>& graph, myVector<myString>& cityNames) {
	myVector<FieldDijkstra> shortestRoute(graph.size());
	int numberOfQueries;
	cin >> numberOfQueries;

	for (int i = 0; i < numberOfQueries; i++) {
		int sourceCityIndex, destinationCityIndex;
		myString sourceCityName, destinationCityName;
		bool queryType;

		cin >> sourceCityName >> destinationCityName >> queryType;

		// find source and destination city indexes in the graph using hash table
		sourceCityIndex = hash_table[sourceCityName.hash()];
		destinationCityIndex = hash_table[destinationCityName.hash()];

		// find the shortest route between the source and rest of the fields in the graph
		dijkstraSearch(graph, shortestRoute, sourceCityIndex);

		printOutput(shortestRoute, cityNames, sourceCityIndex, destinationCityIndex, queryType);
	}
}