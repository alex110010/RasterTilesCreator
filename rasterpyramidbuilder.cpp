#include "rasterpyramidbuilder.h"

RasterPyramidBuilder::RasterPyramidBuilder(QString rasterDataPath, QString rasterCachePath, int pyramidMaxLevel, QObject *parent) : QObject(parent)
{
    qDebug() << __FUNCTION__;
    _rasterDataPath = rasterDataPath;
    _rasterCachePath = rasterCachePath;
    _rasterPyramidMaxLevel = pyramidMaxLevel;
    _poRasterDataSet = nullptr;

    _imRasterWidth = 0;
    _imRasterHeight = 0;

    _realRasterWidth = 0;
    _realRasterHeight = 0;

    GDALAllRegister();
}

void RasterPyramidBuilder::READ_RASTER_DATA()
{
    qDebug() << __FUNCTION__;
    if(!QFile(_rasterDataPath).exists() || _rasterDataPath.isEmpty())
    {
        emit RASTER_DATA_HAS_BEEN_READ(false, 0);
        return;
    }

    if (!QDir(_rasterCachePath + "/cache").exists())
    {
        mkdir((_rasterCachePath + "/cache").toStdString().data());
    }

    // Чтение растрового изображения
    _poRasterDataSet = (GDALDataset*)GDALOpen(_rasterDataPath.toStdString().data(), GA_ReadOnly);
    if (_poRasterDataSet == nullptr)
    {
        emit RASTER_DATA_HAS_BEEN_READ(false, 0);
        return;
    }

    _imRasterWidth = qMax(_poRasterDataSet->GetRasterXSize(), _poRasterDataSet->GetRasterYSize());
    _imRasterHeight = qMax(_poRasterDataSet->GetRasterXSize(), _poRasterDataSet->GetRasterYSize());

    _realRasterWidth = _poRasterDataSet->GetRasterXSize();
    _realRasterHeight = _poRasterDataSet->GetRasterYSize();

    // Максимальный допустимый слой
    int maxLayer = 1;
    int layerWidthInBase = qPow(2, 8 + maxLayer);
    while (layerWidthInBase + 1 < _imRasterWidth)
    {
        maxLayer++;
        layerWidthInBase = qPow(2, 8 + maxLayer);
    }

    emit RASTER_DATA_HAS_BEEN_READ(true, maxLayer);
}

void RasterPyramidBuilder::PROCESS_RASTER_DATA()
{
    qDebug() << __FUNCTION__;
    // Параметры алгоритма построения растровой пирамиды
    _hasPalette = (GDALGetRasterColorInterpretation(GDALGetRasterBand((GDALDatasetH*)_poRasterDataSet, 1)) == GCI_PaletteIndex);
    int rasterWidth = qMax(_poRasterDataSet->GetRasterXSize(), _poRasterDataSet->GetRasterYSize());   // (!) quarterWidth = quarterHeight (!)
    int rasterHeight = qMax(_poRasterDataSet->GetRasterXSize(), _poRasterDataSet->GetRasterYSize());
    int layerNum = 1;
    QString quarterName("");
    QQueue<QString> queueQuarterNames;

    if (convertRasterQuarter((GDALDatasetH*)_poRasterDataSet, layerNum, quarterName, 0, 0, rasterWidth, rasterHeight))
    {
        queueQuarterNames.enqueue("q");
        queueQuarterNames.enqueue("r");
        queueQuarterNames.enqueue("s");
        queueQuarterNames.enqueue("t");

        emit PROCESS_STEP_FINISHED(4);

        while (!queueQuarterNames.empty() && layerNum < _rasterPyramidMaxLevel)
        {
            quarterName = queueQuarterNames.dequeue();
            QString quarterNameNumber;
            QString quarterNameBinX;
            QString quarterNameBinY;
            int quarterX;
            int quarterY;
            layerNum = quarterName.size();
            int quarterWidth = rasterWidth / qPow(2, layerNum);
            int quarterHeight = rasterHeight / qPow(2, layerNum);

            if (layerNum >= _rasterPyramidMaxLevel)
            {
                break;
            }

            for (int i = 0; i < quarterName.size(); i++)
            {
                switch (quarterName[i].toLatin1())
                {
                case 'q':
                    quarterNameNumber += QString::number(0);
                    break;
                case 'r':
                    quarterNameNumber += QString::number(1);
                    break;
                case 's':
                    quarterNameNumber += QString::number(2);
                    break;
                case 't':
                    quarterNameNumber += QString::number(3);
                    break;
                }

                if (quarterNameNumber[i].digitValue() % 2 == 0)
                {
                    quarterNameBinX += QString::number(0);
                }
                else
                {
                    quarterNameBinX += QString::number(1);
                }

                if (quarterNameNumber[i].digitValue() < 2)
                {
                    quarterNameBinY += QString::number(0);
                }
                else
                {
                    quarterNameBinY += QString::number(1);
                }
            }

            bool okX;
            bool okY;
            quarterX = quarterNameBinX.toInt(&okX, 2) * quarterWidth;
            quarterY = quarterNameBinY.toInt(&okY, 2) * quarterHeight;

            if (okX && okY)
            {
                if (convertRasterQuarter((GDALDatasetH*)_poRasterDataSet, layerNum + 1, quarterName, quarterX, quarterY, quarterWidth, quarterHeight))
                {
                    queueQuarterNames.enqueue(quarterName + "q");
                    queueQuarterNames.enqueue(quarterName + "r");
                    queueQuarterNames.enqueue(quarterName + "s");
                    queueQuarterNames.enqueue(quarterName + "t");

                    emit PROCESS_STEP_FINISHED(4);
                }
                else
                {
                    emit PROCESS_FINISHED(true);
                    return;
                }
            }
            else
            {
                emit PROCESS_FINISHED(false);
                return;
            }
        }
    }
    else
    {
        emit PROCESS_FINISHED(false);
        return;
    }

    if (!queueQuarterNames.empty())
    {
        queueQuarterNames.clear();
    }
    GDALClose(_poRasterDataSet);

    emit PROCESS_FINISHED(true);
    return;
}

bool RasterPyramidBuilder::convertRasterQuarter(GDALDatasetH *poSrcDS, int layerNum, QString quarterName, int xOff, int yOff, int quarterWidth, int quarterHeight) // 1, r, xOff, yOff, w, h
{
    qDebug() << __FUNCTION__;
    // poSrcDS должен быть открыт (!)
    QString cacheLayerPath = _rasterCachePath + "/cache/" + QString::number(layerNum);
    if (!QDir(cacheLayerPath).exists())
    {
        mkdir(cacheLayerPath.toStdString().data());
    }

    if (quarterWidth / 2 < 256 || quarterHeight / 2 < 256)
    {
        return false;
    }

    int quarterCode = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int leftTopPtX = xOff + j * quarterWidth / 2;
            int leftTopPtY = yOff + i * quarterHeight / 2;

            char **argv = NULL;
            argv = CSLAddString(argv, "-of");
            argv = CSLAddString(argv, "png");
            if (_hasPalette)
            {
                argv = CSLAddString(argv, "-expand");
                argv = CSLAddString(argv, "rgba");
            }
            argv = CSLAddString(argv, "-srcwin");
            argv = CSLAddString(argv, QString::number(leftTopPtX - (_imRasterWidth - _realRasterWidth)/2).toStdString().data());
            argv = CSLAddString(argv, QString::number(leftTopPtY - (_imRasterHeight - _realRasterHeight)/2).toStdString().data());
            argv = CSLAddString(argv, QString::number(quarterWidth / 2).toStdString().data()); // +1 ?
            argv = CSLAddString(argv, QString::number(quarterHeight / 2).toStdString().data());
            argv = CSLAddString(argv, "-outsize");
            argv = CSLAddString(argv, "256");
            argv = CSLAddString(argv, "256");

            QString fileNameOut = cacheLayerPath + "/" + quarterName;
            switch (quarterCode)
            {
                case 0:
                    fileNameOut += "q";
                    break;
                case 1:
                    fileNameOut += "r";
                    break;
                case 2:
                    fileNameOut += "s";
                    break;
                case 3:
                    fileNameOut += "t";
                    break;
            }
            fileNameOut += ".png";

            GDALTranslateOptions *psOptions = GDALTranslateOptionsNew(argv, NULL);
            int pbUsageError = false;
            GDALDatasetH poDstDataSet = GDALTranslate(fileNameOut.toStdString().data(), poSrcDS, psOptions, &pbUsageError);

            qDebug() << "pbUsageError=" << fileNameOut << pbUsageError << "-srcwin" << leftTopPtX << leftTopPtY << quarterWidth / 2 << quarterHeight / 2;
            GDALTranslateOptionsFree(psOptions);
            CSLDestroy(argv);
            GDALClose(poDstDataSet);
            QFile::remove(fileNameOut + ".aux.xml");
            quarterCode++;
        }
    }
    return true;
}

QPoint RasterPyramidBuilder::qrst2xyz(const QString &quarterName, int rasterXSize, int rasterYSize, int zoom) // zoom = {1, 2, 3, ..., 32}
{
    QString quarterNameNumber;
    QString quarterNameBinX;
    QString quarterNameBinY;

    for (int i = 0; i < quarterName.size(); i++)
    {
        switch (quarterName[i].toLatin1())
        {
        case 'q':
            quarterNameNumber += QString::number(0);
            break;
        case 'r':
            quarterNameNumber += QString::number(1);
            break;
        case 's':
            quarterNameNumber += QString::number(2);
            break;
        case 't':
            quarterNameNumber += QString::number(3);
            break;
        }

        if (quarterNameNumber[i].digitValue() % 2 == 0)
        {
            quarterNameBinX += QString::number(0);
        }
        else
        {
            quarterNameBinX += QString::number(1);
        }

        if (quarterNameNumber[i].digitValue() < 2)
        {
            quarterNameBinY += QString::number(0);
        }
        else
        {
            quarterNameBinY += QString::number(1);
        }
    }

    bool okX;
    bool okY;
    int quarterWidth = rasterXSize / qPow(2, zoom);
    int quarterHeight = rasterYSize / qPow(2, zoom);
    int quarterX = quarterNameBinX.toInt(&okX, 2) * quarterWidth;
    int quarterY = quarterNameBinY.toInt(&okY, 2) * quarterHeight;

    if (okX && okY)
    {
        return QPoint(quarterX, quarterY);
    }
    else
    {
        return QPoint(-1, -1);
    }
}
