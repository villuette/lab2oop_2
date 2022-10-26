
#include <iostream>
class Point {
	int x{ 0 };
	int y{ 0 };
public:
	static int GetDistance(Point& p1, Point& p2) {
		std::cout << "Called static method getdistance: " << std::endl;
		return 0;
	}
	int GetDistance(Point& p) {
		std::cout << "Called method getdistance: " << std::endl;
		return 0;
	}
	Point(int x, int y) :x(x), y(y) { std::cout << "construct Point(x,y)\n"; }// конструктор с параметрами 	
	Point() : x(0), y(0) { std::cout << "construct Point()\n"; } //конструктор без параметров
	Point(const Point& p, int inter) : x(p.x), y(p.y) { //конструктор копирования
		this->x += inter;
		this->y -= inter;
		std::cout << "construct Point(Point&, int)\n";
	}
	void Set(int ax, int ay) { x = (int)ax, y = (int)ay; } //странно, почему то работает с запятой
	int GetX() { return x; } int GetY() { return y; }
};
class Figure { //класс фигуры 
protected: //свойства 
	int dimension = 0;
public:
	virtual void DrawFigure() = 0; //абстрактный метод
	virtual int GetSquare() = 0; // положим, что все фигуры должны обладать площадью
	virtual ~Figure() = default;
};
class Line :private Figure {//допустим, что линия *является* фигурой (наследование)
	int length;
	Point* p1;//и *состоит из* точек (скопированные точки(line:54,55), это композиция или агрегация?)
	Point* p2;//
public:
	int GetSquare() override {
		std::cout << "Something special)\n";
		return 0;
	}
	void DrawFigure() {
		std::cout << "Drawing line...\n";
	}
	int GetLength() {
		std::cout << "This line length is: " << length << std::endl;
		return length;
	}
	Line(Point& p1, Point& p2) {
		std::cout << "Constructor Line(Point& p1, Point& p2)\n ";
		length = Point::GetDistance(p1, p2);
		this->p1 = new Point(p1); //конструктор копирования класса Point по умлочанию
		this->p2 = new Point(p2, 10); //созданный конструктор копирования
		dimension = 1; //protected-свойство доступно для использования в классах-наследниках
	}
	//Line(Point& p1, Point& p2) :p1(new Point(p1)), p2(new Point(p2, 10)) { dimension = 1; }//по аналогии
	~Line() { //также является виртуальным
		std::cout << "Called destr of line\n";
		delete p1; //освобождение памяти, выделенной под точки в конструкторе
		delete p2;
	}
};
int main()
{
	Point a(10, 5);
	Point b(2, 5);
	//Line lin(a, b);
	a.Set(10, 4);
	b.Set(b.GetX() + 3, b.GetY() + 1);
	Line* dinlin = new Line(a, b);
	delete dinlin;
	dinlin = nullptr;
	//Line solin = Line(a, b); //создание статического объекта с конструктором (и висящей в памяти безымянной копией)
	//dinlin->DrawFigure(); //не вызывает исключения, но ломает программу
	//delete dinlin;	
	//if(dinlin != nullptr)
	//	dinlin->GetLength();
	//lin.GetLength();
	//lin.GetSquare(); //не скомпилируется(т.о. можно переписать абстрактный метод, чтобы он был private, но выглядит как костыль)
	//lin.GetSquare(); //
	//lin.p1 //нет доступа к отдельным точкам 
	//lin.DrawFigure();
}
