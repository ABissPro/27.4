#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

enum class Color {
    Red, Green, Blue, None
};

Color parseColor(const std::string& colorStr) {
    if (colorStr == "Red") return Color::Red;
    if (colorStr == "Green") return Color::Green;
    if (colorStr == "Blue") return Color::Blue;
    return Color::None;
}

std::string colorToString(Color color) {
    switch (color) {
    case Color::Red: return "Red";
    case Color::Green: return "Green";
    case Color::Blue: return "Blue";
    default: return "None";
    }
}

struct BoundingRect {
    double x, y, width, height;
};

class Figure {
protected:
    double centerX, centerY;
    Color color;

public:
    Figure(double x, double y, Color c) : centerX(x), centerY(y), color(c) {}

    double getCenterX() const { return centerX; }
    double getCenterY() const { return centerY; }
    Color getColor() const { return color; }

    void setCenter(double x, double y) {
        centerX = x;
        centerY = y;
    }

    void setColor(Color c) {
        color = c;
    }
};

class Circle : public Figure {
    double radius;

public:
    Circle(double x, double y, double r, Color c)
        : Figure(x, y, c), radius(r) {
    }

    double area() const {
        return std::atan(1) * 4 * radius * radius;
    }

    BoundingRect getBoundingRect() const {
        return { centerX - radius, centerY - radius, 2 * radius, 2 * radius };
    }

    void printInfo() const {
        std::cout << "Circle: center=(" << centerX << ", " << centerY << "), radius=" << radius
            << ", color=" << colorToString(color) << std::endl;
        std::cout << "Area: " << area() << std::endl;

        BoundingRect rect = getBoundingRect();
        std::cout << "Bounding rectangle: (" << rect.x << ", " << rect.y << "), "
            << rect.width << " x " << rect.height << std::endl;
    }
};

class Square : public Figure {
    double side;

public:
    Square(double x, double y, double s, Color c)
        : Figure(x, y, c), side(s) {
    }

    double area() const {
        return side * side;
    }

    BoundingRect getBoundingRect() const {
        return { centerX - side / 2, centerY - side / 2, side, side };
    }

    void printInfo() const {
        std::cout << "Square: center=(" << centerX << ", " << centerY << "), side=" << side
            << ", color=" << colorToString(color) << std::endl;
        std::cout << "Area: " << area() << std::endl;

        BoundingRect rect = getBoundingRect();
        std::cout << "Bounding rectangle: (" << rect.x << ", " << rect.y << "), "
            << rect.width << " x " << rect.height << std::endl;
    }
};

class EquilateralTriangle : public Figure {
    double side;

public:
    EquilateralTriangle(double x, double y, double s, Color c)
        : Figure(x, y, c), side(s) {
    }

    double area() const {
        return (sqrt(3) / 4) * side * side;
    }

    BoundingRect getBoundingRect() const {
        double triangleHeight = side * sqrt(3) / 2;
        return { centerX - side / 2, centerY - triangleHeight / 2, side, triangleHeight };
    }

    void printInfo() const {
        std::cout << "Equilateral triangle: center=(" << centerX << ", " << centerY << "), side=" << side
            << ", color=" << colorToString(color) << std::endl;
        std::cout << "Area: " << area() << std::endl;

        BoundingRect rect = getBoundingRect();
        std::cout << "Bounding rectangle: (" << rect.x << ", " << rect.y << "), "
            << rect.width << " x " << rect.height << std::endl;
    }
};

class Rectangle : public Figure {
    double width, height;

public:
    Rectangle(double x, double y, double w, double h, Color c)
        : Figure(x, y, c), width(w), height(h) {
    }

    double area() const {
        return width * height;
    }

    BoundingRect getBoundingRect() const {
        return { centerX - width / 2, centerY - height / 2, width, height };
    }

    void printInfo() const {
        std::cout << "Rectangle: center=(" << centerX << ", " << centerY << "), width=" << width
            << ", height=" << height << ", color=" << colorToString(color) << std::endl;
        std::cout << "Area: " << area() << std::endl;

        BoundingRect rect = getBoundingRect();
        std::cout << "Bounding rectangle: (" << rect.x << ", " << rect.y << "), "
            << rect.width << " x " << rect.height << std::endl;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::string command;

    std::cout << "Enter commands (circle, square, triangle, rectangle, or exit):" << std::endl;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "circle") {
            double x, y, radius;
            std::string colorStr;
            std::cin >> x >> y >> radius >> colorStr;
            Color color = parseColor(colorStr);

            Circle circle(x, y, radius, color);
            circle.printInfo();

        }
        else if (command == "square") {
            double x, y, side;
            std::string colorStr;
            std::cin >> x >> y >> side >> colorStr;
            Color color = parseColor(colorStr);

            Square square(x, y, side, color);
            square.printInfo();

        }
        else if (command == "triangle") {
            double x, y, side;
            std::string colorStr;
            std::cin >> x >> y >> side >> colorStr;
            Color color = parseColor(colorStr);

            EquilateralTriangle triangle(x, y, side, color);
            triangle.printInfo();

        }
        else if (command == "rectangle") {
            double x, y, width, height;
            std::string colorStr;
            std::cin >> x >> y >> width >> height >> colorStr;
            Color color = parseColor(colorStr);

            Rectangle rectangle(x, y, width, height, color);
            rectangle.printInfo();

        }
        else {
            std::cout << "Unknown command. Available commands: circle, square, triangle, rectangle, exit" << std::endl;
        }
    }

    return 0;
}
