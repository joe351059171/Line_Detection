#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

Mat HoughTransform(Mat*);

void player(String filename) {
	VideoCapture cap;
	if (!cap.open(filename)) {
		cout << "Open Video Failed" << endl;
	}
	Mat frame;
	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "视频宽度=" << width << endl;
	cout << "视频高度=" << height << endl;
	//namedWindow(filename,WINDOW_NORMAL);
	while (true) {
		cap >> frame;
		frame = frame(Rect(530, 0, 580, 500));
		//cvtColor(frame, frame, COLOR_BGR2GRAY);
		//threshold(frame, frame, 80, 180, THRESH_BINARY);
		frame = HoughTransform(&frame);
		imshow(filename, frame);
		if (waitKey(33) >= 0) {
			//if (waitKey(32) == 0)
				waitKey(0);
			//break;
		}
	}
	cap.release();
}

Mat HoughTransform(Mat *file) {
	Mat src = *file;
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	//GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> Circles;
	HoughCircles(gray, Circles, CV_HOUGH_GRADIENT, 1, 15, 160, 60, 0, 0);
	for (size_t i = 0;i < Circles.size();++i)
	{
		Point center(cvRound(Circles[i][0]), cvRound(Circles[i][1]));
		int radius = cvRound(Circles[i][2]);
		//绘制圆心
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	return src;
}

int main(int argc, char** argv) {
	player(string(argv[1]));
	return 0;
}
