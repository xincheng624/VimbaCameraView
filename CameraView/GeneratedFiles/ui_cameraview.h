/********************************************************************************
** Form generated from reading UI file 'cameraview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAVIEW_H
#define UI_CAMERAVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraViewClass
{
public:
    QAction *actionTest;
    QAction *actionAbout;
    QAction *actionCircle;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollAreaPic;
    QWidget *scrollAreaWidgetContents;
    QWidget *widgetControl;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelImgNumber;
    QLineEdit *lineEditImgNumber;
    QPushButton *pushButtonSave;
    QCheckBox *checkBoxProcess;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelWidth;
    QLineEdit *lineEditWidth;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelHeight;
    QLineEdit *lineEditHeight;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelFramePerSecond;
    QLineEdit *lineEditFramePerSecond;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelExposureTime;
    QLineEdit *lineEditExposureTime;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelFrame;
    QLineEdit *lineEditFrame;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelX;
    QLineEdit *lineEditX;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelY;
    QLineEdit *lineEditY;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label;
    QLineEdit *lineEditRadius1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelRadius;
    QLineEdit *lineEditRadius2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelRadiusError;
    QLineEdit *lineEditRadiusError;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *labelInfo;
    QSpacerItem *horizontalSpacer_2;
    QTextBrowser *textBrowserInfo;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *labelError;
    QSpacerItem *horizontalSpacer_3;
    QTextBrowser *textBrowserError;
    QLabel *labelPicShow;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CameraViewClass)
    {
        if (CameraViewClass->objectName().isEmpty())
            CameraViewClass->setObjectName(QString::fromUtf8("CameraViewClass"));
        CameraViewClass->resize(1000, 800);
        actionTest = new QAction(CameraViewClass);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        actionTest->setMenuRole(QAction::NoRole);
        actionAbout = new QAction(CameraViewClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionCircle = new QAction(CameraViewClass);
        actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
        centralwidget = new QWidget(CameraViewClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 974, 700));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollAreaPic = new QScrollArea(layoutWidget);
        scrollAreaPic->setObjectName(QString::fromUtf8("scrollAreaPic"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaPic->sizePolicy().hasHeightForWidth());
        scrollAreaPic->setSizePolicy(sizePolicy);
        scrollAreaPic->setMinimumSize(QSize(620, 420));
        scrollAreaPic->setMaximumSize(QSize(1000, 1000));
        scrollAreaPic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaPic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaPic->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 618, 418));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 0));
        scrollAreaWidgetContents->setMaximumSize(QSize(60000, 30000));
        scrollAreaPic->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollAreaPic);

        widgetControl = new QWidget(layoutWidget);
        widgetControl->setObjectName(QString::fromUtf8("widgetControl"));
        widgetControl->setMinimumSize(QSize(600, 80));
        widgetControl->setMaximumSize(QSize(600, 80));
        widgetControl->setAutoFillBackground(true);
        layoutWidget_2 = new QWidget(widgetControl);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(70, 0, 481, 81));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(40, -1, 40, -1);
        pushButtonStart = new QPushButton(layoutWidget_2);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setEnabled(false);

        horizontalLayout->addWidget(pushButtonStart);

        pushButtonStop = new QPushButton(layoutWidget_2);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setEnabled(false);

        horizontalLayout->addWidget(pushButtonStop);


        verticalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(40, -1, 40, -1);
        labelImgNumber = new QLabel(layoutWidget_2);
        labelImgNumber->setObjectName(QString::fromUtf8("labelImgNumber"));
        labelImgNumber->setMaximumSize(QSize(60, 20));

        horizontalLayout_2->addWidget(labelImgNumber);

        lineEditImgNumber = new QLineEdit(layoutWidget_2);
        lineEditImgNumber->setObjectName(QString::fromUtf8("lineEditImgNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditImgNumber->sizePolicy().hasHeightForWidth());
        lineEditImgNumber->setSizePolicy(sizePolicy1);
        lineEditImgNumber->setMinimumSize(QSize(40, 10));
        lineEditImgNumber->setMaximumSize(QSize(40, 20));

        horizontalLayout_2->addWidget(lineEditImgNumber);

        pushButtonSave = new QPushButton(layoutWidget_2);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setEnabled(false);

        horizontalLayout_2->addWidget(pushButtonSave);

        checkBoxProcess = new QCheckBox(layoutWidget_2);
        checkBoxProcess->setObjectName(QString::fromUtf8("checkBoxProcess"));
        checkBoxProcess->setEnabled(false);
        checkBoxProcess->setMinimumSize(QSize(100, 20));
        checkBoxProcess->setMaximumSize(QSize(100, 20));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        checkBoxProcess->setFont(font);
        checkBoxProcess->setContextMenuPolicy(Qt::NoContextMenu);
        checkBoxProcess->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(checkBoxProcess);


        verticalLayout_6->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(widgetControl);


        horizontalLayout_12->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelWidth = new QLabel(layoutWidget);
        labelWidth->setObjectName(QString::fromUtf8("labelWidth"));
        labelWidth->setMinimumSize(QSize(100, 0));
        labelWidth->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(labelWidth);

        lineEditWidth = new QLineEdit(layoutWidget);
        lineEditWidth->setObjectName(QString::fromUtf8("lineEditWidth"));
        lineEditWidth->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(lineEditWidth);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelHeight = new QLabel(layoutWidget);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));
        labelHeight->setMinimumSize(QSize(100, 0));
        labelHeight->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(labelHeight);

        lineEditHeight = new QLineEdit(layoutWidget);
        lineEditHeight->setObjectName(QString::fromUtf8("lineEditHeight"));
        lineEditHeight->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(lineEditHeight);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelFramePerSecond = new QLabel(layoutWidget);
        labelFramePerSecond->setObjectName(QString::fromUtf8("labelFramePerSecond"));
        labelFramePerSecond->setMinimumSize(QSize(100, 0));
        labelFramePerSecond->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(labelFramePerSecond);

        lineEditFramePerSecond = new QLineEdit(layoutWidget);
        lineEditFramePerSecond->setObjectName(QString::fromUtf8("lineEditFramePerSecond"));
        lineEditFramePerSecond->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(lineEditFramePerSecond);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelExposureTime = new QLabel(layoutWidget);
        labelExposureTime->setObjectName(QString::fromUtf8("labelExposureTime"));
        labelExposureTime->setMinimumSize(QSize(100, 0));
        labelExposureTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(labelExposureTime);

        lineEditExposureTime = new QLineEdit(layoutWidget);
        lineEditExposureTime->setObjectName(QString::fromUtf8("lineEditExposureTime"));
        lineEditExposureTime->setMinimumSize(QSize(0, 30));

        horizontalLayout_6->addWidget(lineEditExposureTime);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelFrame = new QLabel(layoutWidget);
        labelFrame->setObjectName(QString::fromUtf8("labelFrame"));
        labelFrame->setMinimumSize(QSize(100, 0));
        labelFrame->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(labelFrame);

        lineEditFrame = new QLineEdit(layoutWidget);
        lineEditFrame->setObjectName(QString::fromUtf8("lineEditFrame"));
        lineEditFrame->setMinimumSize(QSize(0, 30));

        horizontalLayout_7->addWidget(lineEditFrame);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelX = new QLabel(layoutWidget);
        labelX->setObjectName(QString::fromUtf8("labelX"));
        labelX->setMinimumSize(QSize(80, 0));
        labelX->setMaximumSize(QSize(50, 16777215));
        labelX->setLayoutDirection(Qt::LeftToRight);
        labelX->setAutoFillBackground(false);
        labelX->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(labelX);

        lineEditX = new QLineEdit(layoutWidget);
        lineEditX->setObjectName(QString::fromUtf8("lineEditX"));
        lineEditX->setMinimumSize(QSize(0, 30));

        horizontalLayout_8->addWidget(lineEditX);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelY = new QLabel(layoutWidget);
        labelY->setObjectName(QString::fromUtf8("labelY"));
        labelY->setMinimumSize(QSize(80, 0));
        labelY->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(labelY);

        lineEditY = new QLineEdit(layoutWidget);
        lineEditY->setObjectName(QString::fromUtf8("lineEditY"));
        lineEditY->setMinimumSize(QSize(0, 30));

        horizontalLayout_9->addWidget(lineEditY);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(80, 0));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label);

        lineEditRadius1 = new QLineEdit(layoutWidget);
        lineEditRadius1->setObjectName(QString::fromUtf8("lineEditRadius1"));
        lineEditRadius1->setMinimumSize(QSize(0, 30));

        horizontalLayout_16->addWidget(lineEditRadius1);


        verticalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelRadius = new QLabel(layoutWidget);
        labelRadius->setObjectName(QString::fromUtf8("labelRadius"));
        labelRadius->setMinimumSize(QSize(80, 0));
        labelRadius->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(labelRadius);

        lineEditRadius2 = new QLineEdit(layoutWidget);
        lineEditRadius2->setObjectName(QString::fromUtf8("lineEditRadius2"));
        lineEditRadius2->setMinimumSize(QSize(0, 30));

        horizontalLayout_10->addWidget(lineEditRadius2);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        labelRadiusError = new QLabel(layoutWidget);
        labelRadiusError->setObjectName(QString::fromUtf8("labelRadiusError"));
        labelRadiusError->setMinimumSize(QSize(80, 0));
        labelRadiusError->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(labelRadiusError);

        lineEditRadiusError = new QLineEdit(layoutWidget);
        lineEditRadiusError->setObjectName(QString::fromUtf8("lineEditRadiusError"));
        lineEditRadiusError->setMinimumSize(QSize(0, 30));

        horizontalLayout_11->addWidget(lineEditRadiusError);


        verticalLayout_2->addLayout(horizontalLayout_11);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_12->addLayout(verticalLayout_3);


        verticalLayout_8->addLayout(horizontalLayout_12);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        labelInfo = new QLabel(layoutWidget);
        labelInfo->setObjectName(QString::fromUtf8("labelInfo"));

        horizontalLayout_13->addWidget(labelInfo);

        horizontalSpacer_2 = new QSpacerItem(338, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_13);

        textBrowserInfo = new QTextBrowser(layoutWidget);
        textBrowserInfo->setObjectName(QString::fromUtf8("textBrowserInfo"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textBrowserInfo->sizePolicy().hasHeightForWidth());
        textBrowserInfo->setSizePolicy(sizePolicy2);
        textBrowserInfo->setMinimumSize(QSize(480, 150));
        textBrowserInfo->setMaximumSize(QSize(480, 150));

        verticalLayout_5->addWidget(textBrowserInfo);


        horizontalLayout_15->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        labelError = new QLabel(layoutWidget);
        labelError->setObjectName(QString::fromUtf8("labelError"));

        horizontalLayout_14->addWidget(labelError);

        horizontalSpacer_3 = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_3);


        verticalLayout_7->addLayout(horizontalLayout_14);

        textBrowserError = new QTextBrowser(layoutWidget);
        textBrowserError->setObjectName(QString::fromUtf8("textBrowserError"));
        sizePolicy2.setHeightForWidth(textBrowserError->sizePolicy().hasHeightForWidth());
        textBrowserError->setSizePolicy(sizePolicy2);
        textBrowserError->setMinimumSize(QSize(480, 150));
        textBrowserError->setMaximumSize(QSize(480, 150));

        verticalLayout_7->addWidget(textBrowserError);


        horizontalLayout_15->addLayout(verticalLayout_7);


        verticalLayout_8->addLayout(horizontalLayout_15);

        labelPicShow = new QLabel(centralwidget);
        labelPicShow->setObjectName(QString::fromUtf8("labelPicShow"));
        labelPicShow->setEnabled(true);
        labelPicShow->setGeometry(QRect(0, 0, 0, 0));
        labelPicShow->setMinimumSize(QSize(0, 0));
        labelPicShow->setMaximumSize(QSize(30000, 30000));
        labelPicShow->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        CameraViewClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CameraViewClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        CameraViewClass->setMenuBar(menubar);
        statusbar = new QStatusBar(CameraViewClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CameraViewClass->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actionTest);
        menu->addAction(actionCircle);
        menu_2->addAction(actionAbout);

        retranslateUi(CameraViewClass);

        QMetaObject::connectSlotsByName(CameraViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *CameraViewClass)
    {
        CameraViewClass->setWindowTitle(QApplication::translate("CameraViewClass", "CameraView", 0, QApplication::UnicodeUTF8));
        actionTest->setText(QApplication::translate("CameraViewClass", "\344\270\255\345\277\203\347\202\271\346\261\202\345\217\226", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("CameraViewClass", "About", 0, QApplication::UnicodeUTF8));
        actionCircle->setText(QApplication::translate("CameraViewClass", "\345\233\236\350\275\254\345\215\212\345\276\204\346\261\202\345\217\226", 0, QApplication::UnicodeUTF8));
        pushButtonStart->setText(QApplication::translate("CameraViewClass", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("CameraViewClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        labelImgNumber->setText(QApplication::translate("CameraViewClass", "\351\207\207\351\233\206\345\274\240\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButtonSave->setText(QApplication::translate("CameraViewClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        checkBoxProcess->setText(QApplication::translate("CameraViewClass", "\345\234\206\345\277\203\346\261\202\345\217\226", 0, QApplication::UnicodeUTF8));
        labelWidth->setText(QApplication::translate("CameraViewClass", "\345\256\275\357\274\210Width\357\274\211", 0, QApplication::UnicodeUTF8));
        labelHeight->setText(QApplication::translate("CameraViewClass", "\351\253\230\357\274\210Height\357\274\211", 0, QApplication::UnicodeUTF8));
        labelFramePerSecond->setText(QApplication::translate("CameraViewClass", "\345\270\247\347\216\207\357\274\210Frame\357\274\211", 0, QApplication::UnicodeUTF8));
        labelExposureTime->setText(QApplication::translate("CameraViewClass", "\346\233\235\345\205\211\346\227\266\351\227\264\357\274\210Time\357\274\211", 0, QApplication::UnicodeUTF8));
        labelFrame->setText(QApplication::translate("CameraViewClass", "\346\200\273\345\270\247\346\225\260\357\274\210Frames\357\274\211", 0, QApplication::UnicodeUTF8));
        labelX->setText(QApplication::translate("CameraViewClass", "\345\234\206\345\277\203\345\235\220\346\240\207X", 0, QApplication::UnicodeUTF8));
        labelY->setText(QApplication::translate("CameraViewClass", "\345\234\206\345\277\203\345\235\220\346\240\207Y", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CameraViewClass", "\345\215\212\345\276\204R1", 0, QApplication::UnicodeUTF8));
        lineEditRadius1->setText(QString());
        labelRadius->setText(QApplication::translate("CameraViewClass", "\345\215\212\345\276\204R2", 0, QApplication::UnicodeUTF8));
        labelRadiusError->setText(QApplication::translate("CameraViewClass", "\345\233\236\350\275\254\350\257\257\345\267\256T", 0, QApplication::UnicodeUTF8));
        labelInfo->setText(QApplication::translate("CameraViewClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#0000ff;\">\344\277\241\346\201\257</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelError->setText(QApplication::translate("CameraViewClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#ff0000;\">\351\224\231\350\257\257</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelPicShow->setText(QString());
        menu->setTitle(QApplication::translate("CameraViewClass", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("CameraViewClass", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraViewClass: public Ui_CameraViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAVIEW_H
