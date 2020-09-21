/*
    Author : Ankit Patnala
    May 2020
 */


#ifdef WIN32
#include "windows.h"
#endif


extern "C" {
#include <GL/freeglut.h>
}
#ifdef __linux__
#include <GL/glx.h>
#endif // __linux__


#if !defined(M_PI)
#   define M_PI 3.1415926535897932384626433832795
#endif  // !defined(M_PI)
#include "AdvectionEquation.h"

#include <math.h>

Sphere::Sphere(
    float radius, 
    float posX,
    float posY,
    float posZ) :
    m_radius(radius),
    m_posX(posX),
    m_posY(posY),
    m_posZ(posZ)
{};

void Sphere::translate(float transX, float transY, float transZ)
{
    m_posX += transX;
    m_posY += transY;
    m_posZ += transZ;
}
void Sphere::updateZ(float newZ)
{
    m_posZ = newZ;
}

float Sphere::GetX()
{
    return m_posX;
}

float Sphere::GetY()
{
    return m_posY;
}

float Sphere::GetZ()
{
    return m_posZ;
}

float Sphere::GetRadius()
{
    return m_radius;
}

namespace Solver
{
    AdvectionEquation::AdvectionEquation(
        float boxLength,
        float boxWidth,
        float boxHeight,
        float advectionSpeed,
        float numberOfParticles) :
        m_boxLength(boxLength), m_boxWidth(boxWidth), m_boxHeight(boxHeight), m_advectionSpeed(advectionSpeed), m_numberOfParticles(numberOfParticles)
    {
        int numberOfBallsPerLength = (int)(m_boxLength /0.05);
        int numberOfBallsPerWidth = (int)(m_boxWidth / 0.05);
        for (size_t numberOfBallsPerLengthIdx = 0; numberOfBallsPerLengthIdx < numberOfBallsPerLength; numberOfBallsPerLengthIdx++)
        {
            std::vector<Sphere> sphereVector;
            for (size_t numberOfBallsPerWidthIdx = 0; numberOfBallsPerWidthIdx < numberOfBallsPerWidth; numberOfBallsPerWidthIdx++)
            {
                sphereVector.push_back(
                    Sphere(0.05,
                        0.05 * numberOfBallsPerLengthIdx, 
                        0.05 * numberOfBallsPerWidthIdx,
                        AdvectionSolution(
                            0.05 * numberOfBallsPerLengthIdx,
                            0.0)));
            }
            m_vectorOfSphereVector.push_back(sphereVector);
        }
    };

    double AdvectionEquation::AdvectionSolution(float posX, float time)
    {
        return sin(3.14 * ((double)posX - m_advectionSpeed * time));
    }
    float AdvectionEquation::getBoxLength()
    {
        return m_boxLength;
    }

    float AdvectionEquation::getBoxWidth()
    {
        return m_boxWidth;
    }

    float AdvectionEquation::getBoxHeight()
    {
        return m_boxHeight;
    }

    float AdvectionEquation::getNumberOfParticles()
    {
        return m_numberOfParticles;
    }

    std::vector<std::vector<Sphere>> AdvectionEquation::getVectorOfSphere()
    {
        return m_vectorOfSphereVector;
    }
}