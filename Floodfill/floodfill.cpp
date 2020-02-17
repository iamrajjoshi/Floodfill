#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>

using namespace cv;
using namespace std;

const int WINDOW_SIZE = 500;

String imgName = "Floodfill";
Mat img;

void CallBackFunc(int, int, int, int, void*);
void drawRandomLines(Mat&, String&, RNG rng);
bool checkValid(Point, int, int, int);
void myFloodFill(Point);

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		//RNG rng(time(0));
		//floodFill(img, Point(x, y), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
		myFloodFill(Point(x, y));
		imshow(imgName, img);
		return;
	}
}

void drawRandomLines(Mat& image, String& window_name, RNG rng) {
	Point pt1, pt2;
	for (int i = 0; i < 25; i++) {
		pt1.x = rng.uniform(0, WINDOW_SIZE);
		pt1.y = rng.uniform(0, WINDOW_SIZE);
		pt2.x = rng.uniform(0, WINDOW_SIZE);
		pt2.y = rng.uniform(0, WINDOW_SIZE);

		line(image, pt1, pt2, Scalar(255, 255, 255));
	}
	return;
}

bool checkValid(Point p, int b, int g, int r) {
	if (!(p.x > 0 && p.x < WINDOW_SIZE && p.y > 0 && p.y < WINDOW_SIZE))
		return false;

	auto color = img.at<Vec3b>(p);
	if (!(color == Vec3b(b, g, r)) && !(color == Vec3b(255, 255, 255)))
		return true;
	else
		return false;
}

void myFloodFill(Point start) {
	RNG rng(time(0));
	auto b = rng.uniform(0, 255);
	auto g = rng.uniform(0, 255);
	auto r = rng.uniform(0, 255);

	queue<Point> q;
	q.push(start);

	while (!q.empty()) {
		Point p = q.front();
		q.pop();
		if (checkValid(Point(p.x + 1, p.y), b, g, r)) {
			img.at<Vec3b>(Point(p.x + 1, p.y)) = Vec3b(b, g, r);
			q.push(Point(p.x + 1, p.y));
		}

		if (checkValid(Point(p.x - 1, p.y), b, g, r)) {
			img.at<Vec3b>(Point(p.x + 1, p.y)) = Vec3b(b, g, r);
			q.push(Point(p.x - 1, p.y));
		}
			
		if (checkValid(Point(p.x, p.y + 1), b, g, r)) {
			img.at<Vec3b>(Point(p.x, p.y + 1)) = Vec3b(b, g, r);
			q.push(Point(p.x, p.y + 1));
		}	
		if (checkValid(Point(p.x, p.y - 1), b, g, r)) {
			img.at<Vec3b>(Point(p.x, p.y - 1)) = Vec3b(b, g, r);
			q.push(Point(p.x, p.y - 1));
		}
			
		//imshow(imgName, img);
		//waitKey(1);
	}
}

int main(void) {
	namedWindow(imgName);
	img = Mat::zeros(WINDOW_SIZE, WINDOW_SIZE, CV_8UC3);

	drawRandomLines(img, imgName, RNG(time(0)));
	setMouseCallback(imgName, CallBackFunc, NULL);

	imshow(imgName, img);

	waitKey(0);
	return 0;
}
