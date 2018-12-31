#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMimeData>
#include <QSizePolicy>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>

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
    m_hideAct = new QAction(this);
    m_exitAct = new QAction(this);
    m_clipBoard = QApplication::clipboard();
    m_timer = new QTimer(this);
    m_icon = new QIcon(":/icon.png");

    QFileInfo ini_file("./ClipboardReminder.ini");
    if(ini_file.exists() == true){
        ReadConfigure();
    }

    m_trayIcon->setContextMenu(m_menu);
    m_trayIcon->setIcon(*m_icon);
    m_menu->addAction(m_enableAct);
    m_menu->addAction(m_disableAct);
    m_menu->addAction(m_showAct);
    m_menu->addAction(m_hideAct);
    m_menu->addAction(m_exitAct);

    this->setCentralWidget(m_centralWidget);
    QVBoxLayout* mainBoxLayout = new QVBoxLayout();
    mainBoxLayout->addWidget(m_infoLabel);
    mainBoxLayout->addWidget(m_detailLabel);
    m_centralWidget->setLayout(mainBoxLayout);

    connect(m_enableAct, &QAction::triggered, this, &MainWindow::Enable);
    connect(m_disableAct, &QAction::triggered, this, &MainWindow::Disable);
    connect(m_showAct, &QAction::triggered, this, &MainWindow::Show);
    connect(m_hideAct, &QAction::triggered, this, &MainWindow::Hide);
    connect(m_exitAct, &QAction::triggered, this, &MainWindow::close);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::hide);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::TrayIconSlot);
    connect(m_trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::ClipboardUpdate);

    //------------------------------------------设置样式------------------------------------------------

    m_enableAct->setText(QString::fromLocal8Bit("启动"));
    m_disableAct->setText(QString::fromLocal8Bit("禁止"));
    m_showAct->setText(QString::fromLocal8Bit("查看"));
    m_hideAct->setText(QString::fromLocal8Bit("隐藏"));
    m_exitAct->setText(QString::fromLocal8Bit("退出"));

    m_centralWidget->setObjectName("Central_Widget");
    m_centralWidget->setStyleSheet("QWidget#Central_Widget {border: 2px solid #1296db; background-color: white; border-radius: 15px}");

    m_infoLabel->setFont(QFont("Microsoft YaHei", m_fontSize, 75));

    m_detailLabel->setFont(QFont("Microsoft YaHei", m_fontSize, 75));
    m_detailLabel->setObjectName("Detail_Label");
    m_detailLabel->setStyleSheet("QLabel#Detail_Label {border: 2px solid #1296db;}");
    m_detailLabel->setMaximumSize(QSize(m_detailLabelMaxWidth, m_detailLabelMaxHeight));

    setAttribute(Qt::WA_TranslucentBackground);//窗口透明，否则圆角露馅
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);//总在最前、无边框
    setWindowIcon(*m_icon);//程序icon

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
    if(!b_showing)
        StartHide();
}

void MainWindow::ReadConfigure()
{
    QSettings ini_settings("./ClipboardReminder.ini", QSettings::IniFormat);
    float ini_showTime = ini_settings.value("setting/showtime").toFloat();
    int ini_fontSize = ini_settings.value("setting/fontsize").toInt();
    int ini_width = ini_settings.value("setting/width").toInt();
    int ini_height = ini_settings.value("setting/height").toInt();
    if(ini_showTime > 0)
        m_showTime = ini_showTime;
    if(ini_fontSize > 0)
        m_fontSize = ini_fontSize;
    if(ini_width > 0)
        m_detailLabelMaxWidth = ini_width;
    if(ini_height > 0)
        m_detailLabelMaxHeight = ini_height;
}

void MainWindow::StartHide()
{
    m_timer->start((int)(m_showTime * 1000));
}

void MainWindow::StopHide()
{
    m_timer->stop();
}

void MainWindow::UpdateSize()
{
    m_detailLabel->adjustSize();
    m_infoLabel->adjustSize();
    m_centralWidget->adjustSize();
    this->setMinimumSize(QSize(m_centralWidget->width(),m_centralWidget->height()));
    this->setMaximumSize(QSize(m_centralWidget->width(),m_centralWidget->height()));
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
        img = img.scaled(QSize(m_detailLabelMaxWidth, m_detailLabelMaxHeight),Qt::KeepAspectRatio);
        m_detailLabel->setPixmap(QPixmap::fromImage(img));
    }
    else if(data->hasColor()){
        m_infoLabel->setText(QString::fromLocal8Bit("颜色"));
        m_detailLabel->setText(QString::fromLocal8Bit("颜色"));
    }
    else if(data->hasHtml()){//text有可能是误判
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

    UpdateSize();
    this->show();

    //显示时不计时隐藏
    if(b_showing)
        StopHide();
    else
        StartHide();
}

void MainWindow::Enable()
{
    connect(m_clipBoard, &QClipboard::dataChanged, this, &MainWindow::ClipboardUpdate);
}

void MainWindow::Disable()
{
    disconnect(m_clipBoard, &QClipboard::dataChanged, this, &MainWindow::ClipboardUpdate);
}

void MainWindow::Show()
{
    b_showing = true;
    ClipboardUpdate();
}

void MainWindow::Hide()
{
    b_showing = false;
    this->hide();
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
