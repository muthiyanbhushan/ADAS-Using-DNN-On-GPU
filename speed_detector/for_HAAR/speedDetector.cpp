/**
 * @file objectDetection2.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
 */
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
CascadeClassifier cascade;
//CascadeClassifier eyes_cascade;
String window_name = "Capture - speed sign detection";
/**
 * @function main
 */
int main( int argc, char *argv[] )
{

    string cascadeName;
    string inputName;
    bool isInputImage = false;
 
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--cascade")
        {
            cascadeName = argv[++i];
        }
        else if (!isInputImage)
        {
            inputName = argv[i];
            isInputImage = true;
        }
        else
        {
            cout << "Unknown key: " << argv[i] << endl;
            return -1;
        }
    }

    Mat image;

    if (isInputImage)
    {
        image = imread(inputName);
        CV_Assert(!image.empty());
    }


    //-- 1. Load the cascade
    if( !cascade.load( cascadeName ) ){ printf("--(!)Error loading speed cascade\n"); return -1; };

detectAndDisplay(image);


int c = waitKey();
    return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> speed;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect speed
    cascade.detectMultiScale( frame_gray, speed, 1.1, 2, 0, Size(32, 32) );

    //printf ("x = %d, y = %d, width = %d, he = %d\n", speed[0].x, speed[0].y, speed[0].width, speed[0].height);
    for( size_t i = 0; i < speed.size(); i++ )
    {
        Mat speedROI = frame_gray( speed[i] );
        std::vector<Rect> speed_focused;

        //-- In each image, detect speed sign board
        cascade.detectMultiScale( speedROI, speed_focused, 1.1, 2, 0, Size(32, 32) );
        if( speed_focused.size() > 0)
        {
            rectangle(frame_gray, speed[i], Scalar(255));
        }
    }
    cv::cvtColor(frame_gray, frame, COLOR_GRAY2BGR);
    //-- Show what you got
//    imshow( window_name, frame );

    // crop the image
    Rect board(speed[0].x, speed[0].y, speed[0].width, speed[0].height);
    Mat croppedImage;
    Mat(frame, board).copyTo(croppedImage);
    imwrite("output.ppm", croppedImage);
    imshow(window_name, croppedImage);
}
