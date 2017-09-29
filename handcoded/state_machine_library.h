#ifndef SM_LIB_H
#define SM_LIB_H

//----------------------------------------------------------------//
//                                                                //
//                  CUSTOM STATE MACHINE LIBRARY                  //
//                                                                //
//----------------------------------------------------------------//

#include "simple_types.h"

/*
 * Defines the signature of methods used to define enter, exit and during
 * actions for states.
 */
typedef void (* void_method)();

/*
 * Define the signature of methods used to define transition events handled by
 * states.
 */
typedef stateid_t (* transition_method)(event_t);
typedef stateid_t (* default_transition_method)();

//----------------------------------------------------------------//
//                     CLASS-LIKE DATA TYPES                      //
//----------------------------------------------------------------//


/*
 * Defines a simple state, which does not have any child states.
 */
typedef struct simple_state_s {
	const stateid_t self;                   // Id of the state
	const stateid_t superstate;             // Id of the super-state, if no
	                                        // super-state is there it points to
	                                        // the top state
	const void_method enter;                // Pointer to enter method, if any
	const void_method during;               // Pointer to during method, if any
	const void_method exit;                 // Pointer to exit method, if any

	const event_t declared_transitions;     // Specifies which events are
	                                        // handled by the state itself

	const transition_method event_handler;  // The event handler, which acts as
	                                        // an outgoing transition from the
	                                        // state

	const boolean_t is_simple;              // Specifies whether this is a
	                                        // simple state or an extended one,
	                                        // see below.
} simple_state;

typedef simple_state* state_p;

// Extends the simple state described above by adding the ability of having
// multiple sub-states.
typedef struct extended_state_s {
	const simple_state super;               // Used to mimic inheritance of OO
	                                        // programming in C
	const default_transition_method
	    default_substate;                   // Specifies the transition that has
	                                        // to be performed when entering the
	                                        // state to move into the correct
	                                        // sub-state

	stateid_t current_substate;             // Id of the current sub-state
} extended_state;


// State machine, a set of state machines. The states pointer points to the
// first element of an array of state pointers.
typedef struct state_machine_s {
    state_p*    states;                     // Array of the states, size of the
                                            // array doesn't matter as long as
                                            // any transition goes to a valid
                                            // state.

    stateid_t*  root_states;                // Array of root states
    uint8_t     root_states_num;            // Number of root states
} state_machine;


#define STATE_INVALID (-1)                  // Identifier of an invalid state,
                                            // for error handling only.


/*
 * Macro used to cut down unnecessary arguments.
 */
#define CUT_ARGS_PRIVATE(first, ...) first

//----------------------------------------------------------------//
//                          CONSTRUCTORS                          //
//----------------------------------------------------------------//

/*
 * Macro used to define a simple state. See below for arguments meaning.
 */
#define SIMPLE_STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple) \
{stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple}

/*
 * Macro used to define an extended state. See below for arguments meaning.
 */
#define EXTENDED_STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, def_substate) \
{ SIMPLE_STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple), def_substate, STATE_INVALID }


/*
 * The value of is_simple is used to dispatch the correct constructor from the two above:
 * - true: there were no additional arguments hopefully.
 * - false: additional arguments are cut away when defining an extended state.
 *
 * DO NOT USE EXPLICITLY, to be used only automatically by the STATE_DECL macro
 * below.
 */
#define STATE_DECL_true(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
SIMPLE_STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple)

#define STATE_DECL_false(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
EXTENDED_STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, CUT_ARGS_PRIVATE(args))

/*
 * State constructor. Additional arguments are used only if the state is
 * extended.
 *
 * Arguments:
 *
 * - name:       state id
 * - superstate: id of the super-state
 * - enter:      pointer to enter function, if any, NULL otherwise
 * - during:     pointer to during function, if any, NULL otherwise
 * - exit:       pointer to exit function, if any, NULL otherwise
 * - dec_trans:  bit mask of events handled by the state
 * - event_h:    transition handler, to be called when one of aforesaid events is
 *               triggered
 * - is_simple:  true for a simple state, false for an extended one
 *
 * Additional Arguments, to be used only when is_simple is false, hence when
 * declaring an extended state:
 *
 * - def_substate: transition function called to select the sub-state on enter
 *
 */
#define STATE_DECL(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, args...) \
STATE_DECL_##is_simple(stateid, superstate, enter, during, exit, dec_trans, event_h, is_simple, ##args)


//----------------------------------------------------------------//
//                            METHODS                             //
//----------------------------------------------------------------//

/*
 * Initializes a state machine. A state machine is defined by an array of
 * pointers to state objects, which can be both simple or extended. The size of
 * the state machine doesn't matter, the important thing is that states are put
 * in the exact position defined by their ids, which shall hence be progressive.
 *
 * Initialization consists mainly in performing enter actions on each specified
 * root state.
 *
 * The library supports only one state machine at a time, don't expect it to
 * work with multiple state machines. A new init invalidates any previously
 * defined state machine, leaving it in whatever condition it was before.
 * However the new machine will be correctly initialized.
 *
 * Do not initialize more than once a same state machine, correct behavior
 * cannot be ensured in that case.
 *
 * Arguments:
 * - state_machine:     Pointer to the state machine that has to be initialized.
 * - root_states:       Array of state ids identifying the root states of the
 *                      machine. A root state is a state which has no
 *                      super-state. Root states of a state machine are executed
 *                      in parallel and each can handle any event without
 *                      modifying the other root states (and their children)
 *                      behavior. A root state is ALWAYS an active state, they
 *                      cannot have transitions unless they are toward
 *                      themselves or one of their children.
 * - root_states_num:   The number of root states in the provided array.
 *
 */
extern void state_machine_init(state_machine* machine, state_p* states_pointer, stateid_t* root_states,
        uint8_t root_states_num);

/*
 * Step function of the state machine. The only argument is a bit mask of events
 * that shall be handled by the machine. Internally, this mask is provided to
 * each root event, which will handle it according to state machine behavior,
 * dispatching it also to his current child if needed.
 */
extern void state_machine_step(state_machine* machine, event_t events);


#endif


