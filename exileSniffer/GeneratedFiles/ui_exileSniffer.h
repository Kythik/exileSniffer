/********************************************************************************
** Form generated from reading UI file 'exileSniffer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXILESNIFFER_H
#define UI_EXILESNIFFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "statuswidget.h"

QT_BEGIN_NAMESPACE

class Ui_exileSniffer
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *processTabs;
    QWidget *interceptionTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *ex_sniff_layout;
    statusWidget *keyExStatusWidget;
    statusWidget *sniffStatusWidget;
    QWidget *decrypt_status_widget;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *decryptionIconsLayout;
    QLabel *no_decrypt_label;
    QLabel *yes_decrypt_label;
    QFrame *decryptionInfoFrame;
    QHBoxLayout *horizontalLayout_9;
    QStackedWidget *decrypt_details_stack;
    QWidget *noDecryptStack;
    QVBoxLayout *verticalLayout_9;
    QLabel *decryptionStatusText;
    QWidget *yesDecryptStack;
    QVBoxLayout *verticalLayout_10;
    QLabel *label;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPlainTextEdit *keyHexText;
    QLineEdit *sendIVText;
    QLineEdit *recvIVText;
    QLabel *label_5;
    QLineEdit *sendIterText;
    QLabel *label_6;
    QLineEdit *recvIterText;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *stopDecryptBtn;
    QWidget *decodeTab;
    QGridLayout *gridLayout_3;
    QFrame *decodeDisplayFrame;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QFrame *decodedControlFrame;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *decodedAutoscrollCheck;
    QFrame *decodedLabelFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *decodedDisplayedLabel;
    QPushButton *decodedFiltersBtn;
    QSplitter *splitter;
    QTableWidget *decodedListTable;
    QTabWidget *decodedDetailsTab;
    QWidget *decodeAnalysisTab;
    QHBoxLayout *horizontalLayout_8;
    QPlainTextEdit *decodedText;
    QWidget *decodeRawTab;
    QHBoxLayout *horizontalLayout_11;
    QPlainTextEdit *decodedRawHex;
    QPlainTextEdit *decodedRawText;
    QWidget *metaLogTab;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *metaLog;
    QWidget *settingsTab;
    QHBoxLayout *horizontalLayout_7;
    QListWidget *settingsChoiceList;
    QStackedWidget *settingsStack;
    QWidget *logSettings;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QCheckBox *logsEnabledCheck;
    QPushButton *logsOpenDirBtn;
    QLineEdit *logDirLine;
    QPushButton *logSetDirBtn;
    QWidget *feedSettings;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QLineEdit *namedPipeChosenName;
    QLabel *label_8;
    QLabel *label_9;
    QCheckBox *pipeFeedEnableCheck;
    QLineEdit *namedPipePathResult;
    QWidget *utilsTab;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLineEdit *hashUtilInputText;
    QLabel *order1hash;
    QLabel *order2hash;
    QLabel *order1hashres;
    QLabel *order2hashres;
    QLabel *label_11;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QTextEdit *textEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *exileSniffer)
    {
        if (exileSniffer->objectName().isEmpty())
            exileSniffer->setObjectName(QString::fromUtf8("exileSniffer"));
        exileSniffer->resize(827, 673);
        centralWidget = new QWidget(exileSniffer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        processTabs = new QTabWidget(centralWidget);
        processTabs->setObjectName(QString::fromUtf8("processTabs"));
        processTabs->setTabPosition(QTabWidget::North);
        interceptionTab = new QWidget();
        interceptionTab->setObjectName(QString::fromUtf8("interceptionTab"));
        verticalLayout_4 = new QVBoxLayout(interceptionTab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 12);
        ex_sniff_layout = new QHBoxLayout();
        ex_sniff_layout->setSpacing(0);
        ex_sniff_layout->setObjectName(QString::fromUtf8("ex_sniff_layout"));
        keyExStatusWidget = new statusWidget(interceptionTab);
        keyExStatusWidget->setObjectName(QString::fromUtf8("keyExStatusWidget"));

        ex_sniff_layout->addWidget(keyExStatusWidget);

        sniffStatusWidget = new statusWidget(interceptionTab);
        sniffStatusWidget->setObjectName(QString::fromUtf8("sniffStatusWidget"));

        ex_sniff_layout->addWidget(sniffStatusWidget);


        verticalLayout_4->addLayout(ex_sniff_layout);

        decrypt_status_widget = new QWidget(interceptionTab);
        decrypt_status_widget->setObjectName(QString::fromUtf8("decrypt_status_widget"));
        decrypt_status_widget->setMinimumSize(QSize(600, 280));
        decrypt_status_widget->setMaximumSize(QSize(999999, 99999));
        horizontalLayout_10 = new QHBoxLayout(decrypt_status_widget);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        decryptionIconsLayout = new QVBoxLayout();
        decryptionIconsLayout->setSpacing(6);
        decryptionIconsLayout->setObjectName(QString::fromUtf8("decryptionIconsLayout"));
        decryptionIconsLayout->setContentsMargins(-1, -1, -1, 0);
        no_decrypt_label = new QLabel(decrypt_status_widget);
        no_decrypt_label->setObjectName(QString::fromUtf8("no_decrypt_label"));
        no_decrypt_label->setMinimumSize(QSize(130, 130));
        no_decrypt_label->setMaximumSize(QSize(130, 130));
        no_decrypt_label->setBaseSize(QSize(130, 130));
        no_decrypt_label->setStyleSheet(QString::fromUtf8(""));

        decryptionIconsLayout->addWidget(no_decrypt_label);

        yes_decrypt_label = new QLabel(decrypt_status_widget);
        yes_decrypt_label->setObjectName(QString::fromUtf8("yes_decrypt_label"));
        yes_decrypt_label->setMinimumSize(QSize(130, 130));
        yes_decrypt_label->setMaximumSize(QSize(130, 130));
        yes_decrypt_label->setBaseSize(QSize(130, 130));
        yes_decrypt_label->setStyleSheet(QString::fromUtf8(""));

        decryptionIconsLayout->addWidget(yes_decrypt_label);


        horizontalLayout_10->addLayout(decryptionIconsLayout);

        decryptionInfoFrame = new QFrame(decrypt_status_widget);
        decryptionInfoFrame->setObjectName(QString::fromUtf8("decryptionInfoFrame"));
        horizontalLayout_9 = new QHBoxLayout(decryptionInfoFrame);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        decrypt_details_stack = new QStackedWidget(decryptionInfoFrame);
        decrypt_details_stack->setObjectName(QString::fromUtf8("decrypt_details_stack"));
        noDecryptStack = new QWidget();
        noDecryptStack->setObjectName(QString::fromUtf8("noDecryptStack"));
        verticalLayout_9 = new QVBoxLayout(noDecryptStack);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        decryptionStatusText = new QLabel(noDecryptStack);
        decryptionStatusText->setObjectName(QString::fromUtf8("decryptionStatusText"));
        QFont font;
        font.setPointSize(16);
        decryptionStatusText->setFont(font);
        decryptionStatusText->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(decryptionStatusText);

        decrypt_details_stack->addWidget(noDecryptStack);
        yesDecryptStack = new QWidget();
        yesDecryptStack->setObjectName(QString::fromUtf8("yesDecryptStack"));
        verticalLayout_10 = new QVBoxLayout(yesDecryptStack);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label = new QLabel(yesDecryptStack);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label);

        groupBox_3 = new QGroupBox(yesDecryptStack);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 16777206));
        QFont font1;
        font1.setPointSize(12);
        groupBox_3->setFont(font1);
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setHorizontalSpacing(22);
        formLayout_2->setContentsMargins(20, -1, 20, -1);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_4);

        keyHexText = new QPlainTextEdit(groupBox_3);
        keyHexText->setObjectName(QString::fromUtf8("keyHexText"));
        keyHexText->setMaximumSize(QSize(16777215, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Courier"));
        font2.setPointSize(10);
        keyHexText->setFont(font2);
        keyHexText->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        keyHexText->setReadOnly(true);
        keyHexText->setTabStopWidth(80);
        keyHexText->setMaximumBlockCount(0);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, keyHexText);

        sendIVText = new QLineEdit(groupBox_3);
        sendIVText->setObjectName(QString::fromUtf8("sendIVText"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Courier"));
        sendIVText->setFont(font3);
        sendIVText->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, sendIVText);

        recvIVText = new QLineEdit(groupBox_3);
        recvIVText->setObjectName(QString::fromUtf8("recvIVText"));
        recvIVText->setFont(font3);
        recvIVText->setReadOnly(true);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, recvIVText);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font4;
        font4.setPointSize(11);
        font4.setItalic(false);
        label_5->setFont(font4);
        label_5->setIndent(15);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_5);

        sendIterText = new QLineEdit(groupBox_3);
        sendIterText->setObjectName(QString::fromUtf8("sendIterText"));
        sendIterText->setFont(font3);
        sendIterText->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, sendIterText);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font5;
        font5.setPointSize(11);
        label_6->setFont(font5);
        label_6->setIndent(15);

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_6);

        recvIterText = new QLineEdit(groupBox_3);
        recvIterText->setObjectName(QString::fromUtf8("recvIterText"));
        recvIterText->setFont(font3);
        recvIterText->setReadOnly(true);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, recvIterText);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(2, QFormLayout::FieldRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(5, QFormLayout::FieldRole, verticalSpacer_2);


        verticalLayout_10->addWidget(groupBox_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        stopDecryptBtn = new QPushButton(yesDecryptStack);
        stopDecryptBtn->setObjectName(QString::fromUtf8("stopDecryptBtn"));
        stopDecryptBtn->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_4->addWidget(stopDecryptBtn);


        verticalLayout_10->addLayout(horizontalLayout_4);

        decrypt_details_stack->addWidget(yesDecryptStack);

        horizontalLayout_9->addWidget(decrypt_details_stack);


        horizontalLayout_10->addWidget(decryptionInfoFrame);


        verticalLayout_4->addWidget(decrypt_status_widget);

        processTabs->addTab(interceptionTab, QString());
        decodeTab = new QWidget();
        decodeTab->setObjectName(QString::fromUtf8("decodeTab"));
        gridLayout_3 = new QGridLayout(decodeTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 5);
        decodeDisplayFrame = new QFrame(decodeTab);
        decodeDisplayFrame->setObjectName(QString::fromUtf8("decodeDisplayFrame"));
        decodeDisplayFrame->setFrameShape(QFrame::StyledPanel);
        decodeDisplayFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(decodeDisplayFrame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        decodedControlFrame = new QFrame(decodeDisplayFrame);
        decodedControlFrame->setObjectName(QString::fromUtf8("decodedControlFrame"));
        decodedControlFrame->setFrameShape(QFrame::StyledPanel);
        decodedControlFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(decodedControlFrame);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 3, -1, 3);
        decodedAutoscrollCheck = new QCheckBox(decodedControlFrame);
        decodedAutoscrollCheck->setObjectName(QString::fromUtf8("decodedAutoscrollCheck"));
        decodedAutoscrollCheck->setLayoutDirection(Qt::LeftToRight);
        decodedAutoscrollCheck->setChecked(true);

        horizontalLayout_6->addWidget(decodedAutoscrollCheck);


        horizontalLayout_5->addWidget(decodedControlFrame);

        decodedLabelFrame = new QFrame(decodeDisplayFrame);
        decodedLabelFrame->setObjectName(QString::fromUtf8("decodedLabelFrame"));
        decodedLabelFrame->setMinimumSize(QSize(0, 0));
        decodedLabelFrame->setFrameShape(QFrame::StyledPanel);
        decodedLabelFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(decodedLabelFrame);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 3, -1, 3);
        decodedDisplayedLabel = new QLabel(decodedLabelFrame);
        decodedDisplayedLabel->setObjectName(QString::fromUtf8("decodedDisplayedLabel"));

        horizontalLayout_3->addWidget(decodedDisplayedLabel);

        decodedFiltersBtn = new QPushButton(decodedLabelFrame);
        decodedFiltersBtn->setObjectName(QString::fromUtf8("decodedFiltersBtn"));
        decodedFiltersBtn->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(decodedFiltersBtn);


        horizontalLayout_5->addWidget(decodedLabelFrame);


        verticalLayout_3->addLayout(horizontalLayout_5);

        splitter = new QSplitter(decodeDisplayFrame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(2);
        decodedListTable = new QTableWidget(splitter);
        if (decodedListTable->columnCount() < 4)
            decodedListTable->setColumnCount(4);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setForeground(brush);
        decodedListTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        decodedListTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        decodedListTable->setObjectName(QString::fromUtf8("decodedListTable"));
        decodedListTable->setContextMenuPolicy(Qt::CustomContextMenu);
        decodedListTable->setLayoutDirection(Qt::LeftToRight);
        decodedListTable->setStyleSheet(QString::fromUtf8(""));
        decodedListTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        decodedListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        decodedListTable->setProperty("showDropIndicator", QVariant(false));
        decodedListTable->setDragEnabled(false);
        decodedListTable->setSelectionMode(QAbstractItemView::SingleSelection);
        decodedListTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        decodedListTable->setSortingEnabled(false);
        splitter->addWidget(decodedListTable);
        decodedListTable->horizontalHeader()->setDefaultSectionSize(60);
        decodedListTable->horizontalHeader()->setMinimumSectionSize(43);
        decodedListTable->verticalHeader()->setVisible(false);
        decodedListTable->verticalHeader()->setHighlightSections(false);
        decodedDetailsTab = new QTabWidget(splitter);
        decodedDetailsTab->setObjectName(QString::fromUtf8("decodedDetailsTab"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Courier"));
        font6.setPointSize(10);
        font6.setBold(true);
        font6.setWeight(75);
        decodedDetailsTab->setFont(font6);
        decodedDetailsTab->setTabPosition(QTabWidget::West);
        decodeAnalysisTab = new QWidget();
        decodeAnalysisTab->setObjectName(QString::fromUtf8("decodeAnalysisTab"));
        horizontalLayout_8 = new QHBoxLayout(decodeAnalysisTab);
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(4, 4, 4, 4);
        decodedText = new QPlainTextEdit(decodeAnalysisTab);
        decodedText->setObjectName(QString::fromUtf8("decodedText"));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Courier New"));
        font7.setPointSize(11);
        decodedText->setFont(font7);

        horizontalLayout_8->addWidget(decodedText);

        decodedDetailsTab->addTab(decodeAnalysisTab, QString());
        decodeRawTab = new QWidget();
        decodeRawTab->setObjectName(QString::fromUtf8("decodeRawTab"));
        horizontalLayout_11 = new QHBoxLayout(decodeRawTab);
        horizontalLayout_11->setSpacing(1);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(4, 4, 4, 4);
        decodedRawHex = new QPlainTextEdit(decodeRawTab);
        decodedRawHex->setObjectName(QString::fromUtf8("decodedRawHex"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Courier New"));
        font8.setBold(false);
        font8.setWeight(50);
        decodedRawHex->setFont(font8);
        decodedRawHex->setStyleSheet(QString::fromUtf8("background: rgb(245, 245, 245)"));
        decodedRawHex->setReadOnly(true);

        horizontalLayout_11->addWidget(decodedRawHex);

        decodedRawText = new QPlainTextEdit(decodeRawTab);
        decodedRawText->setObjectName(QString::fromUtf8("decodedRawText"));
        decodedRawText->setFont(font8);
        decodedRawText->setStyleSheet(QString::fromUtf8("background: rgb(245, 245, 245)"));
        decodedRawText->setReadOnly(true);

        horizontalLayout_11->addWidget(decodedRawText);

        horizontalLayout_11->setStretch(0, 5);
        horizontalLayout_11->setStretch(1, 3);
        decodedDetailsTab->addTab(decodeRawTab, QString());
        splitter->addWidget(decodedDetailsTab);

        verticalLayout_3->addWidget(splitter);


        gridLayout_3->addWidget(decodeDisplayFrame, 0, 0, 1, 1);

        processTabs->addTab(decodeTab, QString());
        metaLogTab = new QWidget();
        metaLogTab->setObjectName(QString::fromUtf8("metaLogTab"));
        gridLayout_2 = new QGridLayout(metaLogTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        metaLog = new QPlainTextEdit(metaLogTab);
        metaLog->setObjectName(QString::fromUtf8("metaLog"));

        gridLayout_2->addWidget(metaLog, 0, 0, 1, 1);

        processTabs->addTab(metaLogTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        horizontalLayout_7 = new QHBoxLayout(settingsTab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        settingsChoiceList = new QListWidget(settingsTab);
        new QListWidgetItem(settingsChoiceList);
        new QListWidgetItem(settingsChoiceList);
        settingsChoiceList->setObjectName(QString::fromUtf8("settingsChoiceList"));
        settingsChoiceList->setMaximumSize(QSize(200, 16777215));
        settingsChoiceList->setSpacing(3);
        settingsChoiceList->setViewMode(QListView::ListMode);

        horizontalLayout_7->addWidget(settingsChoiceList);

        settingsStack = new QStackedWidget(settingsTab);
        settingsStack->setObjectName(QString::fromUtf8("settingsStack"));
        logSettings = new QWidget();
        logSettings->setObjectName(QString::fromUtf8("logSettings"));
        verticalLayout = new QVBoxLayout(logSettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(logSettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 115));
        QFont font9;
        font9.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font9.setPointSize(10);
        groupBox_2->setFont(font9);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        logsEnabledCheck = new QCheckBox(groupBox_2);
        logsEnabledCheck->setObjectName(QString::fromUtf8("logsEnabledCheck"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logsEnabledCheck->sizePolicy().hasHeightForWidth());
        logsEnabledCheck->setSizePolicy(sizePolicy);
        logsEnabledCheck->setMinimumSize(QSize(100, 0));
        logsEnabledCheck->setMaximumSize(QSize(128, 60));
        logsEnabledCheck->setLayoutDirection(Qt::LeftToRight);
        logsEnabledCheck->setChecked(true);

        gridLayout_4->addWidget(logsEnabledCheck, 0, 0, 1, 1);

        logsOpenDirBtn = new QPushButton(groupBox_2);
        logsOpenDirBtn->setObjectName(QString::fromUtf8("logsOpenDirBtn"));
        logsOpenDirBtn->setMinimumSize(QSize(95, 0));
        logsOpenDirBtn->setMaximumSize(QSize(100, 16777215));
        logsOpenDirBtn->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(logsOpenDirBtn, 0, 1, 1, 1);

        logDirLine = new QLineEdit(groupBox_2);
        logDirLine->setObjectName(QString::fromUtf8("logDirLine"));

        gridLayout_4->addWidget(logDirLine, 1, 0, 1, 1);

        logSetDirBtn = new QPushButton(groupBox_2);
        logSetDirBtn->setObjectName(QString::fromUtf8("logSetDirBtn"));
        logSetDirBtn->setMinimumSize(QSize(95, 0));

        gridLayout_4->addWidget(logSetDirBtn, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        settingsStack->addWidget(logSettings);
        feedSettings = new QWidget();
        feedSettings->setObjectName(QString::fromUtf8("feedSettings"));
        verticalLayout_5 = new QVBoxLayout(feedSettings);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox = new QGroupBox(feedSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(400, 128));
        QFont font10;
        font10.setPointSize(10);
        groupBox->setFont(font10);
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        namedPipeChosenName = new QLineEdit(groupBox);
        namedPipeChosenName->setObjectName(QString::fromUtf8("namedPipeChosenName"));
        namedPipeChosenName->setMaximumSize(QSize(300, 16777215));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Calibri Light"));
        font11.setPointSize(12);
        namedPipeChosenName->setFont(font11);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, namedPipeChosenName);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        pipeFeedEnableCheck = new QCheckBox(groupBox);
        pipeFeedEnableCheck->setObjectName(QString::fromUtf8("pipeFeedEnableCheck"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, pipeFeedEnableCheck);

        namedPipePathResult = new QLineEdit(groupBox);
        namedPipePathResult->setObjectName(QString::fromUtf8("namedPipePathResult"));
        namedPipePathResult->setMaximumSize(QSize(300, 16777215));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Calibri"));
        font12.setPointSize(12);
        namedPipePathResult->setFont(font12);
        namedPipePathResult->setReadOnly(true);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, namedPipePathResult);


        verticalLayout_5->addWidget(groupBox);

        settingsStack->addWidget(feedSettings);

        horizontalLayout_7->addWidget(settingsStack);

        processTabs->addTab(settingsTab, QString());
        utilsTab = new QWidget();
        utilsTab->setObjectName(QString::fromUtf8("utilsTab"));
        verticalLayout_6 = new QVBoxLayout(utilsTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_4 = new QGroupBox(utilsTab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 135));
        QFont font13;
        font13.setPointSize(9);
        groupBox_4->setFont(font13);
        formLayout_4 = new QFormLayout(groupBox_4);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setVerticalSpacing(10);
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_10);

        hashUtilInputText = new QLineEdit(groupBox_4);
        hashUtilInputText->setObjectName(QString::fromUtf8("hashUtilInputText"));
        hashUtilInputText->setMaximumSize(QSize(230, 16777215));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, hashUtilInputText);

        order1hash = new QLabel(groupBox_4);
        order1hash->setObjectName(QString::fromUtf8("order1hash"));
        order1hash->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, order1hash);

        order2hash = new QLabel(groupBox_4);
        order2hash->setObjectName(QString::fromUtf8("order2hash"));
        order2hash->setMinimumSize(QSize(100, 0));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, order2hash);

        order1hashres = new QLabel(groupBox_4);
        order1hashres->setObjectName(QString::fromUtf8("order1hashres"));
        order1hashres->setFont(font13);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, order1hashres);

        order2hashres = new QLabel(groupBox_4);
        order2hashres->setObjectName(QString::fromUtf8("order2hashres"));
        order2hashres->setFont(font13);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, order2hashres);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, label_11);


        verticalLayout_6->addWidget(groupBox_4);

        processTabs->addTab(utilsTab, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(800, 280));
        textEdit->setReadOnly(true);

        gridLayout_5->addWidget(textEdit, 0, 0, 1, 1);

        processTabs->addTab(tab, QString());

        gridLayout->addWidget(processTabs, 0, 0, 1, 1);

        exileSniffer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(exileSniffer);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        exileSniffer->setStatusBar(statusBar);

        retranslateUi(exileSniffer);
        QObject::connect(decodedListTable, SIGNAL(clicked(QModelIndex)), exileSniffer, SLOT(decodedListClicked()));
        QObject::connect(decodedListTable, SIGNAL(customContextMenuRequested(QPoint)), exileSniffer, SLOT(decodedTableMenuRequest(QPoint)));
        QObject::connect(stopDecryptBtn, SIGNAL(clicked()), exileSniffer, SLOT(stopDecrypting()));
        QObject::connect(settingsChoiceList, SIGNAL(itemSelectionChanged()), exileSniffer, SLOT(settingsSelectionChanged()));
        QObject::connect(decodedListTable, SIGNAL(cellPressed(int,int)), exileSniffer, SLOT(decodedCellActivated(int,int)));
        QObject::connect(hashUtilInputText, SIGNAL(textChanged(QString)), exileSniffer, SLOT(hashUtilInput()));
        QObject::connect(decodedAutoscrollCheck, SIGNAL(toggled(bool)), exileSniffer, SLOT(toggleDecodedAutoScroll(bool)));
        QObject::connect(decodedFiltersBtn, SIGNAL(clicked()), exileSniffer, SLOT(showRawFiltersDLG()));
        QObject::connect(namedPipeChosenName, SIGNAL(returnPressed()), exileSniffer, SLOT(updateSettings()));
        QObject::connect(logSetDirBtn, SIGNAL(clicked()), exileSniffer, SLOT(doLogSetDir()));
        QObject::connect(logsOpenDirBtn, SIGNAL(clicked()), exileSniffer, SLOT(doLogOpenDir()));

        processTabs->setCurrentIndex(5);
        decrypt_details_stack->setCurrentIndex(1);
        decodedDetailsTab->setCurrentIndex(0);
        settingsChoiceList->setCurrentRow(-1);
        settingsStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(exileSniffer);
    } // setupUi

    void retranslateUi(QMainWindow *exileSniffer)
    {
        exileSniffer->setWindowTitle(QApplication::translate("exileSniffer", "exileSniffer", nullptr));
        no_decrypt_label->setText(QString());
        yes_decrypt_label->setText(QString());
        decryptionStatusText->setText(QApplication::translate("exileSniffer", "Not decrypting", nullptr));
        label->setText(QApplication::translate("exileSniffer", "Decryption in progress", nullptr));
        groupBox_3->setTitle(QApplication::translate("exileSniffer", "Salsa Key Material", nullptr));
        label_2->setText(QApplication::translate("exileSniffer", "Key", nullptr));
        label_3->setText(QApplication::translate("exileSniffer", "Send IV", nullptr));
        label_4->setText(QApplication::translate("exileSniffer", "Receive IV", nullptr));
        keyHexText->setPlainText(QApplication::translate("exileSniffer", "33 56 29 3D B7 82 89 24 1D BA E8 CD 9A 00 01 F4 \n"
"FD DD ED DC 1A DD DD DD DD DD DD DD DD DD DD DD", nullptr));
        label_5->setText(QApplication::translate("exileSniffer", "Iteration", nullptr));
        label_6->setText(QApplication::translate("exileSniffer", "Iteration", nullptr));
        stopDecryptBtn->setText(QApplication::translate("exileSniffer", "Stop Decrypting", nullptr));
        processTabs->setTabText(processTabs->indexOf(interceptionTab), QApplication::translate("exileSniffer", "Decryption", nullptr));
        decodedAutoscrollCheck->setText(QApplication::translate("exileSniffer", "Auto Scroll", nullptr));
        decodedDisplayedLabel->setText(QApplication::translate("exileSniffer", "No packets decoded", nullptr));
        decodedFiltersBtn->setText(QApplication::translate("exileSniffer", "Filters", nullptr));
        QTableWidgetItem *___qtablewidgetitem = decodedListTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("exileSniffer", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = decodedListTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("exileSniffer", "Origin", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = decodedListTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("exileSniffer", "PktID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = decodedListTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("exileSniffer", "Summary", nullptr));
        decodedDetailsTab->setTabText(decodedDetailsTab->indexOf(decodeAnalysisTab), QApplication::translate("exileSniffer", "Analysis", nullptr));
        decodedRawHex->setPlainText(QString());
        decodedDetailsTab->setTabText(decodedDetailsTab->indexOf(decodeRawTab), QApplication::translate("exileSniffer", "Raw", nullptr));
        processTabs->setTabText(processTabs->indexOf(decodeTab), QApplication::translate("exileSniffer", "Decoding", nullptr));
        processTabs->setTabText(processTabs->indexOf(metaLogTab), QApplication::translate("exileSniffer", "Log", nullptr));

        const bool __sortingEnabled = settingsChoiceList->isSortingEnabled();
        settingsChoiceList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = settingsChoiceList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("exileSniffer", "Logfiles", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = settingsChoiceList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("exileSniffer", "Feeds", nullptr));
        settingsChoiceList->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("exileSniffer", "Packet Hexdumps Directory", nullptr));
        logsEnabledCheck->setText(QApplication::translate("exileSniffer", "Logging Enabled", nullptr));
        logsOpenDirBtn->setText(QApplication::translate("exileSniffer", "Open", nullptr));
        logSetDirBtn->setText(QApplication::translate("exileSniffer", "Choose", nullptr));
        groupBox->setTitle(QApplication::translate("exileSniffer", "Named Pipe (Decoded Packets - JSON)", nullptr));
        label_8->setText(QApplication::translate("exileSniffer", "Name:", nullptr));
        label_9->setText(QApplication::translate("exileSniffer", "Current Path:", nullptr));
        pipeFeedEnableCheck->setText(QApplication::translate("exileSniffer", "Enabled", nullptr));
        namedPipePathResult->setText(QApplication::translate("exileSniffer", "fffffffffff", nullptr));
        processTabs->setTabText(processTabs->indexOf(settingsTab), QApplication::translate("exileSniffer", "Settings", nullptr));
        groupBox_4->setTitle(QApplication::translate("exileSniffer", "Hash Lookup", nullptr));
        label_10->setText(QApplication::translate("exileSniffer", "Input Hex:", nullptr));
        order1hash->setText(QString());
        order2hash->setText(QString());
        order1hashres->setText(QString());
        order2hashres->setText(QString());
        label_11->setText(QApplication::translate("exileSniffer", "Enter a sequence of hex bytes to lookup a murmur2 hash. Only works for the GGPK strings we have catalogued.", nullptr));
        processTabs->setTabText(processTabs->indexOf(utilsTab), QApplication::translate("exileSniffer", "Utilities", nullptr));
        textEdit->setHtml(QApplication::translate("exileSniffer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">exileSniffer Version 1.0.1</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">https://github.com/ncatlin/exileSniffer</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin"
                        "-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Developed by Nia Catlin</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Apache 2.0 Licenced</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Interacts with (and requires) WinPcap to sniff packets - Get it from https://www.winpcap.org/install/default.htm</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Other libraries used: libtins (stream processing), rapidjson, Qt</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">PyPoE (https://github.com/OmegaK2/PyPoE) is used to generate the game data dictionary</p></body></html>", nullptr));
        processTabs->setTabText(processTabs->indexOf(tab), QApplication::translate("exileSniffer", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class exileSniffer: public Ui_exileSniffer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXILESNIFFER_H
