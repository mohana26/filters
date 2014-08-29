//Implementation of old school pixelate filter 
//for both still images and live feed. 

#include <opencv\highgui.h> 
#include <opencv\cv.h> 
#include <iostream> 
using namespace cv;

const bool VIDEO_FEED = false;
const int WIDTH = 640; 
const int HEIGHT = 480;

Mat image;
Mat& dst2 = image;
IplImage* img;
int sliderValue;
VideoCapture cap;
//CvCapture* pCapture;

void pixelate(IplImage* &img, int size);
void on_trackBar(int, void*);
//void pixelate(Mat &img, int size);void on_trackbar( int, void* )

//Callback function for trackbar to update
//current value. Issue in live feed when converting
//between Mat and IplImages. 
void on_trackBar(int, void*) {
	IplImage* dst;
	if(VIDEO_FEED) {
		//dst2 = NULL;
		//dst2 = image;
		//dst2 = image;
		IplImage temp = dst2;
		dst = &temp;
		pixelate(dst, sliderValue);
		dst2 = cv::Mat(dst, false);
		//imshow("window", dst2);
	} else {
		dst = cvLoadImage( "some pic" );
		pixelate(dst, sliderValue);
		cvShowImage("window", dst);
	}
}


int main() 
{
	sliderValue = 1;
	namedWindow("window", 1);
	//cvNamedWindow( "window", CV_WINDOW_NORMAL );

	if(VIDEO_FEED) {
		// Start capturing data from the web cam
		pCapture = cvCaptureFromCAM(CV_CAP_V4L2);
 
		// Get an initial frame and set width and height to defaults. 
		cap.open(0);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
		//IplImage* pFrame = NULL;
		//img = cvQueryFrame(pCapture);
		cv::createTrackbar("pixel size", "window", &sliderValue,WIDTH,on_trackBar);
		while(1)
		{
			VideoCapture cap(0);
			Mat frame;
			cap >> frame;

			img.LoadFromPixels(frame.cols, frame.rows, camData);
			img = cvQueryFrame(pCapture);
			try
			{
				//img = cvQueryFrame(pCapture);
				img = NULL;
				image = cv::Mat(img, false);
				cap >> image;
				dst2 = image;
				on_trackBar(0,0);
				//image = dst2;
				imshow("window", image);
			}
			catch (Exception& e)
			{
				const char* err_msg = e.what();
				std::cout << "exception caught: imshow:\n" << err_msg << std::endl;
			} 
			waitKey(33);
		}
		 cvReleaseCapture(&pCapture); //release live feed. 
	} else {
		img = cvLoadImage( "some pic" ); //change the name (image.jpg) according to your Image filename.
		cv::createTrackbar("pixel size", "window", &sliderValue, WIDTH,on_trackBar);
		on_trackBar(0,0);
		//pixelate(img, sliderValue);
		//imshow("window", cv::Mat(img, false));
		//imwrite("C:\\Users\\Amrita\\Desktop\\testPics_HI\\pixelate_10.jpg", cv::Mat(img,false));
		cvWaitKey(0);
		//cvDestroyWindow( "window" );
		return 0;
	}
}


//Actual pixelate algorithm. Uses current image 
//along with desired pixel size to figure out pixelation
//on image. 
void pixelate(IplImage* &img, int size) {
	if(size > 0) {
		for( int y=0; y<img->height; y++ ) { 
			for( int x=0; x<img->width; x++ ) { //traverse each pixel 
				for(int c=0; c<3; c++) { //access color channel
					int xPixel = x-(x%size); 
					int yPixel = y-(y%size);
					img->imageData[(y*img->width+x)*3+c] = img->imageData[(yPixel*img->width+xPixel)*3+c]; //replace with pixel img at adjustment value. 
				}
			}
		}
	}
}
