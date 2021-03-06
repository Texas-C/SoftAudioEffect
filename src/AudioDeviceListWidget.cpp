#include "AudioDeviceListWidget.h"
#include "ui_AudioDeviceListWidget.h"

#include <QAudio>
#include <QDebug>

AudioDeviceListWidget::AudioDeviceListWidget( QWidget *parent ) : QWidget(parent),
    ui(new Ui::AudioDeviceListWidget),
    audio_dev_list( new AudioDeviceList)
{
    ui->setupUi( this );
    this->initDeviceList();
}

AudioDeviceListWidget::~AudioDeviceListWidget()
{
    delete this->audio_dev_list;
    delete this->ui;
}

void AudioDeviceListWidget::initDeviceList()
{
    // get default device:
    const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultInputDevice();

    // get available device list
    *(this->audio_dev_list) = QAudioDeviceInfo::availableDevices( QAudio::AudioInput);

    // set default device:
    this->ui->combo_devlist->addItem( defaultDeviceInfo.deviceName() );

    // add device list to combo box
    for(AudioDeviceList::iterator it = this->audio_dev_list->begin();
            it != this->audio_dev_list->end(); ++it)
    {
        if( *it != defaultDeviceInfo)
            this->ui->combo_devlist->addItem( it->deviceName());
    }
}

// get input device:
QAudioDeviceInfo AudioDeviceListWidget::getInputAudioDeviceInfo( const int &index)
{
    if( index >= 0 && index < this->audio_dev_list->size())
        return this->audio_dev_list->at(index);
    else
        return QAudioDeviceInfo::defaultInputDevice();
}

// get current device's info
QAudioDeviceInfo AudioDeviceListWidget::getCurrentDeviceInfo()
{
    return this->audio_dev_list->at( this->ui->combo_devlist->currentIndex());
}

void AudioDeviceListWidget::on_combo_devlist_currentIndexChanged(int index)
{
    emit signal_audioDeviceInfo( this->audio_dev_list->at(index));
}
