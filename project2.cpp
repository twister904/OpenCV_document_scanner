#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//Basic functions//
Mat imgorig, imgthre, imggray, imgblur, imgcanny, imgdilate, imgerode, imgwarp,imgcrop, matrix;
vector<Point> initialpoint, docpoint;
float w = 420, h = 596;

vector<Point> getcontours(Mat imgdilate) 
{
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy; 
	vector<Point> biggest;

	findContours(imgdilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	/*drawContours(img, contours, -1, Scalar(0, 0, 0), 5);*/
	vector<vector<Point>>conpoly(contours.size());
	vector<Rect>boundrect(contours.size());
	Point mypoint(0, 0);
	int area, maxarea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conpoly[i], 0.02 * peri, true);
			if (area > maxarea&&conpoly[i].size() == 4)
			{
				biggest = {conpoly[i][0],conpoly[i][1] ,conpoly[i][2] ,conpoly[i][3] };
				maxarea = area;
				//drawContours(imgorig, conpoly, i, Scalar(255, 0, 255), 3);

			}


		}


	}

	return biggest;


}

Mat preprocessing(Mat img)
{
	cvtColor(img, imggray, COLOR_BGR2GRAY); //to convert from rgb to gray
	GaussianBlur(img, imgblur, Size(3, 3), 3, 0); //to convert into blurry image
	Canny(imgblur, imgcanny, 25, 75); //to get edges in images
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgcanny, imgdilate, kernal); //to increase the thickness of edges
	//erode(imgdilate, imgerode, kernal); //to decrease the thickness of edges

	return imgdilate;
}
void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgorig, points[i], 10, color, FILLED);
		putText(imgorig, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> reorder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int>  sumPoints, subPoints;

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

	return newPoints;
}
Mat getwarp(Mat img,vector<Point>points, float w,float h)
{
	Point2f src[4] = { points[0],points[1],points[2],points[3]};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgwarp, matrix, Point(w, h));

	return imgwarp;

}


void main()
{
	string path;
	cout << "enter the path of img to scan";
	cin >> path;

	imgorig = imread(path);
	//resize(imgorig, imgorig, Size(), 0.9, 0.9);
	//preprocessing
	imgthre=preprocessing(imgorig);
	//getcontours
	initialpoint=getcontours(imgthre);
	//draw coordinates
	//drawPoints(initialpoint, Scalar(255, 0, 0));
	//reorder points
	docpoint = reorder(initialpoint);
	//image warp
	imgwarp = getwarp(imgorig,docpoint,w,h);
	//cropimage
	imshow("image", imgorig);
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	imgcrop = imgwarp(roi);

	
	//imshow("imagethre", imgthre);
	//imshow("imagewarp", imgwarp);
	//imshow("imagecrop", imgcrop);
	imwrite("Resources/scanimg.jpg", imgcrop);
	waitKey(0);

}