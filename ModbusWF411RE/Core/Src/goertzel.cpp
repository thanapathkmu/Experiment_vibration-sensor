#include "goertzel.h"
#include <math.h>

void Goertzel_Init(Goertzel *goertzel, int numberOfCalculation) {
    goertzel->N = numberOfCalculation; // Block size
    Goertzel_ResetGoertzel(goertzel);
}

void Goertzel_ResetGoertzel(Goertzel *goertzel) {
    goertzel->Q2 = 0;
    goertzel->Q1 = 0;
}

void Goertzel_SetNumberCalculation(Goertzel *goertzel, int numberOfCalculation) {
    goertzel->N = numberOfCalculation;
}

void Goertzel_SetSamplingRate(Goertzel *goertzel, float samplingRate) {
    goertzel->SAMPLING_RATE = samplingRate;
}

/* Call this once, to precompute the constants. */
void Goertzel_InitGoertzel(Goertzel *goertzel, float TARGET_FREQUENCY) {
    FLOATING k;
    FLOATING floatN;
    FLOATING omega;
    FLOATING sine;
    FLOATING cosine;
    
    floatN = (FLOATING)goertzel->N;
    k = (0.5f + ((floatN * TARGET_FREQUENCY) / goertzel->SAMPLING_RATE));
    omega = (2.0f * PI * k) / floatN;
    sine = sin(omega);
    cosine = cos(omega);
    goertzel->coeff = 2.0f * cosine;
    Goertzel_ResetGoertzel(goertzel);
}

/* Call this routine for every sample. */
void Goertzel_ProcessSample(Goertzel *goertzel, float sample) {
    FLOATING Q0;
    Q0 = goertzel->coeff * goertzel->Q1 - goertzel->Q2 + (FLOATING)sample;
    goertzel->Q2 = goertzel->Q1;
    goertzel->Q1 = Q0;
}

/* Optimized Goertzel */
/* Call this after every block to get the RELATIVE magnitude squared. */
float Goertzel_GetMagnitudeSquared(Goertzel *goertzel) {
    FLOATING result;
    result = goertzel->Q1 * goertzel->Q1 + goertzel->Q2 * goertzel->Q2 - goertzel->Q1 * goertzel->Q2 * goertzel->coeff;
    return result;
}

/*** End of Goertzel-specific code, the remainder is test code. */

float Goertzel_Goertzel_Magnitude(Goertzel *goertzel, float *signal, int size) {
    int index;
    int maxIndex;
    float magnitude;
    maxIndex = size / sizeof(signal);
    /* Process the samples */
    for (int runIndex = 0; runIndex < goertzel->N; runIndex++) {
        index = runIndex % maxIndex;
        Goertzel_ProcessSample(goertzel, signal[index]);
    }

    /* Do the "optimized Goertzel" processing */
    magnitude = sqrt(Goertzel_GetMagnitudeSquared(goertzel));
    Goertzel_ResetGoertzel(goertzel);
    return magnitude;
}
