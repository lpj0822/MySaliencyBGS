#include "performanceanalysis.h"
#include "dirprocess.h"
#include <iostream>
#include <sstream>
#include <iomanip>

PerformanceAnalysis::PerformanceAnalysis(std::string gtPath, std::string testPath)
{
    init();
    this->gtImagePath = gtPath;
    this->testImagePath = testPath;
    std::cout << "PerformanceAnalysis()" << std::endl;
}

PerformanceAnalysis::~PerformanceAnalysis()
{
    std::cout << "~PerformanceAnalysis()" << std::endl;
}

void PerformanceAnalysis::analysis()
{
    DirProcess dirProcess;
    QList<QString> gtImageList = dirProcess.getDirFileName(QString(gtImagePath.c_str()),QString("*.png"));
    QList<QString> testImageList = dirProcess.getDirFileName(QString(testImagePath.c_str()),QString("*.png"));
    if(gtImageList.size()<= 0 || testImageList.size() <= 0 || gtImageList.size() != testImageList.size())
    {
        std::cout << "image path error!" << std::endl;
        return;
    }
    cv::Mat binary;
    cv::Mat gt;
    for(int loop = 0; loop < gtImageList.size() ; loop++)
    {
        binary = cv::imread(testImageList[loop].toStdString(), cv::IMREAD_GRAYSCALE);
        gt = cv::imread(gtImageList[loop].toStdString(), cv::IMREAD_GRAYSCALE);
        if (binary.empty())
        {
            throw std::string("Binary frame is null. Probably a bad path or incomplete folder.\n");
        }
        if (gt.empty())
        {
            throw std::string("gt frame is null. Probably a bad path or incomplete folder.\n");
        }

        cv::Mat_<uchar>::const_iterator itBinary=binary.begin<uchar>();
        cv::Mat_<uchar>::const_iterator itGT = gt.begin<uchar>();
        cv::Mat_<uchar>::const_iterator itEnd = binary.end<uchar>();
        for (; itBinary != itEnd; ++itBinary, ++itGT)
        {
            // Current pixel needs to be in the ROI && it must not be an unknown color
            if(*itGT != UNKNOWN)
            {
                if(*itBinary == WHITE)
                {
                    // Model thinks pixel is foreground
                    if(*itGT == WHITE)
                    {
                        ++tp; // and it is
                    }
                    else
                    {
                        ++fp; // but it's not
                    }
                }
                else
                {
                    // Model thinks pixel is background
                    if(*itGT == WHITE)
                    {
                        ++fn; // but it's not
                    }
                    else
                    {
                        ++tn; // and it is
                    }
                }

                if(*itGT == SHADOW)
                {
                    if(*itBinary == WHITE)
                    {
                        ++nbShadowErrors;
                    }
                }
            }
        }
    }
}

void PerformanceAnalysis::save()
{
    //写入文件
    float recall = .0;//TP / (TP + FN)
    float precision = .0;//TP / (TP + FP)
    float fscore = .0 ;//2*(Precision*Recall)/(Precision+Recall)
    std::string savePath = testImagePath + "/analysis.xml";
    cv::FileStorage fs;
    fs.open(savePath, cv::FileStorage::WRITE);

    recall = tp * 1.0 / (tp + fn);
    precision = tp * 1.0 / (tp + fp);
    fscore = 2 * (precision * recall) / (precision + recall);

    std::ostringstream output1;
    std::ostringstream output2;
    std::ostringstream output3;
    output1 << std::setprecision(3) << precision;
    output2 << std::setprecision(3) << recall;
    output3 << std::setprecision(3) << fscore;

    cv::write(fs, "precision", output1.str());
    cv::write(fs,"recall", output2.str());
    cv::write(fs,"fscore", output3.str());

    fs.release();
}

void PerformanceAnalysis::init()
{
    tp = 1; //前景像素点中被正确标记为前景像素的数目
    fp = 0; //背景像素点中被错误标记为前景像素的数目
    fn = 0; //前景像素点中被错误标记为背景像素的数目
    tn = 1; //背景像素点中被正确标记为背景像素的数目
    nbShadowErrors = 0; //把阴影检测为前景像素的数目
}
