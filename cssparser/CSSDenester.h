/************************************************************************
 **
 **  CSSDenester.h
 **  Used for the Simple C++ CSS Parser
 **
 **  Copyright (C) 2026  Kevin B. Hendricks, Stratford, Ontario, Canada
 **  Co-authored with Google AI
 **
 **  License: LGPL v2.1 or later
 **
 **  Extracted and modified from code suggestions from Google's Browser AI
 **      and refined by repeated prompts
 **
 ** You should have received a copy of the GNU Lesser General Public License 2.1
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <iomanip>

struct ParseError {
    std::string message;
    size_t line;
    std::string context;
};

class CSSDenester {
private:
    std::vector<ParseError> errors;

    std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        auto end = s.find_last_not_of(" \t\n\r");
        return s.substr(start, end - start + 1);
    }

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            std::string t = trim(item);
            if (!t.empty()) result.push_back(t);
        }
        return result;
    }

    void logError(const std::string& msg, size_t line, const std::string& buffer) {
        // Capture a small snippet of the buffer to help identify the error
        std::string snippet = buffer.substr(0, 20) + (buffer.length() > 20 ? "..." : "");
        errors.push_back({msg, line, trim(snippet)});
    }

public:
    std::string process(const std::string& input) {
        errors.clear();
        std::stringstream output;
        std::vector<std::vector<std::string>> selectorStack;
        std::vector<std::string> atRuleStack;
        std::string buffer;
        size_t currentLine = 1;

        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (c == '\n') currentLine++;

            // 1. Skip Comments and track internal lines
            if (c == '/' && i + 1 < input.size() && input[i + 1] == '*') {
                size_t end = input.find("*/", i + 2);
                if (end == std::string::npos) {
                    logError("Unclosed comment", currentLine, "/*...");
                    break;
                }
                std::string commentBody = input.substr(i, end - i);
                currentLine += std::count(commentBody.begin(), commentBody.end(), '\n');
                i = end + 1;
                continue;
            }

            // 2. Handle Strings (prevents braces inside quotes from breaking logic)
            if (c == '"' || c == '\'') {
                char quote = c;
                buffer += c;
                while (++i < input.size() && input[i] != quote) {
                    if (input[i] == '\\') buffer += input[i++];
                    buffer += input[i];
                    if (input[i] == '\n') currentLine++;
                }
                if (i >= input.size()) logError("Unclosed string literal", currentLine, buffer);
                else buffer += quote;
                continue;
            }

            // 3. Structural Parsing
            if (c == '{') {
                std::string context = trim(buffer);
                if (context.empty()) {
                    logError("Empty block selector", currentLine, "{");
                } else if (context[0] == '@') {
                    atRuleStack.push_back(context);
                } else {
                    selectorStack.push_back(split(context, ','));
                }
                buffer.clear();
            } else if (c == '}') {
                if (selectorStack.empty() && atRuleStack.empty()) {
                    logError("Unexpected closing brace", currentLine, "}");
                } else {
                    if (!selectorStack.empty()) selectorStack.pop_back();
                    else atRuleStack.pop_back();
                }
                buffer.clear();
            } else if (c == ';') {
                if (!buffer.empty()) writeRule(output, buffer, selectorStack, atRuleStack);
                buffer.clear();
            } else {
                buffer += c;
            }
        }

        if (!selectorStack.empty() || !atRuleStack.empty()) {
            logError("Missing closing brace(s)", currentLine, "End of File");
        }

        return output.str();
    }

    void writeRule(std::stringstream& out, const std::string& prop,
                   const std::vector<std::vector<std::string>>& sStack,
                   const std::vector<std::string>& aStack) {

        std::string property = trim(prop);
        if (property.empty()) return;

        // Apply At-Rule wrappers (e.g., @media)
        for (const auto& rule : aStack) out << rule << " { ";

        // Flatten Selector Hierarchy (Cartesian Product for comma-separated selectors)
        std::vector<std::string> paths = {""};
        for (const auto& level : sStack) {
            std::vector<std::string> next;
            for (const auto& p : paths) {
                for (const auto& c : level) {
                    std::string combined;
                    size_t ampPos = c.find('&');
                    if (ampPos != std::string::npos) {
                        combined = c;
                        combined.replace(ampPos, 1, p);
                    } else {
                        combined = p.empty() ? c : p + " " + c;
                    }
                    next.push_back(trim(combined));
                }
            }
            paths = next;
        }

        for (size_t i = 0; i < paths.size(); ++i) {
            out << paths[i] << (i == paths.size() - 1 ? "" : ", ");
        }

        out << " { " << property << "; } ";
        for (size_t i = 0; i < aStack.size(); ++i) out << "}";
        out << "\n";
    }

    void printErrorReport() {
        if (errors.empty()) {
            std::cout << "\n[Success] No syntax errors found.\n";
            return;
        }
        std::cout << "\n[Errors Found: " << errors.size() << "]\n";
        std::cout << std::left << std::setw(8) << "Line" << std::setw(30) << "Message" << "Context\n";
        std::cout << std::string(60, '-') << "\n";
        for (const auto& e : errors) {
            std::cout << std::left << std::setw(8) << e.line << std::setw(30) << e.message << "\"" << e.context << "\"\n";
        }
    }
};
