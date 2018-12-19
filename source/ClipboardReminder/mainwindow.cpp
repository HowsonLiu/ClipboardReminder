﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMimeData>
#include <QSizePolicy>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_trayIcon = new QSystemTrayIcon(this);
    m_menu = new QMenu(this);
    m_centralWidget = new QWidget(this);
    m_infoLabel = new QLabel(this);
    m_detailLabel = new QLabel(this);
    m_enableAct = new QAction(this);
    m_disableAct = new QAction(this);
    m_showAct = new QAction(this);
    m_exitAct = new QAction(this);
    m_clipBoard = QApplication::clipboard();
    m_timer = new QTimer(this);
    m_icon = new QIcon();

    m_trayIcon->setContextMenu(m_menu);
    m_menu->addAction(m_enableAct);
    m_menu->addAction(m_disableAct);
    m_menu->addAction(m_showAct);
    m_menu->addAction(m_exitAct);

    this->setCentralWidget(m_centralWidget);
    QVBoxLayout* mainBoxLayout = new QVBoxLayout();
    mainBoxLayout->addWidget(m_infoLabel);
    mainBoxLayout->addWidget(m_detailLabel);
    m_centralWidget->setLayout(mainBoxLayout);

    connect(m_enableAct, &QAction::triggered, this, &MainWindow::Enable);
    connect(m_disableAct, &QAction::triggered, this, &MainWindow::Disable);
    connect(m_showAct, &QAction::triggered, this, &MainWindow::ClipboardUpdate);
    connect(m_exitAct, &QAction::triggered, this, &MainWindow::close);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::hide);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::TrayIconSlot);
    connect(m_trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::ClipboardUpdate);

    //------------------------------------------设置样式------------------------------------------------

    m_enableAct->setText(QString::fromLocal8Bit("启动"));
    m_disableAct->setText(QString::fromLocal8Bit("禁止"));
    m_showAct->setText(QString::fromLocal8Bit("查看"));
    m_exitAct->setText(QString::fromLocal8Bit("退出"));

    m_detailLabel->setMaximumSize(QSize(m_detailLabelMaxWidth, m_detailLabelMaxHeight));
    m_detailLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);//总在最前、无边框、任务栏不显示(Qt::Tooltip)

    //--------------------------------------------------------------------------------------------------

    m_trayIcon->show();
    Enable();
    ClipboardUpdate();
    m_timer->start(1); //构造函数不能使用this->hide
    m_trayIcon->showMessage("ClipboardReminder", QString::fromLocal8Bit("已启用"), *m_icon, 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        b_draging = true;
        m_mousePoint = event->pos();
        StopHide();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(b_draging){
        move(event->pos() - m_mousePoint + pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    b_draging = false;
    StartHide();
}

void MainWindow::StartHide()
{
    m_timer->start((int)(m_showTime * 1000));
}

void MainWindow::StopHide()
{
    m_timer->stop();
}

void MainWindow::ClipboardUpdate()
{
    const QMimeData* data = m_clipBoard->mimeData();
    if(data->hasText()){
        m_infoLabel->setText(QString::fromLocal8Bit("文本"));
        m_detailLabel->setText(data->text());
    }
    else if(data->hasImage()){
        m_infoLabel->setText(QString::fromLocal8Bit("图片"));
        QImage img = qvariant_cast<QImage>(data->imageData());
        if(img.height() > m_detailLabelMaxHeight || img.width() > m_detailLabelMaxWidth){
            if(m_detailLabelMaxHeight/img.height() > m_detailLabelMaxWidth/img.width()){
                img = img.scaled(m_detailLabelMaxWidth, img.height()*m_detailLabelMaxWidth/img.width());
            }
            else{
                img = img.scaled(img.width()*m_detailLabelMaxHeight/img.height(), m_detailLabelMaxHeight);
            }
        }
        m_detailLabel->setPixmap(QPixmap::fromImage(img));
    }
    else if(data->hasColor()){
        m_infoLabel->setText(QString::fromLocal8Bit("颜色"));
        m_detailLabel->setText(QString::fromLocal8Bit("颜色"));
    }
    else if(data->hasHtml()){
        m_infoLabel->setText(QString::fromLocal8Bit("HTML"));


        m_detailLabel->setText(data->html());
    }
    else if(data->hasUrls()){
        m_infoLabel->setText(QString::fromLocal8Bit("URLs"));
        m_detailLabel->setText(data->text());
    }
    else{
        m_infoLabel->setText(QString::fromLocal8Bit("空"));
        m_detailLabel->setText(QString::fromLocal8Bit("空"));
    }

    m_infoLabel->adjustSize();
    m_detailLabel->adjustSize();
    m_centralWidget->adjustSize();
    this->adjustSize();
    this->show();
    StartHide();

    qDebug() << m_centralWidget->width() << m_centralWidget->height();
    qDebug() << m_infoLabel->width() << m_infoLabel->height();
    qDebug() << m_detailLabel->width() << m_detailLabel->height();
}

void MainWindow::Enable()
{
    connect(m_clipBoard, &QClipboard::dataChanged, this, &MainWindow::ClipboardUpdate);
}

void MainWindow::Disable()
{
    disconnect(m_clipBoard, &QClipboard::dataChanged, this, &MainWindow::ClipboardUpdate);
}

void MainWindow::TrayIconSlot(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        ClipboardUpdate();
        break;
    case QSystemTrayIcon::DoubleClick:
        ClipboardUpdate();
        break;
    default:
        break;
    }
}