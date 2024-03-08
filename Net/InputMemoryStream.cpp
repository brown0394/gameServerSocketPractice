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

void InputMemoryStream::ResetHead() {
	mHead = 0;
}