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
*/

#ifndef DOTNETSYSTEMRANDOM_H_
#define DOTNETSYSTEMRANDOM_H_

#include <climits>
#include <string>
#include <vector>
#include "PRNG.h"

static const std::string DOTNET_SYSTEMRANDOM = "dotnet-systemrandom";
static const uint32_t DOTNET_STATE_SIZE = 2147483647;  // State inference attack not yet implemented.

class DotNetSystemRandom: public PRNG {
 public:
    DotNetSystemRandom();
    virtual ~DotNetSystemRandom();

    const std::string getName(void);
    void seed(int64_t value);
    int64_t getSeed(void);
    uint32_t random(void);
    void setBounds(uint32_t, uint32_t);

    int64_t getMinSeed();
    int64_t getMaxSeed();

 private:
    uint32_t getStateSize(void);
    void setState(std::vector<uint32_t> inState);
    std::vector<uint32_t> getState(void);

    void setEvidence(std::vector<uint32_t>);

    std::vector<uint32_t> predictForward(uint32_t);
    std::vector<uint32_t> predictBackward(uint32_t);

    void tune(std::vector<uint32_t>, std::vector<uint32_t>);

    bool reverseToSeed(int64_t *, uint32_t);

    // Specific System.Random methods.

    double Sample(void);
    int32_t InternalSample(void);
    double GetSampleForLargeRange(void);

    // Based off System.Random Private Constants

    static const int32_t MBIG = INT_MAX;  // Int32.MaxValue, 0x7FFFFFFF
    static const int32_t MSEED = 161803398;
    static const int32_t MZ = 0;

    // Based off System.Random Member Variables

    uint32_t inext;
    uint32_t inextp;
    int32_t SeedArray[56];
};

#endif /* DOTNETSYSTEMRANDOM_H_ */
