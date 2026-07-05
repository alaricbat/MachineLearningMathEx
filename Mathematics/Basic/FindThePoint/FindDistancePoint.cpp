/**
 * PROBLEM: POINT REFLECTION
 *
 * 1. Description:
 *    - Given two points, p = (px, py) and q = (qx, qy).
 *    - Find point r = (rx, ry), which is the reflection of point p across point q
 *      (equivalent to a 180-degree rotation of point p around q).
 *
 * 2. Mathematical Formula:
 *    - Since q is the midpoint of the line segment pr:
 *      qx = (px + rx) / 2  ==>  rx = 2 * qx - px
 *      qy = (py + ry) / 2  ==>  ry = 2 * qy - py
 *
 * 3. Function Specification:
 *    - Name: findPoint
 *    - Parameters: int px, int py, int qx, int qy
 *    - Returns: A collection containing two integers denoting rx and ry.
 *      (In HackerRank/C++, this is typically represented as a std::vector<int>)
 *
 * 4. Constraints & Input Format:
 *    - First line contains n, the number of test cases (1 <= n <= 15).
 *    - Each of the subsequent n lines contains 4 integers: px, py, qx, qy.
 *    - Coordinate range: -100 <= px, py, qx, qy <= 100.
 */
#include <iostream>
struct Point {
    double x;
    double y;
};

Point findPoint(const Point& p, const Point& q) {
    double rx = 2 * q.x - p.x;
    double ry = 2 * q.y - p.y;
    Point r = {rx, ry};
    return r;
}

int main() {

    Point p = {1, 1};
    Point q = {2, 2};
    Point r = findPoint(p, q);
    std::cout << "r: {" << r.x << " ; " << r.y << "}" << std::endl;

    return 0;
}