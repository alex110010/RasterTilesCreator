#ifndef RASTERPYRAMIDBUILDER_H
#define RASTERPYRAMIDBUILDER_H

#include <QObject>
#include <QQueue>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <qmath.h>

// include GDAL headers
#include "gdal_priv.h"
#include "cpl_conv.h"
#include "gdal.h"
#include "gdalwarper.h"

#include "gdal_utils.h"
#include "ogr_spatialref.h"
#include "cpl_string.h"
#include "ogr_geometry.h"

class RasterPyramidBuilder : public QObject
{
    Q_OBJECT
public:
    explicit RasterPyramidBuilder(QString rasterDataPath, QString rasterCachePath, int pyramidMaxLevel, QObject *parent = 0);

private:
    GDALDataset* _poRasterDataSet;
    QString _rasterCachePath;
    QString _rasterDataPath;
    int _rasterPyramidMaxLevel;
    bool _hasPalette;
    bool convertRasterQuarter(GDALDatasetH* poSrcDS, int layerNum, QString quarterName, int xOff, int yOff, int quarterWidth, int quarterHeight);
    QPoint qrst2xyz(const QString& quarterName, int rasterXSize, int rasterYSize, int zoom);

    int _imRasterWidth;
    int _imRasterHeight;

    int _realRasterWidth;
    int _realRasterHeight;

signals:
    void RASTER_DATA_HAS_BEEN_READ(bool ok, int realMaxLayer);
    void PROCESS_STEP_FINISHED(int nTilesProcessed);
    void PROCESS_FINISHED(bool ok);
public slots:
    void READ_RASTER_DATA();
    void PROCESS_RASTER_DATA();
};

#endif // RASTERPYRAMIDBUILDER_H
