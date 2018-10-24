#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QFileDialog>
#include <QThread>
#include <QObject>
#include <QTimer>

#include <rasterdatapyramidbuilderthread.h>

// include GDAL headers
#include "gdal_priv.h"
#include "cpl_conv.h"
#include "gdal.h"
#include "gdalwarper.h"

#include "gdal_utils.h"
#include "ogr_spatialref.h"
#include "cpl_string.h"
#include "ogr_geometry.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GDALDataset* poSrcDataSet;
    bool _hasPalette;
    QString _rasterStoragePath;
    QString _rasterCachePath;

    RasterDataPyramidBuilderThread* pyramidBuilderThread;

private slots:
    quint64 getSizeDirRecurs(QString path);

    //интерфейс
    void on_pB_downloadRasterPath_clicked();
    void on_pB_convertRasterData_clicked();
    void on_pB_downloadRasterCachePath_clicked();

signals:
    void READ_RASTER_DATA();
    void PROCESS_RASTER_DATA();
public slots:
    void GET_RASTER_DATA_READING_RESULT(bool ok, int realMaxLayer);
    void GET_PROCESSED_TILES_NUMBER(int nTilesProcessed);
    void GET_PROCESS_FINISH(bool ok);
    void SEND_READ_RASTER_DATA();
};

#endif // MAINWINDOW_H
