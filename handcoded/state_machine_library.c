#include "state_machine_library.h"

/*
 * Macro used to call a method (like exit, during and so on).
 */
#define M_CALL(m) (*m)

/*
 * Macro used to retrieve a pointer to the state identified by i.
 */
#define GET_STATE(i) (CURRENT_MACHINE->states[i])

/*
 * Macro used to get the current sub-state id.
 */
#define GET_C_SUBSTATE(sp) (((extended_state*) sp)->current_substate)

/*
 * Macro used to get the transition used to get move to the correct sub-state
 * when entering an extended state.
 */
#define GET_D_SUBSTATE(sp) (((extended_state*) sp)->default_substate)

/*
 * Macro used to set the current sub-state of an extended state.
 */
#define SET_C_SUBSTATE(sp, i) (((extended_state*) sp)->current_substate = i)

/*
 * Macro used to set the current sub-state when entering an extended state.
 * It actually calls the default transition of that state.
 */
//#define SET_D_SUBSTATE(sp) SET_C_SUBSTATE(sp, M_CALL(GET_D_SUBSTATE(sp))())
#define SET_D_SUBSTATE(sp) (((extended_state *) sp)->current_substate = M_CALL(((extended_state *) sp)->default_substate)())

/*
 * Any state is seen as an extended state, if not specified otherwise.
 */
typedef extended_state state;

/*
 * Pointer to the current state machine.
 */
state_machine* CURRENT_MACHINE;

//#include "debug.h"
//#include "string.h" // TODO: remove, only for debug purpose

/*
 * Performs the during action of the given state, if any during action has been
 * provided.
 */
void perform_during_action(stateid_t i) {
	state_p s = GET_STATE(i);
	void_method m = s->during;

	if(m != NULL)
		M_CALL(m)(s);
}

/*
 * Performs the enter action of the given state, if any enter action has been
 * provided.
 *
 * Implementation choice: when entering a state:
 *
 * - first perform the enter action, if any;
 * - perform the during action of that state;
 * - if the state is an extended state, perform its default transition, then
 *      call again this function on the selected child.
 */
void perform_enter(stateid_t i) {
	state_p s = GET_STATE(i);
	void_method m = s->enter;
	
	if(m != NULL)
		M_CALL(m)(s);
		
	perform_during_action(i);

	if(!s->is_simple) {
		SET_D_SUBSTATE(s);
		perform_enter(GET_C_SUBSTATE(s));
	}
}

/*
 * Performs the exit action of the given state, if any exit action has been
 * provided. It also performs exit actions on all its children, from bottom to
 * top.
 */
void perform_exit(stateid_t i) {
    state_p s = GET_STATE(i);
    void_method m = s->exit;

    if(!s->is_simple)
        perform_exit(GET_C_SUBSTATE(s));

    if(m != NULL)
        M_CALL(m)(s);
}

/*
 * Returns true if a state has to execute a transition, based on the current
 * event bit mask.
 *
 * Notice that as implementation choice a sub-state cannot execute a transition
 * on an event handled by one of its ancestors.
 *
 * In particular, if any ancestor has to handle any event, event propagation on
 * the states tree terminates on that state. This is true for all transitions
 * that lead from one state to another, for inner transitions from a state to
 * itself event propagation continues to next child.
 */
boolean_t has_transition(stateid_t i, event_t e) {
	return (GET_STATE(i)->declared_transitions & e) != 0;
}

/*
 * Performs a transition to another state.
 *
 * Notice that transitions' behavior is roughly the same as Simulink, but it is
 * also slightly different, in a sense that there cannot be outgoing transitions
 * that come back to the same state. A transition from a state to itself is
 * always an inner transition, hence not triggering exit/enter actions.
 *
 * This behavior can be seen in perform_during function.
 */
stateid_t perform_transition(stateid_t i, event_t e) {
	state_p s = GET_STATE(i);
	transition_method m = s->event_handler;
	
	if(m != NULL)
		return M_CALL(m)(e);
	else
		return i;
}



/*
 * This function performs the during action of a given state, if any.
 * Children's during actions have preference over parents during actions.
 *
 * But most importantly this function handles events propagation on a state
 * tree, in a similar way of what happens in Simulink.
 *
 * Its behavior is roughly the following:
 *
 * 1) Given a state and the current event bit mask, check whether the current
 *    state has a transition defined for at least one event in the mask:
 *      1.1) If there is, perform it and if the resulting state is different
 *           than the current one go to point 2).
 *      1.2) If there isn't, go to point 3).
 *      1.3) If after performing it the resulting state is the same state, go to
 *           point 3).
 *
 * 2) Since a transition can lead to a sibling state or to a child state, check
 *    if the state you want to move is a child of the current state.
 *      1.1) If it is, there is no need to performing exit action. You need to
 *           exit from the current child state and move to the new one.
 *           First perform the during callback of the current state, then the
 *           exit on the current child and the enter of the new child, following
 *           the behavior of perform_exit and perform_enter.
 *
 *      1.2) If it is not, it must be a sibling of the current state, to their
 *           parents are the same. Get the parent of the current state, perform
 *           exit action of the current state (no during action on it) and then
 *           perform the enter action on the new state, both following the
 *           behavior of perform_exhit and perform_enter.
 *
 * 3) Call the during callback on this state, then call perform_during on this
 *    state's current child state, to propagate event handling to the next state
 *    in the tree.
 */
void perform_during(stateid_t i, event_t e) {
	state_p s = GET_STATE(i);

	int next_state = i;
	
	if(has_transition(i, e) && ((next_state = perform_transition(i, e)) != i)) {
		// Transition to another state
		
		if(GET_STATE(next_state)->superstate == i) {
			// The next state is a child of the current state: current state is
	        // not exited, only current child is changed
			perform_during_action(i);
			
			if(next_state != GET_C_SUBSTATE(s)) {
				perform_exit(GET_C_SUBSTATE(s));
			
				SET_C_SUBSTATE(s, next_state);
			
				perform_enter(next_state);
			}
		} else {
		    // The next state is a sibiling of the current state, so it changes
		    // the current child of the parent of this state in favor of another
		    // state.
			perform_exit(i);

			// NOTICE: current state cannot be root, since root states have no
			// siblings.
			state_p super = GET_STATE(s->superstate);
			SET_C_SUBSTATE(super, next_state);

			perform_enter(next_state);

			// NOTICE: During action on the new state is performed automatically
			// when entering by perform_enter. During action on the parent has
			// already been performed, since during callbacks are called in
			// order from top to bottom.
		}
		return;
	}

	perform_during_action(i);

	if(!s->is_simple)
		perform_during(GET_C_SUBSTATE(s), e);
}

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
void state_machine_init(state_machine* machine, state_p* states_pointer,
        stateid_t* root_states, uint8_t root_states_num) {

    machine->states = states_pointer;
    machine->root_states = root_states;
    machine->root_states_num = root_states_num;

    CURRENT_MACHINE = machine;

    for(int8_t i = 0; i < machine->root_states_num; ++i) {
        perform_enter(machine->root_states[i]);
    }
}

/*
 * Step function of the state machine. The only argument is a bit mask of events
 * that shall be handled by the machine. Internally, this mask is provided to
 * each root event, which will handle it according to state machine behavior,
 * dispatching it also to his current child if needed. See perform_during for
 * further information about state machine behavior.
 */
void state_machine_step(state_machine* machine, event_t events) {
	int8_t i = 0;
	CURRENT_MACHINE = machine;

	for(; i < CURRENT_MACHINE->root_states_num; ++i) {
		perform_during(CURRENT_MACHINE->root_states[i], events);
	}
	
}

#undef M_CALL

#undef GET_STATE

#undef GET_C_SUBSTATE
#undef GET_D_SUBSTATE

#undef SET_C_SUBSTATE
#undef SET_D_SUBSTATE





