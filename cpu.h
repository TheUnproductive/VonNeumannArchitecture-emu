class cpu{
	public:
		void cycle();
		bool load(const char * filename);
		unsigned char R[128];
		unsigned char memory[256];
	
	private:
		unsigned char opcode;
		unsigned char sr;
		unsigned char A;
		unsigned char pc;
		unsigned char cache;
		bool x;
		
		void init();
		
};
