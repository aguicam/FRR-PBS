/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionLoad;
    QAction *actionLoad_Specular;
    QAction *actionLoad_Diffuse;
    QWidget *Widget;
    QHBoxLayout *horizontalLayout;
    GLWidget *glwidget;
    QVBoxLayout *Configuration;
    QGroupBox *TreeOptions;
    QRadioButton *radio_reflection;
    QRadioButton *radio_brdf;
    QDoubleSpinBox *spin_f0r;
    QDoubleSpinBox *spin_f0g;
    QDoubleSpinBox *spin_f0b;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *spin_rough;
    QLabel *label_5;
    QDoubleSpinBox *spin_metallic;
    QSpacerItem *Spacer;
    QGroupBox *RenderOptions;
    QLabel *Label_NumFaces;
    QLabel *Label_Faces;
    QLabel *Label_Vertices;
    QLabel *Label_NumVertices;
    QLabel *Label_Framerate;
    QLabel *Label_NumFramerate;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(828, 638);
        MainWindow->setMinimumSize(QSize(827, 618));
        MainWindow->setBaseSize(QSize(600, 600));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionLoad_Specular = new QAction(MainWindow);
        actionLoad_Specular->setObjectName(QStringLiteral("actionLoad_Specular"));
        actionLoad_Diffuse = new QAction(MainWindow);
        actionLoad_Diffuse->setObjectName(QStringLiteral("actionLoad_Diffuse"));
        Widget = new QWidget(MainWindow);
        Widget->setObjectName(QStringLiteral("Widget"));
        Widget->setMinimumSize(QSize(827, 0));
        Widget->setBaseSize(QSize(600, 600));
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        glwidget = new GLWidget(Widget);
        glwidget->setObjectName(QStringLiteral("glwidget"));
        glwidget->setMinimumSize(QSize(600, 600));
        glwidget->setMaximumSize(QSize(16777215, 16777215));
        glwidget->setBaseSize(QSize(600, 600));

        horizontalLayout->addWidget(glwidget);

        Configuration = new QVBoxLayout();
        Configuration->setSpacing(6);
        Configuration->setObjectName(QStringLiteral("Configuration"));
        TreeOptions = new QGroupBox(Widget);
        TreeOptions->setObjectName(QStringLiteral("TreeOptions"));
        TreeOptions->setMinimumSize(QSize(200, 0));
        TreeOptions->setMaximumSize(QSize(200, 16777215));
        radio_reflection = new QRadioButton(TreeOptions);
        radio_reflection->setObjectName(QStringLiteral("radio_reflection"));
        radio_reflection->setGeometry(QRect(10, 30, 117, 22));
        radio_reflection->setChecked(true);
        radio_brdf = new QRadioButton(TreeOptions);
        radio_brdf->setObjectName(QStringLiteral("radio_brdf"));
        radio_brdf->setGeometry(QRect(10, 60, 117, 22));
        spin_f0r = new QDoubleSpinBox(TreeOptions);
        spin_f0r->setObjectName(QStringLiteral("spin_f0r"));
        spin_f0r->setGeometry(QRect(70, 80, 69, 27));
        spin_f0r->setMaximum(2);
        spin_f0r->setSingleStep(0.05);
        spin_f0r->setValue(0.2);
        spin_f0g = new QDoubleSpinBox(TreeOptions);
        spin_f0g->setObjectName(QStringLiteral("spin_f0g"));
        spin_f0g->setGeometry(QRect(70, 120, 69, 27));
        spin_f0g->setMaximum(2);
        spin_f0g->setSingleStep(0.05);
        spin_f0g->setValue(0.2);
        spin_f0b = new QDoubleSpinBox(TreeOptions);
        spin_f0b->setObjectName(QStringLiteral("spin_f0b"));
        spin_f0b->setGeometry(QRect(70, 160, 69, 27));
        spin_f0b->setMaximum(2);
        spin_f0b->setSingleStep(0.05);
        spin_f0b->setValue(0.2);
        label = new QLabel(TreeOptions);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 80, 31, 31));
        label_2 = new QLabel(TreeOptions);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 120, 31, 31));
        label_3 = new QLabel(TreeOptions);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 31, 31));
        label_4 = new QLabel(TreeOptions);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 200, 61, 31));
        spin_rough = new QDoubleSpinBox(TreeOptions);
        spin_rough->setObjectName(QStringLiteral("spin_rough"));
        spin_rough->setGeometry(QRect(100, 200, 69, 27));
        spin_rough->setMaximum(1);
        spin_rough->setSingleStep(0.05);
        spin_rough->setValue(0.3);
        label_5 = new QLabel(TreeOptions);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 240, 61, 31));
        spin_metallic = new QDoubleSpinBox(TreeOptions);
        spin_metallic->setObjectName(QStringLiteral("spin_metallic"));
        spin_metallic->setGeometry(QRect(100, 240, 69, 27));
        spin_metallic->setMaximum(1);
        spin_metallic->setSingleStep(0.05);
        spin_metallic->setValue(0.3);

        Configuration->addWidget(TreeOptions);

        Spacer = new QSpacerItem(50, 50, QSizePolicy::Minimum, QSizePolicy::Maximum);

        Configuration->addItem(Spacer);

        RenderOptions = new QGroupBox(Widget);
        RenderOptions->setObjectName(QStringLiteral("RenderOptions"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RenderOptions->sizePolicy().hasHeightForWidth());
        RenderOptions->setSizePolicy(sizePolicy);
        RenderOptions->setMinimumSize(QSize(0, 90));
        RenderOptions->setMaximumSize(QSize(200, 90));
        RenderOptions->setBaseSize(QSize(0, 100));
        Label_NumFaces = new QLabel(RenderOptions);
        Label_NumFaces->setObjectName(QStringLiteral("Label_NumFaces"));
        Label_NumFaces->setGeometry(QRect(90, 24, 91, 17));
        Label_Faces = new QLabel(RenderOptions);
        Label_Faces->setObjectName(QStringLiteral("Label_Faces"));
        Label_Faces->setGeometry(QRect(10, 24, 67, 17));
        Label_Vertices = new QLabel(RenderOptions);
        Label_Vertices->setObjectName(QStringLiteral("Label_Vertices"));
        Label_Vertices->setGeometry(QRect(10, 48, 67, 17));
        Label_NumVertices = new QLabel(RenderOptions);
        Label_NumVertices->setObjectName(QStringLiteral("Label_NumVertices"));
        Label_NumVertices->setGeometry(QRect(90, 48, 91, 17));
        Label_Framerate = new QLabel(RenderOptions);
        Label_Framerate->setObjectName(QStringLiteral("Label_Framerate"));
        Label_Framerate->setGeometry(QRect(10, 71, 71, 17));
        Label_NumFramerate = new QLabel(RenderOptions);
        Label_NumFramerate->setObjectName(QStringLiteral("Label_NumFramerate"));
        Label_NumFramerate->setGeometry(QRect(90, 71, 91, 17));

        Configuration->addWidget(RenderOptions);


        horizontalLayout->addLayout(Configuration);

        MainWindow->setCentralWidget(Widget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 828, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionLoad_Specular);
        menuFile->addAction(actionLoad_Diffuse);

        retranslateUi(MainWindow);
        QObject::connect(glwidget, SIGNAL(SetFaces(QString)), Label_NumFaces, SLOT(setText(QString)));
        QObject::connect(glwidget, SIGNAL(SetVertices(QString)), Label_NumVertices, SLOT(setText(QString)));
        QObject::connect(glwidget, SIGNAL(SetFramerate(QString)), Label_NumFramerate, SLOT(setText(QString)));
        QObject::connect(radio_reflection, SIGNAL(clicked(bool)), glwidget, SLOT(SetReflection(bool)));
        QObject::connect(radio_brdf, SIGNAL(clicked(bool)), glwidget, SLOT(SetBRDF(bool)));
        QObject::connect(spin_f0b, SIGNAL(valueChanged(double)), glwidget, SLOT(SetFresnelB(double)));
        QObject::connect(spin_f0g, SIGNAL(valueChanged(double)), glwidget, SLOT(SetFresnelG(double)));
        QObject::connect(spin_f0r, SIGNAL(valueChanged(double)), glwidget, SLOT(SetFresnelR(double)));
        QObject::connect(spin_rough, SIGNAL(valueChanged(double)), glwidget, SLOT(SetRoughness(double)));
        QObject::connect(spin_metallic, SIGNAL(valueChanged(double)), glwidget, SLOT(SetMetallic(double)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        actionLoad_Specular->setText(QApplication::translate("MainWindow", "Load Specular", nullptr));
        actionLoad_Diffuse->setText(QApplication::translate("MainWindow", "Load Diffuse", nullptr));
        TreeOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
        radio_reflection->setText(QApplication::translate("MainWindow", "Reflection", nullptr));
        radio_brdf->setText(QApplication::translate("MainWindow", "Brdf", nullptr));
        label->setText(QApplication::translate("MainWindow", "F0 R", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "F0 G", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "F0 B", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Roughness", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Metallic", nullptr));
        RenderOptions->setTitle(QString());
        Label_NumFaces->setText(QApplication::translate("MainWindow", "0", nullptr));
        Label_Faces->setText(QApplication::translate("MainWindow", "Faces", nullptr));
        Label_Vertices->setText(QApplication::translate("MainWindow", "Vertices", nullptr));
        Label_NumVertices->setText(QApplication::translate("MainWindow", "0", nullptr));
        Label_Framerate->setText(QApplication::translate("MainWindow", "Framerate", nullptr));
        Label_NumFramerate->setText(QApplication::translate("MainWindow", "0", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
