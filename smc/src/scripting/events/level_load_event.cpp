// -*- mode: c++; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4 -*-
#include "level_load_event.h"
#include "../../core/property_helper.h"

using namespace SMC;
using namespace SMC::Scripting;

cLevel_Load_Event::cLevel_Load_Event(std::string save_data)
{
	m_save_data = save_data;
}

std::string cLevel_Load_Event::Event_Name()
{
	return "load";
}

std::string cLevel_Load_Event::Get_Save_Data()
{
	return m_save_data;
}

void cLevel_Load_Event::Run_MRuby_Callback(cMRuby_Interpreter* p_mruby, mrb_value callback)
{
	mrb_state* p_state = p_mruby->Get_MRuby_State();
	mrb_value mod_json = mrb_const_get(p_state, mrb_obj_value(p_state->object_class), mrb_intern(p_state, "JSON"));

	// Deserialise from the JSON representation into an MRuby hash
	mrb_value target_str = mrb_str_new_cstr(p_state, m_save_data.c_str());
	mrb_value result = mrb_funcall(p_state, mod_json, "parse", 1, target_str);

	// Bad things happened
	if (p_state->exc) {
		std::cerr << "Warning: Failed to deserialize JSON representation from savegame: ";
		std::cerr << format_mruby_error(p_state, p_state->exc);
		std::cerr << std::endl << "(Skipping all handlers registered to Level.on_load)" << std::endl;
		return;
	}

	mrb_funcall(p_state, callback, "call", 1, result);
}