#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QDebug>

extern QString path;

class TagEditor:public QDialog
{
    Q_OBJECT

public:
    QLabel *header = new QLabel("Tag Editor");
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QWidget *formWidget = new QWidget();
    QFormLayout *layout = new QFormLayout(formWidget);
    QLineEdit *title = new QLineEdit();
    QLineEdit *artist = new QLineEdit();
    QLineEdit *album = new QLineEdit();
    QLineEdit *genre = new QLineEdit();
    QLineEdit *track = new QLineEdit();
    QLineEdit *year = new QLineEdit();
    QWidget *artWork = new QWidget();
    QWidget *buttonsWidget = new QWidget();
    QBoxLayout *buttonsLayout = new QBoxLayout(QBoxLayout::LeftToRight,buttonsWidget);
    QPushButton *apply = new QPushButton("Apply");
    QPushButton *addArtwork = new QPushButton("Add Artwork");
    QPushButton *cancel = new QPushButton("Cancel");
    QVariantList songsToEdit;
    QString exp = "[A-Za-z0-9_!¿¡?]{0,30}";



    TagEditor(){

        connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
        mainLayout->addWidget(header);
        mainLayout->addWidget(formWidget);
        mainLayout->addWidget(artWork);
        mainLayout->addWidget(buttonsWidget);
        mainLayout->setAlignment(artWork,Qt::AlignCenter);
        header->setStyleSheet("font-size:30px;color:#888;font-weight:bold");
        title->setMinimumWidth(300);

        title->setValidator(new QRegExpValidator( QRegExp(exp), this ));
        artist->setValidator(new QRegExpValidator( QRegExp(exp), this ));
        genre->setValidator(new QRegExpValidator( QRegExp(exp), this ));
        album->setValidator(new QRegExpValidator( QRegExp(exp), this ));

        artist->setMinimumWidth(300);
        album->setMinimumWidth(300);
        genre->setMinimumWidth(300);
        track->setFixedWidth(50);
        track->setValidator( new QIntValidator(0, 100000, track) );
        year->setFixedWidth(50);
        year->setValidator( new QIntValidator(1000, 3000, year) );
        artWork->setFixedSize(200,200);
        artWork->setStyleSheet("border-image:url(\":res/img/artWork.png\");border-radius:4px");
        layout->addRow(new QLabel("Title"),title);
        layout->addRow(new QLabel("Artist"),artist);
        layout->addRow(new QLabel("Album"),album);
        layout->addRow(new QLabel("Genre"),genre);
        layout->addRow(new QLabel("Track"),track);
        layout->addRow(new QLabel("Year"),year);
        buttonsLayout->addWidget(apply);
        buttonsLayout->addWidget(addArtwork);
        buttonsLayout->addWidget(new QWidget(),10);
        buttonsLayout->addWidget(cancel);

        connect(title,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));
        connect(artist,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));
        connect(album,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));
        connect(genre,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));
        connect(track,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));
        connect(year,SIGNAL(textChanged(QString)),this,SLOT(checkValues()));

        connect(apply,SIGNAL(clicked(bool)),this,SLOT(applyChanges()));

    }

    void setData(QVariantList songs){

        title->setText("");
        artist->setText("");
        album->setText("");
        genre->setText("");
        track->setText("");
        year->setText("");

        cancel->setFocus();
        apply->setDisabled(true);


        songsToEdit = songs;

        bool varTitle = false;
        bool varArtist = false;
        bool varAlbum = false;
        bool varGenre = false;
        bool varTrack = false;
        bool varYear = false;

        header->setText("Tag Editor ( " + QString::number(songs.length()) +" )");

        QVariantMap previus = songs.first().toMap();

        foreach(QVariant song,songs)
        {
            QVariantMap map = song.toMap();

            if(map["title"].toString() != previus["title"].toString()) varTitle = true;
            if(map["artist"].toString() != previus["artist"].toString()) varArtist = true;
            if(map["album"].toString() != previus["album"].toString()) varAlbum = true;
            if(map["genre"].toString() != previus["genre"].toString()) varGenre = true;
            if(map["track"].toInt() != previus["track"].toInt()) varTrack = true;
            if(map["year"].toInt() != previus["year"].toInt()) varYear = true;
            previus = map;

        }

        if(varTitle)
        {
            title->setPlaceholderText("Varies");
        }
        else
        {
            title->setPlaceholderText(previus["title"].toString());
        }

        if(varArtist)
        {
            artist->setPlaceholderText("Varies");
        }
        else
        {
            artist->setPlaceholderText(previus["artist"].toString());
        }

        if(varAlbum)
        {
            album->setPlaceholderText("Varies");
        }
        else
        {
            album->setPlaceholderText(previus["album"].toString());
        }

        if(varAlbum || varArtist)
        {
            artWork->setStyleSheet("border-image:url(\":res/img/artWork.png\");border-radius:4px");
        }
        else
        {
            artWork->setStyleSheet("border-image:url(\""+ path + "/Cuarzo Player/Artwork/" + previus["artist"].toString() + "/" + previus["album"].toString()  +".jpg\");border-radius:4px");
        }

        if(varGenre)
        {
            genre->setPlaceholderText("Varies");
        }
        else
        {
            genre->setPlaceholderText(previus["genre"].toString());
        }

        if(varTrack)
        {
            track->setPlaceholderText("Varies");
        }
        else
        {
            track->setPlaceholderText(QString::number(previus["track"].toInt()));
        }

        if(varYear)
        {
            year->setPlaceholderText("Varies");
        }
        else
        {
            year->setPlaceholderText(QString::number(previus["year"].toInt()));
        }

    }

public slots:
    void checkValues(){

        bool changed = false;

        if(title->text() != "") changed = true;
        if(artist->text() != "") changed = true;
        if(album->text() != "") changed = true;
        if(genre->text() != "") changed = true;
        if(track->text() != "") changed = true;
        if(year->text() != "") changed = true;

        apply->setDisabled(!changed);
    }

    void applyChanges()
    {
        QVariantList editedSongs;

        foreach(QVariant song,songsToEdit)
        {
            QVariantMap s = song.toMap();

            if(title->text() != "") s["title"] = title->text();
            if(artist->text() != "") s["artist"] = artist->text();
            if(album->text() != "") s["album"] = album->text();
            if(genre->text() != "") s["genre"] = genre->text();
            if(track->text() != "") s["track"] = track->text().toInt();
            if(year->text() != "") s["year"] = year->text().toInt();

            editedSongs.append(s);
        }
        songsEdited(editedSongs);
        close();
    }
signals:
    void songsEdited(QVariantList);
};

#endif // TAGEDITOR_H
