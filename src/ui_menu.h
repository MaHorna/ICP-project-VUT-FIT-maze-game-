/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QToolButton *a4loadcustom;
    QToolButton *a5playlast;
    QToolButton *a6savereplay;
    QToolButton *a7loadreplay;
    QToolButton *a8exit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName(QStringLiteral("menu"));
        menu->setWindowModality(Qt::NonModal);
        menu->resize(205, 528);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menu->sizePolicy().hasHeightForWidth());
        menu->setSizePolicy(sizePolicy);
        menu->setMinimumSize(QSize(55, 500));
        menu->setMaximumSize(QSize(205, 5000));
        menu->setBaseSize(QSize(200, 500));
        menu->setToolTipDuration(5);
        verticalLayoutWidget = new QWidget(menu);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 211, 521));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        a4loadcustom = new QToolButton(verticalLayoutWidget);
        a4loadcustom->setObjectName(QStringLiteral("a4loadcustom"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(a4loadcustom->sizePolicy().hasHeightForWidth());
        a4loadcustom->setSizePolicy(sizePolicy1);
        a4loadcustom->setMinimumSize(QSize(55, 55));
        a4loadcustom->setMaximumSize(QSize(200, 55));
        a4loadcustom->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/menu/play1.png"), QSize(), QIcon::Normal, QIcon::Off);
        a4loadcustom->setIcon(icon);
        a4loadcustom->setIconSize(QSize(60, 60));
        a4loadcustom->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout->addWidget(a4loadcustom);

        a5playlast = new QToolButton(verticalLayoutWidget);
        a5playlast->setObjectName(QStringLiteral("a5playlast"));
        sizePolicy1.setHeightForWidth(a5playlast->sizePolicy().hasHeightForWidth());
        a5playlast->setSizePolicy(sizePolicy1);
        a5playlast->setMinimumSize(QSize(55, 55));
        a5playlast->setMaximumSize(QSize(200, 55));
        a5playlast->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/menu/replay1.png"), QSize(), QIcon::Normal, QIcon::Off);
        a5playlast->setIcon(icon1);
        a5playlast->setIconSize(QSize(60, 60));
        a5playlast->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout->addWidget(a5playlast);

        a6savereplay = new QToolButton(verticalLayoutWidget);
        a6savereplay->setObjectName(QStringLiteral("a6savereplay"));
        sizePolicy1.setHeightForWidth(a6savereplay->sizePolicy().hasHeightForWidth());
        a6savereplay->setSizePolicy(sizePolicy1);
        a6savereplay->setMinimumSize(QSize(55, 55));
        a6savereplay->setMaximumSize(QSize(200, 55));
        a6savereplay->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/menu/save1.png"), QSize(), QIcon::Normal, QIcon::Off);
        a6savereplay->setIcon(icon2);
        a6savereplay->setIconSize(QSize(60, 60));
        a6savereplay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout->addWidget(a6savereplay);

        a7loadreplay = new QToolButton(verticalLayoutWidget);
        a7loadreplay->setObjectName(QStringLiteral("a7loadreplay"));
        sizePolicy1.setHeightForWidth(a7loadreplay->sizePolicy().hasHeightForWidth());
        a7loadreplay->setSizePolicy(sizePolicy1);
        a7loadreplay->setMinimumSize(QSize(55, 55));
        a7loadreplay->setMaximumSize(QSize(200, 55));
        a7loadreplay->setFocusPolicy(Qt::NoFocus);
        a7loadreplay->setIcon(icon);
        a7loadreplay->setIconSize(QSize(60, 60));
        a7loadreplay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout->addWidget(a7loadreplay);

        a8exit = new QToolButton(verticalLayoutWidget);
        a8exit->setObjectName(QStringLiteral("a8exit"));
        sizePolicy1.setHeightForWidth(a8exit->sizePolicy().hasHeightForWidth());
        a8exit->setSizePolicy(sizePolicy1);
        a8exit->setMinimumSize(QSize(55, 55));
        a8exit->setMaximumSize(QSize(200, 55));
        a8exit->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/menu/exit1.png"), QSize(), QIcon::Normal, QIcon::Off);
        a8exit->setIcon(icon3);
        a8exit->setIconSize(QSize(60, 60));
        a8exit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        verticalLayout->addWidget(a8exit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QApplication::translate("menu", "Form", Q_NULLPTR));
        a4loadcustom->setText(QApplication::translate("menu", "Load custom map", Q_NULLPTR));
        a5playlast->setText(QApplication::translate("menu", "Play last map again", Q_NULLPTR));
        a6savereplay->setText(QApplication::translate("menu", "Save replay", Q_NULLPTR));
        a7loadreplay->setText(QApplication::translate("menu", "Load replay", Q_NULLPTR));
        a8exit->setText(QApplication::translate("menu", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
