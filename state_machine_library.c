#include "state_machine_library.h"

#define M_CALL(m) (*m)

#define GET_STATE(i) (STATES[i])

#define GET_C_SUBSTATE(sp) (((state*) sp)->current_substate)
#define GET_D_SUBSTATE(sp) (((state*) sp)->default_substate)

#define SET_C_SUBSTATE(sp, i) (((state*) sp)->current_substate = i)
#define SET_D_SUBSTATE(sp) (((state *) sp)->current_substate = M_CALL(((state *) sp)->default_substate)())

typedef extended_state state;

state_p* STATES;
stateid_t* ROOT_STATES;
uint8_t ROOT_STATES_NUM;

//#include "debug.h"
//#include "string.h" // TODO: remove, only for debug purpose

void perform_during_action(stateid_t i) {
	state_p s = GET_STATE(i);
	void_method m = s->during;

	if(m != NULL)
		M_CALL(m)(s);
}

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

void state_machine_init(state_p* s, stateid_t* root_states, uint8_t root_states_num) {
	STATES = s;
	ROOT_STATES = root_states;
	ROOT_STATES_NUM = root_states_num;

	for(int i = 0; i < ROOT_STATES_NUM; ++i) {
		perform_enter(ROOT_STATES[i]);
	}
}

	
void perform_exit(stateid_t i) {
	state_p s = GET_STATE(i);
	void_method m = s->exit;
	
	if(!s->is_simple)
		perform_exit(GET_C_SUBSTATE(s));
		
	if(m != NULL)
		M_CALL(m)(s);
}

// ASSUMPTION: Se uno stato gestisce un evento, nessun suo sottostato lo
// gestisce a sua volta
boolean_t has_transition(stateid_t i, event_t e) {
	return (GET_STATE(i)->declared_transitions & e) != 0;
}

stateid_t perform_transition(stateid_t i, event_t e) {
	state_p s = GET_STATE(i);
	transition_method m = s->event_handler;
	
	if(m != NULL)
		return M_CALL(m)(e);
	else
		return i;
}


// DURING DOPO I FIGLI. DAL BASSO VERSO L'ALTO

void perform_during(stateid_t i, event_t e) {
	state_p s = GET_STATE(i);

	int next_state = i;
	
	if(has_transition(i, e) && ((next_state = perform_transition(i, e)) != i)) {
		// TRANSIZIONE VERSO UN ALTRO STATO
		
		if(GET_STATE(next_state)->superstate == i) {
			// Si esce dal figlio corrente e si entra in quello nuovo;
			// questo vuol dire che non ci si muove dallo stato corrente a 
			// questo livello
			perform_during_action(i);
			
			if(next_state != GET_C_SUBSTATE(s)) {
				perform_exit(GET_C_SUBSTATE(s));
			
				SET_C_SUBSTATE(s, next_state);
			
				perform_enter(next_state);
			} else {
				//perform_during(next_state, e);
			}
		} else {
			// Si esce dallo stato corrente a questo livello, la modifica
			// avviene allo stato superiore
			perform_exit(i);

			// Aggiorna stato corrente dello stato superiore
			// NOTA: il corrente non può essere uno stato ROOT
			state_p super = GET_STATE(s->superstate);
			SET_C_SUBSTATE(super, next_state);

			perform_enter(next_state);
		}
		return;
	}

	perform_during_action(i);

	if(!s->is_simple)
		perform_during(GET_C_SUBSTATE(s), e);
}

// NOTA: gli stati ROOT non possono cambiare
void state_machine_step(event_t events) {
	int32_t i = 0;
	for(; i < ROOT_STATES_NUM; ++i) {
		perform_during(STATES[i]->self, events);
	}
	
}

#undef M_CALL

#undef GET_STATE

#undef GET_C_SUBSTATE
#undef GET_D_SUBSTATE

#undef SET_C_SUBSTATE
#undef SET_D_SUBSTATE





