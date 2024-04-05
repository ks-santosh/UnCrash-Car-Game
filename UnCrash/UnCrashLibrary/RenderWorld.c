//
// Generated 16 bit random number using Linear-Feedback Shift Register
//
uint16_t GetRandomNumber() {

	// seed for random number generation
	static uint16_t RandStart = 0xACE1u;

	uint16_t RandNum = RandStart;

	uint16_t feedback;

	/* taps: 16 15 feedback polynomial: x^16 + x^15 + 1 */
	feedback = ((RandNum >> 0) ^ (RandNum >> 1)) & 1u;
	RandNum = (RandNum >> 1) | (feedback << 7);

	RandStart = RandNum;

	return RandNum;
}

//
//	Creates game world blocks to be rendered
//
void SetWorldBlock(WorldBlock *Block) {

	uint16_t RandNum = GetRandomNumber();

	// Get the obstacle placement type : bits 0,1,2
	uint8_t ObsPlaceType = (RandNum & 7u);
	if(ObsPlaceType == 7) {
		ObsPlaceType = 5;
	}
	Block->ObsPlaceType = ObsPlaceType;

	// Get the coin placement type : bits 3,4,5
	Block->CoinPlaceType = ((RandNum >> 3) & 7u);
	// Get the first Obstacle type : bits 6,7,8
	Block->ObsType1 = ((RandNum >> 6) & 7u);
	// Get the second Obstacle type : bits 9,10,1
	Block->ObsType2 = ((RandNum >> 9) & 7u);
	// Set start and end rows to be rendered between;
	Block->Start = 0;
	Block->End = 63;
}
