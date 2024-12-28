#include <iostream>
#include <stdio.h>
// opencv includes
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace cv;
using namespace std;

void CrossFiller(Mat* image);
static void onMouse( int event, int x, int y, int, void* userInput );
static void onChange(void* userInput);

Point start;
Point stop;

Point* startPtr;
Point* stopPtr;
int countPtr;

int main()
{
    const int width = 640;
    const int height = 480;
    Mat image = Mat::zeros(height, width, CV_8U);
    namedWindow("image", WINDOW_AUTOSIZE);
    CrossFiller(&image);
    setMouseCallback("image", onMouse, &image);

    startPtr = (Point*)malloc(2*sizeof(Point));
    stopPtr = (Point*)malloc(2*sizeof(Point));

    for(;;) {

        if(!image.empty())
            imshow("image", image);

        char key = waitKey();
        if(key == 'e')
            break;
        else if(key == 'c') {
            CrossFiller(&image);
            printf("CrossFiller\n");
        }
    }

    cout << "Hello World!" << endl;
    return 0;
}

void CrossFiller(Mat* image) {
    memset(image->ptr(0), 0, image->rows * image->cols);
    line(*image, Point(image->cols/2, 0), Point(image->cols/2, image->rows), Scalar(255,255,255));
    line(*image, Point(0, image->rows/2), Point(image->cols, image->rows/2), Scalar(255,255,255));
}


static void onMouse( int event, int x, int y, int, void* userInput ){
    Mat* image= (Mat*)userInput;
    if(countPtr > 1) {
        countPtr = 0;
        memset(startPtr, 0, sizeof(Point));
        memset(stopPtr, 0, sizeof(Point));
        CrossFiller(image);
    }

    if( event == EVENT_LBUTTONDOWN ) {
        start = Point(x,y);
        startPtr[countPtr] = start;
    }
    else if( event == EVENT_LBUTTONUP ) {
        stop = Point(x,y);
        stopPtr[countPtr] = stop;
        countPtr++;
        onChange(image);
    }
}

static void onChange(void* userData)
{
    // Get the pointer input image
    Mat* image= (Mat*)userData;
    // Apply
    line(*image, start, stop, Scalar(255,255,255));

    int vector_a[2];
    int vector_b[2];

    vector_a[0] = startPtr[0].x - stopPtr[0].x;
    vector_a[1] = startPtr[0].y - stopPtr[0].y;

    vector_b[0] = startPtr[1].x - stopPtr[1].x;
    vector_b[1] = startPtr[1].y - stopPtr[1].y;

    int dotProduct = vector_a[0]*vector_b[0] + vector_a[1]*vector_b[1];
    int crossProduct = vector_a[0]*vector_b[1] - vector_b[0]*vector_a[1];

    double angle = atan2(double(crossProduct), double(dotProduct)) * 180.0/M_PI;
    printf("angle = %lf\n", angle);
    if(!image->empty())
        imshow("image", *image);
}
