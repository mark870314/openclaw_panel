#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include "webview.h"
#include <QSystemTrayIcon>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
     void closeEvent(QCloseEvent *event) override;

private slots:
    void on_openBut_clicked();
    void on_doctorBut_clicked();
    void on_webBut_clicked();
    void checkStatus();
    void showWindow();
    void quitWindow();

private:
    Ui::Widget *ui;
    void checkOpenClawStatus();
    bool isStart;
    QTimer *timer;
    WebView *webView;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *showAction,*openAction,*doctorAction,*webAction,*quitAction;



};
#endif // WIDGET_H
