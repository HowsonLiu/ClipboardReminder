#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QClipboard>
#include <QTimer>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* m_trayIcon;
    QMenu* m_menu;
    QWidget* m_centralWidget; //QMainWindow不能直接设置layout
    QLabel* m_infoLabel;
    QLabel* m_detailLabel;
    QIcon* m_icon;

    QAction* m_enableAct;
    QAction* m_disableAct;
    QAction* m_showAct;
    QAction* m_hideAct;
    QAction* m_exitAct;

    QClipboard* m_clipBoard;
    QTimer* m_timer;

    bool b_draging = false;
    bool b_showing = false;
    QPoint m_mousePoint;

    float m_showTime = 1;
    int m_fontSize = 12;
    int m_detailLabelMaxWidth = 192;
    int m_detailLabelMaxHeight = 108;

private:
    void ReadConfigure();
    void StartHide();
    void StopHide();
    void UpdateSize();

private slots:
    void ClipboardUpdate();
    void Enable();
    void Disable();
    void Show();
    void Hide();
    void TrayIconSlot(QSystemTrayIcon::ActivationReason);

};

#endif // MAINWINDOW_H
