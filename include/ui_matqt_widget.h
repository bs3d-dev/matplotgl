/********************************************************************************
** Form generated from reading UI file 'matqt_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATQT_WIDGET_H
#define UI_MATQT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <axis_widget.h>
#include <colorbar.h>
#include <glview.h>
#include <legend_box.h>
#include <title_widget.h>

QT_BEGIN_NAMESPACE

class Ui_MatQtWidget
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    TitleWidget *titleWidget;
    YAxisWidget *yAxisWidget;
    QWidget *mainWidget;
    QGridLayout *gridLayout_2;
    GLView *canvas;
    Colorbar *colorbar;
    LegendBox *legendBoxWidget;
    XAxisWidget *xAxisWidget;

    void setupUi(QWidget *MatQtWidget)
    {
        if (MatQtWidget->objectName().isEmpty())
            MatQtWidget->setObjectName("MatQtWidget");
        MatQtWidget->resize(1487, 726);
        gridLayout_3 = new QGridLayout(MatQtWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        widget = new QWidget(MatQtWidget);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        titleWidget = new TitleWidget(widget);
        titleWidget->setObjectName("titleWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWidget->sizePolicy().hasHeightForWidth());
        titleWidget->setSizePolicy(sizePolicy);
        titleWidget->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(titleWidget, 0, 0, 1, 4);

        yAxisWidget = new YAxisWidget(widget);
        yAxisWidget->setObjectName("yAxisWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(yAxisWidget->sizePolicy().hasHeightForWidth());
        yAxisWidget->setSizePolicy(sizePolicy1);
        yAxisWidget->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(yAxisWidget, 1, 0, 1, 1);

        mainWidget = new QWidget(widget);
        mainWidget->setObjectName("mainWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mainWidget->sizePolicy().hasHeightForWidth());
        mainWidget->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(mainWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        canvas = new GLView(mainWidget);
        canvas->setObjectName("canvas");

        gridLayout_2->addWidget(canvas, 0, 0, 1, 2);


        gridLayout->addWidget(mainWidget, 1, 1, 1, 1);

        colorbar = new Colorbar(widget);
        colorbar->setObjectName("colorbar");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(colorbar->sizePolicy().hasHeightForWidth());
        colorbar->setSizePolicy(sizePolicy3);
        colorbar->setMinimumSize(QSize(80, 0));

        gridLayout->addWidget(colorbar, 1, 2, 1, 1);

        legendBoxWidget = new LegendBox(widget);
        legendBoxWidget->setObjectName("legendBoxWidget");
        sizePolicy3.setHeightForWidth(legendBoxWidget->sizePolicy().hasHeightForWidth());
        legendBoxWidget->setSizePolicy(sizePolicy3);
        legendBoxWidget->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(legendBoxWidget, 1, 3, 1, 1);

        xAxisWidget = new XAxisWidget(widget);
        xAxisWidget->setObjectName("xAxisWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(xAxisWidget->sizePolicy().hasHeightForWidth());
        xAxisWidget->setSizePolicy(sizePolicy4);
        xAxisWidget->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(xAxisWidget, 2, 1, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(MatQtWidget);

        QMetaObject::connectSlotsByName(MatQtWidget);
    } // setupUi

    void retranslateUi(QWidget *MatQtWidget)
    {
        MatQtWidget->setWindowTitle(QCoreApplication::translate("MatQtWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatQtWidget: public Ui_MatQtWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATQT_WIDGET_H
