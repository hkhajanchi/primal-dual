%Signal Based MPC Function for Fixed-Point Analysis


function [y_t, u_t] = MPC_Simulator(ref_1, ref_2, T,H,q_,E,F1,z_min,z_max,n,m,N_h,A_d,B_d,C_d,Aob,Bob,Cob,Ld) %#codegen


    % -------- System Initial Conditions ---------

    x_d_obs = zeros(n+m,T); 
    x_plant = zeros(n,T); 
    u_t = zeros(m,T);
    z = zeros( (n+m)*N_h, T);
    y_t = zeros(m,T); 
    y_obs = zeros(m,T); 
    
    
    for i = 1:T-1

        %Simulate Plant 
        x_plant(:,i+1) = A_d*x_plant(:,i) + B_d*u_t(:,i); 
        y_t(:,i) = C_d * x_plant(:,i);


        %Observer 
        x_d_obs(:,i+1) = Aob * x_d_obs(:,i) + Bob*u_t(:,i) - Ld * ( Cob*x_d_obs(:,i) - y_t(:,i) );


        %Scale Reference Voltage to height 
        curr_ref_t0 = ref_1(:,i) * 7.15; %V to Cm scaling factor
        curr_ref_t1 = ref_2(:,i) * 7.15; 

        curr_ref = [curr_ref_t0; curr_ref_t1];

        %Compute f and e Matrix 
        f = q_ * (curr_ref - x_d_obs(n+1:end,i)); 
        e = F1 * x_d_obs(1:n,i);  
        z(:,i) = PrimalDual(H,-f,E,e,z_min,z_max);    


        %Implement DAC Based Saturation
        for j = 1:2 
            if z(j,i) < 0 
                u_t(j,i+1) = 0; 
            elseif z(j,i) > 3.3 
                u_t(j,i+1) = 3.3; 
            else     
                u_t(j,i+1) = z(j,i); 

            end 
        end 

        %Post Board Amplification
        %u_t(:,i+1) = u_t(:,i+1) * 1.5; 
        
         %u_t(:,i+1) = z(1:m,i); %Preamp 

    end 

%% ------- Generate Plots -----------------
 

%subplot(2,1,1);

%y_t_V = y_t / 7.15; 

%plot(ref_1,'r--','Linewidth',4); 
%plot(ref_2, 'r--', 'Linewidth',4); 
%plot(y_t_V','b-','Linewidth',2); hold off;
%ylabel('Output and reference');

%subplot(2,1,2);
%plot(u_t(:,1:T)','b-','Linewidth',2);
%xlabel('Time (sample number)');
   
end 