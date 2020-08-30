#include "physics.h"

void start_moving(stack <t_3d_model>& stack_of_model, stack <t_3d_model>& stack_of_moving_model, timer time) {               // проверка начала какого-то движения и занесение в обрабатываемый далее стек
	
	stack <t_3d_model> dop_stack_of_model = stack_of_model;
	t_3d_model model;

	while (!dop_stack_of_model.empty()) {

		model = dop_stack_of_model.top();
		stack_of_moving_model.pop();

		model.physical_properties.v0_fall = 0.0;                       // определение начальных состояний падения
		time.calc_time();
		model.physical_properties.t0_fall = time.curr_sec;

		dop_stack_of_model.pop();

	}

}
//
void attraction(stack <t_3d_model>& stack_of_model, stack <t_3d_model>& stack_of_moving_model) {                         // обработка столкновений, запрет движения

	stack <t_3d_model> dop_stack_of_model = stack_of_moving_model;

}

void gravity(stack <t_3d_model>& stack_of_moving_model) {                                               // обработка гравитации (пока что просто падения вниз)
	
	timer time;
	stack <t_3d_model> dop_stack_of_model = stack_of_moving_model;
	t_3d_model model;
 
	while (!dop_stack_of_model.empty()) {

		model = dop_stack_of_model.top();
		dop_stack_of_model.pop();

		time.calc_time();
		model.physical_properties.t_fall = time.curr_sec - model.physical_properties.t0_fall;
		model.physical_properties.v_fall = model.physical_properties.v0_fall + 10.0 * model.physical_properties.t_fall;
		model.physical_properties.h_fall = model.physical_properties.v0_fall * model.physical_properties.t_fall
										   + (10.0 * model.physical_properties.t_fall * model.physical_properties.t_fall) / 2;

	}

}

void impulse() {                                               // расчет импульса от столкновения

}

void calc_phys(stack <t_3d_model>& stack_of_model) {                 // типа main, в котором будут выполняться все функции, хз надо ли, но навсякий
	
}