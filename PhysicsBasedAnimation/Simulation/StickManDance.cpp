/*
	Author : Ankit Patnala
	May 2020
 */

#include "StickManDance.h"
#include <iostream>
#include <vector>

cv::Mat frame = cv::imread("C:/Users/ankit/Pictures/Sample_Human_Image.jpg");

cv::Mat img = cv::imread("C:/Users/ankit/Pictures/WhiteBAckground.jpg");

LineAndPoints::LineAndPoints(
	std::pair<std::pair<float, float>,
	std::pair<float, float>> line,
	std::pair<float, float> firstPoint,
	std::pair<float, float> secondPoint) :
	m_line(line),
	m_firstPoint(firstPoint),
	m_secondPoint(secondPoint)
{

}

std::pair<std::pair<float, float>, std::pair<float, float>> LineAndPoints::GetLine()
{
	return m_line;
}

std::pair<float, float> LineAndPoints::GetFirstPoint()
{
	return m_firstPoint;
}

std::pair<float, float> LineAndPoints::GetSecondPoint()
{
	return m_secondPoint;
}

std::string protoFile = "E:/openpose/models/pose/coco/pose_deploy_linevec.prototxt";
std::string weightsFile = "E:/openpose/models/pose/coco/pose_iter_440000.caffemodel";

const int POSE_PAIRS[20][2] = {
	// COCO body
	 {1,2}, {1,5}, {2,3},
	 {3,4}, {5,6}, {6,7},
	 {1,8}, {8,9}, {9,10},
	 {1,11}, {11,12}, {12,13},
	 {1,0}, {0,14},
	 {14,16}, {0,15}, {15,17} };


cv::dnn::Net net = cv::dnn::readNetFromCaffe(protoFile, weightsFile);

int inWidth = 368;
int inHeight = 368;

auto nPoints = 18;
auto npairs = 17;

std::vector<cv::Point> points(nPoints);

std::vector<LineAndPoints> BodyJoints(cv::Mat& frame,cv::Mat& img)
{
		
	cv::Mat inpBlob = cv::dnn::blobFromImage(frame, 1.0 / 255, cv::Size(inWidth, inHeight));
	net.setInput(inpBlob);
	
	
	cv::Mat output = net.forward();

	
	int H = output.size[2];
	int W = output.size[3];
	
	
	// find the position of the body parts
	
	for (int n = 0; n < nPoints; n++)
	{
		// Probability map of corresponding body's part.
		cv::Mat probMap(H, W, CV_32F, output.ptr(0, n));

		cv::Point p(-1, -1),pm;
		cv::Point maxLoc;
		double conf;
		
		cv::minMaxLoc(probMap, 0, &conf,0,&pm);
		if (conf > 0.1)
		{
			p = pm;					
		}
		points[n] = p;
	}

	float SX = float(frame.cols) / W;
	float SY = float(frame.rows) / H;
	std::vector<LineAndPoints> lineAndPointsVector;

	for (int n = 0; n < npairs; n++)
	{
		cv::Point2f a = points[POSE_PAIRS[n][0]];
		cv::Point2f b = points[POSE_PAIRS[n][1]];
		// we did not find enough confidence before
		if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0)
			continue;
		// scale to image size
		a.x *= SX; a.y *= SY;
		b.x *= SX; b.y *= SY;
		
		//lineAndPointsVector.push_back(LineAndPoints(
		//	std::make_pair(std::make_pair(a.x,a.y),
		//		std::make_pair(b.x,b.y)),
		//	std::make_pair(a.x, a.y), 
		//	std::make_pair(b.x,b.y)));
		cv::line(frame, a, b, cv::Scalar(0, 200, 0), 2);
		cv::circle(frame, a, 3, cv::Scalar(0, 0, 200), -1);
		cv::circle(frame, b, 3, cv::Scalar(0, 0, 200), -1);
	}
	cv::imshow("OpenPose", frame);

	return lineAndPointsVector;
}

int play(std::vector<LineAndPoints>& lineAndPointsVector)
{
	cv::Mat frame;

	cv::VideoCapture cap;
	int deviceID = 0;
	int apiID = cv::CAP_ANY;

	cap.open(deviceID + apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	
	//--- GRAB AND WRITE LOOP
	std::cout << "Start grabbing" << std::endl
		<< "Press any key to terminate" << std::endl;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// show live and wait for a key with timeout long enough to show images
		//imshow("Live", frame);

		lineAndPointsVector = BodyJoints(frame,img);

		
		if (cv::waitKey(5) >= 0)
			break;
	}
	return 0;
}
