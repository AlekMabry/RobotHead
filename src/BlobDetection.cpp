#include "BlobDetection.h"

double BlobDetection::getDistance(double knownWidth, double focalLength, double perWidth) {
    return (knownWidth*focalLength) / perWidth;
}

BlobReturn BlobDetection::blobDetect(Mat frame) {
    Mat edges;
    Mat contoursFrame;
    vector <vector<Point> > contours;
    vector <Vec4i> hierarchy;
    int largest_area = 0;
    int largest_contour_index = 0;

    GaussianBlur(frame, edges, Size(7, 7), 1.5, 1.5) ;
    cvtColor(edges, edges, COLOR_BGR2HSV);
    inRange(edges, Scalar(36, 152, 50), Scalar(113, 255, 255), edges);
    findContours(edges.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    double xPos;
    double yPos;
    double widthInPixels;
    double heightInPixels;

    if (contours.size() > 0) {
        vector <Moments> mu(contours.size());
        vector <Point2f> mc(contours.size());
        vector<Rect> boundRect(contours.size());
        vector<vector<Point> > contours_poly( contours.size() );

        for (int i = 0; i < contours.size(); i++) {
            mu[i] = moments(contours[i], false);
            mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
            xPos = mu[i].m10 / mu[i].m00;
            yPos = mu[i].m01 / mu[i].m00;
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            double a = contourArea(contours[i], false);
            if (largest_area < a) {
                largest_area = a;
                largest_contour_index = i;
            }
        }
        rectangle( frame, boundRect[largest_contour_index].tl(), boundRect[largest_contour_index].br(), Scalar(0, 255, 0), 2, 8, 0 );
        widthInPixels = boundRect[largest_contour_index].br().x - boundRect[largest_contour_index].tl().x;
        double widthInIn;
        widthInIn = BlobDetection::getDistance(2.25, 204.0, widthInPixels);
        cout << widthInIn;
        cout << "\n";
        //putText(frame, to_string(widthInPixels), Point2f(10, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1, 8);
        circle(frame, mc[largest_contour_index], 4, Scalar(255, 0, 0), -1, 8, 0);
        drawContours(frame, contours, largest_contour_index, Scalar(255, 0, 0), 1, 8, hierarchy);
    }

    BlobReturn returnValue;
    returnValue.frameOutput = frame;
    returnValue.xPosOutput = xPos;
    returnValue.yPosOutput = yPos;
    return returnValue;
}
