/********************************************************************************
** Form generated from reading UI file 'raaGraphToolInterfaceQt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RAAGRAPHTOOLINTERFACEQT_H
#define RAAGRAPHTOOLINTERFACEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_raaGraphToolInterfaceQt
{
public:
    QAction *actionLoad_Pajek;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTreeWidget *tree_widget;
    QGraphicsView *graph_view;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *zoom_in_button;
    QPushButton *zoom_out_button;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *create_button;
    QLineEdit *create_num_lineedit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *raaGraphToolInterfaceQt)
    {
        if (raaGraphToolInterfaceQt->objectName().isEmpty())
            raaGraphToolInterfaceQt->setObjectName(QStringLiteral("raaGraphToolInterfaceQt"));
        raaGraphToolInterfaceQt->resize(732, 600);
        actionLoad_Pajek = new QAction(raaGraphToolInterfaceQt);
        actionLoad_Pajek->setObjectName(QStringLiteral("actionLoad_Pajek"));
        centralwidget = new QWidget(raaGraphToolInterfaceQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        tree_widget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tree_widget->setHeaderItem(__qtreewidgetitem);
        tree_widget->setObjectName(QStringLiteral("tree_widget"));
        splitter->addWidget(tree_widget);
        graph_view = new QGraphicsView(splitter);
        graph_view->setObjectName(QStringLiteral("graph_view"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graph_view->sizePolicy().hasHeightForWidth());
        graph_view->setSizePolicy(sizePolicy1);
        splitter->addWidget(graph_view);

        verticalLayout->addWidget(splitter);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        zoom_in_button = new QPushButton(frame);
        zoom_in_button->setObjectName(QStringLiteral("zoom_in_button"));
        zoom_in_button->setAutoRepeat(true);
        zoom_in_button->setAutoRepeatDelay(200);

        horizontalLayout_2->addWidget(zoom_in_button);

        zoom_out_button = new QPushButton(frame);
        zoom_out_button->setObjectName(QStringLiteral("zoom_out_button"));
        zoom_out_button->setAutoRepeat(true);
        zoom_out_button->setAutoRepeatDelay(200);

        horizontalLayout_2->addWidget(zoom_out_button);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        create_button = new QPushButton(frame_2);
        create_button->setObjectName(QStringLiteral("create_button"));

        horizontalLayout->addWidget(create_button);

        create_num_lineedit = new QLineEdit(frame_2);
        create_num_lineedit->setObjectName(QStringLiteral("create_num_lineedit"));

        horizontalLayout->addWidget(create_num_lineedit);


        verticalLayout->addWidget(frame_2);

        raaGraphToolInterfaceQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(raaGraphToolInterfaceQt);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 732, 18));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        raaGraphToolInterfaceQt->setMenuBar(menubar);
        statusbar = new QStatusBar(raaGraphToolInterfaceQt);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        raaGraphToolInterfaceQt->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_Pajek);

        retranslateUi(raaGraphToolInterfaceQt);

        QMetaObject::connectSlotsByName(raaGraphToolInterfaceQt);
    } // setupUi

    void retranslateUi(QMainWindow *raaGraphToolInterfaceQt)
    {
        raaGraphToolInterfaceQt->setWindowTitle(QApplication::translate("raaGraphToolInterfaceQt", "MainWindow", 0));
        actionLoad_Pajek->setText(QApplication::translate("raaGraphToolInterfaceQt", "Load Pajek", 0));
        zoom_in_button->setText(QApplication::translate("raaGraphToolInterfaceQt", "Zoom Out", 0));
        zoom_out_button->setText(QApplication::translate("raaGraphToolInterfaceQt", "Zoom In", 0));
        create_button->setText(QApplication::translate("raaGraphToolInterfaceQt", "Create", 0));
        create_num_lineedit->setText(QApplication::translate("raaGraphToolInterfaceQt", "500", 0));
        menuFile->setTitle(QApplication::translate("raaGraphToolInterfaceQt", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class raaGraphToolInterfaceQt: public Ui_raaGraphToolInterfaceQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RAAGRAPHTOOLINTERFACEQT_H
