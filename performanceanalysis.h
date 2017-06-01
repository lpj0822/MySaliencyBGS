#ifndef PERFORMANCEANALYSIS_H
#define PERFORMANCEANALYSIS_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

#define BLACK  0
#define SHADOW  50
#define OUTOFSCOPE  85
#define UNKNOWN  170
#define WHITE  255

class PerformanceAnalysis
{
public:
    PerformanceAnalysis(std::string gtPath, std::string testPath);
    ~PerformanceAnalysis();

    void analysis();
    void save();

private:

    void init();

    uint tp;
    uint fp;
    uint fn;
    uint tn;
    uint nbShadowErrors;

    std::string gtImagePath;
    std::string testImagePath;
};

#endif // PERFORMANCEANALYSIS_H
