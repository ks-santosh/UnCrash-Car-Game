//
// Sets the design and placement of game world's basic blocks
//
typedef struct WorldBlock {
	uint8_t ObsPlaceType;	// Obstacle placement type
	uint8_t CoinPlaceType;	// Coin placement type
	uint8_t ObsType1;
	uint8_t ObsType2;

} WorldBlock;

//
// Generates random number using Linear-Feedback Shift Register
// - returns 16 bit random number
//
uint16_t GetRandomNumber();

//
//	Creates game world blocks to be rendered
//	- no returns as the value is directly written to address
void SetWorldBlock(WorldBlock *Block);
