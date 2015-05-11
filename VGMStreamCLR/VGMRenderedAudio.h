#pragma once

#include "VGMAudio.h"

namespace VGMStreamCLR {
	public ref class VGMRenderedAudio {
	private:
		VGMAudio^ original;
		array<sample>^ samples;
		bool is_disposed;
	public:
		VGMRenderedAudio(VGMAudio^ original, int sample_count) {
			this->original = original;

			samples = gcnew array<sample>(sample_count * original->Channels);
			pin_ptr<sample> pin = &samples[0];
			original->Render(pin, sample_count);
		}

		VGMRenderedAudio(VGMAudio^ original) : VGMRenderedAudio(original, Math::Max(original->LoopEnd, original->NumSamples)) {}

		property VGMAudio^ Original {
			VGMAudio^ get() {
				return original;
			}
		}

		array<uint8_t>^ ExportWav(int32_t start_sample, int32_t num_samples) {
			if (start_sample + num_samples > samples->Length / original->Channels) {
				throw gcnew VGMStreamException("Sample index out of range");
			}

			array<uint8_t>^ arr = gcnew array<uint8_t>(0x2C + num_samples * original->Channels * sizeof(sample));
			pin_ptr<uint8_t> pin = &arr[0];
			make_wav_header(pin, num_samples, original->SampleRate, original->Channels);

			pin_ptr<sample> sample_pin = &samples[0];
			memcpy(pin + 0x2C,
				sample_pin + (start_sample * original->Channels),
				num_samples * original->Channels * sizeof(sample));
			return arr;
		}

		array<uint8_t>^ ExportWav() {
			return ExportWav(0, samples->Length / original->Channels);
		}
	};
}
