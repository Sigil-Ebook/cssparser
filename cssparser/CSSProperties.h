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

#pragma once
#ifndef CSS_PROPERTIES_H
#define CSS_PROPERTIES_H

#include <cstdlib>
#include <string> 
#include <map>

/**
 * Singleton.
 *
 * CSSProperties
 */
 

class CSSProperties
{

public:

    static CSSProperties *instance();

    bool contains(std::string pname);

    std::string levels(std::string pname);

private:

    CSSProperties();

    std::map<std::string, std::string> m_all_properties;
    static CSSProperties *m_instance;
};

#endif // CSS_PROPERTIES_H
