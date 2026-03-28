#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWidget>
#include <QWebEngineView>

class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event) override;
signals:
};

#endif // WEBVIEW_H
