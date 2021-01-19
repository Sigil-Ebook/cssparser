/************************************************************************
 **
 **  CSSParser
 **  A Simple C++ CSS Parser
 **
 **  Copyright (C) 2021  Kevin B. Hendricks, Stratford, Ontario, Canada
 **
 **  License: LGPL v2.1 or later
 **
 **  Extracted and modified from:
 **  CSSTidy (https://github.com/csstidy-c/csstidy)
 **
 **  CSSTidy Portions Copyright:
 **     Florian Schmitz <floele@gmail.com>
 **     Thierry Charbonnel
 **     Will Mitchell <aethon@gmail.com>
 **     Brett Zamir <brettz9@yahoo.com>
 **     sined_ <sined_@users.sourceforge.net>
 **     Dmitry Leskov <git@dmitryleskov.com>
 **     Kevin Coyner <kcoyner@debian.org>
 **     Tuukka Pasanen <pasanen.tuukka@gmail.com>
 **     Frank W. Bergmann <csstidy-c@tuxad.com>
 **     Frank Dana <ferdnyc@gmail.com>
 **
 **     CSSTidy itself is Available under the LGPL 2.1
 **
 ** You should have received a copy of the GNU Lesser General Public License 2.1
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/
 
#ifndef HEADER_CSSUTILS
#define HEADER_CSSUTILS 

#include <cstdlib>
#include <string> 
#include <iterator>
#include <vector>
#include <assert.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

class CSSUtils
{

public:

    // Returns the lowercase version of a string
    static std::string strtolower(std::string istring);

    // Apparently faster replacement for tolower
    static char chartolower(const char c);

    // Returns the uppercase version of a string
    static std::string strtoupper(std::string istring);
    static char chartoupper(const char c);

    // Converts a hexadecimal number (string) to a decimal number
    static double hexdec(std::string istring);

    // Converts a char to a string
    static std::string char2str(const char c);

    // Converts a char to a string
    static std::string char2str(const char* c);

    // Get contents of a file
    static std::string file_get_contents(const std::string filename);

    // Checks if a file exists
    static bool file_exists(const char *filename);

    // Checks if a charcter is escaped
    static bool escaped(const std::string &istring, int pos);

    // Returns a char of a std::string at pos but checks the std::string-length before
    static char s_at(const std::string &istring, int pos);

    // Implodes a vector of std::string  e (string join with e as seprator))
    static std::string implode(const std::string e, const std::vector<std::string> s);

    // Explodes a std::string into a vector of std::strings, splitting at s
    static std::vector<std::string> explode(const std::string e, std::string s, const bool check);

    // Builds a compact value std::string, inserting spaces only where necessary
    static std::string build_value(const std::vector<std::string> subvalues);

    // Replaces <find> with <replace> in <str>
    static std::string str_replace(const std::string find, const std::string replace, std::string str);

    // Checks if a std::string exists in a std::string-array
    static bool in_char_arr(const char* haystack, const char needle);
    static bool in_str_array(const std::string& haystack, const char needle);

    // isspace() and isdigit() do not work correctly with UTF-8 std::strings
    static bool ctype_space(const char c);
    static bool ctype_digit(const char c);
    static bool ctype_xdigit(char c);
    static bool ctype_alpha(char c);

    // trims  whitespace at the specific or both ends of a std::string
    static const std::string trim(const std::string istring);
    static const std::string rtrim(const std::string istring);
    static const std::string rtrim(const std::string istring, const std::string chars);
    static const std::string ltrim(const std::string istring);

    // creates proper indent level
    static const std::string indent(int lvl, const std::string &base);
};
#endif // HEADER_CSSUTILS
