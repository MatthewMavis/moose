// Gmsh project created on Thu Mar  4 15:54:08 2021
//+
pi = 3.1415926535897932384626433832795028841971;
DefineConstant[Intermediate_Thickness = {0.001,Name "Intermediate_Thickness"}];
DefineConstant[Cooling_Tube_Thickness = {0.002,Name "Cooling_Tube_Thickness"}];
DefineConstant[holeSize = {0.005,Name "holeSize"}];
DefineConstant[Thermal_Slit_Width = {0.0002,Name "Thermal_Slit_Width"}];
DefineConstant[Hole_Amount = {0,Name "Hole_Amount"}];
DefineConstant[Small_Hole_Size = {0.0003,Name "Small_Hole_Size"}];
DefineConstant[Angle_between_holes = {10,Name "Angle_between_holes"}];
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
Circle(400) = {4,0,5};
Circle(401) = {5,0,100};
Circle(402) = {100,0,4};
//+
Line(5) = {5, 6};
Line(6) = {6, 7};
Line(7) = {7, 8};
Line(8) = {8, 1};
//+
Circle(900) = {200,0,201};
Circle(901) = {201,0,200};
//+
Circle(100) = {300,0,301};
Circle(101) = {301,0,300};
//+
Curve Loop(1) = {1,2,3,400,5,6,7,8};
Curve Loop(2) = {400,401,402};
Curve Loop(3) = {900,901};
Curve Loop(4) = {100,101};
//+
index = 1;
j=0;
For i In {1:(Hole_Amount)}
	If (i == 1)
		angle[index++] = (j)*(Angle_between_holes*(pi/180));
		j++;
	EndIf
	If (i > 1)
		If (((i) % 2) == 0)
			angle[index++] = ((j)*(Angle_between_holes*(pi/180)));
			j++;
		EndIf
		If (((i) % 2) != 0)
			angle[index++] = (-(j-1)*(Angle_between_holes*(pi/180)));
		EndIf
	EndIf
EndFor

For loop In {1:(Hole_Amount)}
	Printf("%g",angle[loop]);
EndFor
//+
index = 0;
PointID = 9;
CircleID = 11;
CurveID = 5;
//+
For i In {1:(Hole_Amount)}
	If (i == 1)
		x = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(Sin(angle[i]));
		y = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(Cos(angle[i]));
		Point(PointID) = {(x+Small_Hole_Size), y, 0, 1.0};
		PointID++;

		Point(PointID) = {x, y, 0, 1.0};
		PointID++;

		Point(PointID) = {(x-Small_Hole_Size), y, 0, 1.0};

		Circle(CircleID) = {(PointID-2), (PointID-1), (PointID)};
		CircleID++;

		Circle(CircleID) = {(PointID), (PointID-1), (PointID-2)};	
		Curve Loop(CurveID) = {(CircleID-1),CircleID};
		CurveIDs[index++] = CurveID;
		
		CurveID++;
		CircleID++;
		PointID++;
	EndIf
	If (i > 1)
		x = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(Sin(angle[i]));
		y = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(Cos(angle[i]));
		Point(PointID) = {(x+Small_Hole_Size), y, 0, 1.0};
		PointID++;

		Point(PointID) = {x, y, 0, 1.0};
		PointID++;

		Point(PointID) = {(x-Small_Hole_Size), y, 0, 1.0};

		Circle(CircleID) = {(PointID-2), (PointID-1), (PointID)};
		CircleID++;

		Circle(CircleID) = {(PointID), (PointID-1), (PointID-2)};	
		Curve Loop(CurveID) = {(CircleID-1),CircleID};
		CurveIDs[index++] = CurveID;
		
		CurveID++;
		CircleID++;
		PointID++;
	EndIf
EndFor
For loop In {0:index-1}
	Printf("%g",CurveIDs[loop]);
EndFor
//+
Plane Surface(1) = {1,2};

If (Hole_Amount == 0)
	Plane Surface(2) = {2,3};
EndIf

If (Hole_Amount != 0)
	Plane Surface(2) = {2,3,CurveIDs[]};
EndIf

Plane Surface(3) = {3,4};
Plane Surface(4) = {4};
//+
Physical Surface("Tungsten") = {1};
Physical Surface("Intermediate") = {2};
Physical Surface("CoolingTube") = {3};
//+
Physical Curve("Top") = {2,6};
Physical Curve("Right") = {7};
Physical Curve("Bottom") = {8};
Physical Curve("Left") = {1};
Physical Curve("Expansion_Left") = {3};
Physical Curve("Expansion_Right") = {5};
//+
Physical Curve("Tung_Int_Boundary") = {400,401,402};
Physical Curve("Int_Tube_Boundary") = {900,901};
Physical Curve("Tube_Hole_Boundary") = {100,101};
//+
Mesh.Algorithm = 6;
Mesh.ElementOrder = 2;
Mesh.HighOrderOptimize = 2;
Mesh.MeshSizeMin = 0.00001;
Mesh.MeshSizeMax = 0.0003;
