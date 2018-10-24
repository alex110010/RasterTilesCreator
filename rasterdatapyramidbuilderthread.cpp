#include "rasterdatapyramidbuilderthread.h"

RasterDataPyramidBuilderThread::RasterDataPyramidBuilderThread(QString rasterDataPath, QString rasterCachePath, int pyramidMaxLevel, QObject *parent) : QThread(parent)
{
    qDebug() << __FUNCTION__;
    _rasterDataPath = rasterDataPath;
    _rasterCachePath = rasterCachePath;
    _rasterPyramidMaxLevel = pyramidMaxLevel;
}

void RasterDataPyramidBuilderThread::run(){
    qDebug() << __FUNCTION__;
    pyramidBuilder = new RasterPyramidBuilder(_rasterDataPath, _rasterCachePath, _rasterPyramidMaxLevel);

    /*
    connect(this, &RasterDataPyramidBuilderThread::READ_RASTER_DATA, pyramidBuilder, &RasterPyramidBuilder::READ_RASTER_DATA);
    connect(pyramidBuilder, &RasterPyramidBuilder::RASTER_DATA_HAS_BEEN_READ, this, &RasterDataPyramidBuilderThread::RASTER_DATA_HAS_BEEN_READ);
    connect(this, &RasterDataPyramidBuilderThread::PROCESS_RASTER_DATA, pyramidBuilder, &RasterPyramidBuilder::PROCESS_RASTER_DATA);
    connect(pyramidBuilder, &RasterPyramidBuilder::PROCESS_STEP_FINISHED, this, &RasterDataPyramidBuilderThread::PROCESS_STEP_FINISHED);
    connect(pyramidBuilder, &RasterPyramidBuilder::PROCESS_FINISHED, this, &RasterDataPyramidBuilderThread::PROCESS_FINISHED);
    */

    connect(this, SIGNAL(READ_RASTER_DATA()), pyramidBuilder, SLOT(READ_RASTER_DATA()));
    connect(pyramidBuilder, SIGNAL(RASTER_DATA_HAS_BEEN_READ(bool,int)), this, SIGNAL(RASTER_DATA_HAS_BEEN_READ(bool,int)));
    connect(this, SIGNAL(PROCESS_RASTER_DATA()), pyramidBuilder, SLOT(PROCESS_RASTER_DATA()));
    connect(pyramidBuilder, SIGNAL(PROCESS_STEP_FINISHED(int)), this, SIGNAL(PROCESS_STEP_FINISHED(int)));
    connect(pyramidBuilder, SIGNAL(PROCESS_FINISHED(bool)), this, SIGNAL(PROCESS_FINISHED(bool)));

    exec();
}
