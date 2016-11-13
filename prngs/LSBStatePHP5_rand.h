/*
	Heavily based off LSBState.h (Copyright Bishop Fox, 2014)
*/

#include <stdint.h>
#include <vector>

class LSBStatePHP5_rand
{

public:

    LSBStatePHP5_rand();

    /* Other seeds that this one is XOR'd with */
    std::vector<uint32_t> m_xorWith;

    /* Other seeds that this one is XOR'd with */
    std::vector<uint32_t> m_orWith;

    /* Do we know for sure what this LSB is */
    bool m_isKnown;

    /* If we know it, what is the LSB */
    uint32_t m_LSB;
};
