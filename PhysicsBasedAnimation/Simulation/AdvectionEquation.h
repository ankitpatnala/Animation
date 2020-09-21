/*   
    Author : Ankit Patnala 
    May 2020
 */



#pragma once

#ifndef  ADVECTION_EQUATION_H_
#define ADVECTION_EQUATION_H_

#include <vector>
// general equation $u_{t} + a*u_{x} = 0$

/*
enum InitialConditon
{
    sinPiX,
    cosPiX,
    LinearX
};
*/
class Sphere
{
public:
	Sphere(float radius, float posX, float posY, float posZ); 
			
	void translate(float transX, float transY, float transZ);

    void updateZ(float newZ);
	
	float GetX();
	

	float GetY();
	
	float GetZ();
	
	float GetRadius();


private:
	float m_radius;
	float m_posX, m_posY, m_posZ;
};

namespace Solver {    
    class AdvectionEquation
    {
    public:
        AdvectionEquation(float boxLength, float boxWidth, float boxHeight, float advectionSpeed,float numberOfParticles);

        double AdvectionSolution(float posX, float time);

        float getBoxLength();

        float getBoxWidth();
        
        float getBoxHeight();

        float getNumberOfParticles();

        std::vector<std::vector<Sphere>> getVectorOfSphere();


    private:
        float m_boxLength, m_boxWidth, m_boxHeight;
        float m_advectionSpeed;
        float m_numberOfParticles;
        std::vector<std::vector<Sphere>> m_vectorOfSphereVector;
    };
}

#endif

