class RingBuffer {

    public:
        RingBuffer(void);
        ~RingBuffer(void);

        bool write(int value);
        bool read(int &value);

	bool dataAvailable();
        bool spaceAvailable();

        void clear();
	void markOverflow();
	int getOverflow();

    private:
       int modularIncrement(int &value);
       
       const int const SIZE=256;
       int ring[RingBuffer::SIZE];
       int head;
       int tail;
       int overflow;
}
