#include "webview.h"
#include <QCloseEvent>

WebView::WebView(QWidget *parent): QWebEngineView{parent}
{}

void WebView::closeEvent(QCloseEvent *event){
    hide();
    event->ignore();
}
