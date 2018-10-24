#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Alex
    poSrcDataSet = nullptr;
    _hasPalette = false;
    _rasterStoragePath = QString("");
    _rasterCachePath = QString("");
    pyramidBuilderThread = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

quint64 MainWindow::getSizeDirRecurs(QString path) //взято с http://www.cyberforum.ru/qt/thread644532.html
{
    QDir currentFolder(path);
    quint64 total_size = 0;
    currentFolder.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
    currentFolder.setSorting(QDir::Name);

    QFileInfoList folderitems(currentFolder.entryInfoList());

    foreach (QFileInfo i, folderitems)
    {
        QString iname(i.fileName());
        if(iname == "." || iname == ".." || iname.isEmpty())
            continue;

        if(i.isDir())
            total_size += getSizeDirRecurs(path + "/" + iname);
        else
            total_size += i.size();
    }
    return total_size;
}

void MainWindow::on_pB_downloadRasterPath_clicked()
{
    _rasterStoragePath = QFileDialog::getOpenFileName(this, tr("Выберите путь к растровому изображению"), ".", tr("*.tif"));
    ui->le_rasterStoragePath->setText(_rasterStoragePath);
}

void MainWindow::on_pB_convertRasterData_clicked()
{
    if(!_rasterStoragePath.isEmpty() && QFile(_rasterStoragePath).exists())
    {
        if (!_rasterCachePath.isEmpty() && QDir(_rasterCachePath).exists())
        {
            // Общее кол-во тайлов пирамиды
            int totalTilesNumber = 0;
            for (int i = 0; i < ui->sB_rasterPyramidMaxLevel->value(); i++)
            {
                totalTilesNumber += qPow(2, 2 * (i + 1));
            }

            // Инициализация прогресс-бара
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(totalTilesNumber);
            ui->progressBar->setValue(ui->progressBar->minimum());

            pyramidBuilderThread = new RasterDataPyramidBuilderThread(_rasterStoragePath, _rasterCachePath, ui->sB_rasterPyramidMaxLevel->value(), this);

            connect(this, SIGNAL(READ_RASTER_DATA()), pyramidBuilderThread, SIGNAL(READ_RASTER_DATA()));
            connect(pyramidBuilderThread, SIGNAL(RASTER_DATA_HAS_BEEN_READ(bool, int)), this, SLOT(GET_RASTER_DATA_READING_RESULT(bool, int)));
            connect(this, SIGNAL(PROCESS_RASTER_DATA()), pyramidBuilderThread, SIGNAL(PROCESS_RASTER_DATA()));
            connect(pyramidBuilderThread, SIGNAL(PROCESS_STEP_FINISHED(int)), this, SLOT(GET_PROCESSED_TILES_NUMBER(int)));
            connect(pyramidBuilderThread, SIGNAL(PROCESS_FINISHED(bool)), this, SLOT(GET_PROCESS_FINISH(bool)));
            pyramidBuilderThread->start();
            QTimer::singleShot(500, this, SLOT(SEND_READ_RASTER_DATA()));
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Не выбрана директория для кэша растрового изображения!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не выбран исходный растр!");
    }
}

void MainWindow::on_pB_downloadRasterCachePath_clicked()
{
    _rasterCachePath = QFileDialog::getExistingDirectory(this, tr("Выберите директорию для кэша растрового изображения"), ".");
    ui->le_rasterCachePath->setText(_rasterCachePath);
}

void MainWindow::SEND_READ_RASTER_DATA()
{
    emit READ_RASTER_DATA();
}

void MainWindow::GET_RASTER_DATA_READING_RESULT(bool ok, int realMaxLayer)
{
    qDebug() << __FUNCTION__;
    if (ok)
    {
        emit PROCESS_RASTER_DATA();

        // Общее кол-во тайлов пирамиды
        int totalTilesNumber = 0;
        for (int i = 0; i < realMaxLayer; i++)
        {
            totalTilesNumber += qPow(2, 2 * (i + 1));
        }

        // Инициализация прогресс-бара
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(qMin(ui->progressBar->maximum(), totalTilesNumber));
        ui->progressBar->setValue(ui->progressBar->minimum());
    }
}

void MainWindow::GET_PROCESSED_TILES_NUMBER(int nTilesProcessed)
{
    qDebug() << __FUNCTION__;
    ui->progressBar->setValue(ui->progressBar->value() + nTilesProcessed);
}

void MainWindow::GET_PROCESS_FINISH(bool ok)
{
    qDebug() << __FUNCTION__;
    if (ok)
    {
        QMessageBox::information(this, "Информация", "Набор тайлов создан успешно!");
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка при создании набора тайлов!");
    }

    ui->progressBar->setValue(0);
    ui->pB_convertRasterData->setEnabled(true);
    ui->sB_rasterPyramidMaxLevel->setEnabled(true);
}
