#ifndef SM_LIB_H
#define SM_LIB_H

//----------------------------------------------------------------//
//                                                                //
//                  CUSTOM STATE MACHINE LIBRARY                  //
//                                                                //
//----------------------------------------------------------------//

#include "simple_types.h"

struct extended_state_s;
struct simple_state_s;

typedef struct extended_state_s extended_state;
typedef struct simple_state_s simple_state;

typedef simple_state* state_p;

typedef void (* void_method)();
typedef stateid_t (* transition_method)(event_t);
typedef stateid_t (* default_transition_method)();

typedef struct simple_state_s {
	const stateid_t self;
	const stateid_t superstate;
	const void_method enter;
	const void_method during;
	const void_method exit;
	const event_t declared_transitions;
	const transition_method event_handler;
	const boolean_t is_simple;
} simple_state;

typedef struct extended_state_s {
	const simple_state super;
	const default_transition_method default_substate;
	stateid_t current_substate;
} extended_state;

#define STATE_INVALID (-1)

#define CUT_ARGS_PRIVATE(first, ...) first

#define SIMPLE_STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple) \
{name, superstate, enter, during, exit, dec_trans, event_h, is_simple}

#define COMPLEX_STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, def_substate) \
{ SIMPLE_STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple), def_substate, STATE_INVALID }

#define STATE_DECL_true(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
SIMPLE_STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple)

#define STATE_DECL_false(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
COMPLEX_STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, CUT_ARGS_PRIVATE(args))

#define STATE_DECL(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
STATE_DECL_##is_simple(name, superstate, enter, during, exit, dec_trans, event_h, is_simple, ##args)


/* ----------------------------- METHODS ----------------------------------- */

extern void state_machine_init(state_p* s, stateid_t* root_states, uint8_t root_states_num);

extern void state_machine_step(event_t events);


#endif


