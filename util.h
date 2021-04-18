//
// Created by Monika on 18.04.2021.
//

#ifndef POINTSCALCULATION_UTIL_H
#define POINTSCALCULATION_UTIL_H

const float e = 0.01f; //точность сравнения вещественных чисел

struct Point {
    float x, y;
};

struct Triangle {
    Point v[3];

    Point operator[] (const uint8_t& n) const {
        return v[n];
    }
};

[[nodiscard]] static float Surface(const Triangle& tr) {
    return abs((tr.v[0].x - tr.v[2].x) * (tr.v[1].y - tr.v[2].y) -
               (tr.v[1].x - tr.v[2].x) * (tr.v[0].y - tr.v[2].y)) / 2;
}

[[nodiscard]] static bool Includes(const Triangle& tr, const Point& point) {
    // площади 3х маленьких треугольников, образованных
    // двумя вершинами и точкой
    float s1 = Surface({ tr[0], tr[1], point });
    float s2 = Surface({ tr[0], tr[2], point });
    float s3 = Surface({ tr[1], tr[2], point });

    // площадь самого треугольника
    float s = Surface(tr);

    return ((s1 > e) && (s2 > e) && (s3 > e) && /* если все площади маленьких > заданной точности (точки не лежат на сторонах) */
           (abs(s-s1-s2-s3)<=e))                  /* и если площиди маленьких=большому с заданой точностью, то точка внутри треугольника */;
}

#endif //POINTSCALCULATION_UTIL_H
