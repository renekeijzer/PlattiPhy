#ifndef __FORCES__
#define __FORCES__
namespace Physics{
	class DragCoefficient{
		float f;
		DragCoefficient(float arg) : f(arg){}
	public:
		static const DragCoefficient sphere;
		static const DragCoefficient halfSphere;
		static const DragCoefficient cone;
		static const DragCoefficient cube;
		static const DragCoefficient angledCube;
		static const DragCoefficient longCylinder;
		static const DragCoefficient shortCylinder;
		static const DragCoefficient streamLinedBody;
		static const DragCoefficient streamLinedHalfBody;
	};

	const DragCoefficient DragCoefficient::sphere(0.47f);
	const DragCoefficient DragCoefficient::halfSphere(0.42f);
	const DragCoefficient DragCoefficient::cone(0.5f);
	const DragCoefficient DragCoefficient::cube(1.05f);
	const DragCoefficient DragCoefficient::angledCube(0.8f);
	const DragCoefficient DragCoefficient::longCylinder(0.82f);
	const DragCoefficient DragCoefficient::shortCylinder(1.15f);
	const DragCoefficient DragCoefficient::streamLinedBody(0.04f);
	const DragCoefficient DragCoefficient::streamLinedHalfBody(0.09f);

};


#endif