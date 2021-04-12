/*
 * Author : dimos katsimardos
 * Date   : 2019, August 16
 */
#include "youtubedl.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

QString readFile(QString filepath)
{
    QFile in_file(filepath);
    if(in_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&in_file);
        return in.readAll();
    }
    return "";
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString my_style=readFile(":/style.css");
    if(my_style.length()>0) {
        a.setStyleSheet(my_style);
    }
    YoutubeDl w;
    w.show();

    return a.exec();
}
