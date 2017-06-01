#include "dirprocess.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <sstream>
#include <iomanip>
#include <iostream>

DirProcess::DirProcess(QObject *parent) : QObject(parent)
{
    std::cout<< "DirProcess()" << std::endl;
}

DirProcess::~DirProcess()
{
    std::cout<< "~DirProcess()" << std::endl;
}

QList<QString> DirProcess::getDirFileName(const QString& pathDir)
{
    QList<QString> allFileName;
    QDir *dir=new QDir(pathDir);
    allFileName.clear();
    if(dir->exists())
    {
        QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList());
        int fileCount=fileInfo->count();
        for(int loop=0;loop<fileCount;loop++)
        {
            //qDebug()<<fileInfo->at(loop).absoluteFilePath();
            if(fileInfo->at(loop).isFile())
            {
                allFileName.append(fileInfo->at(loop).absoluteFilePath());
            }
        }
    }
    else
    {
        qDebug()<<pathDir<<" not exists!";
    }
    return allFileName;
}

QList<QString> DirProcess::getDirFileName(const QString &pathDir,QString filterPostfix)
{
    QList<QString> allFileName;
    QDir *dir=new QDir(pathDir);
    allFileName.clear();
    if(dir->exists())
    {
        QStringList filter;
        filter<<filterPostfix;
        QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
        int fileCount=fileInfo->count();
        for(int loop=0;loop<fileCount;loop++)
        {
            //qDebug()<<fileInfo->at(loop).absoluteFilePath();
            allFileName.append(fileInfo->at(loop).absoluteFilePath());
        }
    }
    else
    {
        qDebug()<<pathDir<<" not exists!";
    }
    return allFileName;
}

void DirProcess::modifyDirFileName(const QString &pathDir,const QString &rePathDir)
{
    QDir *dir=new QDir(pathDir);
    int count=0;
    if(dir->exists())
    {
        QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList());
        QDir makeDir;
        int fileCount=fileInfo->count();
        int width=QString::number(fileCount).length();
        if(!makeDir.exists(rePathDir))
        {
            if(!makeDir.mkdir(rePathDir))
            {
                return;
            }
        }
        for(int loop=0;loop<fileCount;loop++)
        {
            qDebug()<<fileInfo->at(loop).absoluteFilePath();
            if(fileInfo->at(loop).isFile())
            {
                QString suffix=fileInfo->at(loop).completeSuffix();
                QFile file(fileInfo->at(loop).absoluteFilePath());
                QString post=QString::fromStdString(toNumberStr(count,width));
                count++;
                QString reName=QString("img%1").arg(post)+"."+suffix;
                QString newName=rePathDir+"/"+reName;
                file.rename(newName);
                file.close();
            }
        }
    }
    else
    {
        qDebug()<<pathDir<<" not exists!";
    }
}

void DirProcess::modifyDirFileName(const QString &pathDir,const QString &rePathDir,QString filterPostfix)
{
    QDir *dir=new QDir(pathDir);
    if(dir->exists())
    {
        QStringList filter;
        //filter<<"*.jpg";
        filter<<filterPostfix;
        QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
        QDir makeDir;
        int fileCount=fileInfo->count();
        int width=QString::number(fileCount).length();
        if(!makeDir.exists(rePathDir))
        {
            if(!makeDir.mkdir(rePathDir))
            {
                return;
            }
        }
        for(int loop=0;loop<fileCount;loop++)
        {
            qDebug()<<fileInfo->at(loop).absoluteFilePath();
            QFile file(fileInfo->at(loop).absoluteFilePath());
            QString post=QString::fromStdString(toNumberStr(loop,width));
            QString suffix=filterPostfix.mid(1);
            QString reName=QString("img%1").arg(post)+suffix;
            QString newName=rePathDir+"/"+reName;
            file.rename(newName);
            file.close();
        }
    }
    else
    {
        qDebug()<<pathDir<<" not exists!";
    }
}

std::string DirProcess::toNumberStr(const int number,const int width)
{
    std::ostringstream output;
    output << std::setfill('0') << std::setw(width) << number;
    return output.str();
}
