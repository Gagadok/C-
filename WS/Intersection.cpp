#include <iostream>
using namespace std;

struct Point
{
    double x = 0.0;
    double y = 0.0;
};

bool Square(Point*, int, Point*, int);
double lPoint(Point*, int);
double rPoint(Point*, int);
double tPoint(Point*, int);
double bPoint(Point*, int);
bool Intersection_of_polygons(Point*, int, Point*, int);
bool Intersection_of_segments(Point, Point, Point, Point);

int main(){
// Инициализация многоугольников
    Point Figure_1 [11] = {
        {-1.95, 2.37},
        {-1.27, 3.17},
        {-0.29, 3.45},
        {0.39, 3.15},
        {1.15, 2.71},
        {1.89, 1.51},
        {0.57, 0.27},
        {-0.99, 0.49},
        {-0.41, -0.65},
        {-1.95, -0.67},
        {-3.07, 0.81}
    };

    Point Figure_2[13] = {
        {-0.68, 0.21},
        {0.61, 0.0},
        {1.67, 0.65},
        {2.42, 1.28},
        {3.48, 0.2},
        {2.87, -0.95},
        {1.49, -1.65},
        {1.3, -2.49},
        {0.31, -2.1},
        {1.51, -0.8},
        {0.15, -1.31},
        {-0.05, -0.71},
        {0.57, -0.6}
    };

    /*Point Figure_1[4] = {
        {3, 4},
        {6, 4},
        {6, 2},
        {3, 2}
    };

    Point Figure_2[4] = {
        {5, 5},
        {9, 5},
        {9, 2},
        {5, 2}
    };*/

    if (Square(Figure_1, size(Figure_1), Figure_2, size(Figure_2))) {
        if (Intersection_of_polygons(Figure_1, size(Figure_1), Figure_2, size(Figure_2))) {
            cout << "\nPolygons intersect";
        }
        else {
            cout << "\nPolygons do not intersect";
        }
    }
    else {
        cout << "\nPolygons do not intersect";
    }
}

// Проверка пересечения габаритов (квадратов, в которые влазят наши многоугольники)
bool Square(Point* Figure_1, int size_1, Point* Figure_2, int size_2){
    bool Intersection;

    double center_X_Fig1 = (rPoint(Figure_1, size_1) - lPoint(Figure_1, size_1)) / 2;
    double center_Y_Fig1 = (tPoint(Figure_1, size_1) - bPoint(Figure_1, size_1)) / 2;
    double width_Fig1 = rPoint(Figure_1, size_1) - lPoint(Figure_1, size_1);
    double height_Fig1 = tPoint(Figure_1, size_1) - bPoint(Figure_1, size_1);

    double center_X_Fig2 = (rPoint(Figure_2, size_2) - lPoint(Figure_2, size_2)) / 2;
    double center_Y_Fig2 = (tPoint(Figure_2, size_2) - bPoint(Figure_2, size_2)) / 2;
    double width_Fig2 = rPoint(Figure_2, size_2) - lPoint(Figure_2, size_2);
    double height_Fig2 = tPoint(Figure_2, size_2) - bPoint(Figure_2, size_2);

    if (round(center_X_Fig1 - center_X_Fig2) < ((width_Fig1 + width_Fig2) / 2) &&
        round(center_Y_Fig1 - center_Y_Fig2) < ((height_Fig1 + height_Fig2) / 2)) {
        Intersection = true;
    }
    else {
        Intersection = false;
    }

    return Intersection;
}

// Нахождение крайней левой точки
double lPoint(Point* Figure, int size) {
    double pt = Figure[0].x;

    for (int i = 1; i < size; i++) {
        if (pt > Figure[i].x)
            pt = Figure[i].x;
    }

    return pt;
}

// Нахождение крайней правой точки
double rPoint(Point* Figure, int size) {
    double pt = Figure[0].x;

    for (int i = 1; i < size; i++) {
        if (pt < Figure[i].x)
            pt = Figure[i].x;
    }

    return pt;
}

// Нахождение самой верхней точки
double tPoint(Point* Figure, int size) {
    double pt = Figure[0].y;

    for (int i = 1; i < size; i++) {
        if (pt < Figure[i].y)
            pt = Figure[i].y;
    }

    return pt;
}

// Нахождение самой нижней точки
double bPoint(Point* Figure, int size) {
    double pt = Figure[0].y;

    for (int i = 1; i < size; i++) {
        if (pt > Figure[i].y)
            pt = Figure[i].y;
    }

    return pt;
}

// Проверка пересечения отрезков многоугольников
bool Intersection_of_polygons(Point* Figure_1, int size_1, Point* Figure_2, int size_2){
    bool Intersection = false;
    Point segmentClose1[2] = {
        {Figure_1[size_1 - 1].x, Figure_1[size_1 - 1].y},
        {Figure_1[0].x, Figure_1[0].y}
    };
    Point segmentClose2[2] = {
        {Figure_2[size_2 - 1].x, Figure_2[size_2 - 1].y},
        {Figure_2[0].x, Figure_2[0].y}
    };

    // Проверяем пересечение закрывающего отрезка первой фигуры с отрезками второй
    if (Intersection_of_segments(segmentClose1[0], segmentClose1[1], segmentClose2[0], segmentClose2[1])) {
        cout << "The closing segment of Figure 1 intersects with the closing segment of Figure 2";
        return true;
    }
    else {
        for (int i = 0; i < size_2 - 1; i++) {
            if (Intersection_of_segments(segmentClose1[0], segmentClose1[1], Figure_2[i], Figure_2[i + 1])) {
                cout << "The closing segment of Figure 1 intersects with the " << i << "-" << i + 1 << " segment of Figure 2";
                return true;
            }
        }
    }

    for (int i = 0; i < size_1 - 1; i++) {
        if (Intersection_of_segments(Figure_1[i], Figure_1[i + 1], segmentClose2[0], segmentClose2[1])) {
            cout << "The segment " << i << "-" << i + 1 << " of Figure 1 intersects with the closing segment of figure 2";
            return true;
        }
        for (int j = 0; j < size_2 - 1; j++) {
            if (Intersection_of_segments(Figure_1[i], Figure_1[i + 1], Figure_2[j], Figure_2[j + 1])) {
                cout << "The segment " << i << "-" << i + 1 << " of Figure 1 intersects with the " << j << "-" << j + 1 << " segment of Figure 2";
                return true;
            }
        }
    }

    return Intersection;
}

// Проверка пересечения двух отрезков
bool Intersection_of_segments(Point Segment_1_start, Point Segment_1_end, Point Segment_2_start, Point Segment_2_end) {
    double ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
    ax1 = Segment_1_start.x;
    ax2 = Segment_1_end.x;
    bx1 = Segment_2_start.x;
    bx2 = Segment_2_end.x;
    ay1 = Segment_1_start.y;
    ay2 = Segment_1_end.y;
    by1 = Segment_2_start.y;
    by2 = Segment_2_end.y;

    double v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
    double v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
    double v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
    double v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
    if ((v1 * v2 < 0) && (v3 * v4 < 0)) {
        return true;
    }
    else {
        return false;
    }
}