#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QDialog>
#include <QFileDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QDebug>

#include <fstream>
#include <iostream>
#include <fileref.h>
#include <tag.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <mp4file.h>
#include <mp4tag.h>
#include <mp4coverart.h>
#include <attachedpictureframe.h>
#include <tbytevector.h>
#include <id3v2frame.h>
#include <tfile.h>


extern QString path;

class ImageFile : public TagLib::File
{
public:
    ImageFile(const char *file) : TagLib::File(file)
    {

    }

    TagLib::ByteVector data()
    {
        return readBlock(length());
    }


private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *audioProperties() const { return 0; }
    virtual bool save() { return false; }
};

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
    QList<QUrl> files;
    QString exp = "[A-Za-z0-9_!¿¡?]{0,30}";



    TagEditor(){

        connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
        connect(addArtwork,SIGNAL(released()),this,SLOT(pickArtWork()));
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

    void pickArtWork()
    {

        files = QFileDialog::getOpenFileUrls(new QWidget(),"Select an image",path,"ALL (*.jpg *.jpeg *.png) ;; JPEG (*.jpg *.jpeg) ;; PNG (*.png)");

        if(!files.empty())
        {
            apply->setDisabled(false);
            artWork->setStyleSheet("border-image:url(\""+files.first().path()+"\");border-radius:4px");

        }

    }

    void checkValues()
    {

        bool changed = false;

        if(title->text()    != "") changed = true;
        if(artist->text()   != "") changed = true;
        if(album->text()    != "") changed = true;
        if(genre->text()    != "") changed = true;
        if(track->text()    != "") changed = true;
        if(year->text()     != "") changed = true;
        if(!files.empty()) changed = true;

        apply->setDisabled(!changed);
    }

    void applyChanges()
    {
        QVariantList editedSongs;

        QString prevArtist = "";
        QString prevAlbum = "";

        foreach(QVariant song,songsToEdit)
        {
            QVariantMap s = song.toMap();

            QString songPath = path+"/Cuarzo Player/Music/" + s["artist"].toString() + "/" + s["album"].toString() + "/" + s["fileName"].toString();

            TagLib::MPEG::File MP3FILE(songPath.toStdString().c_str());
            TagLib::ID3v2::Tag *MP3 = MP3FILE.ID3v2Tag();

            if(!files.empty())
            {
                QString savePath = path+"/Cuarzo Player/Artwork/"+s["artist"].toString()+"/"+s["album"].toString()+".jpg";
                if(prevAlbum != s["album"].toString() && prevArtist != s["artist"].toString())
                {
                    if(!QDir(path+"/Cuarzo Player/Artwork/" + s["artist"].toString()).exists()){
                        QDir().mkdir(path+"/Cuarzo Player/Music/" + s["artist"].toString());
                    }
                    if(!QDir(path+"/Cuarzo Player/Artwork/" + s["artist"].toString() + "/" + s["album"].toString()).exists()){
                        QDir().mkdir(path+"/Cuarzo Player/Music/" + s["artist"].toString() + "/" + s["album"].toString());
                    }
                    QImage im(files.first().path());
                    im = im.scaled(256,256,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                    im.save(savePath,"jpg",100);
                    prevAlbum = s["album"].toString();
                    prevArtist = s["artist"].toString();


                }


                MP3->removeFrames("APIC");

                ImageFile imageFile(savePath.toStdString().c_str());
                TagLib::ByteVector imageData = imageFile.data();
                TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;
                frame->setMimeType("image/jpeg");
                frame->setPicture(imageData);
                MP3->addFrame(frame);

            }

            if(title->text() != "") {s["title"] = title->text();MP3->setTitle(title->text().toStdString());}
            if(artist->text() != "") {s["artist"] = artist->text();MP3->setArtist(artist->text().toStdString());}
            if(album->text() != "") {s["album"] = album->text();MP3->setAlbum(album->text().toStdString());}
            if(genre->text() != "") {s["genre"] = genre->text();MP3->setGenre(genre->text().toStdString());}
            if(track->text() != "") {s["track"] = track->text().toInt();MP3->setTrack(track->text().toInt());}
            if(year->text() != "") {s["year"] = year->text().toInt();MP3->setYear(year->text().toInt());}

            MP3FILE.save();

            editedSongs.append(s);
        }
        songsEdited(editedSongs);
        close();
    }
signals:
    void songsEdited(QVariantList);
};

#endif // TAGEDITOR_H
