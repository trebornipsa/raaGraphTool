/********************************************************************************
** Form generated from reading UI file 'raaTestServerInterfaceQt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RAATESTSERVERINTERFACEQT_H
#define RAATESTSERVERINTERFACEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_raaTestServerInterfaceQt
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTextEdit *output_text;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *input_to_combo;
    QLineEdit *input_msg_edit;
    QPushButton *input_send_button;
    QGroupBox *connection_groupbox;
    QHBoxLayout *horizontalLayout;
    QSpinBox *connection_port_spin;
    QCheckBox *connection_check;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QSpinBox *udp_port_spin;
    QPushButton *udp_connect_button;
    QCheckBox *udp_stream_check;
    QLineEdit *udp_name_edit;
    QPlainTextEdit *udp_text;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *raaTestServerInterfaceQt)
    {
        if (raaTestServerInterfaceQt->objectName().isEmpty())
            raaTestServerInterfaceQt->setObjectName(QStringLiteral("raaTestServerInterfaceQt"));
        raaTestServerInterfaceQt->resize(800, 716);
        centralwidget = new QWidget(raaTestServerInterfaceQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        output_text = new QTextEdit(groupBox);
        output_text->setObjectName(QStringLiteral("output_text"));

        verticalLayout->addWidget(output_text);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        input_to_combo = new QComboBox(groupBox_2);
        input_to_combo->setObjectName(QStringLiteral("input_to_combo"));

        horizontalLayout_2->addWidget(input_to_combo);

        input_msg_edit = new QLineEdit(groupBox_2);
        input_msg_edit->setObjectName(QStringLiteral("input_msg_edit"));

        horizontalLayout_2->addWidget(input_msg_edit);

        input_send_button = new QPushButton(groupBox_2);
        input_send_button->setObjectName(QStringLiteral("input_send_button"));

        horizontalLayout_2->addWidget(input_send_button);


        verticalLayout_2->addWidget(groupBox_2);

        connection_groupbox = new QGroupBox(centralwidget);
        connection_groupbox->setObjectName(QStringLiteral("connection_groupbox"));
        horizontalLayout = new QHBoxLayout(connection_groupbox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        connection_port_spin = new QSpinBox(connection_groupbox);
        connection_port_spin->setObjectName(QStringLiteral("connection_port_spin"));
        connection_port_spin->setMaximum(100000);
        connection_port_spin->setValue(17345);

        horizontalLayout->addWidget(connection_port_spin);

        connection_check = new QCheckBox(connection_groupbox);
        connection_check->setObjectName(QStringLiteral("connection_check"));

        horizontalLayout->addWidget(connection_check);


        verticalLayout_2->addWidget(connection_groupbox);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        udp_port_spin = new QSpinBox(groupBox_3);
        udp_port_spin->setObjectName(QStringLiteral("udp_port_spin"));
        udp_port_spin->setMaximum(100000);

        gridLayout->addWidget(udp_port_spin, 0, 1, 1, 1);

        udp_connect_button = new QPushButton(groupBox_3);
        udp_connect_button->setObjectName(QStringLiteral("udp_connect_button"));

        gridLayout->addWidget(udp_connect_button, 0, 2, 1, 1);

        udp_stream_check = new QCheckBox(groupBox_3);
        udp_stream_check->setObjectName(QStringLiteral("udp_stream_check"));

        gridLayout->addWidget(udp_stream_check, 0, 3, 1, 1);

        udp_name_edit = new QLineEdit(groupBox_3);
        udp_name_edit->setObjectName(QStringLiteral("udp_name_edit"));

        gridLayout->addWidget(udp_name_edit, 0, 0, 1, 1);

        udp_text = new QPlainTextEdit(groupBox_3);
        udp_text->setObjectName(QStringLiteral("udp_text"));

        gridLayout->addWidget(udp_text, 1, 0, 1, 4);


        verticalLayout_2->addWidget(groupBox_3);

        raaTestServerInterfaceQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(raaTestServerInterfaceQt);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 36));
        raaTestServerInterfaceQt->setMenuBar(menubar);
        statusbar = new QStatusBar(raaTestServerInterfaceQt);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        raaTestServerInterfaceQt->setStatusBar(statusbar);

        retranslateUi(raaTestServerInterfaceQt);

        QMetaObject::connectSlotsByName(raaTestServerInterfaceQt);
    } // setupUi

    void retranslateUi(QMainWindow *raaTestServerInterfaceQt)
    {
        raaTestServerInterfaceQt->setWindowTitle(QApplication::translate("raaTestServerInterfaceQt", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("raaTestServerInterfaceQt", "Output", 0));
        groupBox_2->setTitle(QApplication::translate("raaTestServerInterfaceQt", "Input", 0));
        input_send_button->setText(QApplication::translate("raaTestServerInterfaceQt", "Send", 0));
        connection_groupbox->setTitle(QApplication::translate("raaTestServerInterfaceQt", "Connection", 0));
        connection_check->setText(QString());
        groupBox_3->setTitle(QApplication::translate("raaTestServerInterfaceQt", "Udp", 0));
        udp_connect_button->setText(QApplication::translate("raaTestServerInterfaceQt", "Connect", 0));
        udp_stream_check->setText(QApplication::translate("raaTestServerInterfaceQt", "Stream", 0));
    } // retranslateUi

};

namespace Ui {
    class raaTestServerInterfaceQt: public Ui_raaTestServerInterfaceQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RAATESTSERVERINTERFACEQT_H
