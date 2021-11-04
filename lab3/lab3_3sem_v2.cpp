#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>


class shape {
protected:
	std::string name;

public:
	shape(std::string name)
	{
		if (name.size() > 0)
			this->name = name;
	}
	virtual void draw_and_move(double coord_x, double coord_y)=0;
	virtual double area() = 0;
	virtual void show() = 0;
	virtual std::string to_string(){
		std::stringstream circ;
		circ << "Name:" << this->Get_name() << "\nS=" << this->area() << std::endl;
		std::string circ1 = circ.str();
		return circ1;
	}
	virtual std::string Get_name() {
		std::string name = this->name;
		return name;
	}
	shape() {};
	virtual ~shape() {
		std::cout << "shape dest!!!" << std::endl;
	}
};
class ellipse :protected shape {
protected:
	double a, b;
public:
	ellipse(std::string name, double a, double b) :shape(name)
	{
		if (a > 0) this->a = a;
		if (b > 0) this->b = b;
	}
	double area()
	{
		return M_PI*a*b;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "S=" << area() << std::endl;
	}
	void draw_and_move(double coord_x, double coord_y)
	{
		sf::RenderWindow window(sf::VideoMode(200, 200), "Ellipse!");
		float radius_x = a;
		float radius_y = b;
		unsigned short quality = 70;

		sf::ConvexShape ellipseslav;
		ellipseslav.setPointCount(quality);

		for (unsigned short i = 0;i < quality;++i) {
			float rad = (360. / quality * i) / (360. / M_PI/ 2.);
			float x = cos(rad) * radius_x;
			float y = sin(rad) * radius_y;

			ellipseslav.setPoint(i, sf::Vector2f(x, y));
		};
		ellipseslav.setFillColor(sf::Color::Magenta);
		
		ellipseslav.setPosition(100+coord_x, 100-coord_y);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(ellipseslav);
			window.display();
		}
	}
	
	std::string to_str()
	{
		std::string zxc;
		zxc = shape::to_string();
		return zxc;
	}

	virtual ~ellipse() {
		std::cout << "elipse dest!" << std::endl;
	}
};
class circle : protected ellipse {
protected:
	double R;
public:
	circle(std::string name, double a) :ellipse(name, a, b)
	{
		R = a;
	}
	double area()
	{
		return M_PI * R * R;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "S=" << area() << std::endl;
	}
	void draw_and_move(double coord_x, double coord_y)
	{
		sf::RenderWindow window(sf::VideoMode(200, 200), "Circle!");// outline is taking 5 more radius(R=10; printed would be 15)
		sf::CircleShape circleslav(R);
		circleslav.setFillColor(sf::Color::Red);
		circleslav.setPosition(100. - R+coord_x, 100. - R-coord_y);
		
		
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(circleslav);
			window.display();
		}
	}
	
	std::string to_str()
	{
		std::string zxc;
		zxc= shape::to_string();
		return zxc;
	}
	virtual ~circle() {
		std::cout << "circle dest!" << std::endl;
	};
};
class triangle : protected shape {
protected:
	double a;
	double b;
	double c;
	
public:
	triangle(std::string name, double a, double b, double c) :shape(name)
	{
		if (a > 0 && b > 0 && c > 0 && (a + b) > c && (a + c) > b && (b + c) > a) {
			this->a = a;
			this->b = b;
			this->c = c;
		}
		else {
			this->a = 0;
			this->b = 0;
			this->c = 0;
		}
	}
	double area()
	{
		double p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "S=" << area() << std::endl;
	}
	void draw_and_move(double coord_x, double coord_y)
	{
		
		
		float h= (2.*this->area())/b;
		
		sf::RenderWindow window(sf::VideoMode(200, 200), "Triangle!");
		sf::ConvexShape triangleslav;
		triangleslav.setPointCount(3);
		triangleslav.setPoint(0, sf::Vector2f(0.f, 0.f));
		triangleslav.setPoint(1, sf::Vector2f(0.f-h, 0.f+b/2.));
		triangleslav.setPoint(2, sf::Vector2f(0.f-h, 0.f-b/2.));
		triangleslav.setFillColor(sf::Color::Cyan);
		triangleslav.setOutlineThickness(0);
		triangleslav.setPosition(100+coord_x, 100+h-coord_y);
		triangleslav.rotate(-90);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(triangleslav);
			window.display();
		}
	}
	
	std::string to_str()
	{
		std::string zxc;
		zxc = shape::to_string();
		return zxc;
	}
	virtual ~triangle() {
		std::cout << "triangle dest!" << std::endl;
	};
};
class rectangle : protected shape {
protected:
	double a;
	double b;
public:
	rectangle(std::string name, double a, double b) :shape(name)
	{
		if (a > 0) this->a = a;
		if (b > 0) this->b = b;
	}
	double area()
	{
		return a * b;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "S=" << area() << std::endl;
	}
	void draw_and_move(double coord_x, double coord_y)
	{
		sf::RenderWindow window(sf::VideoMode(200, 200), "Rectangle!");
		sf::RectangleShape rectangleslav(sf::Vector2f(a, b));
		rectangleslav.setFillColor(sf::Color::Green);
		rectangleslav.setOutlineThickness(0);
		rectangleslav.setPosition(100.-(a/2)+coord_x , 100.-(b/2)-coord_y);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(rectangleslav);
			window.display();
		}
	}
	
	std::string to_str()
	{
		std::string zxc;
		zxc = shape::to_string();
		return zxc;
	}
	virtual ~rectangle() {
		std::cout << "rectangle dest!" << std::endl;
	};
};

class square : protected rectangle {
protected:

	
public:
	square(std::string name, double a) :rectangle(name, a, b)
	{		
		
	}
	double area()
	{
		return a * a;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "S=" << area() << std::endl;
	}
	void draw_and_move(double coord_x, double coord_y)
	{
		sf::RenderWindow window(sf::VideoMode(200, 200), "Square!");
		sf::RectangleShape squareslav(sf::Vector2f(a, a));
		squareslav.setFillColor(sf::Color::Yellow);
		squareslav.setOutlineThickness(0);
		squareslav.setPosition(100.-(a/2)+coord_x, 100.-(a/2)-coord_y);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(squareslav);
			window.display();
		}
	}
	
	std::string to_str()
	{
		std::string zxc;
		zxc = shape::to_string();
		return zxc;
	}
	virtual ~square() {
		std::cout << "square dest!" << std::endl;
	};
};

class SquareCylinder :protected square {
private:
	
	double h;//b from rectangle
public:
	SquareCylinder(std::string name, double a, double h):square(name, a) {
		
		if (h > 0) this->h = h;
	}
	double volume()
	{
		return square::area()*h;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "V=" << volume() << std::endl;
	}
	std::string to_str()
	{
		std::stringstream str;
		str << "Name:" << Get_name() << "\nV=" << volume() << std::endl;
		std::string str1 = str.str();
		return str1;
	}
	~SquareCylinder() {
		std::cout << "SquareCylinder dest!" << std::endl;
	};
};
class TriangleCylinder :protected triangle {
private:
	double h;
	
public:
	TriangleCylinder(std::string name, double h, double a, double b, double c) :triangle(name, a, b, c)
	{
		if (h > 0) this->h = h;
	}
	double volume()
	{
		return  triangle::area() * h;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "V=" << volume() << std::endl;
	}
	
	std::string to_str()
	{
		std::stringstream str;
		str << "Name:" << Get_name() << "\nV=" << volume() << std::endl;
		std::string str1 = str.str();
		return str1;
	}
	~TriangleCylinder() {
		std::cout << "TriangleCylinder dest!" << std::endl;
	};
};
class CircleCylinder :protected circle {
private:
	double h;
	double R1;
public:
	CircleCylinder(std::string name,double a, double h) :circle(name, a)
	{
		if (h > 0) this->h = h;
		R1 = R;
	}
	double volume()
	{
		return circle::area() * h;
	}
	void show()
	{
		std::cout << "Name:" << Get_name() << std::endl << "V=" << volume() << std::endl;
	}
	std::string to_str()
	{
		std::stringstream str;
		str << "Name:" << Get_name() << "\nV=" << volume() << std::endl;
		std::string str1 = str.str();
		return str1;
	}
	~CircleCylinder() {
		std::cout << "CircleCylinder dest!" << std::endl;
	};
};

class app
{
public:
	static void run()
	{

		double x, y;//for elliplse
		double a, b, c;//for triangle
		double a1, b1;//for rectangle
		double h1, h2;//for trianglecylinder and circlecylinder

		double coord_x = 0, coord_y = 0;

		std::cout << "Enter x, y(ellipse diagonals(x will be circle radius):\n"; std::cin >> x >> y;
		std::cout << "Enter a, b, c(triangle):\n"; std::cin >> a >> b >> c;
		std::cout << "Enter a, b(rectangle sides):\n"; std::cin >> a1 >> b1;
		std::cout << "Enter h(triangle cylinder):\n"; std::cin >> h1;
		std::cout << "Enter h(circle cylinder):\n"; std::cin >> h2;
		
		ellipse el = ellipse("Elipz", x, y);
		circle circ = circle("Kryg",x);
		triangle tri = triangle("Treygolnik", a, b, c);
		rectangle rect = rectangle("Pryamoygolnik", a1, b1);
		square sq = square("kvadrat", a1);
		SquareCylinder sqc = SquareCylinder("Cylinder 1",a1,b1);
		TriangleCylinder trc = TriangleCylinder("Cylinder 2", a,b,c,h2);
		CircleCylinder scc = CircleCylinder("Cylinder 3",x, h2);
		el.show();
		circ.show();
		tri.show();
		rect.show();
		sq.show();
		el.draw_and_move(0, 0);
		circ.draw_and_move(0, 0);
		tri.draw_and_move(0, 0);
		rect.draw_and_move(0, 0);
		sq.draw_and_move(0, 0);
		
		sqc.show();
		trc.show();
		scc.show();

		bool t;
		std::cout << "Do you want to move objects? No-0, Yes-1" << std::endl;std::cin >> t;
		if (t)
		{

			int x = -1;
			while (x != 0)
			{
				std::cout << "What object do you want to move?\n1-Ellipse,  2-Circle,  3-Triangle,  4-Rectangle,  5-Square,  0-Exit" << std::endl;
				std::cin >> x;
				switch (x)
				{
				case 1: {
					std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
					el.draw_and_move(coord_x, coord_y);

				}break;

				case 2: {
					std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
					circ.draw_and_move(coord_x, coord_y);

				}break;

				case 3: {
					std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
					tri.draw_and_move(coord_x, coord_y);

				}break;

				case 4: {
					std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
					rect.draw_and_move(coord_x, coord_y);

				}break;

				case 5: {
					std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
					sq.draw_and_move(coord_x, coord_y);
				}break;
				}
			}
		}
		else std::cout << "NO MOVING!" << std::endl;
		std::cout << "To_string example:" << std::endl;
		std::string str1;
		str1 = circ.to_str();
		std::cout << std::endl << str1 << std::endl;
	}

};
int main()
{
	app::run();
	return 0;
}