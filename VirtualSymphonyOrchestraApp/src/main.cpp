#include "ofMain.h"
#include "ofApp.h"

#include "bass.h"
#include "bass_fx.h"

#include <iostream>
#include <thread>

using namespace std;

void task1(ofApp* tmp) {

	while (true) {

		if (tmp->start == 1) {

			if (!BASS_Init(-1, 44100, 0, 0, 0)) //Initializes BASS Library. Needed only once.
				return;

			HSTREAM AudioChannelFloete = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Floete.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXFloette = BASS_FX_TempoCreate(AudioChannelFloete, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelFagott = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Fagott.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXFagott = BASS_FX_TempoCreate(AudioChannelFagott, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelHorn = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Horn.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXHorn = BASS_FX_TempoCreate(AudioChannelHorn, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelKlarinette = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Klarinette.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXKlarinette = BASS_FX_TempoCreate(AudioChannelKlarinette, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelBass = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Bass.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXBass = BASS_FX_TempoCreate(AudioChannelBass, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelBlech = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Blech.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXBlech = BASS_FX_TempoCreate(AudioChannelBlech, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelCello = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Cello.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXCello = BASS_FX_TempoCreate(AudioChannelCello, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelOboe = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Oboe.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXOboe = BASS_FX_TempoCreate(AudioChannelOboe, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelPercussion = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Percussion.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXPercussion = BASS_FX_TempoCreate(AudioChannelPercussion, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelViola = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Viola.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXViola = BASS_FX_TempoCreate(AudioChannelViola, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelVioline1 = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Violine1.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXVioline1 = BASS_FX_TempoCreate(AudioChannelVioline1, BASS_FX_FREESOURCE);

			HSTREAM AudioChannelVioline2 = BASS_StreamCreateFile(false, "C:/Users/efe/VSOData/Sounds/Violine2.wav", 0, 0, BASS_STREAM_DECODE);
			HSTREAM streamFXVioline2 = BASS_FX_TempoCreate(AudioChannelVioline2, BASS_FX_FREESOURCE);

			//Create a Audio Stream from a File.
			BASS_ChannelPlay(streamFXFloette, true);
			BASS_ChannelPlay(streamFXFagott, true);
			BASS_ChannelPlay(streamFXHorn, true);
			BASS_ChannelPlay(streamFXKlarinette, true);
			BASS_ChannelPlay(streamFXBass, true);
			BASS_ChannelPlay(streamFXBlech, true);
			BASS_ChannelPlay(streamFXCello, true);
			BASS_ChannelPlay(streamFXOboe, true);
			BASS_ChannelPlay(streamFXPercussion, true);
			BASS_ChannelPlay(streamFXViola, true);
			BASS_ChannelPlay(streamFXVioline1, true);
			BASS_ChannelPlay(streamFXVioline2, true);

			bool x = true, x1 = true, x2 = true, x3 = true, x4 = true, x5 = true, x6 = true, x7 = true, x8 = true, x9 = true, x10 = true, x11 = true;
			bool y1 = true, y2 = true, y3 = true, y4 = true, y5 = true, y6 = true, y7 = true, y8 = true, y9 = true, y10 = true, y11 = true, y = true;
			float tempo = 0;
			float add = 0;
			float vol = 1;

			clock_t t_o = clock();
			//Plays the Stream.
			while (BASS_ChannelIsActive(streamFXFloette) && BASS_ChannelIsActive(streamFXFagott) && BASS_ChannelIsActive(streamFXHorn) && BASS_ChannelIsActive(streamFXKlarinette) &&
				BASS_ChannelIsActive(streamFXBass) && BASS_ChannelIsActive(streamFXBlech) && BASS_ChannelIsActive(streamFXCello) && BASS_ChannelIsActive(streamFXOboe) && BASS_ChannelIsActive(streamFXPercussion) &&
				BASS_ChannelIsActive(streamFXViola) && BASS_ChannelIsActive(streamFXVioline1) && BASS_ChannelIsActive(streamFXVioline2))
			{

				if (tmp->stopValue == 1) {
					return;
				}

				tempo = tmp->counter;

				// 10
				x = BASS_ChannelSetAttribute(streamFXFloette, BASS_ATTRIB_TEMPO, tempo);
				y = BASS_ChannelSetAttribute(streamFXFloette, BASS_ATTRIB_VOL, tmp->instrumentsArr[10]);

				// 11
				x1 = BASS_ChannelSetAttribute(streamFXFagott, BASS_ATTRIB_TEMPO, tempo);
				y1 = BASS_ChannelSetAttribute(streamFXFagott, BASS_ATTRIB_VOL, tmp->instrumentsArr[11]);

				// 4
				x2 = BASS_ChannelSetAttribute(streamFXHorn, BASS_ATTRIB_TEMPO, tempo);
				y2 = BASS_ChannelSetAttribute(streamFXHorn, BASS_ATTRIB_VOL, tmp->instrumentsArr[4]);

				// 2
				x3 = BASS_ChannelSetAttribute(streamFXKlarinette, BASS_ATTRIB_TEMPO, tempo);
				y3 = BASS_ChannelSetAttribute(streamFXKlarinette, BASS_ATTRIB_VOL, tmp->instrumentsArr[2]);

				// 8
				x4 = BASS_ChannelSetAttribute(streamFXBass, BASS_ATTRIB_TEMPO, tempo);
				y4 = BASS_ChannelSetAttribute(streamFXBass, BASS_ATTRIB_VOL, tmp->instrumentsArr[8]);

				// 3
				x5 = BASS_ChannelSetAttribute(streamFXBlech, BASS_ATTRIB_TEMPO, tempo);
				y5 = BASS_ChannelSetAttribute(streamFXBlech, BASS_ATTRIB_VOL, tmp->instrumentsArr[3]);

				// 1
				x6 = BASS_ChannelSetAttribute(streamFXCello, BASS_ATTRIB_TEMPO, tempo);
				y6 = BASS_ChannelSetAttribute(streamFXCello, BASS_ATTRIB_VOL, tmp->instrumentsArr[1]);

				// 9
				x7 = BASS_ChannelSetAttribute(streamFXOboe, BASS_ATTRIB_TEMPO, tempo);
				y7 = BASS_ChannelSetAttribute(streamFXOboe, BASS_ATTRIB_VOL, tmp->instrumentsArr[9]);

				// 5
				x8 = BASS_ChannelSetAttribute(streamFXPercussion, BASS_ATTRIB_TEMPO, tempo);
				y8 = BASS_ChannelSetAttribute(streamFXPercussion, BASS_ATTRIB_VOL, tmp->instrumentsArr[5]);

				// 0
				x9 = BASS_ChannelSetAttribute(streamFXViola, BASS_ATTRIB_TEMPO, tempo);
				y9 = BASS_ChannelSetAttribute(streamFXViola, BASS_ATTRIB_VOL, tmp->instrumentsArr[0]);

				// 6
				x10 = BASS_ChannelSetAttribute(streamFXVioline1, BASS_ATTRIB_TEMPO, tempo);
				y10 = BASS_ChannelSetAttribute(streamFXVioline1, BASS_ATTRIB_VOL, tmp->instrumentsArr[6]);

				// 7
				x11 = BASS_ChannelSetAttribute(streamFXVioline2, BASS_ATTRIB_TEMPO, tempo);
				y11 = BASS_ChannelSetAttribute(streamFXVioline2, BASS_ATTRIB_VOL, tmp->instrumentsArr[7]);

				if (x == false || x1 == false || x2 == false || x3 == false || x4 == false || x5 == false || x6 == false || x7 == false || x8 == false || x9 == false || x10 == false || x11 == false ||
					y == false || y1 == false || y2 == false || y3 == false || y4 == false || y5 == false || y6 == false || y7 == false || y8 == false || y9 == false || y10 == false || y11 == false) {
					cout << "There is some error while init BASS:" << BASS_ErrorGetCode() << endl;
					return;
				}

				//Waits until song/audio file ends.
				Sleep(500);
			}
			BASS_Free();
			tmp->start = 0;
			tmp->counter = 0;
			for (int i = 0; i < 12; i++) {
				tmp->instrumentsArr[i] = 1;
			}
			t_o = clock() - t_o;
			printf("It took me %d clicks (%f seconds).\n", t_o, ((float)t_o) / CLOCKS_PER_SEC);
		}
	}
}

void task2(ofApp* tmp) {

}
//========================================================================
int main() {
	// <-------- setup the GL context

	ofSetupOpenGL(1440, 1080, OF_WINDOW);
	ofApp* tmp = new ofApp();
	thread t1(task1, tmp);
	ofRunApp(tmp);

	t1.join();
	//t2.join();

	return 0;
}
