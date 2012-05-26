#include <SFGUI/Selector.hpp>
#include <SFGUI/Container.hpp>

namespace sfg {

Selector::Selector() :
	m_hierarchy_type( INVALID ),
	m_state( -1 ),
	m_hash( 0 )
{
}

Selector::Selector( const Selector& other ) :
	m_hierarchy_type( other.m_hierarchy_type ),
	m_widget( other.m_widget ),
	m_id( other.m_id ),
	m_class( other.m_class ),
	m_state( other.m_state ),
	m_hash( 0 )
{
	if( other.m_parent ) {
		m_parent.reset( new Selector( *other.m_parent ) );
	}
}

Selector& Selector::operator=( const Selector& other ) {
	m_hierarchy_type = other.m_hierarchy_type;
	m_widget = other.m_widget;
	m_id = other.m_id;
	m_class = other.m_class;
	m_state = other.m_state;
	m_hash = other.m_hash;

	if( other.m_parent ) {
		m_parent.reset( new Selector( *other.m_parent ) );
	}
	else {
		m_parent.reset();
	}

	return *this;
}

Selector::Ptr Selector::Create( const std::string& str ) {
	std::string::const_iterator str_iter( str.begin() );
	bool parse_next( true );
	Ptr selector;

	int hierarchy_type = ROOT;

	while( parse_next ) {
		// Eat any whitespace before the current simple selector.
		EatWhitespace( str_iter, str.end() );

		// Check bounds.
		if( str_iter == str.end() ) {
			break;
		}

		// If it's not the first simple selector, check for combinator.
		if( selector ) {
			if( *str_iter == '>' ) {
				hierarchy_type = CHILD;

				// Skip combinator.
				++str_iter;

				// Eat any whitespace after the '>'.
				EatWhitespace( str_iter, str.end() );
			}
			else {
				hierarchy_type = DESCENDANT;
			}

			// Check bounds.
			if( str_iter == str.end() ) {
				return Ptr();
			}
		}

		Ptr next( new Selector );

		try {
			next->m_widget = ParseWidget( str_iter, str.end() );
			next->m_id = ParseId( str_iter, str.end() );
			next->m_class = ParseClass( str_iter, str.end() );
			next->m_state = ParseState( str_iter, str.end() );
		}
		catch( const ParserException& /*e*/ ) {
			return Ptr();
		}

		next->m_hierarchy_type = hierarchy_type;

		// If it's the first simple selector, set it as current root.
		if( !selector ) {
			selector = next;
			continue;
		}
		else {
			// If it's not the first, parent the current root.
			next->m_parent = selector;
			selector = next;
		}
	}

	// If there's no selector yet, it means we want to reach ALL widgets, which
	// is perfectly fine.
	// binary1248 says: Actually, we want this case to be handled by the wildcard
	// which means if there is no selector, no widget (wildcard) was parsed
	// and the input is invalid.
	if( !selector ) {
		//selector = Ptr( new Selector );
		return Ptr();
	}

	// Hash.
	std::size_t hash = static_cast<std::size_t>( 2166136261UL );

	std::string selector_string = selector->BuildString();
	std::size_t length = selector_string.length();

	for ( ; length; --length ) {
		hash ^= static_cast<std::size_t>( selector_string[ length - 1 ] );
		hash *= static_cast<std::size_t>( 16777619UL );
	}

	selector->m_hash = hash;

	return selector;
}

Selector::Ptr Selector::Create( const std::string& widget, const std::string& id, const std::string& class_, const std::string& state, int hierarchy, Ptr parent ) {
	Ptr selector( new Selector );

	selector->m_widget = widget;
	selector->m_id = id;
	selector->m_class = class_;

	if( state == "NORMAL" ) {
		selector->m_state = Widget::NORMAL;
	}
	else if( state == "ACTIVE" ) {
		selector->m_state = Widget::ACTIVE;
	}
	else if( state == "PRELIGHT" ) {
		selector->m_state = Widget::PRELIGHT;
	}
	else if( state == "SELECTED" ) {
		selector->m_state = Widget::SELECTED;
	}
	else if( state == "INSENSITIVE" ) {
		selector->m_state = Widget::INSENSITIVE;
	}
	else if( !state.empty() ) {
		throw( ParserException( "Invalid state: " + state ) );
	}

	selector->m_hierarchy_type = hierarchy;

	if( hierarchy != ROOT ) {
		selector->m_parent = parent;
	}

	// Hash.
	std::size_t hash = static_cast<std::size_t>( 2166136261UL );

	std::string selector_string = selector->BuildString();
	std::size_t length = selector_string.length();

	for ( ; length; --length ) {
		hash ^= static_cast<std::size_t>( selector_string[ length - 1 ] );
		hash *= static_cast<std::size_t>( 16777619UL );
	}

	selector->m_hash = hash;

	return selector;
}

std::string Selector::ParseWidget( std::string::const_iterator& begin, const std::string::const_iterator& end ) {
	std::string token;

	for( ; begin != end; ++begin ) {
		// Check for ID, class and state delimiters.
		if( *begin == '#' || *begin == '.' || *begin == ':' || *begin == '>' ) {
			return token;
		}

		// Check for whitespace.
		if( *begin == ' ' ) {
			EatWhitespace( begin, end );
			return token;
		}

		// Check for valid char.
		if(
			(*begin < 'a' || *begin > 'z') &&
			(*begin < 'A' || *begin > 'Z') &&
			(*begin != '*' )
			// TODO: Handle the cases where letters and asterisks (or multiple asterisks) get mixed together.
		) {
			throw( ParserException( std::string( "Invalid character for widget name: " ) + *begin ) );
		}

		token += *begin;
	}

	return token;
}

std::string Selector::ParseId( std::string::const_iterator& begin, const std::string::const_iterator& end ) {
	std::string token;

	// Check bounds.
	if( begin == end ) {
		return "";
	}

	// Check for delimiter.
	if( *begin != '#' ) {
		return "";
	}

	// Skip delimiter.
	++begin;

	for( ; begin != end; ++begin ) {
		// Check for class and state delimiters.
		if( *begin == '.' || *begin == ':' || *begin == '>' ) {
			return token;
		}

		// Check for whitespace.
		if( *begin == ' ' ) {
			EatWhitespace( begin, end );
			return token;
		}

		// Check for valid char.
		if(
			(*begin < 'a' || *begin > 'z') &&
			(*begin < 'A' || *begin > 'Z') &&
			(*begin < '0' || *begin > '9') &&
			(*begin != '_') &&
			(*begin != '-')
		) {
			throw( ParserException( std::string( "Invalid character for ID: " ) + *begin ) );
		}

		token += *begin;
	}

	return token;
}

std::string Selector::ParseClass( std::string::const_iterator& begin, const std::string::const_iterator& end ) {
	std::string token;

	// Check bounds.
	if( begin == end ) {
		return "";
	}

	// Check for delimiter.
	if( *begin != '.' ) {
		return "";
	}

	// Skip delimiter.
	++begin;

	for( ; begin != end; ++begin ) {
		// Check for state delimiters.
		if( *begin == ':' || *begin == '>' ) {
			return token;
		}

		// Check for whitespace.
		if( *begin == ' ' ) {
			EatWhitespace( begin, end );
			return token;
		}

		// Check for valid char.
		if(
			(*begin < 'a' || *begin > 'z') &&
			(*begin < 'A' || *begin > 'Z') &&
			(*begin < '0' || *begin > '9') &&
			(*begin != '_') &&
			(*begin != '-')
		) {
			throw( ParserException( std::string( "Invalid character for class: " ) + *begin ) );
		}

		token += *begin;
	}

	return token;
}

int Selector::ParseState( std::string::const_iterator& begin, const std::string::const_iterator& end ) {
	std::string token;

	// Check bounds.
	if( begin == end ) {
		return -1;
	}

	// Check for delimiter.
	if( *begin != ':' ) {
		return -1;
	}

	// Skip delimiter.
	++begin;

	for( ; begin != end; ++begin ) {
		// If there's whitespace, the state is complete. Check for delimiter or end of string.
		if( *begin == ' ' ) {
			EatWhitespace( begin, end );

			if( begin == end || *begin == '>' ) {
				break;
			}

			// Another stuff follows after whitespace, this shouldn't happen.
			throw( ParserException( "Expected '>' or end of string for state." ) );
		}

		// Check for valid char.
		if(
			(*begin < 'a' || *begin > 'z') &&
			(*begin < 'A' || *begin > 'Z')
		) {
			throw( ParserException( std::string( "Invalid character for state: " ) + *begin ) );
		}

		token += *begin;
	}

	// Check state string.
	if( token == "NORMAL" ) {
		return Widget::NORMAL;
	}
	else if( token == "ACTIVE" ) {
		return Widget::ACTIVE;
	}
	else if( token == "PRELIGHT" ) {
		return Widget::PRELIGHT;
	}
	else if( token == "SELECTED" ) {
		return Widget::SELECTED;
	}
	else if( token == "INSENSITIVE" ) {
		return Widget::INSENSITIVE;
	}

	throw( ParserException( "Invalid state: " + token ) );
}

void Selector::EatWhitespace( std::string::const_iterator& begin, const std::string::const_iterator& end ) {
	for( ; begin != end; ++begin ) {
		if( *begin != ' ' ) {
			return;
		}
	}
}

const std::string& Selector::GetWidgetName() const {
	return m_widget;
}

const std::string& Selector::GetId() const {
	return m_id;
}

const std::string& Selector::GetClass() const {
	return m_class;
}

int Selector::GetState() const {
	return m_state;
}

const Selector::PtrConst& Selector::GetParent() const {
	return m_parent;
}

std::string Selector::BuildString() const {
	std::string str;

	// Build parent's string first.
	if( m_parent ) {
		str += m_parent->BuildString();

		switch( m_hierarchy_type ) {
			case CHILD: {
				str += ">";
			} break;
			case DESCENDANT: {
				str += " ";
			} break;
			default: break;
		}
	}

	// Append own string.
	if( m_widget.empty() ) {
		// Use a wildcard for all widgets.
		str += "*";
	}
	else {
		str += m_widget;
	}

	if( !m_id.empty() ) {
		str += "#";
		str += m_id;
	}

	if( !m_class.empty() ) {
		str += ".";
		str += m_class;
	}

	if( m_state > -1 ) {
		str += ":";

		switch( m_state ) {
			case Widget::NORMAL:
				str += "NORMAL";
				break;
			case Widget::PRELIGHT:
				str += "PRELIGHT";
				break;
			case Widget::ACTIVE:
				str += "ACTIVE";
				break;
			case Widget::SELECTED:
				str += "SELECTED";
				break;
			case Widget::INSENSITIVE:
				str += "INSENSITIVE";
				break;

			default:
				str += "UNKNOWN";
				break;
		}
	}

	return str;
}

bool Selector::operator==( const Selector& other ) {
	// Check if valid selectors.
	if( !m_hash || !other.m_hash ) {
		return false;
	}

	return m_hash == other.m_hash;
}

bool Selector::Matches( const Widget::PtrConst& widget ) const {
	if( !widget ) {
		return false;
	}

	// Recursion is your friend ;)

	// Check if current stage is a pass...
	if( ( !m_widget.compare("*") && m_id.empty() && m_class.empty() && m_state == -1 ) || // Wildcard
		 ( ( m_widget.empty() || m_widget == widget->GetName() ) && //
		 ( m_id.empty() || m_id == widget->GetId() ) && // Selector and widget match
		 ( m_class.empty() || m_class  == widget->GetClass() ) && //
		 ( m_state == (-1) || m_state  == widget->GetState() ) ) ) { //
		// Current stage is a pass...

		// Differentiate between different hierarchy types
		switch( m_hierarchy_type ) {
			case ROOT: {
				// No parent, matching success
				return true;
			} break;
			case CHILD: {
				// This is a child, check direct parent only
				return ( GetParent() && GetParent()->Matches( widget->GetParent() ) );
			} break;
			case DESCENDANT: {
				// This is a descendant, check all parents and try to match to all of widgets parents
				for( PtrConst parent = GetParent(); parent; parent = parent->GetParent() ) {
					for( Widget::PtrConst widget_parent = widget->GetParent(); widget_parent; widget_parent = widget_parent->GetParent() ) {
						if( parent->Matches( widget_parent ) ) {
							return true;
						}
					}
				}
			} break;
			default: break;
		}
	}

	// Not wildcard and doesn't match, fail... :(
	return false;
}

}
