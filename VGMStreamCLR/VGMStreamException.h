#pragma once

namespace VGMStreamCLR {
	using namespace System;

	public ref class VGMStreamException : Exception {
	public:
		VGMStreamException(String^ message) : Exception(message) { }
	};
}
