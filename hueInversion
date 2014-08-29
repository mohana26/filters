//Hue inverting filter. 

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <cstdlib>

using namespace cv;

const bool VIDEO_FEED = true; //Activate live feed option
const int HUE_RANGE = 180; //hue range in openCV HSV color space
const int WIDTH = 640; //frame width
const int HEIGHT = 480; //frame height

Mat image;
void hueInverter(Mat &image);


int main(int argc, char** argv)
{
	if(VIDEO_FEED) {
	
	  //Capture webcam and set frame dimensions. 
		VideoCapture cap;
		cap.open(0);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

		namedWindow("window",1);
	
		while(1)
		{
			 try
			{
				cap >> image;
				hueInverter(image);
				imshow("window", image);
			}
			catch (Exception& e)
			{
				const char* err_msg = e.what();
				std::cout << "exception caught: imshow:\n" << err_msg << std::endl;
			}
			 waitKey(33);
		}
	} else {
		image = cvLoadImage( "some pic" ); //change the name according to Image filename.
		cvNamedWindow( "window", CV_WINDOW_NORMAL );
		hueInverter(image);
		imshow("window", image);
		//imwrite("some dst", image);
		cvWaitKey(0);
		cvDestroyWindow( "window" );
	}
    return 0;
} 

//Take in Mat image address and invert hue 180 degrees. 
void hueInversion(Mat &image) 
{
	//hue inversion
	cv::cvtColor(image, image, CV_BGR2HSV); //BGR -> HSV
	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			Vec3b &hsv = image.at<cv::Vec3b>(Point(i, j)); //pixel(i,j) color channel
			hsv[0] = (hsv[0] + 90)%HUE_RANGE; //invert hue value
		 }
	}
	cv::cvtColor(image, image, CV_HSV2BGR); //HSV -> BGR
}
