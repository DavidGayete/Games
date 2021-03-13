#include "Entity.h"

std::map<std::string, HSAMPLE> Sonido::audios_cargados;

Sonido::Sonido() {

}

HSAMPLE Sonido::Get(const char* audioname, bool loop)
{
    std::map<std::string, HSAMPLE>::iterator it = audios_cargados.find(audioname);
    if (it != audios_cargados.end())
        return it->second;
    HSAMPLE new_sample;
    if (loop) {
        new_sample = BASS_SampleLoad(false, audioname, 0, 0, 3, BASS_SAMPLE_LOOP);
    }
    else {
        new_sample = BASS_SampleLoad(false, audioname, 0, 0, 3, 0);
    }

    audios_cargados[audioname] = new_sample;
    return new_sample;
}

void play_sound(const char* audioname, bool loop) {
    if (BASS_Init(-1, 44100, 0, 0, NULL) == false) //-1 significa usar el por defecto del sistema operativo
    {
        //error abriendo la tarjeta de sonido...
    }

    //El handler para un sample
    HSAMPLE hSample;

    //El handler para un canal
    HCHANNEL hSampleChannel;

    //Cargamos un sample del disco duro (memoria, filename, offset, length, max, flags)
    //use BASS_SAMPLE_LOOP in the last param to have a looped sound
    //hSample = BASS_SampleLoad(false, audioname, 0, 0, 3, 0);
    hSample = Sonido::Get(audioname, loop);
    if (hSample == 0)
    {
        //file not found
    }

    //Creamos un canal para el sample
    hSampleChannel = BASS_SampleGetChannel(hSample, false);
    //Lanzamos un sample
    BASS_ChannelPlay(hSampleChannel, true);
}

void stop_sound(const char* audioname, bool loop) {
    //BASS_Stop();

    BASS_SampleStop(Sonido::Get(audioname, loop));
}