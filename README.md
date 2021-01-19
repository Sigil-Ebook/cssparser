CSSParser - A Simple C++ CSS Parser                                                                                       ===================================                                  

CSSParser is a free, open source, multi-platform simpole C++ based CSS Parser
that only uses the std:: library.

It's code was initially extracted from CSSTidy and then reworked.
     
    CSSTidy (https://github.com/csstidy-c/csstidy)

    CSSTidy Portions Copyright:
       * Florian Schmitz <floele@gmail.com>
       * Thierry Charbonnel
       * Will Mitchell <aethon@gmail.com>
       * Brett Zamir <brettz9@yahoo.com>
       * sined_ <sined_@users.sourceforge.net>
       * Dmitry Leskov <git@dmitryleskov.com>
       * Kevin Coyner <kcoyner@debian.org>
       * Tuukka Pasanen <pasanen.tuukka@gmail.com>
       * Frank W. Bergmann <csstidy-c@tuxad.com>
       * Frank Dana <ferdnyc@gmail.com>
  
       The CSSTidy codebase is itself is Available under the LGPL 2.1
 

Interface
=========

The best way to understand the parser interface is to examine main.cpp
which is excerpted below:

[CODE SNIPPETS]
    
        CSSParser csst;

        css_file = CSSUtils::file_get_contents(argv[1]);

        // valid css levels are "CSS1.0", "CSS2.0", "CSS2.1", "CSS3.0" 
        csst.set_level("CSS3.0");

        // do the actual parsing
        csst.parse_css(css_file);

        // check for any parse errors
        std::vector<std::string> errors = csst.get_parse_errors();

        // check for any parse warnings
        std::vector<std::string> warnings = csst.get_parse_warnings();

        // check for any parse information messages
        std::vector<std::string> infos = csst.get_parse_info();

        // get any @charset without having to walk the csstokens list
        std::string cset = csst.get_charset();

        // get all @import without having to walk the csstokens list
        std::vector<std::string> imports = csst.get_import();

        // get any @namespace without having to walk the csstokens list
        std::string ns = csst.get_namespace();

        // enum token_type
        // {
        //    CHARSET, IMPORT, NAMESP, AT_START, AT_END, SEL_START, SEL_END, PROPERTY, VALUE, COMMENT, CSS_END
        // };

        // struct token
        // {
        //    token_type type;
        //    int pos; // position in input string
        //    int line; // line number in input string
        //    std::string data;
        // };

        // now walk the sequence of parsed tokens
        // if you know the location of the token you want in the sequence (starting with 0)
        // simply pass start_ptr in get_next_token set to a valid starting point in the token sequence

        CSSParser::token atoken = csst.get_next_token();
    
        while(atoken.type != CSSParser::CSS_END) {
    
            std::string ttype = csst.get_type_name(atoken.type);

            std::cout << "Pos: " << atoken.pos
                      << " Line: " << atoken.line
                      << " Type: " << ttype
                      <<"  Data: " << atoken.data << std::endl;
    
            atoken = csst.get_next_token();
        }

        // serialize back to CSS
        std::string cssout;
        cssout = csst.serialize_css();
    
[/CODE SNIPPETS] 


Build and Install
=================

There is a very simplistic Linux/MacOS Makefile and a Windows Makefile using nmake


License
=======

Like the CSSTidy codebase it was derived from, CSSParser is licensed under
the LGPLv2.1 or later. The complete license is located in LICENSE.
