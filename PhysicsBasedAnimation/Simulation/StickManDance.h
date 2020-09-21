/*
    Author : Ankit Patnala
    May 2020
 */

#pragma once

#ifndef  STICK_MAN_DANCE_H_
#define STICK_MAN_DANCE_H_


#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

class LineAndPoints
{
public:
	LineAndPoints(std::pair<std::pair<float, float>, std::pair<float, float>> line
		, std::pair<float, float> firstPoint,
		std::pair<float, float> secondPoint);

	std::pair<std::pair<float, float>, std::pair<float, float>> GetLine();
	std::pair<float, float> GetFirstPoint();
	std::pair<float, float> GetSecondPoint();

private:
	std::pair<std::pair<float, float>, std::pair<float, float>> m_line;
	std::pair<float, float> m_firstPoint;
	std::pair<float, float> m_secondPoint;
};

int play(std::vector<LineAndPoints>& lineAndPointsVector);

#endif