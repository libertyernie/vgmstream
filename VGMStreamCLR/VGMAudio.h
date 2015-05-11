#pragma once

#include <msclr\marshal.h>

extern "C" {
#include "../src/vgmstream.h"
#include "../src/util.h"
}

#include "VGMStreamException.h"

namespace VGMStreamCLR {
	using namespace System;
	using namespace msclr::interop;

	public ref class VGMAudio {
	private:
		VGMSTREAM* instance;
		marshal_context mcontext;
		bool is_disposed;
	public:
		property bool Looped {
			bool get() {
				return instance->loop_flag;
			}
		}
		property int LoopStart {
			int get() {
				return instance->loop_start_sample;
			}
		}
		property int LoopEnd {
			int get() {
				return instance->loop_end_sample;
			}
		}
		property int NumSamples {
			int get() {
				return instance->num_samples;
			}
		}
		property int SampleRate {
			int get() {
				return instance->sample_rate;
			}
		}
		property int Channels {
			int get() {
				return instance->channels;
			}
		}

		/* do format detection, return object holding a pointer to a usable VGMSTREAM, or throw VGMStreamException on failure */
		VGMAudio(String^ filename) : is_disposed(false) {
			instance = init_vgmstream(mcontext.marshal_as<const char*>(filename));
			if (instance == nullptr) {
				throw gcnew VGMStreamException("A null pointer was returned from init_vgmstream");
			}
		}

		/* reset a VGMSTREAM to start of stream */
		void Reset() {
			reset_vgmstream(instance);
		}

		/* calculate the number of samples to be played based on looping parameters */
		int32_t GetPlaySamples(double looptimes, double fadeseconds, double fadedelayseconds) {
			return get_vgmstream_play_samples(looptimes, fadeseconds, fadedelayseconds, instance);
		}

		/* render! */
		void Render(sample* buffer, int32_t sample_count) {
			render_vgmstream(buffer, sample_count, instance);
		}

		/* make a header for PCM .wav */
		static array<uint8_t>^ MakeWavHeader(int32_t sample_count, int32_t sample_rate, int channels) {
			array<uint8_t>^ arr = gcnew array<uint8_t>(0x2C);
			pin_ptr<uint8_t> pin = &arr[0];
			make_wav_header(pin, sample_count, sample_rate, channels);
			return arr;
		}

		/* dispose: call finalizer to close/deallocate VGMSTREAM */
		~VGMAudio() {
			if (is_disposed) return;
			this->!VGMAudio();
			is_disposed = true;
		}

		/* finalize: close/deallocate VGMSTREAM */
		!VGMAudio() {
			close_vgmstream(instance);
		}
	};
}
