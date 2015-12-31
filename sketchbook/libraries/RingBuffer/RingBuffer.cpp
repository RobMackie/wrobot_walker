#include "RingBuffer.h"

//public:
RingBuffer::RingBuffer(void)
{
    this->clear();
}

RingBuffer::~RingBuffer(void)
{
    this->clear();
}

bool RingBuffer::write(int value)
{
    if (spaceAvailable()) {
        modularIncrement(head);
	buffer[head] = value;
	return (true);
    } else {
	return (false);
    }
}

bool RingBuffer::read(int &value)
{
    if (dataAvailable()) {
        value = buffer[tail];
	modularIncrement(tail);
        return (true);
    } else {
        return (false);
    }
}

void RingBuffer::clear()
{
    memset(buffer,0, SIZE);
    head = 0;
    tail = 0;
    overflow = 0;
}

void markOverflow()
{
    overflow++;
}

int getOverflow()
{
    int result = overflow;
    overflow = 0;
    return (result);
}


//private:
bool RingBuffer::dataAvailable()
{
   return (head != tail);
}

bool RingBuffer::spaceAvailable()
{
   // predict where the head will be if we increment it
   int cursor = head;
   cursor = (cursor+1)%SIZE;
   // if the head collides with the tail after we increment it, 
   // then there is no room
   return (cursor == tail);
}

int RingBuffer::modularIncrement(int &value) 
{
   cursor = (cursor+1)%SIZE;
}


