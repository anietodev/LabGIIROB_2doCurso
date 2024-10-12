#include <iostream>

class BrazoRobotico {
	private:
		double x, y, z;
		bool sujeta;
	public:
		BrazoRobotico();
		double get_x();
		double get_y();
		double get_z();
		bool get_sujeta();
		void coger();
		void soltar();
		void mover(double x_, double y_, double z_);
};
