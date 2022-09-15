#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <fstream>
typedef cv::Point3_<uint8_t> Pixel;

using namespace std;
using namespace cv;

const string LongBrightScale = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const string ShortBrightScale = " .,-~:;=!*#$@";

int main(){
	string path;
	char c;
	cout << "Gimme path\n";
	cin >> path;
	cout << "1 for Long Bright Scale, anything else for Short Bright Scale\n";
	cin >> c;

	string BrightScale;
	if (c == '1')
		BrightScale = LongBrightScale;
	else 
		BrightScale = ShortBrightScale;
	

	Mat image = imread(path);
	if (image.empty()){
		cout << "Ur path sucks" << endl;
		return -1;
	}

	vector<vector<char>> output(image.rows);
	for (auto& e : output)
		e.resize(image.cols);

	int height = 0;
	int width = 0;
	for (Pixel& p : cv::Mat_<Pixel>(image)) {
	
		double bright = (0.2126 * p.x) + (0.7152 * p.y) + (0.0722 * p.z); //formula for brightness
		int rounded = round(bright/(255.0/BrightScale.size()-1));

		if (rounded > BrightScale.size() - 2)
			rounded = BrightScale.size() - 2;

		output[height][width] = BrightScale[rounded];

		width++;
		if (width == image.cols) {
			height++;
			width = 0;
		}
	}

	ofstream out;
	out.open("output.txt");

	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < output[0].size(); j++) {
			out << output[i][j];
		}
		out << endl;
	}
	out.close();
	cout << "done";
}

