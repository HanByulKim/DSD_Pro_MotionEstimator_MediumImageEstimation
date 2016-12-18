/**
*********************************************
2016 Autumn Digital Systems Disign Project
Motion Estimator medium image Estimation
SNU Dept. of Electrical & Computer Engineering
2014-13261
Han-Byul Kim
*********************************************
Rev. log.
look for https://github.com/HanByulKim/DSD_Pro_MotionEstimator_MediumImageEstimation
*********************************************
**/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Tokenizer.h"

using namespace cv;
using namespace std;
std::string CleanLine(const std::string& n) {
	std::string cleanline;
	char* char_line = (char*)n.c_str(); // Non-const cast required.

	char* token = NULL;
	char* context = NULL;
	char  delims[] = " ,\t\n";

	// During the first read, establish the char string and get the first token.
	token = strtok_s(char_line, delims, &context);

	// While there are any tokens left in "char_line"...
	while (token != NULL)
	{
		// Accumulate the tokens.
		cleanline += token;
		cleanline += ' ';

		// NOTE: NULL, function just re-uses the context after the first read.
		token = strtok_s(NULL, delims, &context);
	}

	return cleanline;
}
int main(int argc, char** argv)
{
	Mat inputImg;
	Mat yuvImg;
	string dd = "34";
	std::cout << atoi(dd.c_str())+1;

	std::string filename = "output_mediate.txt";
	std::stringstream ss;
	std::string str, cleanstr;
	std::ifstream file(filename);
	std::ofstream myfile("out.txt");

	int i = 0;
	int j = 0;
	string token;
	IplImage *trans = cvCreateImage(CvSize(320, 240), IPL_DEPTH_8U, 1);
	if (file) { // Same as Try Catch Exception
		while (j<240) {
			std::getline(file, str);

			cleanstr = CleanLine(str);

			ss.clear();
			stringstream stream(cleanstr);
			//Tokenizer go(str);
			while (i<640) {
				//token = go.next();
				stream >> token;
				//myfile << str << std::endl;
				int temp = (atoi(token.c_str()) % 16) + ((atoi(token.c_str()) / 16) % 16) * 10 + (((atoi(token.c_str()) / 16) / 16) % 16) * 100;
				myfile << temp << " ";
				trans->imageData[i + trans->width*j] = temp;
				i++;
			}
			myfile << std::endl;
			i = 0;
			j++;
		}
	}
	else { std::cout << "Wrong File!" << std::endl; }
	filename = cv::format("capture1.bmp");
	cvSaveImage(filename.c_str(), trans);
	file.close();
	myfile.close();
		
	waitKey(0);
	return 0;
}

