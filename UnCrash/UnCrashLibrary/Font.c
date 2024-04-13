/*
 * File: Font.h
 *
 * Details : Font image pixel array values
 *
 */

#include "Font.h"

// Alphabet letters pixel array
const uint8_t A[20] =   {255, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0 };
const uint8_t B[20] =   {0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255 };
const uint8_t C[20] =   {255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 255, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t D[20] =   {0, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 0, 255 };
const uint8_t E[20] =   {0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 0, 255, 255, 255, 0, 0, 0, 0 };
const uint8_t F[20] =   {0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 0, 255, 255, 255, 0, 255, 255, 255 };
const uint8_t G[20] =   {255, 0, 0, 255, 0, 255, 255, 255, 0, 255, 0, 0, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t H[20] =   {0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0 };
const uint8_t I[15] =   {0, 0, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 0, 0, 0 };
const uint8_t J[20] =   {255, 255, 255, 0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t K[20] =   {0, 255, 255, 0, 0, 255, 0, 255, 0, 0, 255, 255, 0, 255, 0, 255, 0, 255, 255, 0 };
const uint8_t L[20] =   {0, 255, 255, 255, 0, 255, 255, 255, 0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0 };
const uint8_t M[25] =   {0, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 255, 0, 0, 255, 255, 255, 0, 0, 255, 255, 255, 0 };
const uint8_t N[20] =   {0, 255, 255, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0 };
const uint8_t O[20] =   {255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t P[20] =   {0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 255, 255, 0, 255, 255, 255 };
const uint8_t Q[20] =   {255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 255, 255, 0, 255, 0 };
const uint8_t R[20] =   {0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 0, 255, 255, 0 };
const uint8_t S[20] =   {255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255 };
const uint8_t T[25] =   {0, 0, 0, 0, 0, 255, 255, 0, 255, 255, 255, 255, 0, 255, 255, 255, 255, 0, 255, 255, 255, 255, 0, 255, 255 };
const uint8_t U[20] =   {0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t V[25] =   {0, 255, 255, 255, 0, 0, 255, 255, 255, 0, 255, 0, 255, 0, 255, 255, 0, 255, 0, 255, 255, 255, 0, 255, 255 };
const uint8_t W[25] =   {0, 255, 255, 255, 0, 0, 255, 255, 255, 0, 0, 255, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0 };
const uint8_t X[20] =   {0, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0 };
const uint8_t Y[25] =   {0, 255, 255, 255, 0, 0, 255, 255, 255, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 255, 255, 0, 255, 255 };
const uint8_t Z[20] =   {0, 0, 0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0 };

const uint8_t *const Alphabet[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O ,P, Q, R, S, T, U, V, W, X, Y, Z};

// Numbers pixel array
const uint8_t Num0[20] =  {255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t Num1[15] =  {255, 0, 255, 0, 0, 255, 255, 0, 255, 255, 0, 255, 0, 0, 0 };
const uint8_t Num2[20] =  {255, 0, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 0, 0, 0 };
const uint8_t Num3[20] =  {255, 0, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t Num4[20] =  {255, 255, 0, 255, 255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0, 255, 255, 0, 255 };
const uint8_t Num5[20] =  {0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255 };
const uint8_t Num6[20] =  {255, 0, 0, 255, 0, 255, 255, 255, 0, 0, 0, 255, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t Num7[20] =  {0, 0, 0, 255, 255, 255, 255, 0, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 0, 255 };
const uint8_t Num8[20] =  {255, 0, 0, 255, 0, 255, 255, 0, 255, 0, 0, 255, 0, 255, 255, 0, 255, 0, 0, 255 };
const uint8_t Num9[20] =  {255, 0, 0, 255, 0, 255, 255, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 0, 255 };

const uint8_t *const Digits[10] = {Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9};
