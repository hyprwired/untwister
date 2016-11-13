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

    Heavily based off LSBState.cpp (Copyright Bishop Fox, 2014)
*/

#include "LSBStatePHP5_rand.h"

LSBStatePHP5_rand::LSBStatePHP5_rand()
{
    m_LSB = 0;
    m_isKnown = false;
}
