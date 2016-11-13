/*
    Heavily based off GlibcRand.h (Copyright Bishop Fox 2014)
*/

#ifndef PHP5_RAND_H_
#define PHP5_RAND_H_

#include <algorithm>
#include <random>
#include <deque>
#include "PRNG.h"
#include "LSBStatePHP5_rand.h"

static const std::string PHP5_RAND = "php5-rand";
static const uint32_t PHP5_RAND_STATE_SIZE = 32;

class PHP5_rand: public PRNG
{
public:
    PHP5_rand();
    virtual ~PHP5_rand();

    const std::string getName(void);
    void seed(int64_t value);
    int64_t getSeed(void);
    uint32_t random(void);
    void setBounds(uint32_t, uint32_t);

    int64_t getMinSeed();
    int64_t getMaxSeed();

private:
    uint32_t seedValue;
    uint32_t getStateSize(void);
    void setState(std::vector<uint32_t> inState);
    std::vector<uint32_t> getState(void);

    void setEvidence(std::vector<uint32_t>);

    std::vector<uint32_t> predictForward(uint32_t);
    std::vector<uint32_t> predictBackward(uint32_t);

    bool setLSB(uint32_t index, uint32_t value);
    void setLSBxor(uint32_t index1, uint32_t index2);
    void setLSBor(uint32_t index1, uint32_t index2);
    bool handleRemainder(uint32_t index, std::vector<uint32_t>);

    void tune(std::vector<uint32_t>, std::vector<uint32_t>);
    void tune_repeatedIncrements();
    void tune_chainChecking();

    bool isInitState(std::deque<uint32_t> *);

    bool reverseToSeed(int64_t *, uint32_t);

    /* Keeps track of what LSBs are known */
    std::vector<LSBStatePHP5_rand> m_LSBMap;
    int32_t m_glibcstate[32];
    int32_t *m_fptr;
    int32_t *m_rptr;
};

#endif /* PHP5_RAND_H_ */
