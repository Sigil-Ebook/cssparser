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

#include <cstdlib>
#include <string> 
#include <iterator>
#include <utility>
#include <vector>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "CSSProperties.h"
#include "CSSUtils.h"
#include "CSSParser.h"

int main(int argc, char *argv[])
{
    CSSParser csst;

    if(argc > 1)
    {
        std::string filein = argv[1];
        if(filein != "-" && !CSSUtils::file_exists(argv[1]))
        {
            std::cout << "The file \"" << filein << "\" does not exist." << std::endl;
            return EXIT_FAILURE;
        }
        
        std::string output_filename;
        
        for(int i = 2; i < argc; ++i)
        {
            bool output_file = true;
            if(output_file)
            {
                output_filename = CSSUtils::trim(argv[i]);
            }
        }
        
        std::string css_file;
        if(filein == "-")
        {
            std::string temp;
            do {
                getline(std::cin, temp, '\n');
                css_file += (temp + "\n");
            } while(std::cin);
        }
        else
        {
            css_file = CSSUtils::file_get_contents(argv[1]);
        }

        // The interface


        // valid css levels are "CSS1.0", "CSS2.0", "CSS2.1", "CSS3.0" 
        csst.set_level("CSS3.0");

        // do the actual parsing
        csst.parse_css(css_file);

        // check for any parse errors
        std::vector<std::string> errors = csst.get_parse_errors();
        std::cout << "Errors: " << errors.size() << std::endl;
        for(int i = 0; i < errors.size(); i++) {
            std::cout << "  Error: " << errors[i] << std::endl;
        }

        // check for any parse warnings
        std::vector<std::string> warnings = csst.get_parse_warnings();
        std::cout << "Warnings: " << warnings.size() << std::endl;
        for(int i = 0; i < warnings.size(); i++) {
            std::cout << "  Warning: " << warnings[i] << std::endl;
        }

        // check for any parse information messages
        std::vector<std::string> infos = csst.get_parse_info();
        std::cout << "Information: " << infos.size() << std::endl;
        for(int i = 0; i < infos.size(); i++) {
            std::cout << "  Information: " << infos[i] << std::endl;
        }

        // get any @charset without having to walk the csstokens list
        std::string cset = csst.get_charset();
        if (!cset.empty()) std::cout << "charset: " << cset << std::endl;

        // get all @import without having to walk the csstokens list
        std::vector<std::string> imports = csst.get_import();
        for(int i = 0; i < imports.size(); i++) {
            std::cout << "import: " << imports[i] << std::endl;
        }

        // get any @namespace without having to walk the csstokens list
        std::string ns = csst.get_namespace();
        if (!ns.empty()) std::cout << "namespace: " << ns << std::endl;
        
        // The possible token type are an enum:
        // enum token_type:
        //
        //     CHARSET   =  0
        //     IMPORT    =  1
        //     NAMESP    =  2
        //     AT_START  =  3
        //     AT_END    =  4
        //     SEL_START =  5
        //     SEL_END   =  6
        //     PROPERTY  =  7
        //     VALUE     =  8
        //     COMMENT   =  9
        //     CSS_END   = 10

        // now walk the sequence of parsed tokens
        // if you know the location of the token you want in the sequence (starting with 0)
        // simply pass start_ptr in get_next_token set to a valid starting point in the token sequence

        CSSParser::token atoken = csst.get_next_token();
        while(atoken.type != CSSParser::CSS_END) {
            std::string ttype = csst.get_type_name(atoken.type);
            std::cout << "Pos: " << atoken.pos << " Line: " << atoken.line << " Type: " << ttype
                      <<"  Data: " << atoken.data << std::endl;
            atoken = csst.get_next_token();
        }

        // serialize CSS to stdout if no output file is specified
        std::string cssout;
        if(output_filename == "")
        {
            cssout = csst.serialize_css();
        }
        else
        {
            cssout = csst.serialize_css(output_filename, false);
        }
        
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
