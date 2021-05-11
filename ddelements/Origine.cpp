#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/calib3d.hpp"

using namespace std;
using namespace cv;

/*
@function thresholding
*/

static Mat tresholding(Mat img) {
	//--------------->COLOR_SEGMENTATION
	Mat data;
	Mat original = img.clone();
	img.convertTo(data, CV_32F);
	data = data.reshape(1, data.total());

	//do kmeans
	Mat labels, centers;
	kmeans(data, 8, labels, TermCriteria(TermCriteria::MAX_ITER, 10, 1.0), 3,
		KMEANS_PP_CENTERS, centers);

	//reshape both to a single row of Vec3f pixels:
	centers = centers.reshape(3, centers.rows);
	data = data.reshape(3, data.rows);

	//replace pixel values with their center value:
	Vec3f *p = data.ptr<Vec3f>();
	for (size_t i = 0; i < data.rows; i++) {
		int center_id = labels.at<int>(i);
		p[i] = centers.at<Vec3f>(center_id);
	}

	//back to 2d, and uchar:
	img = data.reshape(3, img.rows);
	img.convertTo(img, CV_8U);
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	Mat segm;
	inRange(imgHSV, Scalar(0, 20, 0), Scalar(50, 255, 255), segm);
	Mat fin;
	bitwise_and(original, original, fin, segm);

	return fin;
}

int main()
{
	Mat src = imread("img1.jpg");
	if (src.empty())
	{
		cout << "Cannot read the image. " << endl;
		return -1;
	}

//	cvtColor(src, src, COLOR_BGR2HSV);

	Mat mask = tresholding(src);
	cvtColor(mask, mask, COLOR_HSV2BGR);
	imshow("original", src);
	imshow("test", mask);

	Mat gray_mask;
	cvtColor(mask, gray_mask, COLOR_RGB2GRAY);

	Mat img_bw;
	threshold(gray_mask, img_bw, 0.1, 255.0, THRESH_BINARY_INV);
//	imshow("img_bw", img_bw);

	Mat outFrame;  // Result output
	src.copyTo(outFrame, img_bw);

	imshow("src", src);
	imshow("output", outFrame);
		
	waitKey(0);
	return 0;
}