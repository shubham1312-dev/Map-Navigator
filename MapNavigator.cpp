#include <bits/stdc++.h>
using namespace std;

// Structure to represent a location and its connections (roads and distances)
struct Location
{
    int id;
    vector<pair<int, int>> neighbors; // pair<neighbor id, distance to neighbor>
    Location(int _id) : id(_id) {}
};

// Function to add a road between two locations with a given distance
void addRoad(vector<Location> &locations, int loc1, int loc2, int distance)
{
    locations[loc1].neighbors.push_back({loc2, distance});
    locations[loc2].neighbors.push_back({loc1, distance});
}

// Dijkstra's algorithm to find shortest path from source to all other locations
vector<int> dijkstra(vector<Location> &locations, int source)
{
    int N = locations.size();
    vector<int> dist(N, numeric_limits<int>::max());                                    // Distance to each location
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min heap for Dijkstra

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currDist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        // If we already found a shorter path to curr, skip
        if (currDist > dist[curr])
            continue;

        // Explore neighbors
        for (auto &neighbor : locations[curr].neighbors)
        {
            int next = neighbor.first;
            int weight = neighbor.second;

            int newDist = currDist + weight;

            // If found a shorter path to next location, update and push to priority queue
            if (newDist < dist[next])
            {
                dist[next] = newDist;
                pq.push({newDist, next});
            }
        }
    }

    return dist;
}

// Function to print shortest path from source to destination
void printShortestPath(vector<int> &dist, int source, int destination, vector<Location> &locations)
{
    // Path reconstruction
    vector<int> path;
    int curr = destination;
    while (curr != source)
    {
        path.push_back(curr);
        int prev = -1;
        for (auto &neighbor : locations[curr].neighbors)
        {
            if (dist[neighbor.first] + neighbor.second == dist[curr])
            {
                prev = neighbor.first;
                break;
            }
        }
        curr = prev;
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    // Print shortest distance
    cout << "Shortest distance from location " << source << " to location " << destination << ": " << dist[destination] << endl;

    // Print path
    cout << "Path: ";
    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

int main()
{
    int N = 5; // Number of locations

    // Initialize locations
    vector<Location> locations(N, Location(0)); // Assuming locations are labeled 0 to N-1

    // Example map: Add roads and distances
    addRoad(locations, 0, 1, 10);
    addRoad(locations, 0, 2, 15);
    addRoad(locations, 1, 3, 12);
    addRoad(locations, 2, 3, 5);
    addRoad(locations, 3, 4, 20);

    int source = 0;      // Source location
    int destination = 4; // Destination location

    // Run Dijkstra's algorithm from source
    vector<int> dist = dijkstra(locations, source);

    // Print shortest path from source to destination
    printShortestPath(dist, source, destination, locations);

    return 0;
}
