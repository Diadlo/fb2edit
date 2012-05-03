#ifndef FB2VIEW_H
#define FB2VIEW_H

#include <QNetworkAccessManager>
#include <QResizeEvent>
#include <QTimer>
#include <QWebView>

class Fb2NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit Fb2NetworkAccessManager(QObject *parent = 0);

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);

};

class Fb2BaseWebView : public QWebView
{
    Q_OBJECT

public:
    Fb2BaseWebView(QWidget* parent = 0)
        : QWebView(parent)
    {
          m_timer.setInterval(100);
          m_timer.setSingleShot(true);
          connect(&m_timer, SIGNAL(timeout()), SLOT(doResize()));
    }

protected slots:
    void doResize() {
        QResizeEvent event(size(), m_size);
        QWebView::resizeEvent(&event);
        QWebView::update();
    }

protected:
     void resizeEvent(QResizeEvent* event) {
          if (!m_timer.isActive()) m_size = event->oldSize();
          m_timer.start();
     }

private:
    QTimer m_timer;
    QSize m_size;
};

class Fb2WebView : public Fb2BaseWebView
{
    Q_OBJECT
public:
    explicit Fb2WebView(QWidget *parent = 0);
    
signals:
    
public slots:
    void zoomIn();
    void zoomOut();
    void zoomOrig();

private:
    Fb2NetworkAccessManager m_network;
};

#endif // FB2VIEW_H
