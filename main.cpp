#include <opencv2/videoio.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "saliencybgs.h"
#include "dirprocess.h"
#include "performanceanalysis.h"

const std::string frameFile = "E:/QtProject/MySaliencyBGS/dataset2012/dataset/shadow/cubicle/input";
const std::string videoFile = "E:/QtProject/MySaliencyBGS/data/video1.avi";
const std::string gtPath = "E:/Egg/MySaliencyBGS/data/gt";
const std::string resultPath = "E:/Egg/MySaliencyBGS/data/test";

cv::Mat img;
cv::Mat img_output;
cv::Mat img_bg;
cv::Mat saliencyMap;

SaliencyBGS saliencyBGS;
HCSaliency saliency;

void drawText(cv::Mat &src, int number)
{
    char temp[16];
    sprintf(temp, "%d", number);
    cv::putText(src, temp, cv::Point(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0,255));
}

void testSaliency(const cv::Mat &src)
{
    saliencyMap = saliency.getSaliency(src);
    cv::normalize(saliencyMap, saliencyMap, 255, 0, cv::NORM_MINMAX);
    saliencyMap.convertTo(img_output,CV_8UC1);
}

void testVideo()
{
    int number = 1;
    cv::VideoCapture capture(videoFile);
    if (!capture.isOpened ())
    {
        std::cerr << "not open the video:" << videoFile << std::endl;
        return;
    }
    while (capture.read(img))
    {
        if(img.empty())
        {
            break;
        }
        int64 beg = cv::getTickCount();
        saliencyBGS.process(img, img_output, img_bg);

        int64 end = cv::getTickCount();
        printf("time = %.4f ms\n", (end - beg) / cv::getTickFrequency() * 1000);

        //drawText(img, number);
        cv::imshow("input", img);
        if (!img_output.empty())
        {
            std::ostringstream output;
            output << std::setfill('0') << std::setw(5) << number << ".png";
            //cv::medianBlur(img_output, img_output ,7);
            cv::imwrite(output.str(), img_output);
            //cv::imshow("img_output",img_output);
        }

        if (cv::waitKey(25) == 27)
        {
                break;
        }
        number++;
    }
    capture.release();
    cv::destroyAllWindows();
}

void testVideoFrame()
{
    int number = 1;
    DirProcess dirProcess;
    QList<QString> imageList=dirProcess.getDirFileName(QString(frameFile.c_str()),QString("*.jpg"));

    foreach (QString str, imageList)
    {
        img = cv::imread(str.toStdString());
        if (img.empty())
        {
            break;
        }
        if (number >= 975)
        {
            int64 beg = cv::getTickCount();
            saliencyBGS.process(img, img_output, img_bg);
            int64 end = cv::getTickCount();
            printf("time = %.4f ms\n", (end - beg) / cv::getTickFrequency() * 1000);
        }
        drawText(img, number);
        cv::imshow("input",img);
        if (!img_output.empty())
        {
            std::ostringstream output;
            output << std::setfill('0') << std::setw(5) << number << ".png";
            //cv::medianBlur(img_output, img_output ,7);
            cv::imwrite(output.str(), img_output);
            //cv::imshow("img_output",img_output);
        }
        if (cv::waitKey(20) == 27)
        {
            break;
        }
        number++;
    }
    cv::destroyAllWindows();
}

void analysisResult()
{
    PerformanceAnalysis myAnalysis(gtPath, resultPath);
    myAnalysis.analysis();
    myAnalysis.save();
}

int main(int argc, char *argv[])
{
    testVideo();
    return 0;
}
