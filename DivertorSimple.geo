// Gmsh project created on Thu Mar  4 15:54:08 2021
//+
DefineConstant[Intermediate_Thickness = {0.001,Name "Intermediate_Thickness"}];
DefineConstant[Cooling_Tube_Thickness = {0.002,Name "Cooling_Tube_Thickness"}];
DefineConstant[holeSize = {0.005,Name "holeSize"}];
DefineConstant[Thermal_Slit_Width = {0.0002,Name "Thermal_Slit_Width"}];
//+
SetFactory("Built-in");
//+
Point(0) = {0, 0, 0, 1.0};
Point(100) = {0, -(holeSize + Cooling_Tube_Thickness + Intermediate_Thickness), 0, 1.0};
//+
Point(200) = {0, (holeSize + Cooling_Tube_Thickness), 0, 1.0};
Point(201) = {0, -(holeSize + Cooling_Tube_Thickness), 0, 1.0};
//+
Point(300) = {0, (holeSize), 0, 1.0};
Point(301) = {0, -(holeSize), 0, 1.0};
//+
Point(1) = {-0.014, -0.014, 0, 1.0};
Point(2) = {-0.014, 0.014, 0, 1.0};
//+
Point(3) = {-(Thermal_Slit_Width/2), 0.014, 0, 1.0};
Point(4) = {-(Thermal_Slit_Width/2), (holeSize + Cooling_Tube_Thickness + Intermediate_Thickness), 0, 1.0};
Point(5) = {(Thermal_Slit_Width/2), (holeSize + Cooling_Tube_Thickness + Intermediate_Thickness), 0, 1.0};
Point(6) = {(Thermal_Slit_Width/2), 0.014, 0, 1.0};
//+
Point(7) = {0.014, 0.014, 0, 1.0};
Point(8) = {0.014, -0.014, 0, 1.0};
//+
Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
//+
Circle(4) = {4,0,5};
Circle(41) = {5,0,100};
Circle(42) = {100,0,4};
//+
Line(5) = {5, 6};
Line(6) = {6, 7};
Line(7) = {7, 8};
Line(8) = {8, 1};
//+
Circle(9) = {200,0,201};
Circle(91) = {201,0,200};
//+
Circle(10) = {300,0,301};
Circle(101) = {301,0,300};
//+
Curve Loop(1) = {1,2,3,4,5,6,7,8};
Curve Loop(2) = {4,41,42};
Curve Loop(3) = {9,91};
Curve Loop(4) = {10,101};
//+
Plane Surface(1) = {1,2};
Plane Surface(2) = {2,3};
Plane Surface(3) = {3,4};
Plane Surface(4) = {4};
//+
Physical Surface("Tungsten") = {1};
Physical Surface("Intermediate") = {2};
Physical Surface("CoolingTube") = {3};
Physical Surface("Hole") = {4};
//+
Physical Curve("Top") = {2,6};
Physical Curve("Right") = {7};
Physical Curve("Bottom") = {8};
Physical Curve("Left") = {1};
//+
Physical Curve("Tung_Int_Boundary") = {4,41,42};
Physical Curve("Int_Tube_Boundary") = {9,91};
Physical Curve("Tube_Hole_Boundary") = {10,101};
//+
Mesh.Algorithm = 6;
Mesh.ElementOrder = 2;
Mesh.HighOrderOptimize = 2;
Mesh.MeshSizeMin = 0.00001;
Mesh.MeshSizeMax = 0.0003;
