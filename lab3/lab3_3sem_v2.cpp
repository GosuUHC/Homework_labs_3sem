#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>



class Exc {
private:
	int number;
	std::string message;
public:
	Exc(int a, std::string b)
	{
		number = a;
		message = b;
	}
	void show()
	{
		std::cout << std::endl;
		std::cout << "Error number " << number << ":" << std::endl;
		std::cout << "\t" << message << std::endl;

	}
	~Exc() {};
};

class shape {
protected:
	std::string name;

public:
	shape(std::string name)
	{
		if (name.size() > 0) {
			this->name = name;
		}
		else throw Exc(1, "Shape name error");
	}
	virtual void draw_and_move(double coord_x, double coord_y) = 0;
	virtual double area()=0;
	virtual void show()
	{
		std::cout << "Name:" << this->Get_name() << std::endl << "S=" << area() << std::endl;
	}
	virtual std::string to_string()
	{
		std::stringstream circ;
		circ << "Name:" << this->Get_name() << "\nS=" << area() << std::endl;
		std::string circ1 = circ.str();
		return circ1;
	}
	 std::string Get_name() 
	{
		std::string name = this->name;
		return name;
	}
	shape() {};
	virtual ~shape() {
		std::cout << "shape dest!!!" << std::endl;
	}
};
class ellipse :public shape {
protected:
	double a, b;
public:
	ellipse(std::string name, double a, double b) :shape(name)
	{
		if (a >= 0 && b >= 0) {
			this->a = a;
			this->b = b;
		}
		else throw Exc(2, "Ellipse diagonals error");
	}
	double area()
	{
		return M_PI*a*b;
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
		
		ellipseslav.setPosition(100.+coord_x, 100.-coord_y);

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
	
	virtual ~ellipse() {
		std::cout << "elipse dest!" << std::endl;
	}
};

class circle : public ellipse {
protected:
	
public:
	circle(std::string name, double a) :ellipse(name, a, b)
	{
		b = a;
	}
	
	void draw_and_move(double coord_x, double coord_y)
	{
		sf::RenderWindow window(sf::VideoMode(200, 200), "Circle!");
		sf::CircleShape circleslav(a);
		circleslav.setFillColor(sf::Color::Red);
		circleslav.setPosition(100. - a+coord_x, 100. - a-coord_y);
		
		
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

	virtual ~circle() {
		std::cout << "circle dest!" << std::endl;
	};
};
class triangle : public shape {
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
		else throw Exc(3, "Triangle creating error");
	}
	double area()
	{
		double p = (a + b + c) / 2.;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	
	void draw_and_move(double coord_x, double coord_y)
	{
		double h = (2. * this->area()) / b;
		sf::RenderWindow window(sf::VideoMode(200, 200), "Triangle!");
		sf::ConvexShape triangleslav;
		triangleslav.setPointCount(3);
		triangleslav.setPoint(0, sf::Vector2f(0.f, 0.f));
		triangleslav.setPoint(1, sf::Vector2f(0.f+(sqrt(a*a-h*h)), 0.f+h));
		triangleslav.setPoint(2, sf::Vector2f(0.f-(sqrt(c*c-h*h)), 0.f+h));
		triangleslav.setFillColor(sf::Color::Cyan);
		triangleslav.setOutlineThickness(0);
		triangleslav.setPosition(100.+coord_x, 100.-h/2.-coord_y);
		
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
	virtual ~triangle() {
		std::cout << "triangle dest!" << std::endl;
	};
};
class rectangle : public shape {
protected:
	double a;
	double b;
public:
	rectangle(std::string name, double a, double b) :shape(name)
	{
		if (a >= 0 && b >= 0) {
			this->a = a;
			this->b = b;
		}
		else throw Exc(4, "Rectangle creating error");
	}
	double area()
	{
		return a * b;
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
	
	virtual ~rectangle() {
		std::cout << "rectangle dest!" << std::endl;
	};
};

class square : public rectangle {
protected:
public:
	square(std::string name, double a) :rectangle(name, a, b)
	{		
		b = a;
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
	virtual ~square() {
		std::cout << "square dest!" << std::endl;
	};
};
template<typename T>
class Cylinder {
protected:
	T* f;
private:
	double h;
public:
	Cylinder(T* f, double h)
	{
		if (h > 0) {
			this->f = f;
			this->h = h;
		}
		else throw Exc(5, "Cylinder height <=0");
	}
	double volume()
	{
		return h * f->area();
	}
	void show()
	{
		std::cout << std::endl << "Name=" << this->Get_name() << " V=" << this->volume() << "\nCreated from " << f->Get_name() << " With S=" << f->area() << std::endl;
	}
	std::string Get_name()
	{
		return f->Get_name();
	}
	std::string to_str()
	{
		std::stringstream str;
		str << "Name:" << this->Get_name() << "V=" << this->volume() << "\nCreated from " << f->Get_name() << " With S=" << f->area() << std::endl;
		std::string str1 = str.str();
		return str1;
	}
	~Cylinder() {
		std::cout << "Cylinder dest!!" << std::endl;
		delete f;
	}
};

class app
{
public:
	static void run()
	{

		double x, y;//for elliplse
		double a, b, c;//for triangle
		double a1, b1;//for rectangle
		double h1;//for trianglecylinder and circlecylinder

		double coord_x = 0, coord_y = 0;//for redrawing objects
		
		std::cout << "Enter x, y(ellipse diagonals(x will be circle radius):\n"; std::cin >> x >> y;
			std::cout << "Enter a, b, c(triangle):\n"; std::cin >> a >> b >> c;
			std::cout << "Enter a, b(rectangle sides):\n"; std::cin >> a1 >> b1;
			try {
				

				ellipse el = ellipse("Elipz", x, y);
				circle* circ = new circle("Kryg", x);
				triangle* tri = new triangle("Treygolnik", a, b, c);
				rectangle rect = rectangle("Pryamoygolnik", a1, b1);
				square* sq = new square("kvadrat", a1);

				el.show();
				(*circ).show();
				(*tri).show();
				rect.show();
				(*sq).show();
				el.draw_and_move(0, 0);
				(*circ).draw_and_move(0, 0);
				(*tri).draw_and_move(0, 0);
				rect.draw_and_move(0, 0);
				(*sq).draw_and_move(0, 0);
				bool t;
				std::cout << "Do you want to create cylinders? 0-no 1-yes" << std::endl;std::cin >> t;
				if (t) {
					int z = -1;
					while (z != 0)
					{
						std::cout << std::endl << "What cylinder do you want to create? 1-circle 2-triangle 3-square  0-exit" << std::endl;
						std::cin >> z;
						switch (z)
						{
						case 1: {
							std::cout << "CircleCylinder with r from ellipse" << std::endl;
							std::cout << "Enter height:";std::cin >> h1;

							Cylinder<circle> CYL (circ, h1);
							CYL.show();
							std::string CYLstr = CYL.to_str();

						}break;
						case 2: {
							std::cout << "TriangleCylinder with a, b, c from triangle!" << std::endl;
							std::cout << "Enter height:";std::cin >> h1;
							Cylinder<triangle> CYL(tri, h1);
							CYL.show();
							std::string CYLstr = CYL.to_str();;

						}break;
						case 3: {
							std::cout << "SquareCylinder with a=a and b=h from rectangle!" << std::endl;

							Cylinder<square> CYL(sq, h1);
							CYL.show();
							std::string CYLstr = CYL.to_str();

						}break;
						default:
						{
							break;
						}
						}
					}

				}
				std::cout << "Do you want to move objects? No-0, Yes-1" << std::endl;std::cin >> t;
				if (t)
				{
					int x1 = -1;
					while (x1 != 0)
					{
						std::cout << "What object do you want to move?\n1-Ellipse,  2-Circle,  3-Triangle,  4-Rectangle,  5-Square,  0-Exit" << std::endl;
						std::cin >> x1;
						switch (x1)
						{
						case 1: {
							std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
							el.draw_and_move(coord_x, coord_y);

						}break;

						case 2: {
							std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
							(*circ).draw_and_move(coord_x, coord_y);

						}break;

						case 3: {
							std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
							(*tri).draw_and_move(coord_x, coord_y);

						}break;

						case 4: {
							std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
							rect.draw_and_move(coord_x, coord_y);

						}break;

						case 5: {
							std::cout << "Enter coordinates x, y:" << std::endl;std::cin >> coord_x >> coord_y;
							(*sq).draw_and_move(coord_x, coord_y);
						}break;
						default: {break;}
						}
					}
				}
				else std::cout << "NO MOVING!" << std::endl;
				std::cout << "To_string example:" << std::endl;
				std::string str1;
				str1 = (*circ).to_string();
				std::cout << std::endl << str1 << std::endl;
			
				
			}
			catch (Exc exc) {
				exc.show();
			}
			catch (...) {
				std::cout << "Some unknown error" << std::endl;
			}
	}
};
int main()
{
	app::run();
	system("pause");
	return 0;
}