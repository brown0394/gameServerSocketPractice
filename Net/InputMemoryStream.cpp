#include "InputMemoryStream.h"

uint32_t InputMemoryStream::GetRemainingDataSize() const {
	return mCapacity - mHead; 
}
void InputMemoryStream::Read(void* outData, uint32_t inByteCount) {
	if (mHead + inByteCount < mCapacity) {
		std::memcpy(outData, mBuffer + mHead, inByteCount);
		mHead += inByteCount;
	}
};

void InputMemoryStream::Read(uint32_t& outData) { 
	Read(&outData, sizeof(outData));
}

void InputMemoryStream::Read(int32_t& outData) {
	Read(&outData, sizeof(outData));
}

template<typename T>
void InputMemoryStream::Read(T& outData) {
	Read(&outData, sizeof(outData));
}

void InputMemoryStream::ResetHead() {
	mHead = 0;
}

InputMemoryStream::InputMemoryStream(uint32_t inByteCount) : mCapacity(inByteCount), mHead(0) {
	mBuffer = static_cast<char*>(std::malloc(mCapacity));
}

uint32_t InputMemoryStream::getCapacity() {
	return mCapacity;
}

char* InputMemoryStream::getBufferPtr() {
	return mBuffer;
}

template<typename T>
void InputMemoryStream::Read(std::vector<T>& outVector) {
	size_t elementCount;
	Read(elementCount);
	outVector.resize(elementCount);
	for (const T& element : outVector) {
		Read(element);
	}
}
