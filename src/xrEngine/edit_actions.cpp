////////////////////////////////////////////////////////////////////////////
//	Module 		: edit_actions.cpp
//	Created 	: 04.03.2008
//	Author		: Evgeniy Sokolov
//	Description : edit actions chars class implementation
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "edit_actions.h"
#include "line_edit_control.h"


namespace text_editor
{

base::base():	m_previous_action( NULL )
{
}

base::~base()
{
	xr_delete( m_previous_action );
}

void base::on_assign( base* const prev_action )
{
	m_previous_action = prev_action;
}

void base::on_key_press( line_edit_control* const control )
{
	if ( m_previous_action )
	{
		m_previous_action->on_key_press( control );
	}
}

// -------------------------------------------------------------------------------------------------

callback_base::callback_base( Callback const& callback, key_state state )
{
	m_callback  = callback;
	m_run_state = state;
}

callback_base::~callback_base()
{
}

void callback_base::on_key_press( line_edit_control* const control )
{
	if ( control->get_key_state( m_run_state ) )
	{
		m_callback();
		return;
	}
	base::on_key_press( control );
}

// -------------------------------------------------------------------------------------------------

type_pair::type_pair( char c, char c_shift )
{
	init( c, c_shift );
}

type_pair::~type_pair()
{
}

void type_pair::init( char c, char c_shift )
{
	m_char = c;
	m_char_shift = c_shift;
}

void type_pair::on_key_press( line_edit_control* const control )
{
	char c = m_char;
	if ( control->get_key_state( ks_Shift ) )
	{
		c = m_char_shift;
	}
	control->insert_character( c );
}

// -------------------------------------------------------------------------------------------------

key_state_base::key_state_base( key_state state )
{
	 m_state = state;
}

key_state_base::~key_state_base()
{
}

void key_state_base::on_key_press( line_edit_control* const control )
{
	control->set_key_state( m_state, true );
}

} // namespace text_editor