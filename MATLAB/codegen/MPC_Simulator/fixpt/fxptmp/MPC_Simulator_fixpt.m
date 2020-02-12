%#codegen
%Signal Based MPC Function for Fixed-Point Analysis
function [y_t, u_t] = MPC_Simulator_fixpt(ref_1, ref_2, noise, T,H,q_,E,F1,z_min,z_max,n,m,N_h,A_d,B_d,C_d,Aob,Bob,Cob,Ld)


    % -------- System Initial Conditions ---------

    fm = get_fimath();

    x_d_obs = fi(zeros(fi_toint(n+m),fi_toint(T)), 1, 16, 13, fm); 
    x_plant = fi(zeros(fi_toint(n),fi_toint(T)), 0, 16, 14, fm); 
    u_t = fi(zeros(fi_toint(m),fi_toint(T)), 0, 16, 15, fm);
    z = fi(zeros( fi_toint((n+m)*N_h), fi_toint(T)), 0, 16, 14, fm);
    y_t = fi(zeros(fi_toint(m),fi_toint(T)), 1, 16, 11, fm); 
    y_obs = fi(zeros(fi_toint(m),fi_toint(T)), 0, 1, 0, fm); 
    
    
    for i = fi(1, 0, 1, 0, fm):T-fi(1, 0, 1, 0, fm)

        %Simulate Plant 
        x_plant(:,i+fi(1, 0, 1, 0, fm)) = fi(A_d*x_plant(:,i) + B_d*u_t(:,i), 0, 16, 14, fm); 
        y_t(:,i) = fi(C_d * x_plant(:,i)+fi(0.01, 0, 16, 22, fm)*noise(:,i), 1, 16, 11, fm); 

        %Observer 
        x_d_obs(:,i+fi(1, 0, 1, 0, fm)) = fi(fi_signed(Aob * x_d_obs(:,i) + Bob*u_t(:,i)) - Ld * ( fi_signed(Cob*x_d_obs(:,i)) - y_t(:,i) ), 1, 16, 13, fm);


        %Scale Reference Voltage to height 
        curr_ref_t0 = fi(ref_1(:,i) * fi(7.15, 0, 16, 13, fm), 0, 16, 12, fm); %V to Cm scaling factor
        curr_ref_t1 = fi(ref_2(:,i) * fi(7.15, 0, 16, 13, fm), 0, 16, 12, fm); 

        curr_ref = fi([fi(curr_ref_t0, 0, 16, 12, fm); curr_ref_t1], 0, 16, 12, fm);

        %Compute f and e Matrix 
        f = fi(q_ * (curr_ref - x_d_obs(n+fi(1, 0, 1, 0, fm):fi_toint(end),i)), 0, 16, 12, fm); 
        e = fi(F1 * x_d_obs(fi(1, 0, 1, 0, fm):n,i), 1, 16, 14, fm);  
        z(:,i) = fi(PrimalDual(H,fi_uminus(f),E,e,z_min,z_max), 0, 16, 14, fm);    


        %Implement DAC Based Saturation
        for j = 1:2 
            if z(j,i) < fi(0, 0, 1, 0, fm) 
                %F2F: No information found for converting the following block of code
                %F2F: Start block
                u_t(j,i+fi(1, 0, 1, 0, fm)) = fi(0, 0, 16, 15, fm);
                %F2F: End block 
            elseif z(j,i) > fi(3.3, 0, 16, 14, fm) 
                %F2F: No information found for converting the following block of code
                %F2F: Start block
                u_t(j,i+fi(1, 0, 1, 0, fm)) = fi(3.3, 0, 16, 15, fm);
                %F2F: End block 
            else     
                u_t(j,i+fi(1, 0, 1, 0, fm)) = fi(z(j,i), 0, 16, 15, fm); 

            end 
        end 

         u_t(:,i+fi(1, 0, 1, 0, fm)) = fi(z(fi(1, 0, 1, 0, fm):m,i), 0, 16, 15, fm); 

    end 

%% ------- Generate Plots -----------------


%subplot(2,1,1);
%plot(ref_1 * 7.15,'r--','Linewidth',4); 
%plot(ref_2 * 7.15, 'r--', 'Linewidth',4); 
%plot(y_t','b-','Linewidth',2); hold off;
%ylabel('Output and reference');

%subplot(2,1,2);
%plot(u_t(:,1:T)','b-','Linewidth',2);
%xlabel('Time (sample number)');
   
end

