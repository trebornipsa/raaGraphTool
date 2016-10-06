/********************************************************************************
** Form generated from reading UI file 'raaDE2ClientInterfaceQt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RAADE2CLIENTINTERFACEQT_H
#define RAADE2CLIENTINTERFACEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_raaDE2ClientInterfaceQt
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QToolBox *toolbox;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *connection_ip_combo;
    QSpinBox *connection_port_spin;
    QCheckBox *connection_connect_check;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *connection_verbose_check;
    QPlainTextEdit *connection_text;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *de_model_load_path_edit;
    QPushButton *de_model_load_path_button;
    QLineEdit *de_model_load_name_edit;
    QPushButton *de_model_load_button;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QComboBox *model_models_combo;
    QCheckBox *model_solve_check;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *raaDE2ClientInterfaceQt)
    {
        if (raaDE2ClientInterfaceQt->objectName().isEmpty())
            raaDE2ClientInterfaceQt->setObjectName(QStringLiteral("raaDE2ClientInterfaceQt"));
        raaDE2ClientInterfaceQt->resize(800, 707);
        centralwidget = new QWidget(raaDE2ClientInterfaceQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        toolbox = new QToolBox(centralwidget);
        toolbox->setObjectName(QStringLiteral("toolbox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 774, 543));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        connection_ip_combo = new QComboBox(groupBox);
        connection_ip_combo->setObjectName(QStringLiteral("connection_ip_combo"));

        horizontalLayout->addWidget(connection_ip_combo);

        connection_port_spin = new QSpinBox(groupBox);
        connection_port_spin->setObjectName(QStringLiteral("connection_port_spin"));
        connection_port_spin->setMaximum(100000);
        connection_port_spin->setValue(65204);

        horizontalLayout->addWidget(connection_port_spin);

        connection_connect_check = new QCheckBox(groupBox);
        connection_connect_check->setObjectName(QStringLiteral("connection_connect_check"));

        horizontalLayout->addWidget(connection_connect_check);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        connection_verbose_check = new QCheckBox(groupBox_2);
        connection_verbose_check->setObjectName(QStringLiteral("connection_verbose_check"));

        verticalLayout_2->addWidget(connection_verbose_check);

        connection_text = new QPlainTextEdit(groupBox_2);
        connection_text->setObjectName(QStringLiteral("connection_text"));

        verticalLayout_2->addWidget(connection_text);


        verticalLayout_3->addWidget(groupBox_2);

        toolbox->addItem(page, QStringLiteral("Connection"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 774, 543));
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        de_model_load_path_edit = new QLineEdit(groupBox_4);
        de_model_load_path_edit->setObjectName(QStringLiteral("de_model_load_path_edit"));

        horizontalLayout_2->addWidget(de_model_load_path_edit);

        de_model_load_path_button = new QPushButton(groupBox_4);
        de_model_load_path_button->setObjectName(QStringLiteral("de_model_load_path_button"));

        horizontalLayout_2->addWidget(de_model_load_path_button);

        de_model_load_name_edit = new QLineEdit(groupBox_4);
        de_model_load_name_edit->setObjectName(QStringLiteral("de_model_load_name_edit"));

        horizontalLayout_2->addWidget(de_model_load_name_edit);

        de_model_load_button = new QPushButton(groupBox_4);
        de_model_load_button->setObjectName(QStringLiteral("de_model_load_button"));

        horizontalLayout_2->addWidget(de_model_load_button);


        verticalLayout_5->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 381, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        toolbox->addItem(page_2, QStringLiteral("Data Engine"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 774, 543));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        model_models_combo = new QComboBox(page_3);
        model_models_combo->setObjectName(QStringLiteral("model_models_combo"));

        verticalLayout_4->addWidget(model_models_combo);

        model_solve_check = new QCheckBox(page_3);
        model_solve_check->setObjectName(QStringLiteral("model_solve_check"));

        verticalLayout_4->addWidget(model_solve_check);

        verticalSpacer = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        toolbox->addItem(page_3, QStringLiteral("Model"));

        verticalLayout->addWidget(toolbox);

        raaDE2ClientInterfaceQt->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(raaDE2ClientInterfaceQt);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        raaDE2ClientInterfaceQt->setStatusBar(statusbar);

        retranslateUi(raaDE2ClientInterfaceQt);

        toolbox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(raaDE2ClientInterfaceQt);
    } // setupUi

    void retranslateUi(QMainWindow *raaDE2ClientInterfaceQt)
    {
        raaDE2ClientInterfaceQt->setWindowTitle(QApplication::translate("raaDE2ClientInterfaceQt", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("raaDE2ClientInterfaceQt", "Connection to Server", 0));
        connection_ip_combo->clear();
        connection_ip_combo->insertItems(0, QStringList()
         << QApplication::translate("raaDE2ClientInterfaceQt", "localhost", 0)
        );
        connection_connect_check->setText(QApplication::translate("raaDE2ClientInterfaceQt", "Connect", 0));
        groupBox_2->setTitle(QApplication::translate("raaDE2ClientInterfaceQt", "Monitor", 0));
        connection_verbose_check->setText(QApplication::translate("raaDE2ClientInterfaceQt", "Monitor", 0));
        toolbox->setItemText(toolbox->indexOf(page), QApplication::translate("raaDE2ClientInterfaceQt", "Connection", 0));
        groupBox_4->setTitle(QApplication::translate("raaDE2ClientInterfaceQt", "Load Model", 0));
        de_model_load_path_edit->setText(QApplication::translate("raaDE2ClientInterfaceQt", "C:/robbie/data/DecisionTrees/raaSingleTree.de2", 0));
        de_model_load_path_button->setText(QApplication::translate("raaDE2ClientInterfaceQt", "...", 0));
        de_model_load_name_edit->setText(QApplication::translate("raaDE2ClientInterfaceQt", "Name", 0));
        de_model_load_button->setText(QApplication::translate("raaDE2ClientInterfaceQt", "Load", 0));
        toolbox->setItemText(toolbox->indexOf(page_2), QApplication::translate("raaDE2ClientInterfaceQt", "Data Engine", 0));
        model_models_combo->clear();
        model_models_combo->insertItems(0, QStringList()
         << QApplication::translate("raaDE2ClientInterfaceQt", "Model", 0)
        );
        model_solve_check->setText(QApplication::translate("raaDE2ClientInterfaceQt", "Solve", 0));
        toolbox->setItemText(toolbox->indexOf(page_3), QApplication::translate("raaDE2ClientInterfaceQt", "Model", 0));
    } // retranslateUi

};

namespace Ui {
    class raaDE2ClientInterfaceQt: public Ui_raaDE2ClientInterfaceQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RAADE2CLIENTINTERFACEQT_H
