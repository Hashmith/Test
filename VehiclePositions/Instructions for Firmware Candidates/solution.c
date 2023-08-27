#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//created constructor for data type
struct Location {
    int positionId;
    char vehicleRegistration[20]; 
    float latitude;
    float longitude;
    unsigned long long utcTimestamp;
};

//calcualte distance, takes (x,y) values
double calculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int findClosestLocation(struct Location *locations, int numLocations, float x, float y) {
    double minDistance = -1;
    int closestIndex = -1;

    for (int j = 0; j < numLocations; j++) {
        double distance = calculateDistance(x, y, locations[j].latitude, locations[j].longitude);
        if (minDistance == -1 || distance < minDistance) {
            minDistance = distance;
            closestIndex = j;
        }
    }

    return closestIndex;
}

int main() {
    FILE *file = fopen("VehiclePositions.dat", "rb"); 
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int numLocations = 2000000; 
    struct Location *locations = malloc(numLocations * sizeof(struct Location));
    if (locations == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return 1;
    }

    // Read data from file
    for (int i = 0; i < numLocations; i++) {
        fread(&locations[i].positionId, sizeof(int), 1, file);
        fread(locations[i].vehicleRegistration, sizeof(char), 20, file);
        locations[i].vehicleRegistration[19]; 
        fread(&locations[i].latitude, sizeof(float), 1, file);
        fread(&locations[i].longitude, sizeof(float), 1, file);
        fread(&locations[i].utcTimestamp, sizeof(unsigned long long), 1, file);
    }

    fclose(file);

    
    float predefinedPoints[10][2] = {
        {32.345544,-99.123124},
        {33.234235,-100.214124},
        {35.195739,-95.348899},
        {31.895839,-97.789573},
        {32.895839-101.789573},
        {34.115839,-100.225732},
        {32.335839,-99.992232},
        {33.535339,-94.792232},
        {32.234235,-100.222222}
    };

    //finds closest location and distance based on predefinedPoints
    for (int i = 0; i < 10; i++) {
        int closestIndex = findClosestLocation(locations, numLocations, predefinedPoints[i][0], predefinedPoints[i][1]);
        double minDistance = calculateDistance(predefinedPoints[i][0], predefinedPoints[i][1],
                                               locations[closestIndex].latitude, locations[closestIndex].longitude);

       printf("Closest PositionID to Point %d : %d\n",
              i + 1, locations[closestIndex].positionId
                );
    }

    free(locations);

    return 0;
}
