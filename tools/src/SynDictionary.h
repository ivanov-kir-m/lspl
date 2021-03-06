/*
 * Author: Antonov Vadim (avadim@gmail.com)
 *
 * Synonim dictionary.
 */

#ifndef __LSPL_SYN_DICTIONARY
#define __LSPL_SYN_DICTIONARY

#include <map>
#include <set>
#include <string>

#include "lspl/Namespace.h"
#include <lspl/dictionaries/Dictionary.h>

namespace lspl {
	namespace dictionaries {

		class SynDictionary : public Dictionary {
			typedef std::map<std::string, std::set<std::string> >
					SynonimPatterns;
		 private:
			SynonimPatterns _synonim_patterns;

			void LoadDictionary(const std::string &filename);
		 public:
			virtual bool acceptsWords(
					const std::vector<std::string> &words) const;
			virtual bool acceptsWords(const std::string &word1,
					const std::string &word2) const;

			SynDictionary(const std::string &name, const std::string &filename);
			virtual ~SynDictionary();
		}; // SynDictionary

	} // namesoace dictionaries
} // namespace lspl

#endif // __LSPL_SYN_DICTIONARY
