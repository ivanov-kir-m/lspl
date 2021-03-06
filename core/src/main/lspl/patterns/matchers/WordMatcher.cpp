#include "../../base/BaseInternal.h"

#include "WordMatcher.h"

#include "../../text/Node.h"
#include "../../text/markup/Word.h"

#include "../../morphology/Morphology.h"

using lspl::text::Transition;
using lspl::text::TransitionRef;
using lspl::text::TransitionList;
using lspl::text::markup::Word;

using lspl::text::attributes::SpeechPart;

using lspl::morphology::Morphology;

namespace lspl { namespace patterns { namespace matchers {

WordMatcher::WordMatcher( const std::string & base, SpeechPart speechPart )  :
	AnnotationMatcher( WORD ), base( Morphology::instance().upcase( base ) ), speechPart( speechPart ) {

}

TransitionList WordMatcher::buildTransitions( const text::Node & node, const Context & context ) const {
	TransitionList transitions;

	for ( uint i = node.getTokenCount(), sz = node.getTokenCount() + node.getWordCount(); i < sz; ++ i )
		if ( matchTransition( *node.getTransition( i ), context ) )
			transitions.push_back( node.getTransition( i ) );

	return transitions;
}

bool WordMatcher::matchTransition( const Transition & transition, const Context & context ) const {
	if ( transition.type != Transition::WORD )
		return false;

	Word & word = *(Word *)&transition;

	if ( speechPart != SpeechPart::WORD && speechPart != word.getSpeechPart() ) // Проверяем соответствие частей речи
		return false;

	if ( base != "" && base != word.getBase() ) // Проверяем соответствие начальной формы
		return false;

	return matchRestrictions( transition, context );
}

void WordMatcher::dump( std::ostream & out, const std::string & tabs ) const {
	out << "WordMatcher{ base = " << base << ", speechPart = " << speechPart.getAbbrevation() << ", variable = " << variable << ", restrictions = ";
	dumpRestrictions( out );
	out << " }";
}

bool WordMatcher::equals( const Matcher & m ) const {
	if ( !Matcher::equals( m ) ) return false; // Разные сопоставители

	const WordMatcher & wm = static_cast<const WordMatcher &>( m );

	if ( wm.speechPart != speechPart ) return false; // Различная часть речи
	if ( wm.base != base ) return false; // Различная основа

	return true;
}

} } } // namespace lspl::patterns::matchers
