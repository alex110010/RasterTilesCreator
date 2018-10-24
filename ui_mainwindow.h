/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lbl_RasterPyramidMaxLevel;
    QSpinBox *sB_rasterPyramidMaxLevel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pB_convertRasterData;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *le_rasterStoragePath;
    QToolButton *pB_downloadRasterPath;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *le_rasterCachePath;
    QToolButton *pB_downloadRasterCachePath;
    QProgressBar *progressBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(565, 304);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lbl_RasterPyramidMaxLevel = new QLabel(centralWidget);
        lbl_RasterPyramidMaxLevel->setObjectName(QStringLiteral("lbl_RasterPyramidMaxLevel"));

        horizontalLayout_2->addWidget(lbl_RasterPyramidMaxLevel);

        sB_rasterPyramidMaxLevel = new QSpinBox(centralWidget);
        sB_rasterPyramidMaxLevel->setObjectName(QStringLiteral("sB_rasterPyramidMaxLevel"));
        sB_rasterPyramidMaxLevel->setMinimum(2);
        sB_rasterPyramidMaxLevel->setMaximum(32);
        sB_rasterPyramidMaxLevel->setValue(7);

        horizontalLayout_2->addWidget(sB_rasterPyramidMaxLevel);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pB_convertRasterData = new QPushButton(centralWidget);
        pB_convertRasterData->setObjectName(QStringLiteral("pB_convertRasterData"));
        pB_convertRasterData->setEnabled(true);
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        pB_convertRasterData->setFont(font);

        horizontalLayout->addWidget(pB_convertRasterData);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        le_rasterStoragePath = new QLineEdit(groupBox_2);
        le_rasterStoragePath->setObjectName(QStringLiteral("le_rasterStoragePath"));
        le_rasterStoragePath->setReadOnly(true);

        gridLayout_2->addWidget(le_rasterStoragePath, 0, 0, 1, 1);

        pB_downloadRasterPath = new QToolButton(groupBox_2);
        pB_downloadRasterPath->setObjectName(QStringLiteral("pB_downloadRasterPath"));

        gridLayout_2->addWidget(pB_downloadRasterPath, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        le_rasterCachePath = new QLineEdit(groupBox);
        le_rasterCachePath->setObjectName(QStringLiteral("le_rasterCachePath"));
        le_rasterCachePath->setEnabled(true);
        le_rasterCachePath->setReadOnly(true);

        gridLayout->addWidget(le_rasterCachePath, 0, 0, 1, 1);

        pB_downloadRasterCachePath = new QToolButton(groupBox);
        pB_downloadRasterCachePath->setObjectName(QStringLiteral("pB_downloadRasterCachePath"));
        pB_downloadRasterCachePath->setEnabled(true);

        gridLayout->addWidget(pB_downloadRasterCachePath, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setOrientation(Qt::Vertical);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::BottomToTop);

        gridLayout_3->addWidget(progressBar, 0, 1, 3, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 565, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Raster Tiles Creator (Zavarzin A.A.)", Q_NULLPTR));
        lbl_RasterPyramidMaxLevel->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \321\203\321\200\320\276\320\262\320\275\320\265\320\271 \320\277\320\270\321\200\320\260\320\274\320\270\320\264\321\213: ", Q_NULLPTR));
        pB_convertRasterData->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\260\320\261\320\276\321\200 \321\202\320\260\320\271\320\273\320\276\320\262", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\200\320\260\321\201\321\202\321\200\320\276\320\262\320\276\320\274\321\203 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\216", Q_NULLPTR));
        pB_downloadRasterPath->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\272\321\215\321\210\321\203 \321\200\320\260\321\201\321\202\321\200\320\276\320\262\320\276\320\263\320\276 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", Q_NULLPTR));
        le_rasterCachePath->setText(QString());
        pB_downloadRasterCachePath->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
