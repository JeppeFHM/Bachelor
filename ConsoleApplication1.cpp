
#include<opencv2/opencv.hpp>//OpenCV header to use VideoCapture class//
#include<iostream>
using namespace std;
using namespace cv;
int main() {
    Mat myImage;//Declaring a matrix to load the frames//
    namedWindow("Video Player", WINDOW_KEEPRATIO);
    namedWindow("Video Player2", WINDOW_KEEPRATIO);//Declaring the video to show the video//
    namedWindow("Video Player3", WINDOW_KEEPRATIO);//Declaring the video to show the video//
    VideoCapture cap(0);//Declaring an object to capture stream of frames from default camera//
    if (!cap.isOpened()) { //This section prompt an error message if no video stream is found//
        cout << "No video stream detected" << endl;
        system("pause");
        return-1;
    }
    int lowTh = 48;
    int highTh = 183;
    int a = 260;
    int b = 124;
    int c = 283;
    int d = 276;
    Mat imgBlurred;
    Mat imgCanny;
    namedWindow("Linear Blend", WINDOW_KEEPRATIO); // Create Window
    while (true) { //Taking an everlasting loop to show the video//
        cap >> myImage;
        if (myImage.empty()) { //Breaking the loop if no video frame is detected//
            break;
        }
        Mat input = myImage;
        Mat gray;
        cvtColor(input, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, imgBlurred, Size(5, 5), 5);


        imshow("Video Player", imgBlurred);//Showing the video//
        Canny(imgBlurred, imgCanny, lowTh, highTh);
        //imshow("Video Player2", imgCanny);

        vector<Vec4i> lines;
        HoughLinesP(imgCanny, lines, 1, (2 * CV_PI) / a, b, c, d);

        imshow("Video Player2", imgCanny);

        createTrackbar("LowTh", "Video Player2", &lowTh, 500);
        createTrackbar("HighTh", "Video Player2", &highTh, 500);
        createTrackbar("a", "Video Player2", &a, 500);
        createTrackbar("b", "Video Player2", &b, 500);
        createTrackbar("c", "Video Player2", &c, 500);
        createTrackbar("d", "Video Player2", &d, 500);

        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4i l = lines[i];

            line(input, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(100, 2, 255), 1);

        }

        vector<pair<int, int>> pixels;
        Point a;
        Point b;
        int center = input.cols / 2;
        //line(input, Point(center, 100), Point(center, 500), Scalar(24, 2, 155), 10);
        for (int i = 240; i < input.rows ; i++) {

            if (input.at<Vec3b>(i, center) == Vec3b(100, 2, 255))
            {
                cout << "bruh" << endl;
                pixels.push_back(make_pair(abs(i - center), i));

            }
        }
        sort(pixels.rbegin(), pixels.rend());
        reverse(pixels.begin(), pixels.end());
        if (pixels.size() > 2) {
            cout << pixels.size() << endl;
            int p1 = pixels[0].second;
            int p2 = pixels[1].second;
            a = { center, p1 };
            b = { center,p2 };
            double dist = norm(a - b);
            Point org(30, 300);
            putText(input, to_string(dist), org,
                FONT_HERSHEY_SCRIPT_COMPLEX, 2.1,
                Scalar(0, 0, 255), 2, LINE_AA);

            line(input, Point(center, p1), Point(center, p2), Scalar(155, 2, 50), 10);
        }


        pixels.clear();

        imshow("Video Player3", input);




        char c = (char)waitKey(25);//Allowing 25 milliseconds frame processing time and initiating break condition//
        if (c == 27) { //If 'Esc' is entered break the loop//
            break;
        }
    }
    cap.release();//Releasing the buffer memory//
    return 0;
}
//}
//#include <iostream>
//#include <opencv2/calib3d.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//int main(int argc, char** argv) {
//
//    (void)argc;
//    (void)argv;
//
//    std::vector<cv::String> fileNames;
//    cv::glob("C:/Users/jeppe/Desktop/Calibration/image*.jpg", fileNames, false);
//    cv::Size patternSize(10 - 1, 7 - 1);
//    std::vector<std::vector<cv::Point2f>> q(fileNames.size());
//
//    std::vector<std::vector<cv::Point3f>> Q;
//    // 1. Generate checkerboard (world) coordinates Q. The board has 25 x 18
//    // fields with a size of 15x15mm
//
//    int checkerBoard[2] = { 10,7 };
//    // Defining the world coordinates for 3D points
//    std::vector<cv::Point3f> objp;
//    for (int i = 1; i < checkerBoard[1]; i++) {
//        for (int j = 1; j < checkerBoard[0]; j++) {
//            objp.push_back(cv::Point3f(j, i, 0));
//        }
//    }
//
//    std::vector<cv::Point2f> imgPoint;
//    // Detect feature points
//    std::size_t i = 0;
//    for (auto const& f : fileNames) {
//        std::cout << std::string(f) << std::endl;
//
//        // 2. Read in the image an call cv::findChessboardCorners()
//        cv::Mat img = cv::imread(fileNames[i]);
//        cv::Mat gray;
//
//        cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
//
//        bool patternFound = cv::findChessboardCorners(gray, patternSize, q[i], cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);
//
//        // 2. Use cv::cornerSubPix() to refine the found corner detections
//        if (patternFound) {
//            cv::cornerSubPix(gray, q[i], cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
//            Q.push_back(objp);
//        }
//
//        // Display
//        cv::drawChessboardCorners(img, patternSize, q[i], patternFound);
//        cv::imshow("chessboard detection", img);
//        cv::waitKey(0);
//
//        i++;
//    }
//
//
//    cv::Matx33f K(cv::Matx33f::eye());  // intrinsic camera matrix
//    cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients
//
//    std::vector<cv::Mat> rvecs, tvecs;
//    std::vector<double> stdIntrinsics, stdExtrinsics, perViewErrors;
//    int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 +
//        cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;
//    cv::Size frameSize(1440, 1080);
//
//    std::cout << "Calibrating..." << std::endl;
//    // 4. Call "float error = cv::calibrateCamera()" with the input coordinates
//    // and output parameters as declared above...
//
//    float error = cv::calibrateCamera(Q, q, frameSize, K, k, rvecs, tvecs, flags);
//
//    std::cout << "Reprojection error = " << error << "\nK =\n"
//        << K << "\nk=\n"
//        << k << std::endl;
//
//    // Precompute lens correction interpolation
//    cv::Mat mapX, mapY;
//    cv::initUndistortRectifyMap(K, k, cv::Matx33f::eye(), K, frameSize, CV_32FC1,
//        mapX, mapY);
//
//    // Show lens corrected images
//    for (auto const& f : fileNames) {
//        std::cout << std::string(f) << std::endl;
//
//        cv::Mat img = cv::imread(f, cv::IMREAD_COLOR);
//
//        cv::Mat imgUndistorted;
//        // 5. Remap the image using the precomputed interpolation maps.
//        cv::remap(img, imgUndistorted, mapX, mapY, cv::INTER_LINEAR);
//
//        // Display
//        cv::imshow("undistorted image", imgUndistorted);
//        cv::waitKey(0);
//    }
//
//    return 0;
//}

