#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape{
public:
    // constructors and destructor
    // Shape(double length);
    // Shape(double length1, double length2);
    // Shape(const Shape &other);
    // Shape &operator=(const Shape &other);
    virtual ~Shape(){};
    Shape(){};

    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea() const=0;
    virtual double CalculatePerimeter() const=0;
    virtual int NumberCorners() const=0;

private:
    // member variables
    double size1;
    double size2;
};



/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle: public Shape {
public:
    Rectangle(double length, double width):size1(length),size2(width){};
    // Rectangle(const Rectangle &other);
    // Rectangle &operator=(const Rectangle &other);
    virtual ~Rectangle(){
        std::cout << "A Rectangle has been destroyed." << std::endl;
    }
    double CalculateArea() const{
        return size1 * size2;
    }
    double CalculatePerimeter() const{
        return 2 * (size1 + size2);
    }
    int NumberCorners() const{
        return 4;
    }
private:
    double length;
    double width;
    double size1;
    double size2;
};
class Square: public Shape {
public:
    Square(double length):size1(length){};
    Square(const Square &other);
    Square &operator=(const Square &other);
    virtual ~Square(){
        std::cout<<"A Square has been destroyed."<<std::endl;
    }
    double CalculateArea() const{
        return size1 * size1;
    }
    double CalculatePerimeter() const{
        return 4 * size1;
    }
    int NumberCorners() const{
        return 4;
    }
private:
    double length;
    double size1;
};
class Triangle: public Shape {
public:
    Triangle(double length1, double length2):size1(length1),size2(length2){};
    Triangle(const Triangle &other);
    Triangle &operator=(const Triangle &other);
    virtual ~Triangle(){
        std::cout<<"A Triangle has been destroyed."<<std::endl;
    }
    double CalculateArea() const{
        return size1 * size2 * 0.5;
    }
    double CalculatePerimeter() const{
        return size1 + size2 + sqrt(size1 * size1 + size2 * size2);
    }
    int NumberCorners() const{
        return 3;
    }
private:
    double length1;
    double length2;
    double size1;
    double size2;
};
class Circle: public Shape {
public:
    Circle(double radius):size1(radius){};
    Circle(const Circle &other);
    Circle &operator=(const Circle &other);
    virtual ~Circle(){
        std::cout<<"A Circle has been destroyed."<<std::endl;
    }
    double CalculateArea() const{
        return PI * size1 * size1;
    }
    double CalculatePerimeter() const{
        return 2 * PI * size1;
    }
    int NumberCorners() const{
        return 0;
    }   
private:
    double radius;
    double size1;
};

/************************************************************************
* Main Function which is creating/reporting database (do not change!) *
************************************************************************/
int main() {
    //initialize an empty list of shapes
    std::list<Shape*> shapeDatabase;
    //interact with the user: ask the user to enter shapes one by one
    while (1) {
        //print instructions as to how to enter a shape
        std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
        std::cout << "and one or two size parameters, ";
        std::cout << "separated with blank spaces:\n";
        double size1;
        double size2;
        //check which shape has been requested and store in the database
        std::string shapeType;
        std::cin >> shapeType;
        if (shapeType == std::string("Circle")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Circle(size1) );
        }
        else if (shapeType == std::string("Triangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Triangle(size1,size2) );
        }
        else if (shapeType == std::string("Square")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Square(size1) );
        }
        else if (shapeType == std::string("Rectangle")) { 
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Rectangle(size1,size2) );
        }
        else {
            std::cout << "Unrecognized shape!!\n";
        }
        //check if the user wants to add more shapes
        std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
        std::string answer;
        std::cin >> answer;
        if (answer != std::string("Y"))
            break;
    }
    //iterate through the list and output the area, perimeter,
    //and number of corners of each entered shape
    std::list<Shape *>::iterator it = shapeDatabase.begin();
    int shapeCounter = 0;
    while (it != shapeDatabase.end()) {   
        std::cout << "Properties of shape " << shapeCounter++ << ":\n";
        std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea() << "\n";
        std::cout << "Perimeter: " << std::setprecision(5) << (*it)->CalculatePerimeter() << "\n";
        std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
        std::cout << std::endl;
        it++;
    }

    it = shapeDatabase.begin();
    while (it != shapeDatabase.end()) {
        delete (*it);
        it = shapeDatabase.erase(it);
    }
    
    return 0;
}