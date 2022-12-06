#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QMainWindow>
#include <QMediaRecorder>
#include <QUrl>



namespace Ui {
class audiorecorder;
}


class QAudioRecorder;
class QAudioProbe;
class QAudioBuffer;


class QAudioLevel;

class audiorecorder : public QMainWindow
{
    Q_OBJECT

public:
    explicit audiorecorder(QWidget *parent = nullptr);
    ~audiorecorder();

private slots:
    void toggleRecord();

    void updateStatus(QMediaRecorder::Status);
    void onStateChanged(QMediaRecorder::State);
    void updateProgress(qint64 pos);

private:
    Ui::audiorecorder *ui;
    QAudioRecorder *audioRecorder;
    bool outputLocationSet;
};

#endif // AUDIORECORDER_H
