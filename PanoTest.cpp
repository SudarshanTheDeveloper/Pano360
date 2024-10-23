#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

Mat cube_map_to_360(const Mat& front, const Mat& back, const Mat& right, const Mat& left, const Mat& top, const Mat& bottom) {
    const int width = 24000;  // 24K equirectangular resolution
    const int height = 12000;
    Mat output(height, width, CV_8UC3, Scalar(0, 0, 0));

    // Cube map coordinates
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double theta = (static_cast<double>(x) / width) * 2 * CV_PI;  // Angle in radians
            double phi = (static_cast<double>(y) / height) * CV_PI - CV_PI / 2;  // Angle from top to bottom
            double sx = cos(phi) * cos(theta);
            double sy = sin(phi);
            double sz = cos(phi) * sin(theta);

            const Mat* img;
            double u, v;

            if (std::abs(sx) >= std::abs(sy) && std::abs(sx) >= std::abs(sz)) {
                if (sx > 0) {
                    img = &right;
                    u = -sz / sx * 0.5 + 0.5;
                    v = -sy / sx * 0.5 + 0.5;
                }
                else {
                    img = &left;
                    u = sz / -sx * 0.5 + 0.5;
                    v = -sy / -sx * 0.5 + 0.5;
                }
            }
            else if (std::abs(sy) >= std::abs(sx) && std::abs(sy) >= std::abs(sz)) {
                img = (sy > 0) ? &top : &bottom;
                u = (sx / sy * 0.5) + 0.5;
                v = (sz / sy * 0.5) + 0.5;
            }
            else {
                img = (sz > 0) ? &front : &back;
                u = (sx / sz * 0.5) + 0.5;
                v = (sy / sz * 0.5) + 0.5;
            }

            u = static_cast<int>(u * img->cols);
            v = static_cast<int>(v * img->rows);

            if (u >= 0 && u < img->cols && v >= 0 && v < img->rows) {
                output.at<Vec3b>(y, x) = img->at<Vec3b>(v, u);
            }
        }
    }

    return output;
}

int main() {
    // Load cube map images and apply transformations
    Mat front = imread("File_5.jpg");
    flip(front, front, 1);  // Flip horizontally

    Mat back = imread("File_4.jpg");
    rotate(back, back, ROTATE_180);

    Mat right = imread("File_2.jpg");
    rotate(right, right, ROTATE_180);

    Mat left = imread("File_3.jpg");
    rotate(left, left, ROTATE_180);

    Mat top = imread("File_1.jpg");
    transpose(top, top);
    flip(top, top, 1);

    Mat bottom = imread("File_0.jpg");
    transpose(bottom, bottom);
    flip(bottom, bottom, -1);

    // Create the 360-degree image
    Mat result_image = cube_map_to_360(front, back, right, left, top, bottom);

    // Save the result
    imwrite("360_image_4k_seam_blended.jpg", result_image);

    waitKey(0);
    return 0;
}
