#include <iostream>
using namespace std;

class Point {
public:
    Point(int x, int y) : xCoord(x), yCoord(y) {
        cout << "Point Constructor" << endl;
    }

    Point() {
        this->xCoord = 8;
        this->yCoord = 6;
    }

    void printCoordinates() {
        cout << "x: " << xCoord << ", y: " << yCoord << endl;
    }

private:
    int xCoord;
    int yCoord;
};

int main() {
    Point point(3, 4);
    point.printCoordinates();

    Point point1;
    point1.printCoordinates();

    return 0;
}
