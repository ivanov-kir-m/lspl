/*
 * AotMorphology.h
 *
 *  Created on: Dec 24, 2008
 *      Author: alno
 */

#ifndef _LSPL_MORPHOLOGY_AOTMORPHOLOGY_H_
#define _LSPL_MORPHOLOGY_AOTMORPHOLOGY_H_

#include <cstdlib>
#include "Morphology.h"

class CLemmatizer;
class CAgramtab;
class CFormInfo;

namespace lspl { namespace morphology {

class LSPL_EXPORT AotMorphology : public Morphology {
public:
	AotMorphology();
	~AotMorphology();

	void appendWordForms( const std::string & token, boost::ptr_vector<WordForm> & forms );

	text::attributes::SpeechPart getSpeechPart( const char * gramCode );

	uint64 getAttributes( const char * gramCode );

	std::string getAttributesString( uint64 attValues );

	bool getParadigm(std::string word, std::vector<CFormInfo> &form);
	int getSP(const char *code) const;
	
	std::string upcase( const char * str );
	std::string upcase( const char * start, const char * end );

	std::string lowcase( const char * str );
	std::string lowcase( const char * start, const char * end );
private:
	const char * findRml();
	void setupRml();

	const char * getStem( const CFormInfo & f );
private:
	CLemmatizer * lemmatizer;
	CAgramtab * agramtab;
};

} } // namespace lspl::morphology

#endif /* _LSPL_MORPHOLOGY_AOTMORPHOLOGY_H_ */
