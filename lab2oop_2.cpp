
#include <iostream>
class Point {
	int x;
	int y;
public:
	static int GetDistance(Point& p1, Point& p2) {
		std::cout << "a distance between p1 and p2 is: " << std::endl;
		return 0;
	}
	int GetDistance(Point& p) {
		std::cout << "a distance btw this point and point P is: " << std::endl;
		return 0;
	}
	Point(int x, int y) { // конструктор с параметрами 
		this->x = x;
		this->y = y;
	}
	Point() { //конструктор без параметров
		x = 0;
		y = 0;
	}
};
class Figure { //класс фигуры 
protected: //свойства 
	int dimension;
public:
	virtual void DrawFigure() = 0; //абстрактный метод
	virtual int GetSquare() = 0; // положим, что все фигуры должны обладать площадью
	virtual ~Figure() = 0;
};
class Line :private Figure {
	int length;
	Point* p1;
	Point* p2;
	int GetSquare() { //(по умолчанию private)-метод
		return 0;
	}
public:
	void DrawFigure() {
		std::cout << "Drawing line...\n";
	}
	int GetLength() {
		std::cout << "This line length is: " << length << std::endl;
		return length;
	}
	Line(Point& p1, Point& p2) {
		length = Point::GetDistance(p1, p2);
		this->p1 = new Point(p1); //конструктор копирования класса Point по умлочанию
		this->p2 = new Point(p2);
		dimension = 1; //protected-свойство доступно для использования в классах-наследниках
	}
	~Line() {
		delete p1;
		delete p2;
	}
};
int main()
{
	Point a(10, 5);
	Point b(2, 5);
	Line lin(a,b);
	lin.GetLength();
	//lin.GetSquare(); //не скомпилируется(т.о. можно переписать абстрактный метод, чтобы он был недоступен для вызова)
	//lin.p1 //нет доступа к отдельным точкам 
	lin.DrawFigure();
}
