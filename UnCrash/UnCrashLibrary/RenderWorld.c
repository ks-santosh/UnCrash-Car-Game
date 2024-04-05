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
