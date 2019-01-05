#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

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
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		threshold(frame, frame, 80, 180, THRESH_BINARY);
		imshow(filename, frame);
		if (waitKey(33) >= 0) {
			//if (waitKey(32) == 0)
				waitKey(0);
			//break;
		}
	}
	cap.release();
}

int main(int argc, char** argv) {
	player(string(argv[1]));
	return 0;
}
