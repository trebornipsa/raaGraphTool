/********************************************************************************
** Form generated from reading UI file 'raaGraphInterfaceQt.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RAAGRAPHINTERFACEQT_H
#define RAAGRAPHINTERFACEQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <raaQTOSGWidget/raaQTOSGWidget.h>

QT_BEGIN_NAMESPACE

class Ui_raaGraphInterfaceQt
{
public:
    QAction *actionLoad_Pajek;
    QAction *actionLoad_Mo_ARM;
    QAction *actionLoad_Raa_ARM;
    QAction *actionLoad_Decision_Tree;
    QAction *actionLoad_Test;
    QAction *actionLoad_Decision_Trees;
    QAction *actionSave_Graph;
    QAction *actionLoad_Graph;
    QAction *actionLoad_MultiYear_Decision_Trees;
    QAction *actionLoad_Ali_Malware;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_11;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QToolBox *toolbox;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QCheckBox *de_solve_check;
    QLabel *label_3;
    QDoubleSpinBox *de_solve_interval_spin;
    QPushButton *de_solve_button;
    QLabel *de_solve_energy_label;
    QLabel *label_4;
    QDoubleSpinBox *de_solve_damping_spin;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *de_arc_cen_sqt_check;
    QCheckBox *de_arc_node_sqr_check;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QCheckBox *de_cluster_check;
    QLabel *label;
    QDoubleSpinBox *de_cluster_eps_spin;
    QLabel *label_2;
    QSpinBox *de_cluster_min_spin;
    QGroupBox *groupBox_9;
    QFormLayout *formLayout_3;
    QCheckBox *de_show_inactive_check;
    QSlider *de_node_size_slider;
    QLabel *label_5;
    QSlider *de_text_size_slider;
    QSlider *de_arc_transp_slider;
    QLabel *label_7;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QPushButton *de_reset_view_button;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QTreeView *layer_tree_view;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_17;
    QFrame *lm_frame;
    QVBoxLayout *verticalLayout_16;
    QScrollArea *layout_buttons;
    QWidget *layout_buttons_frame;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_18;
    QTextEdit *layout_text_edit;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *lo_normalise_arcs_check;
    QCheckBox *lo_layout_ring_check;
    QCheckBox *lo_discard_undef_check;
    QCheckBox *lo_round_float_check;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *lo_ideal_arc_length_spin;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_4;
    QDoubleSpinBox *lo_max_rand_pos_spin;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *lo_position_results_check;
    QCheckBox *de_combine_result_strengths_check;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *de_discard_check;
    QDoubleSpinBox *de_discard_spin;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_14;
    QRadioButton *lo_aw_as_sw_radio;
    QRadioButton *lo_aw_as_sl_radio;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_22;
    QCheckBox *mouse_over_check;
    QCheckBox *mouse_screen_text_check;
    QTextEdit *mouse_text;
    QFrame *gl_frame;
    QVBoxLayout *verticalLayout_10;
    raaQTOSGWidget *gl_window;
    QTabWidget *info_tab;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout;
    QTableView *info_node_table_view;
    QCheckBox *info_track_updates_check;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_6;
    QTableView *info_arc_table_view;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QTableView *info_layer_table_view;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *info_cluster_show_check;
    QSplitter *splitter_3;
    QColumnView *info_cluster_column_view;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_21;
    QTableView *info_cluster_node_view;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_20;
    QLabel *info_cluster_count_label;
    QLabel *info_cluster_pos_label;
    QLabel *info_cluster_size_label;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_9;
    QTableView *info_model_table_view;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *raaGraphInterfaceQt)
    {
        if (raaGraphInterfaceQt->objectName().isEmpty())
            raaGraphInterfaceQt->setObjectName(QStringLiteral("raaGraphInterfaceQt"));
        raaGraphInterfaceQt->resize(1418, 1180);
        actionLoad_Pajek = new QAction(raaGraphInterfaceQt);
        actionLoad_Pajek->setObjectName(QStringLiteral("actionLoad_Pajek"));
        actionLoad_Mo_ARM = new QAction(raaGraphInterfaceQt);
        actionLoad_Mo_ARM->setObjectName(QStringLiteral("actionLoad_Mo_ARM"));
        actionLoad_Raa_ARM = new QAction(raaGraphInterfaceQt);
        actionLoad_Raa_ARM->setObjectName(QStringLiteral("actionLoad_Raa_ARM"));
        actionLoad_Decision_Tree = new QAction(raaGraphInterfaceQt);
        actionLoad_Decision_Tree->setObjectName(QStringLiteral("actionLoad_Decision_Tree"));
        actionLoad_Test = new QAction(raaGraphInterfaceQt);
        actionLoad_Test->setObjectName(QStringLiteral("actionLoad_Test"));
        actionLoad_Decision_Trees = new QAction(raaGraphInterfaceQt);
        actionLoad_Decision_Trees->setObjectName(QStringLiteral("actionLoad_Decision_Trees"));
        actionSave_Graph = new QAction(raaGraphInterfaceQt);
        actionSave_Graph->setObjectName(QStringLiteral("actionSave_Graph"));
        actionLoad_Graph = new QAction(raaGraphInterfaceQt);
        actionLoad_Graph->setObjectName(QStringLiteral("actionLoad_Graph"));
        actionLoad_MultiYear_Decision_Trees = new QAction(raaGraphInterfaceQt);
        actionLoad_MultiYear_Decision_Trees->setObjectName(QStringLiteral("actionLoad_MultiYear_Decision_Trees"));
        actionLoad_Ali_Malware = new QAction(raaGraphInterfaceQt);
        actionLoad_Ali_Malware->setObjectName(QStringLiteral("actionLoad_Ali_Malware"));
        centralwidget = new QWidget(raaGraphInterfaceQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_11 = new QVBoxLayout(centralwidget);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        toolbox = new QToolBox(splitter);
        toolbox->setObjectName(QStringLiteral("toolbox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolbox->sizePolicy().hasHeightForWidth());
        toolbox->setSizePolicy(sizePolicy1);
        toolbox->setMinimumSize(QSize(360, 0));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 360, 874));
        sizePolicy1.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        de_solve_check = new QCheckBox(groupBox_2);
        de_solve_check->setObjectName(QStringLiteral("de_solve_check"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, de_solve_check);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        de_solve_interval_spin = new QDoubleSpinBox(groupBox_2);
        de_solve_interval_spin->setObjectName(QStringLiteral("de_solve_interval_spin"));
        de_solve_interval_spin->setDecimals(4);
        de_solve_interval_spin->setMinimum(0.001);
        de_solve_interval_spin->setMaximum(0.3);
        de_solve_interval_spin->setSingleStep(0.001);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, de_solve_interval_spin);

        de_solve_button = new QPushButton(groupBox_2);
        de_solve_button->setObjectName(QStringLiteral("de_solve_button"));

        formLayout_2->setWidget(5, QFormLayout::SpanningRole, de_solve_button);

        de_solve_energy_label = new QLabel(groupBox_2);
        de_solve_energy_label->setObjectName(QStringLiteral("de_solve_energy_label"));

        formLayout_2->setWidget(6, QFormLayout::SpanningRole, de_solve_energy_label);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        de_solve_damping_spin = new QDoubleSpinBox(groupBox_2);
        de_solve_damping_spin->setObjectName(QStringLiteral("de_solve_damping_spin"));
        de_solve_damping_spin->setDecimals(3);
        de_solve_damping_spin->setMaximum(100);
        de_solve_damping_spin->setSingleStep(0.001);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, de_solve_damping_spin);

        groupBox_8 = new QGroupBox(groupBox_2);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_15 = new QVBoxLayout(groupBox_8);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        de_arc_cen_sqt_check = new QCheckBox(groupBox_8);
        de_arc_cen_sqt_check->setObjectName(QStringLiteral("de_arc_cen_sqt_check"));

        verticalLayout_15->addWidget(de_arc_cen_sqt_check);

        de_arc_node_sqr_check = new QCheckBox(groupBox_8);
        de_arc_node_sqr_check->setObjectName(QStringLiteral("de_arc_node_sqr_check"));

        verticalLayout_15->addWidget(de_arc_node_sqr_check);


        formLayout_2->setWidget(7, QFormLayout::SpanningRole, groupBox_8);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        de_cluster_check = new QCheckBox(groupBox);
        de_cluster_check->setObjectName(QStringLiteral("de_cluster_check"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, de_cluster_check);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        de_cluster_eps_spin = new QDoubleSpinBox(groupBox);
        de_cluster_eps_spin->setObjectName(QStringLiteral("de_cluster_eps_spin"));
        de_cluster_eps_spin->setMaximum(10000);
        de_cluster_eps_spin->setSingleStep(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, de_cluster_eps_spin);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        de_cluster_min_spin = new QSpinBox(groupBox);
        de_cluster_min_spin->setObjectName(QStringLiteral("de_cluster_min_spin"));
        de_cluster_min_spin->setMinimum(3);

        formLayout->setWidget(2, QFormLayout::FieldRole, de_cluster_min_spin);


        verticalLayout_2->addWidget(groupBox);

        groupBox_9 = new QGroupBox(page);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        formLayout_3 = new QFormLayout(groupBox_9);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        de_show_inactive_check = new QCheckBox(groupBox_9);
        de_show_inactive_check->setObjectName(QStringLiteral("de_show_inactive_check"));

        formLayout_3->setWidget(0, QFormLayout::SpanningRole, de_show_inactive_check);

        de_node_size_slider = new QSlider(groupBox_9);
        de_node_size_slider->setObjectName(QStringLiteral("de_node_size_slider"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(de_node_size_slider->sizePolicy().hasHeightForWidth());
        de_node_size_slider->setSizePolicy(sizePolicy3);
        de_node_size_slider->setMinimum(1);
        de_node_size_slider->setMaximum(1000);
        de_node_size_slider->setSliderPosition(500);
        de_node_size_slider->setOrientation(Qt::Horizontal);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, de_node_size_slider);

        label_5 = new QLabel(groupBox_9);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, label_5);

        de_text_size_slider = new QSlider(groupBox_9);
        de_text_size_slider->setObjectName(QStringLiteral("de_text_size_slider"));
        sizePolicy3.setHeightForWidth(de_text_size_slider->sizePolicy().hasHeightForWidth());
        de_text_size_slider->setSizePolicy(sizePolicy3);
        de_text_size_slider->setMinimum(1);
        de_text_size_slider->setMaximum(1000);
        de_text_size_slider->setSliderPosition(500);
        de_text_size_slider->setOrientation(Qt::Horizontal);

        formLayout_3->setWidget(3, QFormLayout::LabelRole, de_text_size_slider);

        de_arc_transp_slider = new QSlider(groupBox_9);
        de_arc_transp_slider->setObjectName(QStringLiteral("de_arc_transp_slider"));
        sizePolicy3.setHeightForWidth(de_arc_transp_slider->sizePolicy().hasHeightForWidth());
        de_arc_transp_slider->setSizePolicy(sizePolicy3);
        de_arc_transp_slider->setMinimum(1);
        de_arc_transp_slider->setMaximum(1000);
        de_arc_transp_slider->setSliderPosition(500);
        de_arc_transp_slider->setOrientation(Qt::Horizontal);

        formLayout_3->setWidget(4, QFormLayout::LabelRole, de_arc_transp_slider);

        label_7 = new QLabel(groupBox_9);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, label_7);

        label_6 = new QLabel(groupBox_9);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, label_6);


        verticalLayout_2->addWidget(groupBox_9);

        verticalSpacer = new QSpacerItem(20, 573, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        de_reset_view_button = new QPushButton(page);
        de_reset_view_button->setObjectName(QStringLiteral("de_reset_view_button"));

        verticalLayout_2->addWidget(de_reset_view_button);

        toolbox->addItem(page, QStringLiteral("Data Engine"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 360, 874));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        layer_tree_view = new QTreeView(page_2);
        layer_tree_view->setObjectName(QStringLiteral("layer_tree_view"));
        layer_tree_view->setIndentation(10);
        layer_tree_view->setHeaderHidden(true);

        verticalLayout_3->addWidget(layer_tree_view);

        toolbox->addItem(page_2, QStringLiteral("Layers"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 360, 874));
        verticalLayout_17 = new QVBoxLayout(page_4);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        lm_frame = new QFrame(page_4);
        lm_frame->setObjectName(QStringLiteral("lm_frame"));
        lm_frame->setFrameShape(QFrame::StyledPanel);
        lm_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_16 = new QVBoxLayout(lm_frame);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        layout_buttons = new QScrollArea(lm_frame);
        layout_buttons->setObjectName(QStringLiteral("layout_buttons"));
        layout_buttons->setWidgetResizable(true);
        layout_buttons_frame = new QWidget();
        layout_buttons_frame->setObjectName(QStringLiteral("layout_buttons_frame"));
        layout_buttons_frame->setGeometry(QRect(0, 0, 296, 399));
        verticalLayout_19 = new QVBoxLayout(layout_buttons_frame);
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(2);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));

        verticalLayout_19->addLayout(verticalLayout_18);

        layout_buttons->setWidget(layout_buttons_frame);

        verticalLayout_16->addWidget(layout_buttons);

        layout_text_edit = new QTextEdit(lm_frame);
        layout_text_edit->setObjectName(QStringLiteral("layout_text_edit"));

        verticalLayout_16->addWidget(layout_text_edit);


        verticalLayout_17->addWidget(lm_frame);

        toolbox->addItem(page_4, QStringLiteral("Layouts"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 370, 844));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        lo_normalise_arcs_check = new QCheckBox(page_3);
        lo_normalise_arcs_check->setObjectName(QStringLiteral("lo_normalise_arcs_check"));
        lo_normalise_arcs_check->setChecked(true);

        verticalLayout_5->addWidget(lo_normalise_arcs_check);

        lo_layout_ring_check = new QCheckBox(page_3);
        lo_layout_ring_check->setObjectName(QStringLiteral("lo_layout_ring_check"));
        lo_layout_ring_check->setChecked(false);

        verticalLayout_5->addWidget(lo_layout_ring_check);

        lo_discard_undef_check = new QCheckBox(page_3);
        lo_discard_undef_check->setObjectName(QStringLiteral("lo_discard_undef_check"));
        lo_discard_undef_check->setChecked(true);

        verticalLayout_5->addWidget(lo_discard_undef_check);

        lo_round_float_check = new QCheckBox(page_3);
        lo_round_float_check->setObjectName(QStringLiteral("lo_round_float_check"));
        lo_round_float_check->setChecked(true);

        verticalLayout_5->addWidget(lo_round_float_check);

        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lo_ideal_arc_length_spin = new QDoubleSpinBox(groupBox_3);
        lo_ideal_arc_length_spin->setObjectName(QStringLiteral("lo_ideal_arc_length_spin"));
        lo_ideal_arc_length_spin->setMinimum(1);
        lo_ideal_arc_length_spin->setSingleStep(0.1);
        lo_ideal_arc_length_spin->setValue(10);

        horizontalLayout->addWidget(lo_ideal_arc_length_spin);


        verticalLayout_5->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(page_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_4 = new QVBoxLayout(groupBox_5);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lo_max_rand_pos_spin = new QDoubleSpinBox(groupBox_5);
        lo_max_rand_pos_spin->setObjectName(QStringLiteral("lo_max_rand_pos_spin"));
        lo_max_rand_pos_spin->setMinimum(10);
        lo_max_rand_pos_spin->setMaximum(2000);
        lo_max_rand_pos_spin->setValue(20);

        verticalLayout_4->addWidget(lo_max_rand_pos_spin);


        verticalLayout_5->addWidget(groupBox_5);

        groupBox_4 = new QGroupBox(page_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_12 = new QVBoxLayout(groupBox_4);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        lo_position_results_check = new QCheckBox(groupBox_4);
        lo_position_results_check->setObjectName(QStringLiteral("lo_position_results_check"));
        lo_position_results_check->setChecked(true);

        verticalLayout_12->addWidget(lo_position_results_check);

        de_combine_result_strengths_check = new QCheckBox(groupBox_4);
        de_combine_result_strengths_check->setObjectName(QStringLiteral("de_combine_result_strengths_check"));

        verticalLayout_12->addWidget(de_combine_result_strengths_check);

        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_13 = new QVBoxLayout(groupBox_6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        de_discard_check = new QCheckBox(groupBox_6);
        de_discard_check->setObjectName(QStringLiteral("de_discard_check"));

        verticalLayout_13->addWidget(de_discard_check);

        de_discard_spin = new QDoubleSpinBox(groupBox_6);
        de_discard_spin->setObjectName(QStringLiteral("de_discard_spin"));
        de_discard_spin->setEnabled(false);
        de_discard_spin->setMaximum(10000);
        de_discard_spin->setValue(100);

        verticalLayout_13->addWidget(de_discard_spin);

        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_14 = new QVBoxLayout(groupBox_7);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        lo_aw_as_sw_radio = new QRadioButton(groupBox_7);
        lo_aw_as_sw_radio->setObjectName(QStringLiteral("lo_aw_as_sw_radio"));
        lo_aw_as_sw_radio->setChecked(true);

        verticalLayout_14->addWidget(lo_aw_as_sw_radio);

        lo_aw_as_sl_radio = new QRadioButton(groupBox_7);
        lo_aw_as_sl_radio->setObjectName(QStringLiteral("lo_aw_as_sl_radio"));

        verticalLayout_14->addWidget(lo_aw_as_sl_radio);


        verticalLayout_13->addWidget(groupBox_7);


        verticalLayout_12->addWidget(groupBox_6);


        verticalLayout_5->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 322, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        toolbox->addItem(page_3, QStringLiteral("Load Options"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setGeometry(QRect(0, 0, 360, 874));
        verticalLayout_22 = new QVBoxLayout(page_5);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        mouse_over_check = new QCheckBox(page_5);
        mouse_over_check->setObjectName(QStringLiteral("mouse_over_check"));

        verticalLayout_22->addWidget(mouse_over_check);

        mouse_screen_text_check = new QCheckBox(page_5);
        mouse_screen_text_check->setObjectName(QStringLiteral("mouse_screen_text_check"));

        verticalLayout_22->addWidget(mouse_screen_text_check);

        mouse_text = new QTextEdit(page_5);
        mouse_text->setObjectName(QStringLiteral("mouse_text"));

        verticalLayout_22->addWidget(mouse_text);

        toolbox->addItem(page_5, QStringLiteral("Mouse"));
        splitter->addWidget(toolbox);
        gl_frame = new QFrame(splitter);
        gl_frame->setObjectName(QStringLiteral("gl_frame"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(4);
        sizePolicy4.setVerticalStretch(3);
        sizePolicy4.setHeightForWidth(gl_frame->sizePolicy().hasHeightForWidth());
        gl_frame->setSizePolicy(sizePolicy4);
        gl_frame->setMinimumSize(QSize(100, 100));
        verticalLayout_10 = new QVBoxLayout(gl_frame);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        gl_window = new raaQTOSGWidget(gl_frame);
        gl_window->setObjectName(QStringLiteral("gl_window"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(3);
        sizePolicy5.setHeightForWidth(gl_window->sizePolicy().hasHeightForWidth());
        gl_window->setSizePolicy(sizePolicy5);

        verticalLayout_10->addWidget(gl_window);

        splitter->addWidget(gl_frame);
        splitter_2->addWidget(splitter);
        info_tab = new QTabWidget(splitter_2);
        info_tab->setObjectName(QStringLiteral("info_tab"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(2);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(info_tab->sizePolicy().hasHeightForWidth());
        info_tab->setSizePolicy(sizePolicy6);
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout = new QVBoxLayout(tab_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        info_node_table_view = new QTableView(tab_4);
        info_node_table_view->setObjectName(QStringLiteral("info_node_table_view"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(1);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(info_node_table_view->sizePolicy().hasHeightForWidth());
        info_node_table_view->setSizePolicy(sizePolicy7);

        verticalLayout->addWidget(info_node_table_view);

        info_track_updates_check = new QCheckBox(tab_4);
        info_track_updates_check->setObjectName(QStringLiteral("info_track_updates_check"));

        verticalLayout->addWidget(info_track_updates_check);

        info_tab->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_6 = new QVBoxLayout(tab_5);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        info_arc_table_view = new QTableView(tab_5);
        info_arc_table_view->setObjectName(QStringLiteral("info_arc_table_view"));

        verticalLayout_6->addWidget(info_arc_table_view);

        info_tab->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        info_layer_table_view = new QTableView(tab);
        info_layer_table_view->setObjectName(QStringLiteral("info_layer_table_view"));

        verticalLayout_7->addWidget(info_layer_table_view);

        info_tab->addTab(tab, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        verticalLayout_8 = new QVBoxLayout(tab_7);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        info_cluster_show_check = new QCheckBox(tab_7);
        info_cluster_show_check->setObjectName(QStringLiteral("info_cluster_show_check"));

        verticalLayout_8->addWidget(info_cluster_show_check);

        splitter_3 = new QSplitter(tab_7);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        info_cluster_column_view = new QColumnView(splitter_3);
        info_cluster_column_view->setObjectName(QStringLiteral("info_cluster_column_view"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(1);
        sizePolicy8.setHeightForWidth(info_cluster_column_view->sizePolicy().hasHeightForWidth());
        info_cluster_column_view->setSizePolicy(sizePolicy8);
        info_cluster_column_view->setEditTriggers(QAbstractItemView::SelectedClicked);
        info_cluster_column_view->setSelectionMode(QAbstractItemView::SingleSelection);
        splitter_3->addWidget(info_cluster_column_view);
        tabWidget = new QTabWidget(splitter_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(3);
        sizePolicy9.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy9);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_21 = new QVBoxLayout(tab_2);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        info_cluster_node_view = new QTableView(tab_2);
        info_cluster_node_view->setObjectName(QStringLiteral("info_cluster_node_view"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(info_cluster_node_view->sizePolicy().hasHeightForWidth());
        info_cluster_node_view->setSizePolicy(sizePolicy10);

        verticalLayout_21->addWidget(info_cluster_node_view);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_20 = new QVBoxLayout(tab_3);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        info_cluster_count_label = new QLabel(tab_3);
        info_cluster_count_label->setObjectName(QStringLiteral("info_cluster_count_label"));

        verticalLayout_20->addWidget(info_cluster_count_label);

        info_cluster_pos_label = new QLabel(tab_3);
        info_cluster_pos_label->setObjectName(QStringLiteral("info_cluster_pos_label"));

        verticalLayout_20->addWidget(info_cluster_pos_label);

        info_cluster_size_label = new QLabel(tab_3);
        info_cluster_size_label->setObjectName(QStringLiteral("info_cluster_size_label"));

        verticalLayout_20->addWidget(info_cluster_size_label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_3, QString());
        splitter_3->addWidget(tabWidget);

        verticalLayout_8->addWidget(splitter_3);

        info_tab->addTab(tab_7, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_9 = new QVBoxLayout(tab_6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        info_model_table_view = new QTableView(tab_6);
        info_model_table_view->setObjectName(QStringLiteral("info_model_table_view"));

        verticalLayout_9->addWidget(info_model_table_view);

        info_tab->addTab(tab_6, QString());
        splitter_2->addWidget(info_tab);

        verticalLayout_11->addWidget(splitter_2);

        raaGraphInterfaceQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(raaGraphInterfaceQt);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1418, 36));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        raaGraphInterfaceQt->setMenuBar(menubar);
        statusbar = new QStatusBar(raaGraphInterfaceQt);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        raaGraphInterfaceQt->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_Pajek);
        menuFile->addAction(actionLoad_Mo_ARM);
        menuFile->addAction(actionLoad_Raa_ARM);
        menuFile->addAction(actionLoad_Decision_Tree);
        menuFile->addAction(actionLoad_Test);
        menuFile->addAction(actionLoad_Decision_Trees);
        menuFile->addAction(actionLoad_MultiYear_Decision_Trees);
        menuFile->addAction(actionLoad_Ali_Malware);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Graph);
        menuFile->addAction(actionLoad_Graph);

        retranslateUi(raaGraphInterfaceQt);

        toolbox->setCurrentIndex(0);
        info_tab->setCurrentIndex(3);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(raaGraphInterfaceQt);
    } // setupUi

    void retranslateUi(QMainWindow *raaGraphInterfaceQt)
    {
        raaGraphInterfaceQt->setWindowTitle(QApplication::translate("raaGraphInterfaceQt", "raaGraph", 0));
        actionLoad_Pajek->setText(QApplication::translate("raaGraphInterfaceQt", "Load Pajek", 0));
        actionLoad_Mo_ARM->setText(QApplication::translate("raaGraphInterfaceQt", "Load Mo ARM", 0));
        actionLoad_Raa_ARM->setText(QApplication::translate("raaGraphInterfaceQt", "Load Raa ARM", 0));
        actionLoad_Decision_Tree->setText(QApplication::translate("raaGraphInterfaceQt", "Load Decision Tree", 0));
        actionLoad_Test->setText(QApplication::translate("raaGraphInterfaceQt", "Load Test", 0));
        actionLoad_Decision_Trees->setText(QApplication::translate("raaGraphInterfaceQt", "Load Decision Trees", 0));
        actionSave_Graph->setText(QApplication::translate("raaGraphInterfaceQt", "Save Graph", 0));
        actionLoad_Graph->setText(QApplication::translate("raaGraphInterfaceQt", "Load Graph", 0));
        actionLoad_MultiYear_Decision_Trees->setText(QApplication::translate("raaGraphInterfaceQt", "Load MultiYear Decision Trees", 0));
        actionLoad_Ali_Malware->setText(QApplication::translate("raaGraphInterfaceQt", "Load Ali-Malware", 0));
        groupBox_2->setTitle(QApplication::translate("raaGraphInterfaceQt", "Solve", 0));
        de_solve_check->setText(QApplication::translate("raaGraphInterfaceQt", "Solve", 0));
        label_3->setText(QApplication::translate("raaGraphInterfaceQt", "Interval (s)", 0));
        de_solve_button->setText(QApplication::translate("raaGraphInterfaceQt", "Solve Once", 0));
        de_solve_energy_label->setText(QString());
        label_4->setText(QApplication::translate("raaGraphInterfaceQt", "Damping %", 0));
        groupBox_8->setTitle(QApplication::translate("raaGraphInterfaceQt", "GroupBox", 0));
        de_arc_cen_sqt_check->setText(QApplication::translate("raaGraphInterfaceQt", "Arcs Centre SQR Force", 0));
        de_arc_node_sqr_check->setText(QApplication::translate("raaGraphInterfaceQt", "Node SQR Force", 0));
        groupBox->setTitle(QApplication::translate("raaGraphInterfaceQt", "Cluster", 0));
        de_cluster_check->setText(QApplication::translate("raaGraphInterfaceQt", "Cluster", 0));
        label->setText(QApplication::translate("raaGraphInterfaceQt", "EPS", 0));
        label_2->setText(QApplication::translate("raaGraphInterfaceQt", "Min", 0));
        groupBox_9->setTitle(QApplication::translate("raaGraphInterfaceQt", "Display", 0));
        de_show_inactive_check->setText(QApplication::translate("raaGraphInterfaceQt", "Show Inactive Nodes/Arcs", 0));
        label_5->setText(QApplication::translate("raaGraphInterfaceQt", "Node Size", 0));
        label_7->setText(QApplication::translate("raaGraphInterfaceQt", "Arc Transp", 0));
        label_6->setText(QApplication::translate("raaGraphInterfaceQt", "Text Size", 0));
        de_reset_view_button->setText(QApplication::translate("raaGraphInterfaceQt", "Reset View", 0));
        toolbox->setItemText(toolbox->indexOf(page), QApplication::translate("raaGraphInterfaceQt", "Data Engine", 0));
        toolbox->setItemText(toolbox->indexOf(page_2), QApplication::translate("raaGraphInterfaceQt", "Layers", 0));
        toolbox->setItemText(toolbox->indexOf(page_4), QApplication::translate("raaGraphInterfaceQt", "Layouts", 0));
        lo_normalise_arcs_check->setText(QApplication::translate("raaGraphInterfaceQt", "Normalise Arcs", 0));
        lo_layout_ring_check->setText(QApplication::translate("raaGraphInterfaceQt", "Layout Ring", 0));
        lo_discard_undef_check->setText(QApplication::translate("raaGraphInterfaceQt", "Discard Undef results", 0));
        lo_round_float_check->setText(QApplication::translate("raaGraphInterfaceQt", "Round floating point values", 0));
        groupBox_3->setTitle(QApplication::translate("raaGraphInterfaceQt", "Ideal Arc Length", 0));
        groupBox_5->setTitle(QApplication::translate("raaGraphInterfaceQt", "Max Rand Pos", 0));
        groupBox_4->setTitle(QApplication::translate("raaGraphInterfaceQt", "Descision Tree Options", 0));
        lo_position_results_check->setText(QApplication::translate("raaGraphInterfaceQt", "Position Result Nodes", 0));
        de_combine_result_strengths_check->setText(QApplication::translate("raaGraphInterfaceQt", "Combine +/- results", 0));
        groupBox_6->setTitle(QApplication::translate("raaGraphInterfaceQt", "Filter Arcs", 0));
        de_discard_check->setText(QApplication::translate("raaGraphInterfaceQt", "Discard Arcs below threshold", 0));
        groupBox_7->setTitle(QApplication::translate("raaGraphInterfaceQt", "Arc Weights", 0));
        lo_aw_as_sw_radio->setText(QApplication::translate("raaGraphInterfaceQt", "As Spring Weight", 0));
        lo_aw_as_sl_radio->setText(QApplication::translate("raaGraphInterfaceQt", "As Spring Length", 0));
        toolbox->setItemText(toolbox->indexOf(page_3), QApplication::translate("raaGraphInterfaceQt", "Load Options", 0));
        mouse_over_check->setText(QApplication::translate("raaGraphInterfaceQt", "Mouse Over Active", 0));
        mouse_screen_text_check->setText(QApplication::translate("raaGraphInterfaceQt", "Screen Text", 0));
        toolbox->setItemText(toolbox->indexOf(page_5), QApplication::translate("raaGraphInterfaceQt", "Mouse", 0));
        info_track_updates_check->setText(QApplication::translate("raaGraphInterfaceQt", "Track updates", 0));
        info_tab->setTabText(info_tab->indexOf(tab_4), QApplication::translate("raaGraphInterfaceQt", "Nodes", 0));
        info_tab->setTabText(info_tab->indexOf(tab_5), QApplication::translate("raaGraphInterfaceQt", "Arcs", 0));
        info_tab->setTabText(info_tab->indexOf(tab), QApplication::translate("raaGraphInterfaceQt", "Layers", 0));
        info_cluster_show_check->setText(QApplication::translate("raaGraphInterfaceQt", "Show", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("raaGraphInterfaceQt", "Nodes", 0));
        info_cluster_count_label->setText(QString());
        info_cluster_pos_label->setText(QString());
        info_cluster_size_label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("raaGraphInterfaceQt", "Cluster Info", 0));
        info_tab->setTabText(info_tab->indexOf(tab_7), QApplication::translate("raaGraphInterfaceQt", "Clusters", 0));
        info_tab->setTabText(info_tab->indexOf(tab_6), QApplication::translate("raaGraphInterfaceQt", "Model", 0));
        menuFile->setTitle(QApplication::translate("raaGraphInterfaceQt", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class raaGraphInterfaceQt: public Ui_raaGraphInterfaceQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RAAGRAPHINTERFACEQT_H
