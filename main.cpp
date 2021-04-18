#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>

#include "util.h"

const uint8_t nmin = 3;
const uint8_t nmax = 15; //чтобы вошли в строку по щирине экрана

int main() {
    srand(time(NULL));

    printf("The number of points in the set is from %i to %i, n = ", nmin, nmax);

    uint32_t n = 0;
    scanf("%i", &n);
    if (n < nmin || n > nmax)
        return -1;

    auto* points = (Point*)malloc(sizeof(Point) * n);

    // множество
    printf("\nSet of points: \n  ");
    for (uint8_t i = 0; i < (uint8_t)n; i++) {
        printf("\t%i", i);

        points[i] = {
                (float)rand() / 1000,
                (float)rand() / 1000
        };
    }

    printf("\nX:");
    for (uint8_t i = 0; (uint8_t)i < n; i++)
        printf("\t%.*f", 2, points[i].x);

    printf("\nY:");
    for (uint8_t i = 0; (uint8_t)i < n; i++)
        printf("\t%.*f", 2, points[i].y);

    printf("\n\n");

    uint16_t countPoints = 0;
    uint16_t maxPoints   = 0;

    // номера вершин треугольника с макс. кол. точек
    uint8_t imp = 0, jmp = 0, kmp = 0;

    // перебираем треугольники из множества и ищем в каком больше точек
    for (uint8_t k = 0; k < (uint8_t)n - 2; k++)
        for (uint8_t j = 0; j < (uint8_t)n - 1; j++)
            for (uint8_t i = 0; i < (uint8_t)n; i++) {
                countPoints = 0;

                for (uint8_t  p = 0; p < (uint8_t)n; p++)
                    if (Includes({ points[i], points[j], points[k]}, points[p]))
                        countPoints++;

                if (countPoints > maxPoints) {
                    maxPoints = countPoints;

                    imp = i;
                    jmp = j;
                    kmp = k;
                }
            }

    printf("Maximum number of points in a triangle: \n");

    printf("%i (%.*f; %.*f)\n", imp, 2, points[imp].x, 2, points[imp].y);
    printf("%i (%.*f; %.*f)\n", jmp, 2, points[jmp].x, 2, points[jmp].y);
    printf("%i (%.*f; %.*f)\n", kmp, 2, points[kmp].x, 2, points[kmp].y);

    printf("\nAmount of points = %i\n", maxPoints);

    free(points);
    return 0;
}
