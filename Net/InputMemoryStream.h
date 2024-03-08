#pragma once
#include <memory>
class InputMemoryStream
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount) :
		mCapacity(inByteCount), mHead(0), mBuffer(inBuffer) {}
	~InputMemoryStream() { std::free(mBuffer); }
	uint32_t GetRemainingDataSize() const;
	void Read(void* outData, uint32_t inByteCount);
	void Read(uint32_t& outData);
	void Read(int32_t& outData);
	void ResetHead();
private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

