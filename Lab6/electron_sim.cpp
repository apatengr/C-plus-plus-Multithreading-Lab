//  main.cpp
//  Lab6
//
//  Created by Animesh Patel on 11/25/17.
//  Copyright © 2017 Animesh Patel. All rights reserved.

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "gthread.h"
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

#define k 1.38064852e-23 // Boltzmann's constant
#define tottimeSteps 1000000 // total # of size
#define Tau 8.92e-13 // Tau constant
#define T 300
#define m0 9.109e-31
#define e 1.602e-19
#define deltaT 8.92e-16
#define electricField -1.0e5


class electronPath{
    
private:
    double mass; // = 1.12*9.109e-31;   // mass
    double eField; // = 1.609e-19;  // electric field
    double scatTime; //= 8.92e-13;  // scattering time
    double simuTime; //= 1000.0*scatTime;  //total simulation time
    double stepTime; //= 1000000;  // time step size
   // int tottimeSteps;
    
    double *dynamicTime;
    double *xPos;
    double *zPos;
    double *vX;
    double *vZ;
    double vth;
    double Probability;
    double randomNum;
    int randAngle;

public:
    // return the velocity in x and y directions

   // double simulateVelocity(){
     //   return(9); //
    //}
    
    //return the position in x and y directions
   // double simulatePosition(){
   //     return(4);
    //}
    
    // printtofile function to print everything in a file
    
    
    // Constructor
    electronPath(double a, double b, double c, double d, double t)
    :mass(a), eField(b), scatTime(c), simuTime(d), stepTime(t)
    {
        // 1 million allocated for each
        dynamicTime = new double[totTimeSteps];
        xPos = new double[totTimeSteps];
        zPos = new double[totTimeSteps];
        vX = new double[totTimeSteps];
        vZ = new double[totTimeSteps];
        mass = 1.12* m0;
    }
    
    // Copy Constructor
    electronPath(const electronPath &pXTK)
    :mass(pXTK.mass), eField(pXTK.eField),scatTime(pXTK.scatTime), simuTime(pXTK.simuTime), stepTime(pXTK.stepTime){
    
        dynamicTime = new double[totTimeSteps];
        xPos = new double[totTimeSteps];
        zPos = new double[totTimeSteps];
        vX = new double[totTimeSteps];
        vZ = new double[totTimeSteps];
        
        for (int i = 0; i < totTimeSteps; i++){
        dynamicTime[i] = pXTK.dynamicTime[i];
        xPos[i] = pXTK.xPos[i];
        zPos[i] = pXTK.zPos[i];
        vX[i] = pXTK.vX[i];
        vZ[i] = pXTK.vZ[i];
        }
        // return NULL;
    }
    
    void operator =(const electronPath &obj){
        dynamicTime = new double[totTimeSteps];
        xPos = new double[totTimeSteps];
        zPos = new double[totTimeSteps];
        vX = new double[totTimeSteps];
        vZ = new double[totTimeSteps];
        
        for (int i = 0; i < totTimeSteps; i++){

            dynamicTime[i] = obj.dynamicTime[i];
            xPos[i] = obj.xPos[i];
            zPos[i] = obj.zPos[i];
            vX[i] = obj.vX[i];
            vZ[i] = obj.vZ[i];
        }
    }
    
    //overloading assignment operator
    //electronPath& operator= (const electronPath &object){
    // ostream& operator << (ostream& out, const electronPath &obj1);
    //  }
    
void simulateVelocity(){
    srand(time(NULL));
    for (int i = 1; i < totTimeSteps; i++){
        dynamicTime[i] = (i*1000*Tau)/totTimeSteps;
        Probability = deltaT/Tau; // P
        randomNum = rand()%10000;
        randomNum = randomNum/10000; // randomNumber
        
        // if randomNum is less than the probability, then generate random angle
        if (randomNum < Probability){
            randAngle = rand() % 360; // random angle
            vth = sqrt(((2*k*T)/mass));
            vX[i] = vth*sin(randAngle);
            vZ[i] = vth*cos(randAngle);
        }
        
        else{
            vX[i] = vX[i - 1];
            vZ[i] = vZ[i - 1] - ((eField*e)/mass)*deltaT;
        }
    }
}
  
    // simulating position
    void simulatePosition(){
        for (int i = 1; i < totTimeSteps; i++){
            xPos[i] = xPos[i-1] + vX[i-1]*deltaT;
            zPos[i] = zPos[i-1] + vZ[i-1]*deltaT;
        }
    }
    
    ~electronPath(){ // destructor
        
        delete[] dynamicTime;
        delete[] xPos;
        delete[] zPos;
        delete[] vX;
        delete[] vZ;
    }
    
    
    void printToFile(string name){
        
        // printToFile member function to print an electronPath’s time t and x and z positions on each time step to a data file in comma-separated format
        ofstream ofs(name);
        //ofs.open(name, ofstream::out);
        
        for (int i = 0; i < totTimeSteps; i++){
            ofs << dynamicTime[i] << ", " << xPos[i] << ", " << zPos[i] << endl;
            
        }
        
        ofs.close();
    }
    
    // overloading + operator
    electronPath operator+ (const electronPath& A){
        // making an object
        electronPath obj(A.mass, A.eField, A.scatTime, A.simuTime, A.stepTime);
        
        for (int i = 0; i < totTimeSteps; i++){
            obj.dynamicTime[i] = A.dynamicTime[i] + dynamicTime[i];
            obj.xPos[i] = A.xPos[i] + xPos[i];
            obj.zPos[i] = A.zPos[i] + zPos[i];
            obj.vX[i] = A.vX[i]+ vX[i];
            obj.vZ[i] = A.vZ[i] + vZ[i];
        }
        return obj;
    }
    
    
    // overloading operator
    
    electronPath operator /(double C){
        // making an object
        //electronPath obj(&dynamicTime);
            electronPath temporary(0,0,0,0,0);
        for (int i  = 0; i < totTimeSteps; i++) {
            
            temporary.dynamicTime[i] = temporary.dynamicTime[i]/C;
            
            temporary.xPos[i] = temporary.xPos[i]/C;
            
            temporary.zPos[i] = temporary.zPos[i]/C;
            
            temporary.vX[i] = temporary.vX[i]/C;
            
            temporary.vZ[i] = temporary.vZ[i]/C;
            
            //dynamicTime[i] = dynamicTime[i]/C;
            
            //xPos[i] = xPos[i]/C;
            
            //zPos[i] = zPos[i]/C;
            
            //vX[i] = vX[i]/C;
            
            //vZ[i] = vZ[i]/C;
        }
        
        return temporary;
    }
protected:
    int totTimeSteps;
    
};

    void run_sim(electronPath *ptr){
        ptr->simulatePosition();
        ptr->simulateVelocity();
        EndThread();
    }
    
    electronPath average_paths(vector<electronPath> objects){
        electronPath temporary(objects[0]);
        
        int sizeee = objects.size();
        
        //for (int j = 0; j < totTimeSteps; j++){
            
            for (int i = 1; i < sizeee; i++){
                temporary = temporary + objects[i];
                /*temporary.dynamicTime[i] = temporary.dynamicTime[i] + objects[i].dynamicTime[i];
                temporary.xPos[i] = temporary.xPos[i] + objects[i].xPos[i];
                temporary.zPos[i] = temporary.zPos[i] + objects[i].zPos[i];
                temporary.vX[i] = temporary.vX[i] + objects[i].vX[i];
                temporary.vZ[i] = temporary.vZ[i] + objects[i].vZ[i];*/
            }
           // temporary.
            temporary = temporary/sizeee;
        //}
        return temporary;
    }
    
   
    
        // double** info = new double* [10];  // double
    // total of 1000000 time steps, each has five components
    /*
    double* dynamicTime = new double[1000000] ();
    double* xPos = new double[1000000] ();
    double* zPos = new double[1000000] ();
    double* vX = new double [1000000] ();
    double* vZ = new double [1000000] ();
    */
    



int main(){
    srand(time(NULL));
    
    int numelepaths = 0;
    
    cout << "How many threads you want? " << endl;
    cin >> numelepaths;
    
    vector<electronPath> vec;
    
    for (int i = 0; i < numelepaths; i++){
        electronPath object(1.12* m0, electricField, Tau, 1000*Tau, deltaT);
        vec.push_back(object);
    }
    
    for (int j = 0; j < numelepaths; j++){
        CreateThread(run_sim,&(vec[j]));
        // createThread(run_simulation, vec[i]);
    }
    
    WaitAllThreads();
    string file;
    cout << "enter the file name " << endl;
    cin>> file;
    
    vec[1].printToFile(file);
    
    string file2;
    cout << "enter the file name 2: " << endl;
    cin >> file2;
    
    electronPath temp = average_paths(vec);
    temp.printToFile(file2);
    
    return 0;
}
