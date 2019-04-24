#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "processutils.h"
#include "splashwindow.h"

#define SPLASH_DURATION 1000
#define SPLASH_WIDTH 512
#define SPLASH_HEIGHT 320

SplashWindow::SplashWindow()
    : QMainWindow(nullptr, Qt::SplashScreen)
{
    setCentralWidget(buildCentralWidget());
    setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    setStyleSheet("QLabel { background-color: transparent; color: white; padding: 0 }");
    QTimer::singleShot(SPLASH_DURATION, [=] {
        (new MainWindow())->show();
        close();
    });
}

QWidget *SplashWindow::buildCentralWidget()
{
    auto widget = new QWidget(this);
    auto layout = new QVBoxLayout(widget);
    QPixmap pixmap(":/images/splash.png");
    auto banner = new QLabel(this);
    banner->setPixmap(pixmap);
    layout->addWidget(banner);
    auto loading = new QLabel(widget);
    loading->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    loading->setContentsMargins(10, 0, 0, 72);
    loading->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    loading->setText(tr("Loading..."));
    QFont font = loading->font();
    font.setPointSize(10);
    loading->setFont(font);
    auto commit = new QLabel(widget);
    commit->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    commit->setContentsMargins(10, 0, 0, 40);
    commit->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    commit->setFont(font);
    commit->setText(QString("%1 (%2)").arg(GIT_COMMIT_SHORT).arg(GIT_COMMIT_NUMBER));
    const QString tag = QString(GIT_TAG);
    if (tag.isEmpty()) {
        auto version = new QLabel(tag, widget);
        version->setAlignment(Qt::AlignRight);
        version->setContentsMargins(0, 2, 4, 0);
        version->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
        version->setFont(font);
    }
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    widget->setLayout(layout);
    return widget;
}

SplashWindow::~SplashWindow()
{
}