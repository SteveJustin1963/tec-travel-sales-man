#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRID_SIZE 60
#define NUM_POINTS 20

typedef struct {
    int x, y;
} Point;

Point points[NUM_POINTS];
int visited[NUM_POINTS] = {0};

// Function to generate random points
void generate_random_points() {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < NUM_POINTS; i++) {
        points[i].x = rand() % GRID_SIZE;
        points[i].y = rand() % GRID_SIZE;
    }
}

// Function to print the map
void print_map() {
    char grid[GRID_SIZE][GRID_SIZE];

    // Initialize the grid with dots
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    // Place points on the grid
    for (int i = 0; i < NUM_POINTS; i++) {
        grid[points[i].y][points[i].x] = 'A' + i;  // Label points A, B, C, etc.
    }

    // Print the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the Euclidean distance between two points
double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to find the nearest unvisited point
int find_nearest(Point current) {
    int nearest = -1;
    double min_dist = 1e9;

    for (int i = 0; i < NUM_POINTS; i++) {
        if (!visited[i]) {
            double dist = distance(current, points[i]);
            if (dist < min_dist) {
                min_dist = dist;
                nearest = i;
            }
        }
    }

    return nearest;
}

// Function to find and print the shortest path (nearest neighbor approach) and calculate total distance
void find_shortest_path() {
    Point current = points[0];  // Start from the first point
    visited[0] = 1;  // Mark the first point as visited
    int tour[NUM_POINTS];
    double total_distance = 0;
    tour[0] = 0; // Start the tour with point 0

    for (int i = 1; i < NUM_POINTS; i++) {
        int next = find_nearest(current);
        visited[next] = 1;
        total_distance += distance(current, points[next]);  // Accumulate total distance
        tour[i] = next;
        current = points[next];
    }

    // Print the tour
    printf("Shortest Path: ");
    for (int i = 0; i < NUM_POINTS; i++) {
        printf("%c ", 'A' + tour[i]);
    }
    printf("\n");

    // Print the total distance covered
    printf("Total Distance Covered: %.2lf units\n", total_distance);
}

int main() {
    generate_random_points();
    print_map();
    find_shortest_path();

    return 0;
}
