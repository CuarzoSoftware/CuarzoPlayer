#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include "pix.h"

extern QString blue;

class TableView : public QTableWidget
{
    Q_OBJECT

public:
    Pix p;
    TableView()
    {
        hide();
        verticalHeader()->setVisible(false);
        verticalHeader()->setDefaultSectionSize(22);
        horizontalHeader()->setStretchLastSection(true);
        setShowGrid(false);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        //setSelectionMode(QAbstractItemView::MultiSelection);
        setAlternatingRowColors(true);
        resizeRowsToContents();
        setStyleSheet("TableView {border:0px;alternate-background-color:#F4F4F4;color:#444;font-size:12px;}");
        QPalette p = palette();
        p.setColor(QPalette::Highlight, QColor(blue));
        setPalette(p);

        QStringList header;
        header << "" << "Title" << "State" << "Time" << "Artist" << "Album" << "Genre" << "Year" << "";
        setRowCount(1);
        setColumnCount(9);
        setColumnWidth(0,20);
        setColumnWidth(1,200);
        setColumnWidth(2,40);
        setColumnWidth(3,40);
        setColumnWidth(4,150);
        setColumnWidth(5,150);
        setColumnWidth(6,200);
        setColumnWidth(7,40);
        setHorizontalHeaderLabels(header);

    }
    void setData(QVariantList songs)
    {
        setRowCount(songs.length() + 10);

        int i = 0;
        foreach (QVariant s, songs)
        {
            QVariantMap song = s.toMap();
            QTableWidgetItem *title = new QTableWidgetItem(song["title"].toString());
            title->setData(32,s);
            setItem(i,1,title);
            setItem(i,3,new QTableWidgetItem(p.timeFromSecconds(song["duration"].toInt())));
            setItem(i,4,new QTableWidgetItem(song["artist"].toString()));
            setItem(i,5,new QTableWidgetItem(song["album"].toString()));
            setItem(i,6,new QTableWidgetItem(song["genre"].toString()));
            setItem(i,7,new QTableWidgetItem(QString::number(song["year"].toInt())));
            i++;
        }
    }
};

#endif // TABLEVIEW_H
