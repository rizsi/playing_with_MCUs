

#include <stdint.h>

class Serial
{
public:
	Serial() { }
	~Serial() { }
	void begin(uint32_t baudrate);
	static void end();
	int peek();
	int peek(uint8_t offset);
	int read();
	int available();
	int availableForWrite();
	void write(uint8_t byte);
	void writeString(const char * str);
	uint8_t writeNumber(uint32_t v);
	void writeBin(uint8_t data);


	void flush();
	/// Wait until all bytes are sent
	void flushWrite();
	/// Delete all received bytes in the input buffer
	void flushRead();
	static void flushInput();
	static void flushOutput();
	/// Is transfer currently active?
	bool isTxOn();
	/// The number of bytes received altogether. May overflow.
	uint16_t getReceiveCounter();
};
