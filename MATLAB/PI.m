% PID Controller  emulation


function [u_t,acc_out,error] = PI(ref,y_in,acc_prev)


Kp = 1.289; 
Ki = 0.0156;

	error = ref - y_in;

	internal_acc = acc_prev + error;

    %Integrator Clipping during Overflow
    
    
    integrator_max = 64; 
    integrator_min = 0; 
    
	if (internal_acc > integrator_max)
		internal_acc = integrator_max;
    elseif (internal_acc < integrator_min)
		internal_acc = integrator_min;
    else 
        internal_acc = internal_acc; 
    end 

	gain_1 = error * Kp;
	gain_2 = internal_acc * Ki;
    
	pi_out = gain_1 + gain_2;


	if (pi_out > 3.3)
		pi_out = 3.3;        
    elseif (pi_out < 0)
       pi_out = 0;
    else
       pi_out = pi_out;  
    end 
    
    

    u_t = pi_out; 
	acc_out = internal_acc;
end
