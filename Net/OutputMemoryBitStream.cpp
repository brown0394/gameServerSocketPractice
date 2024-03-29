#include "OutputMemoryBitStream.h"

OutputMemoryBitStream::OutputMemoryBitStream() { 
	ReallocBuffer(256);
}

OutputMemoryBitStream::~OutputMemoryBitStream() {
	std::free(mBuffer);
}
void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount) {
	uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);
	if (nextBitHead > mBitCapacity) {
		ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));
	}
	//calculate the byteOffset into our buffer 
	//by dividing the head by 8 
	//and the bitOffset by taking the last 3 bits 
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;
	//calculate which bits of the current byte to preserve 
	uint8_t currentMask = ~(0xff << bitOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask)
		| (inData << bitOffset);
	//calculate how many bits were not yet used in 
	//our target byte in the buffer 
	uint32_t bitsFreeThisByte = 8 - bitOffset;
	//if we needed more than that, carry to the next byte 
	if (bitsFreeThisByte < inBitCount) {
		//we need another byte 
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}
	mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void* inData, size_t inBitCount) {
	const char* srcByte = static_cast<const char*>(inData);
	//write all the bytes 
	while (inBitCount > 8) {
		WriteBits(*srcByte, 8);
		++srcByte;
		inBitCount -= 8;
	}
	//write anything left
	if (inBitCount > 0) {
		WriteBits(*srcByte, inBitCount);
	}
}

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitCapacity) {
	void* realloced = std::realloc(mBuffer, inNewBitCapacity);
	if (realloced != nullptr) {
		mBuffer = static_cast<char*>(realloced);
		mBitCapacity = inNewBitCapacity;
	}
	else {
		//handle realloc failure 
		//...
	}
}
const char* OutputMemoryBitStream::GetBufferPtr() const { 
	return mBuffer; 
}

uint32_t OutputMemoryBitStream::GetBitLength() const {
	return mBitHead; 
}

uint32_t OutputMemoryBitStream::GetByteLength() const {
	return (mBitHead + 7) >> 3; 
}

void OutputMemoryBitStream::WriteBytes(const void* inData, size_t inByteCount) {
	WriteBits(inData, inByteCount << 3);
}

template<typename T>
void OutputMemoryBitStream::Write(T inData, size_t inBitCount)
{
	static_assert(std::is_arithmetic<T>::value ||
		std::is_enum<T>::value,
		"Generic Write only supports primitive data types");
	WriteBits(&inData, inBitCount);
}

uint32_t OutputMemoryBitStream::ConvertToFixed(float inNumber, float inMin, float inPrecision) {
	return static_cast<uint32_t> ((inNumber - inMin) / inPrecision);
}

float OutputMemoryBitStream::ConvertFromFixed(uint32_t inNumber, float inMin, float inPrecision) {
	return static_cast<float>(inNumber) * inPrecision + inMin;
}