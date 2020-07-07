#include <QtGui>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QWindow w;
    w.setGeometry(100, 100, 200, 300);
    w.show();
    return app.exec();
}
