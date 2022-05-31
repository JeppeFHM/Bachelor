// RampCoords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include<cmath>
float pi = 3.141592653589793238463;
using namespace std;
#include <string>
#include <fstream>
#include<sstream>

using namespace std;

struct Location {
    float x, y, z, e;
};



vector<float> ArmPoints3(float x, float y, float arm1L, float arm2L) {
    float orgx = 0;
    float orgy = 0;
    float PrevBigArmAngle = 180;
    float dist = sqrtf(pow((x - orgx), 2) + pow((y - orgx), 2));
    cout << "dist = " << dist << endl;

    float sigma = 0.25 * sqrt((dist + arm1L + arm2L) * (dist + arm1L - arm2L) * (dist - arm1L + arm2L) * (-dist + arm1L + arm2L));
    cout << "sigma = " << sigma << endl;

    float x1 = ((orgx + x) / 2) + (((x - orgx) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) + 2 * ((orgy - y) / (pow(dist, 2))) * sigma));
    cout << "x1 = " << x1 << endl;

    float y1 = ((orgy + y) / 2) + (((y - orgy) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) - 2 * ((orgx - x) / (pow(dist, 2))) * sigma));
    cout << "y1 = " << y1 << endl;

    float x2 = ((orgx + x) / 2) + (((x - orgx) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) - 2 * ((orgy - y) / (pow(dist, 2))) * sigma));
    cout << "x2 = " << x2 << endl;

    float y2 = ((orgy + y) / 2) + (((y - orgy) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) + 2 * ((orgx - x) / (pow(dist, 2))) * sigma));
    cout << "y2 = " << y2 << endl;

    float firstArmAngle1 = atan2(y2, x2);
    float firstArmAngle2 = atan2(y1, x1);

    float distPtoOrg = sqrtf(pow(x, 2) + pow(y, 2));

    float secondArmAngle1 = 2 * pi - acos((pow(arm1L, 2) + pow(arm2L, 2) - pow(distPtoOrg, 2)) / (2 * arm1L * arm2L));
    float secondArmAngle2 = (acos((pow(arm1L, 2) + pow(arm2L, 2) - pow(distPtoOrg, 2)) / (2 * arm1L * arm2L)));

    firstArmAngle1 = firstArmAngle1 * (180 / pi);
    secondArmAngle1 = secondArmAngle1 * (180 / pi);

    firstArmAngle2 = firstArmAngle2 * (180 / pi);
    secondArmAngle2 = secondArmAngle2 * (180 / pi);


    cout << "arm 1 angle1:  " << firstArmAngle1 << endl << endl;
    cout << "arm 2 angle1:  " << secondArmAngle1 << endl << endl;

    cout << "arm 1 angle2:  " << firstArmAngle2 << endl << endl;
    cout << "arm 2 angle2:  " << secondArmAngle2 << endl << endl;

    vector<float> solution1;
    vector<float> solution2;

    solution1.push_back(firstArmAngle1);
    solution1.push_back(secondArmAngle1);

    solution2.push_back(firstArmAngle2);
    solution2.push_back(secondArmAngle2);

    float sol1DifferenceFromLastArm = abs(firstArmAngle1 - PrevBigArmAngle);
    float sol2DifferenceFromLastArm = abs(firstArmAngle2 - PrevBigArmAngle);

    if (y1 <= 0) {
        return solution1;
    }

    else if (y2 <= 0) {
        return solution2;
    }

    else if (sol1DifferenceFromLastArm > sol2DifferenceFromLastArm) {
        return solution2;

    }

    else return solution1;



}


vector<float> ArmAngle2(float x1, float y1, float x, float y, float arm1L, float arm2L) {

    float firstArmAngle = atan2(y1, x1);
    cout << x1 << ", " << y1 << endl << endl;
    float distPtoOrg = sqrtf(pow(x, 2) + pow(y, 2));
    float secondArmAngle = acos((pow(arm1L, 2) + pow(arm2L, 2) - pow(distPtoOrg, 2)) / (2 * arm1L * arm2L));
    firstArmAngle = firstArmAngle * (180 / pi);
    secondArmAngle = secondArmAngle * (180 / pi);

    if (firstArmAngle < 90.0) {
        secondArmAngle = 360 - secondArmAngle;
    }

    vector<float> anglesRad;
    anglesRad.push_back(firstArmAngle);
    anglesRad.push_back(secondArmAngle);
    cout << "arm 1 angle:  " << firstArmAngle << endl << endl;
    cout << "arm 2 angle:  " << secondArmAngle << endl << endl;
    return anglesRad;



}

vector<float> ArmPoints2(float x, float y, float arm1L, float arm2L, float destx, float desty) {
    float orgx = 0;
    float orgy = 0;
    float PrevBigArmAngle = 0;
    float dist = sqrtf(pow((x - orgx), 2) + pow((y - orgx), 2));
    cout << "dist = " << dist << endl;

    float sigma = 0.25 * sqrt((dist + arm1L + arm2L) * (dist + arm1L - arm2L) * (dist - arm1L + arm2L) * (-dist + arm1L + arm2L));
    cout << "sigma = " << sigma << endl;

    float x1 = ((orgx + x) / 2) + (((x - orgx) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) + 2 * ((orgy - y) / (pow(dist, 2))) * sigma));
    cout << "x1 = " << x1 << endl;

    float y1 = ((orgy + y) / 2) + (((y - orgy) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) - 2 * ((orgx - x) / (pow(dist, 2))) * sigma));
    cout << "y1 = " << y1 << endl;

    float x2 = ((orgx + x) / 2) + (((x - orgx) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) - 2 * ((orgy - y) / (pow(dist, 2))) * sigma));
    cout << "x2 = " << x2 << endl;

    float y2 = ((orgy + y) / 2) + (((y - orgy) * ((pow((arm1L), 2) - pow((arm2L), 2)) / (2 * pow(dist, 2))) + 2 * ((orgx - x) / (pow(dist, 2))) * sigma));
    cout << "y2 = " << y2 << endl;



    //if (y1 <= 0) {
    //    vector<float> cord1;
    //    return ArmAngle2(x2, y2, destx, desty, arm1L, arm2L);
    //    cout << "y2 = " << y2 << endl;
    //    cout << "x2 = " << x2 << endl;
    //    return cord1;
    //}
    //else {
    //    vector<float> firstPosb = ArmAngle2(x1, y1, destx, desty, arm1L, arm2L);
    //    vector<float> SecondPosb = ArmAngle2(x2, y2, destx, desty, arm1L, arm2L);

    //    if (firstPosb[1] > SecondPosb[1]) {
    //        cout << SecondPosb[1] << ",,, " << SecondPosb[0] << endl;
    //        return SecondPosb;
    //    }
    //    else {
    //        cout << firstPosb[1] << ", " << firstPosb[0] << endl;
    //        return firstPosb;
    //    }
    //}


    if (y1 <= 0) {
        vector<float> cord1;
        return ArmAngle2(x2, y2, destx, desty, arm1L, arm2L);
        cout << "y2 = " << y2 << endl;
        cout << "x2 = " << x2 << endl;
        return cord1;
    }
    else {
        vector<float> firstPosb = ArmAngle2(x1, y1, destx, desty, arm1L, arm2L);
        vector<float> SecondPosb = ArmAngle2(x2, y2, destx, desty, arm1L, arm2L);
        float FirstPosClosenessToLastAngle = abs(firstPosb[1] - PrevBigArmAngle);
        float SecondPosClosenessToLastAngle = abs(SecondPosb[1] - PrevBigArmAngle);

        if (FirstPosClosenessToLastAngle > SecondPosClosenessToLastAngle) {
            cout << SecondPosb[1] << ",,, " << SecondPosb[0] << endl;
            PrevBigArmAngle = SecondPosb[1];

            return SecondPosb;
        }
        else {
            cout << firstPosb[1] << ", " << firstPosb[0] << endl;
            PrevBigArmAngle = firstPosb[1];
            return firstPosb;
        }
    }


}



vector<pair<int, int>> readFile() {
    vector<int> tempStorage;
    vector<pair<int, int>> inputCords;
    fstream myFile;
    myFile.open("cords.txt", ios::in);
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            cout << line << endl;
            stringstream ss(line);

            while (ss.good()) {
                string substr;
                if (std::isspace(ss.peek())) ss >> std::ws;
                getline(ss, substr, ',');
                int num;


                num = std::stoi(substr);

                tempStorage.push_back(num);
                cout << substr << endl << endl;
            }
            inputCords.push_back(make_pair(tempStorage[1], tempStorage[0]));
            tempStorage.clear();
        }
        myFile.close();
    }
    cout << "done" << endl;
    return inputCords;
}


void writeAngleFile(vector<pair<int, int>> inputVec) {

    vector<pair<float, float>> AnglesVector;
    vector<float> tempAngleStorage;

    int vectorSize = inputVec.size();
    for (int i = 0; i < vectorSize; i++) {
        cout << " x = " << inputVec[i].second << "  y =  " << inputVec[i].first << endl << endl;
        tempAngleStorage = ArmPoints2(inputVec[i].second, inputVec[i].first, 140.0, 140.0, inputVec[i].first, inputVec[i].second);
        AnglesVector.push_back(make_pair(tempAngleStorage[0], tempAngleStorage[1]));
        tempAngleStorage.clear();

    }


    fstream myFile;
    myFile.open("outputCords.txt", ios::out);
    if (myFile.is_open()) {
        for (int j = 0; j < AnglesVector.size(); j++) {
            //  myFile << AnglesVector[j].first << "," << AnglesVector[j].second << "\n";
            myFile << "moveTo(" << static_cast<int>(AnglesVector[j].first) << "," << static_cast<int>(AnglesVector[j].second) << ");" << "\n";


        }
        myFile.close();
    }

}

void writeAngleFile2(vector<pair<int, int>> inputVec) {

    vector<pair<float, float>> AnglesVector;
    vector<float> tempAngleStorage;

    int vectorSize = inputVec.size();
    for (int i = 0; i < vectorSize; i++) {
        cout << " x = " << inputVec[i].second << "  y =  " << inputVec[i].first << endl << endl;
        tempAngleStorage = ArmPoints3(inputVec[i].second, inputVec[i].first, 140.0, 140.0);   // husk at ændre arm længde her. sat til 143 efter nyt arm design længde
        AnglesVector.push_back(make_pair(tempAngleStorage[0], tempAngleStorage[1]));
        tempAngleStorage.clear();

    }


    fstream myFile;
    myFile.open("outputCords.txt", ios::out);
    if (myFile.is_open()) {
        for (int j = 0; j < AnglesVector.size(); j++) {
            //  myFile << AnglesVector[j].first << "," << AnglesVector[j].second << "\n";
            myFile << "moveTo(" << (AnglesVector[j].first) << "," << (AnglesVector[j].second) << ");" << "\n";



        }
        myFile.close();
    }

}

void writeAngleFile3(vector<pair<float, float>> inputVec , vector<Location> RampCords) {



    fstream myFile;
    myFile.open("outputCords.txt", ios::out);
    if (myFile.is_open()) {
        for (int j = 0; j < inputVec.size(); j++) {
            //  myFile << AnglesVector[j].first << "," << AnglesVector[j].second << "\n";
            myFile << (inputVec[j].first) << "," << (inputVec[j].second) << "," << (RampCords[j].z) << "," << (RampCords[j].e) << "\n";



        }
        myFile.close();
    }


}


float GenerateRampInc(float inc, float height, float wdt) {

    float B = 90 - inc;
    double rads = B * pi / 180;
    float length = height * tan(rads);
    float funcInc = height / length;
    return funcInc;

}


float GenerateRampLgt(int inc, int height, float wdt) {

    double B = 90 - inc;
    double rads = B * pi / 180;
    float length = height * tan(rads);
    float funcInc = height / length;
    return length;

}

float Functionx(float FuncInc, float y) {
    return y/FuncInc ;
}


vector<Location> GenerateBase(float weidth,float x0,float length,float offset, float z , float e, float xoff, float yoff) {
    vector<float> line1;
    vector<float> line2;
    vector<Location> path;

    for (float i = x0; i < length; i = i + offset) {
        line1.push_back(i);
        line2.push_back(i);
    }

    path.push_back({ x0 + xoff,0 + yoff,z,e }); // starting point

    
    for (int i = 0; i < line1.size() -2; i = i+2) {

        path.push_back({ line1[i]+ xoff, weidth + yoff,z, e });
        path.push_back({ line1[i + 1] + xoff, weidth+ yoff,z,e });
        path.push_back({ line2[i + 1] + xoff, 0 + yoff ,z,e});
        path.push_back({ line2[i + 2] + xoff, 0 + yoff ,z,e});
        

    }

    return path;

}

vector<Location> GenerateFinalRamp(float inc, float height, float wdt, float offset,float zStep, float e, float xoff, float yoff) {
    
    vector<Location> FinalPath;
    vector<Location> Temp;



    for (float i = 0; i < height; i = i + zStep) {
        float x0 = Functionx(GenerateRampInc(inc,height,wdt), i);
        float Length = GenerateRampLgt(inc, height, wdt);

       Temp=GenerateBase(wdt,x0,Length,offset,i,e, xoff, yoff);
       FinalPath.insert(FinalPath.end(), Temp.begin(), Temp.end());

    }

    return FinalPath;


}
float distance(float x1, float y1, float x2, float y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
        pow(y2 - y1, 2) * 1.0);
}
vector<Location> PointsOnLine2(float x0, float y0, float x1, float y1, float e, float z) {
    vector<Location> LinePoints;
    float split = 4;
    float xdistance = (x1 - x0);
    float ydistance = (y1 - y0);

    float xstep = xdistance / split;
    float ystep = ydistance / split;
    LinePoints.push_back({ x0 , y0 ,z,0 });
    for (int i = 1; i < split + 1; i++)
    {
        LinePoints.push_back({ x0 + i * xstep, y0 + i * ystep,z, distance(x0 + i * xstep, y0 + i * ystep,x0 + (i - 1) * xstep, y0 + (i - 1) * ystep) * e });

    };


    return LinePoints;
}
vector<Location> GenerateInfill(float RecWidth, float RecLength, float x0, float y0, float offset, float spacing, float filamentDiameter , float z, float e) {
    vector<Location> FinalPath;
    vector<pair<float, float>> line1;
    vector<pair<float,float>> line2;
    vector<pair<float, float>> combined;
    RecWidth = RecWidth - 2 * filamentDiameter;
    RecLength = RecLength - 2 * filamentDiameter;
    x0 = x0 - filamentDiameter;
    y0 = y0 + filamentDiameter;

    Location startingPos = {x0 , y0 , z, 0};

    float lineNumberOfPoints = (RecLength / spacing) ;
     
    for (float i = 0; i-3 < lineNumberOfPoints ; i = i++) // dono why -3 is ineeded to reach full length
    {
        line1.push_back(make_pair(x0 + i*spacing, y0 -3));

    }
    for (float i = 0; i-3 < lineNumberOfPoints; i =i++) // same
    {
        line2.push_back(make_pair(x0 + i*spacing, y0+ RecWidth +3)); // added +2 because infill does not reach the edges for some reason

    }

    for (float i = 0; i -3 < lineNumberOfPoints -2 ; i= i+3) {
        combined.push_back(line1[i]);
        combined.push_back(line1[i+1]);
        combined.push_back(line2[i+1]);
        combined.push_back(line2[i + 2]);
        
    }



    if(size(combined) != 0)
    FinalPath.push_back({ combined[0].first,combined[0].second,z,0 });

    for (int i = 1; i < size(combined) - 2; i++)
    {
        FinalPath.push_back({ combined[i].first,combined[i].second,z,distance(combined[i - 1].first,combined[i - 1].second,combined[i].first,combined[i].second)*e });

    };

    vector<Location> infillPoints;
    vector<Location> infillPoints2;

    for (int i = 0; i < size(FinalPath) - 1; i++) {
        infillPoints = (PointsOnLine2(FinalPath[i].x, FinalPath[i].y, FinalPath[i + 1].x, FinalPath[i + 1].y, e, FinalPath[i].z));
        infillPoints2.insert(infillPoints2.end(), infillPoints.begin(), infillPoints.end());
    }
    return infillPoints2;

}

vector<Location> PointsOnLine(float x0, float y0, float x1, float y1, float e, float z) {
    vector<Location> LinePoints;
    float split = 8;
    float xdistance = (x1 - x0);
    float ydistance = (y1 - y0);

    float xstep = xdistance / split;
    float ystep = ydistance / split;
    LinePoints.push_back({ x0 , y0 ,z,0 });
        for (int i = 1; i < split +1; i++)
        {
            LinePoints.push_back({ x0 + i * xstep, y0 + i * ystep,z, distance(x0 + i * xstep, y0 + i * ystep,x0 + (i - 1) * xstep, y0 + (i - 1) * ystep)*e });

        };

        return LinePoints;
}


vector<Location> GenerateSimpleRamp(float inc, float height, float wdt, float zstep, float e, float xoff, float yoff) {

    float length = GenerateRampLgt(inc, height, wdt);
    float inc2 = GenerateRampInc(inc, height, wdt);

    vector<Location> holder;
    vector<Location> finalPath;


 /*   for ( float i = 0; i < height; i = i + zstep)
    {
        finalPath.push_back({ Functionx(inc2,i)+ xoff,0+ yoff,i,-600 });
        
        finalPath.push_back({ Functionx(inc2,i)+ xoff,wdt+yoff,i,                distance(Functionx(inc2,i)+xoff , 0+yoff , Functionx(inc2,i) + xoff,  wdt + yoff)*e});
        finalPath.push_back({ length + xoff,wdt+yoff,i,             distance(Functionx(inc2,i) + xoff , wdt + yoff , length + xoff , wdt + yoff)*e });
        finalPath.push_back({ length+ xoff,0+ yoff,i,                distance(length + xoff,wdt + yoff,length + xoff,0 + yoff)*e });
        finalPath.push_back({ Functionx(inc2,i + zstep) + xoff,0 + yoff,i,          distance(length + xoff,0 + yoff,Functionx(inc2,i + zstep) + xoff,0 + yoff) * e });
        vector<Location> infill;
        infill = (GenerateInfill(wdt , abs(length-Functionx(inc2, i)), Functionx(inc2, i + zstep) + xoff,yoff, 0 + yoff,2.0,2.0,i, e));
   
        finalPath.insert(finalPath.end(), infill.begin(), infill.end());
    };*/

    //for (float i = 0; i < height; i = i + zstep)
    //{
    //    finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i,-600 });
    //    vector<Location> Line1;
    //    Line1 = PointsOnLine (Functionx(inc2, i) + xoff, 0 + yoff, Functionx(inc2, i) + xoff, wdt + yoff, e, i);
    //    finalPath.insert(finalPath.end(), Line1.begin(), Line1.end());

    //    vector<Location> Back;
    //    Back = PointsOnLine(Functionx(inc2, i) + xoff, wdt + yoff, Functionx(inc2, i) + xoff, 0 + yoff, e, i);
    //    finalPath.insert(finalPath.end(), Back.begin(), Back.end());

    //    vector<Location> Return;
    //    Return = PointsOnLine(Functionx(inc2, i) + xoff, 0 + yoff, Functionx(inc2, i) + xoff, wdt + yoff, e, i);
    //    finalPath.insert(finalPath.end(), Return.begin(), Return.end());



    //    vector<Location> Line2;
    //    Line2= PointsOnLine(Functionx(inc2, i) + xoff, wdt + yoff, length + xoff, wdt + yoff, e, i);
    //    finalPath.insert(finalPath.end(), Line2.begin(), Line2.end());
    //    vector<Location> Line3;
    //    Line3 =PointsOnLine(length + xoff, wdt + yoff, length + xoff, 0 + yoff, e, i);
    //    finalPath.insert(finalPath.end(), Line3.begin(), Line3.end());
    //    vector<Location> Line4;
    //    Line4 =PointsOnLine(length + xoff, 0 + yoff, Functionx(inc2, i + zstep) + xoff, 0 + yoff, e, i);
    //     finalPath.insert(finalPath.end(), Line4.begin(), Line4.end());
    //    vector<Location> infill;
    //    infill = (GenerateInfill(wdt, abs(length - Functionx(inc2, i)), Functionx(inc2, i + zstep) + xoff, yoff, 0 + yoff, 4, 2.0, i, e));
    //    finalPath.insert(finalPath.end(), infill.begin(), infill.end());

    //    Location current = finalPath.back(); // get end position
    //    current.z = i + 5; // lift up end positinop
    //    current.e = 0; // stop extrustion
    //    finalPath.push_back(current); // add to path
    //    finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i+5,0 }); // move over to next layer
    //    finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i + zstep,0 }); // lower nozzle
    //};

    for (float i = 0; i < height; i = i + zstep)
    {
        finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i,-600 });
        vector<Location> Line1;
        Line1 = PointsOnLine(Functionx(inc2, i) + xoff, 0 + yoff, Functionx(inc2, i) + xoff, wdt + yoff, e , i);
        finalPath.insert(finalPath.end(), Line1.begin(), Line1.end());

        vector<Location> Back;
        Back = PointsOnLine(Functionx(inc2, i) + xoff, wdt + yoff, Functionx(inc2, i) + xoff + 1, wdt + yoff, e, i);
        finalPath.insert(finalPath.end(), Back.begin(), Back.end());

        vector<Location> Return;
        Return = PointsOnLine(Functionx(inc2, i) + xoff + 1, wdt + yoff, Functionx(inc2, i) + xoff +1,  yoff, e, i);
        finalPath.insert(finalPath.end(), Return.begin(), Return.end());

        vector<Location> Return2;
        Return2 = PointsOnLine(Functionx(inc2, i) + xoff + 1, yoff, Functionx(inc2, i) + xoff + 2,  yoff, e, i);
        finalPath.insert(finalPath.end(), Return2.begin(), Return2.end());


        vector<Location> Back2;
        Back2 = PointsOnLine(Functionx(inc2, i) + xoff + 2,  yoff, Functionx(inc2, i) + xoff + 2, wdt + yoff, e, i);
        finalPath.insert(finalPath.end(), Back2.begin(), Back2.end());

        vector<Location> Back3;
        Back3 = PointsOnLine(Functionx(inc2, i) + xoff +2 , wdt + yoff, Functionx(inc2, i) + xoff + 3, wdt + yoff, e, i);
        finalPath.insert(finalPath.end(), Back3.begin(), Back3.end());

        vector<Location> Return3;
        Return3 = PointsOnLine(Functionx(inc2, i) + xoff + 3, wdt + yoff, Functionx(inc2, i) + xoff + 3, yoff, e, i);
        finalPath.insert(finalPath.end(), Return3.begin(), Return3.end());

        vector<Location> Return4;
        Return4 = PointsOnLine(Functionx(inc2, i) + xoff + 3, yoff, Functionx(inc2, i) + xoff + 4, yoff, e, i);
        finalPath.insert(finalPath.end(), Return4.begin(), Return4.end());


        vector<Location> Back4;
        Back4 = PointsOnLine(Functionx(inc2, i) + xoff + 4, yoff, Functionx(inc2, i) + xoff + 4, wdt + yoff, e, i);
        finalPath.insert(finalPath.end(), Back4.begin(), Back4.end());





        vector<Location> Line2;
        Line2 = PointsOnLine(Functionx(inc2, i) + xoff, wdt + yoff, length + xoff, wdt + yoff, e, i);
        finalPath.insert(finalPath.end(), Line2.begin(), Line2.end());
        vector<Location> Line3;
        Line3 = PointsOnLine(length + xoff, wdt + yoff, length + xoff, 0 + yoff, e, i);
        finalPath.insert(finalPath.end(), Line3.begin(), Line3.end());
        vector<Location> Line4;
        Line4 = PointsOnLine(length + xoff, 0 + yoff, Functionx(inc2, i + zstep) + xoff, 0 + yoff, e, i);
        finalPath.insert(finalPath.end(), Line4.begin(), Line4.end());
        vector<Location> infill;
        infill = (GenerateInfill(wdt, abs(length - Functionx(inc2, i)), Functionx(inc2, i + zstep) + xoff, yoff, 0 + yoff, 4, 2.0, i, e));
        finalPath.insert(finalPath.end(), infill.begin(), infill.end());

        Location current = finalPath.back(); // get end position
        current.z = i + 5; // lift up end positinop
        current.e = 0; // stop extrustion
        finalPath.push_back(current); // add to path
        finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i + 5,0 }); // move over to next layer
        finalPath.push_back({ Functionx(inc2,i) + xoff,0 + yoff,i + zstep,0 }); // lower nozzle
    };


   

    

    return finalPath;
}

vector<Location> GenerateCalCube(float x, float y, float height, float zstep, float e, float xoff, float yoff) {



    vector<Location> holder;
    vector<Location> finalPath;



    for (float i = 0; i < height; i = i + zstep)
    {
        finalPath.push_back({xoff, yoff,i,-200 });
        vector<Location> Line1;
        Line1 = PointsOnLine( xoff,yoff, x+ xoff, yoff, e, i );
        finalPath.insert(finalPath.end(), Line1.begin(), Line1.end());
        vector<Location> Line2;
        Line2 = PointsOnLine(x + xoff, yoff, x+ xoff, y+yoff, e, i);
        finalPath.insert(finalPath.end(), Line2.begin(), Line2.end());
        vector<Location> Line3;
        Line3 = PointsOnLine(x + xoff, y + yoff, xoff, y+ yoff, e, i);
        finalPath.insert(finalPath.end(), Line3.begin(), Line3.end());
        vector<Location> Line4;
        Line4 = PointsOnLine(xoff, y + yoff,  xoff, yoff, e, i);
        finalPath.insert(finalPath.end(), Line4.begin(), Line4.end());
        //Location current = finalPath.back(); // get end position
        //current.z = i + 5; // lift up end positinop
        //current.e = 0; // stop extrustion
        //finalPath.push_back(current); // add to path
        //finalPath.push_back({ xoff+x,   y + yoff,    i + 5,   0 }); // move over to next layer
        //finalPath.push_back({ x+xoff,  y + yoff,    i + zstep,0 }); // lower nozzle
    };






    return finalPath;
}

int main()
{
    std::cout << "Hello World!\n";
    vector<Location> RampCords;
    vector<pair<float, float>>RampCordsXY;
    //RampCords = GenerateFinalRamp(10, 7.5, 50, 2, 0.25, -400, 0, 120);

    // vector<Location> GenerateSimpleRamp(float inc, float height, float wdt, float zstep, float e, float xoff, float yoff) {


    //RampCords = GenerateSimpleRamp(20, 38.24, 180, 0.9, -230, 20, 60);
    RampCords = GenerateCalCube(125, 125, 10, 0.9, -230, 0, 75);
    //RampCords.push_back({ 50,50,100,0 });

    vector<pair<float, float>> AnglesVector;
    vector<float> tempAngleStorage;

    int vectorSize = RampCords.size();
    for (int i = 0; i < vectorSize; i++) {
        cout << " x = " << RampCords[i].x << "  y =  " << RampCords[i].y << endl << endl;
        tempAngleStorage = ArmPoints3(RampCords[i].x, RampCords[i].y, 140.0, 140.0);   // husk at ændre arm længde her. sat til 143 efter nyt arm design længde
        AnglesVector.push_back(make_pair(tempAngleStorage[0], tempAngleStorage[1]));
        tempAngleStorage.clear();

    }

    

    writeAngleFile3(AnglesVector,RampCords); 
}

