#pragma once
#include <memory>
class OutputMemoryBitStream
{
public:
	OutputMemoryBitStream();
	~OutputMemoryBitStream();
	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);
	const char* GetBufferPtr() const;
	uint32_t GetBitLength() const;
	uint32_t GetByteLength() const;
	void WriteBytes(const void* inData, size_t inByteCount);
	template<typename T>
	void Write(T inData, size_t inBitCount = sizeof(T) * 8);
	inline uint32_t ConvertToFixed(float inNumber, float inMin, float inPrecision);
	inline float ConvertFromFixed(uint32_t inNumber, float inMin, float inPrecision);
private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
};

//only in little endian