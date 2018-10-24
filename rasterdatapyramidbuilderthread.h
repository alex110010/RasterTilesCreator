#ifndef RASTERDATAPYRAMIDBUILDERTHREAD_H
#define RASTERDATAPYRAMIDBUILDERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include <rasterpyramidbuilder.h>

class RasterDataPyramidBuilderThread : public QThread
{
    Q_OBJECT
public:
    RasterDataPyramidBuilderThread(QString rasterDataPath, QString rasterCachePath, int pyramidMaxLevel, QObject *parent = 0);
    RasterPyramidBuilder* pyramidBuilder;
signals:
    void RASTER_DATA_HAS_BEEN_READ(bool ok, int realMaxLayer);
    void READ_RASTER_DATA();
    void PROCESS_RASTER_DATA();
    void PROCESS_STEP_FINISHED(int nTilesProcessed);
    void PROCESS_FINISHED(bool ok);
private:
    QString _rasterCachePath;
    QString _rasterDataPath;
    int _rasterPyramidMaxLevel;
protected:
    void run();
public slots:
};

#endif // RASTERDATAPYRAMIDBUILDERTHREAD_H
