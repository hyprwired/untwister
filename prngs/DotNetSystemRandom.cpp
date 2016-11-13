/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------------------
    Some code based off System.Random code located at:
        https://github.com/dotnet/coreclr/blob/master/src/mscorlib/src/System/Random.cs

    Above System.random code licensed under MIT license:
    "
        The MIT License (MIT)

        Copyright (c) .NET Foundation and Contributors

        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
    "
-----------------------------------------------------------------------------------------
    Implements System.Random() C# method, using Next(), and Next(min, max).

*/

#include <climits>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "DotNetSystemRandom.h"
#include "../ConsoleColors.h"

DotNetSystemRandom::DotNetSystemRandom() {}

DotNetSystemRandom::~DotNetSystemRandom() {}

const std::string DotNetSystemRandom::getName() {
    return DOTNET_SYSTEMRANDOM;
}

// Based off System.Random Random()
void DotNetSystemRandom::seed(int64_t Seed) {
    uint32_t ii = 0;
    uint32_t i, k, n; // Used in loops
    int32_t mj, mk;

    int32_t subtraction = (Seed == INT_MIN) ? INT_MAX : std::abs(Seed);
    mj = MSEED - subtraction;
    SeedArray[55] = mj;
    mk = 1;
    
    for (i = 1; i < 55; i++) {
      if ((ii += 21) >= 55) ii -= 55;
      SeedArray[ii] = mk;
      mk = mj - mk;
      if (mk < 0) mk+=MBIG;
      mj = SeedArray[ii];
    }
    
    for (k = 1; k < 5; k++) {
      for (i = 1; i < 56; i++) {
        n = i + 30;
        if (n >= 55) n -= 55;
        SeedArray[i] -= SeedArray[1 + n];
        if (SeedArray[i] < 0) SeedArray[i]+=MBIG;
      }
    }
    inext = 0;
    inextp = 21;
    Seed = 1;
}
// Based off System.Random->Sample()
double DotNetSystemRandom::Sample() {
    return (DotNetSystemRandom::InternalSample()*(1.0/MBIG));
}

// Based off System.Random->InternalSample()
int32_t DotNetSystemRandom::InternalSample() {
    int32_t retVal;
    uint32_t locINext = inext;
    uint32_t locINextp = inextp;

    if (++locINext >= 56) locINext = 1;
    if (++locINextp >= 56) locINextp = 1;

    retVal = SeedArray[locINext]-SeedArray[locINextp];

    if (retVal == MBIG) retVal--;
    if (retVal < 0) retVal+=MBIG;

    SeedArray[locINext] = retVal;

    inext = locINext;
    inextp = locINextp;

    return retVal;
}

// Based off System.Random->GetSampleForLargeRange()
double DotNetSystemRandom::GetSampleForLargeRange() {
    bool negative;

    int32_t result = DotNetSystemRandom::InternalSample();

    negative = (DotNetSystemRandom::InternalSample()%2 == 0) ? true : false;
    if (negative) {
      result = -result;
    }
    double d = result;
    d += (INT_MAX - 1);
    d /= 2*(uint32_t)INT_MAX - 1;
    return d;
}

/* 
    Based off System.Random->Next(), System.Random->Next(minValue, maxValue)
    Known limitations; can only return positive numbers (uint32_t) due to 
    PRNG class virtual uint32_t random(void).

*/
uint32_t DotNetSystemRandom::random() {
    uint32_t randomResult;

    if (m_isBounded) {
        // Based off System.Random->Next(minValue, maxValue)
        int64_t range = (int64_t)m_maxBound - m_minBound;
        if (range <= (int64_t)INT_MAX) {
          randomResult = ((int32_t)(DotNetSystemRandom::Sample() * range) + m_minBound);
        } else {
          randomResult = (int32_t)((int64_t)(DotNetSystemRandom::GetSampleForLargeRange() * range) + m_minBound);
        }
    } else {
        // Based off System.Random->Next()
        randomResult = DotNetSystemRandom::InternalSample();
    }

    return randomResult;
}

void DotNetSystemRandom::setBounds(uint32_t min, uint32_t max) {
    m_minBound = min;
    m_maxBound = max;
    m_isBounded = true;
}

int64_t DotNetSystemRandom::getMinSeed() {
    // System.Random() is seeded with an int; signed integer
    return 0;
}

int64_t DotNetSystemRandom::getMaxSeed() {
    // System.Random() is seeded with an int; signed integer
    return INT_MAX;
}


// Placeholder methods, aren't doing anything yet

// State inference attack not yet implemented
uint32_t DotNetSystemRandom::getStateSize(void) {
    return DOTNET_STATE_SIZE;
}

int64_t DotNetSystemRandom::getSeed() {
    return 0;
}

void DotNetSystemRandom::setState(std::vector<uint32_t> inState) {}

std::vector<uint32_t> DotNetSystemRandom::getState(void) {
    std::vector<uint32_t> ret;
    return ret;
}

void DotNetSystemRandom::setEvidence(std::vector<uint32_t> evidence) {}

std::vector<uint32_t> DotNetSystemRandom::predictForward(uint32_t length) {
    std::vector<uint32_t> ret;
    return ret;
}

std::vector<uint32_t> DotNetSystemRandom::predictBackward(uint32_t length) {
    std::vector<uint32_t> ret;
    return ret;
}

void DotNetSystemRandom::tune(std::vector<uint32_t> evidenceForward, std::vector<uint32_t> evidenceBackward) {}

bool DotNetSystemRandom::reverseToSeed(int64_t *outSeed, uint32_t depth) {
    return false;
}
