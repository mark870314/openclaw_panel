#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QDir>
#include <QCloseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("openclaw_manage"));
    ui->webBut->setDisabled(true);
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->start();

    isStart = false;
    webView = new WebView();

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(tr("openclaw_manage"));

    trayMenu = new QMenu(this);
    trayMenu->setStyleSheet("QMenu { width: 400px; }");
    trayMenu->addSeparator();
    showAction = trayMenu->addAction(tr("system"));
    showAction->setIcon(QIcon(":/resources/window.png"));
    trayMenu->addSeparator();
    openAction = trayMenu->addAction(tr("open"));
    openAction->setIcon(QIcon(":/resources/open.png"));
    trayMenu->addSeparator();
    doctorAction = trayMenu->addAction(tr("doctor"));
    doctorAction->setIcon(QIcon(":/resources/doctor.png"));
    trayMenu->addSeparator();
    webAction = trayMenu->addAction(tr("panel"));
    webAction->setIcon(QIcon(":/resources/system.png"));
    webAction->setShortcut(QKeySequence::Open);
    trayMenu->addSeparator();
    quitAction = trayMenu->addAction(tr("quit"));
    quitAction->setIcon(QIcon(":/resources/quit.png"));
    quitAction->setShortcut(QKeySequence::Quit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    connect(showAction,&QAction::triggered,this,&Widget::showWindow);
    connect(openAction,&QAction::triggered,this,&Widget::on_openBut_clicked);
    connect(doctorAction,&QAction::triggered,this,&Widget::on_doctorBut_clicked);
    connect(webAction,&QAction::triggered,this,&Widget::on_webBut_clicked);
    connect(quitAction,&QAction::triggered,this,&Widget::quitWindow);
    connect(timer,&QTimer::timeout,this,&Widget::checkStatus);

}

void Widget::showWindow(){
    show();
}

Widget::~Widget()
{
     webView->close();
    delete ui;

}

void Widget::quitWindow(){
    QProcess process;
    QStringList args;
    args << "/opt/homebrew/bin/openclaw" << "gateway" << "stop";
    process.start("/opt/homebrew/bin/node", args);
    process.waitForFinished();
    webView->close();
    close();
    QApplication::quit();
}



void Widget::on_openBut_clicked()
{
    QString runStr = "start";
    QString statusText = tr("start_success");
    if(isStart){
        runStr = "stop";
        statusText = tr("close_success");
        webView->close();
    }

    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QStringList args;
    args << "/opt/homebrew/bin/openclaw" << "gateway" << runStr;
    process.start("/opt/homebrew/bin/node", args);
    process.waitForFinished();
    if(process.exitCode()==0){
        ui->textEdit->append("<b style='color:green'>"+statusText+"</b>");
    }else{
        ui->textEdit->append("<b style='color:red'>"+process.readAllStandardError()+"</b>");
    }

}


void Widget::closeEvent(QCloseEvent *event){
    hide();
    event->ignore();
}


void Widget::on_doctorBut_clicked()
{
    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QStringList args;
    args << "/opt/homebrew/bin/openclaw" << "doctor";
    process.start("/opt/homebrew/bin/node", args);
    process.waitForFinished();
    if(process.exitCode()==0){
        ui->textEdit->append("<b style='color:green'>"+process.readAllStandardOutput()+"</b>");
    }else{
        ui->textEdit->append("<b style='color:red'>"+process.readAllStandardError()+"</b>");
    }
}


void Widget::on_webBut_clicked()
{
    webView->load(QUrl("http://127.0.0.1:18789"));
    webView->resize(1920,1080);
    webView->show();
    hide();
}

void Widget::checkOpenClawStatus(){
    QProcess process;
    process.start("pgrep",QStringList() << "openclaw-gateway");
    process.waitForFinished();
    isStart = !process.readAllStandardOutput().trimmed().isEmpty();
}

void Widget::checkStatus(){
    checkOpenClawStatus();
    if(isStart){
        ui->openBut->setText(tr("close"));
        openAction->setText(tr("close"));
        webAction->setDisabled(false);
        ui->webBut->setDisabled(false);
    }else{
        ui->openBut->setText(tr("open"));
        openAction->setText(tr("open"));
        webAction->setDisabled(true);
        ui->webBut->setDisabled(true);
    }
}
