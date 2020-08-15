#include "physics.h"
#include "../../render/model.h"
#include "../../ent/timer.h"

void attraction(stack <t_model> stack_of_model) {
	stack <t_model> dop_stack_of_model = stack_of_model;
}

void gravity(stack <t_model> stack_of_model) {
	stack <t_model> dop_stack_of_model = stack_of_model;
	t_model model;
 
	while (!dop_stack_of_model.empty()) {
		model = dop_stack_of_model.top();
		dop_stack_of_model.pop();

		//if (time.delta_sec)

	}
}

void calc_phys() {                                            // типа main, в котором будут выполняться все функции, хз надо ли, но навсякий

}