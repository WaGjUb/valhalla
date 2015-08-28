#ifndef VALHALLA_BALDR_VERBAL_TEXT_FORMATTER_US_H_
#define VALHALLA_BALDR_VERBAL_TEXT_FORMATTER_US_H_

#include <valhalla/baldr/verbal_text_formatter.h>

#include <regex>
#include <string>
#include <array>
#include <utility>

namespace valhalla {
namespace baldr {

const std::regex kUsNumberSplitRegex("(\\D*)(\\d+)(st|nd|rd|th)?(\\D*)",
                                     std::regex_constants::icase);

const std::regex kInterstateRegex("(\\bI)([ -])(H)?(\\d{1,3})",
                                  std::regex_constants::icase);
const std::string kInterstateOutPattern = "Interstate $3$4";

const std::regex kUsHighwayRegex("(\\bUS)([ -])(\\d{1,3})",
                                 std::regex_constants::icase);
const std::string kUsHighwayOutPattern = "U.S. $3";

const std::regex kThousandRegex("(^| )([1-9]{1,2})(000)($| )");
const std::string kThousandOutPattern = "$1$2 thousand$4";

const std::regex kHundredRegex("(^| )([1-9]{1,2})(00)($| )");
const std::string kHundredOutPattern = "$1$2 hundred$4";

const std::regex kLeadingOhRegex("( )(0)([1-9])");
const std::string kLeadingOhOutPattern = "$1o$3";

const std::array<std::pair<std::regex, std::string>, 52> kStates = {{
    { std::regex("(\\bSR)([ -])?(\\d{1,4})", std::regex_constants::icase), "State Route $3" },
    { std::regex("(\\bAL)([ -])(\\d{1,3})", std::regex_constants::icase), "Alabama $3" },
    { std::regex("(\\bAK)([ -])(\\d{1,3})", std::regex_constants::icase), "Alaska $3" },
    { std::regex("(\\bAZ)([ -])(\\d{1,3})", std::regex_constants::icase), "Arizona $3" },
    { std::regex("(\\bAR)([ -])(\\d{1,3})", std::regex_constants::icase), "Arkansas $3" },
    { std::regex("(\\bCA)([ -])(\\d{1,3})", std::regex_constants::icase), "California $3" },
    { std::regex("(\\bCO)([ -])(\\d{1,3})", std::regex_constants::icase), "Colorado $3" },
    { std::regex("(\\bCT)([ -])(\\d{1,3})", std::regex_constants::icase), "Connecticut $3" },
    { std::regex("(\\bDE)([ -])(\\d{1,3})", std::regex_constants::icase), "Delaware $3" },
    { std::regex("(\\bDC)([ -])(\\d{1,3})", std::regex_constants::icase), "D C $3" },
    { std::regex("(\\bFL)([ -])(A)?(\\d{1,3})", std::regex_constants::icase), "Florida $3$4" },
    { std::regex("(\\bGA)([ -])(\\d{1,3})", std::regex_constants::icase), "Georgia $3" },
    { std::regex("(\\bHI)([ -])(\\d{1,4})", std::regex_constants::icase), "Hawaii $3" },
    { std::regex("(\\bID)([ -])(\\d{1,3})", std::regex_constants::icase), "Idaho $3" },
    { std::regex("(\\bIL)([ -])(\\d{1,3})", std::regex_constants::icase), "Illinois $3" },
    { std::regex("(\\bIN)([ -])(\\d{1,3})", std::regex_constants::icase), "Indiana $3" },
    { std::regex("(\\bIA)([ -])(\\d{1,3})", std::regex_constants::icase), "Iowa $3" },
    { std::regex("(\\bKS)([ -])(\\d{1,3})", std::regex_constants::icase), "Kansas $3" },
    { std::regex("(\\bKY)([ -])(\\d{1,4})", std::regex_constants::icase), "Kentucky $3" },
    { std::regex("(\\bLA)([ -])(\\d{1,4})", std::regex_constants::icase), "Louisiana $3" },
    { std::regex("(\\bME)([ -])(\\d{1,3})", std::regex_constants::icase), "Maine $3" },
    { std::regex("(\\bMD)([ -])(\\d{1,3})", std::regex_constants::icase), "Maryland $3" },
    { std::regex("(\\bMA)([ -])(\\d{1,3})", std::regex_constants::icase), "Massachusetts $3" },
    { std::regex("(\\bM)([ -])(\\d{1,3})", std::regex_constants::icase), "Michigan $3" },
    { std::regex("(\\bMN)([ -])(\\d{1,3})", std::regex_constants::icase), "Minnesota $3" },
    { std::regex("(\\bMS)([ -])(\\d{1,3})", std::regex_constants::icase), "Mississippi $3" },
    { std::regex("(\\bMO)([ -])(\\d{1,3})", std::regex_constants::icase), "Missouri $3" },
    { std::regex("(\\bMT)([ -])(\\d{1,3})", std::regex_constants::icase), "Montana $3" },
    { std::regex("(\\bNE)([ -])(\\d{1,3})", std::regex_constants::icase), "Nebraska $3" },
    { std::regex("(\\bNV)([ -])(\\d{1,3})", std::regex_constants::icase), "Nevada $3" },
    { std::regex("(\\bNH)([ -])(\\d{1,3})", std::regex_constants::icase), "New Hampshire $3" },
    { std::regex("(\\bNJ)([ -])(\\d{1,3})", std::regex_constants::icase), "New Jersey $3" },
    { std::regex("(\\bNM)([ -])(\\d{1,4})", std::regex_constants::icase), "New Mexico $3" },
    { std::regex("(\\bNY)([ -])(\\d{1,3})", std::regex_constants::icase), "New York $3" },
    { std::regex("(\\bNC)([ -])(\\d{1,3})", std::regex_constants::icase), "North Carolina $3" },
    { std::regex("(\\bND)([ -])(\\d{1,4})", std::regex_constants::icase), "North Dakota $3" },
    { std::regex("(\\bOH)([ -])(\\d{1,3})", std::regex_constants::icase), "Ohio $3" },
    { std::regex("(\\bOK)([ -])(\\d{1,3})", std::regex_constants::icase), "Oklahoma $3" },
    { std::regex("(\\bOR)([ -])(\\d{1,3})", std::regex_constants::icase), "Oregon $3" },
    { std::regex("(\\bPA)([ -])(\\d{1,3})", std::regex_constants::icase), "Pennsylvania $3" },
    { std::regex("(\\bRI)([ -])(\\d{1,3})", std::regex_constants::icase), "Rhode Island $3" },
    { std::regex("(\\bSC)([ -])(\\d{1,3})", std::regex_constants::icase), "South Carolina $3" },
    { std::regex("(\\bSD)([ -])(\\d{1,4})", std::regex_constants::icase), "South Dakota $3" },
    { std::regex("(\\bTN)([ -])(\\d{1,3})", std::regex_constants::icase), "Tennessee $3" },
    { std::regex("(\\bTX)([ -])(\\d{1,3})", std::regex_constants::icase), "Texas $3" },
    { std::regex("(\\bUT)([ -])(\\d{1,3})", std::regex_constants::icase), "Utah $3" },
    { std::regex("(\\bVT)([ -])(\\d{1,3})", std::regex_constants::icase), "Vermont $3" },
    { std::regex("(\\bVA)([ -])(\\d{1,3})", std::regex_constants::icase), "Virginia $3" },
    { std::regex("(\\bWA)([ -])(\\d{1,3})", std::regex_constants::icase), "Washington $3" },
    { std::regex("(\\bWV)([ -])(\\d{1,3})", std::regex_constants::icase), "West Virginia $3" },
    { std::regex("(\\bWI)([ -])(\\d{1,3})", std::regex_constants::icase), "Wisconsin $3" },
    { std::regex("(\\bWY)([ -])(\\d{1,3})", std::regex_constants::icase), "Wyoming $3" }
}};

class VerbalTextFormatterUs : public VerbalTextFormatter {
 public:
  VerbalTextFormatterUs(const std::string& country_code,
                        const std::string& state_code);

  ~VerbalTextFormatterUs();

  std::string Format(const std::string& text) const override;

 protected:

  std::string ProcessNumberSplitMatch(const std::smatch& m) const override;

  std::string FormNumberSplitTts(const std::string& source) const override;

  std::string FormInterstateTts(const std::string& source) const;

  std::string FormUsHighwayTts(const std::string& source) const;

  std::string ProcessStatesTts(const std::string& source) const;

  bool FormStateTts(const std::string& source, const std::regex& state_regex,
                    const std::string& state_output_pattern,
                    std::string& tts) const;

  std::string FormThousandTts(const std::string& source) const;

  std::string FormHundredTts(const std::string& source) const;

  std::string FormLeadingOhTts(const std::string& source) const;
};

}
}

#endif  // VALHALLA_BALDR_VERBAL_TEXT_FORMATTER_US_H_
