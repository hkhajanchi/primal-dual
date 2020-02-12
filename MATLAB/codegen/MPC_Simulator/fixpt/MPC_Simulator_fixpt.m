%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
%           Generated by MATLAB 9.6 and Fixed-Point Designer 6.3           %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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

function Z = PrimalDual(H,Q,E,e,Z_MIN,Z_MAX)


% Define Loop Parameters
fm = get_fimath();

x = fi(size(H,fi(1, 0, 1, 0, fm)), 0, 5, 0, fm); 
y = fi(size(E,fi(1, 0, 1, 0, fm)), 0, 5, 0, fm); 

% Instantiate z and lambda vectors 
Z = fi(zeros (fi_toint(x),1), 1, 16, 13, fm); 
L = fi(zeros (fi_toint(y),1), 1, 16, 13, fm); 

% Convergence Parameters 

D = fi(max(max(H)), 0, 4, 0, fm); 
U = fi(4.33, 0, 16, 13, fm); %Arbitrary Positive Number
W = fi(1, 0, 1, 0, fm); 
A = fi(1, 0, 1, 0, fm); 

k = fi(0, 0, 8, 0, fm); 
maxIterations = fi(200, 0, 8, 0, fm); 


while (k < maxIterations)
    
    %Compute Z_k+1
    
    for i = fi(1, 0, 1, 0, fm):x
        delta = fi(0, 1, 16, 14, fm); 
        
        temp1 = fi(0, 1, 16, 11, fm); 
        temp2 = fi(0, 1, 16, 13, fm); 
        
        for j = fi(1, 0, 1, 0, fm):x
            temp1(:) = temp1 + H(i,j)*Z(j);
        end 
        
        for j = fi(1, 0, 1, 0, fm):y
            temp2(:) = temp2 + E(j,i)*L(j);
        end 
        
        delta(:) = fi_div(A * ((temp1-temp2) + Q(i)), D); 
        
        %Projection 
        if ((Z(i) - delta) < Z_MIN(i))
            %F2F: No information found for converting the following block of code
            %F2F: Start block
            Z(i) = Z_MIN(i);
            %F2F: End block 
        elseif ((Z(i) - delta) > Z_MAX(i))
            %F2F: No information found for converting the following block of code
            %F2F: Start block
            Z(i) = Z_MAX(i);
            %F2F: End block 
        else 
            Z(i) = Z(i) - delta; 
        end 
             
    end 
    
    %Compute Lambda_k+1
    
    for i = fi(1, 0, 1, 0, fm):y
        delta_lambda = fi(0, 1, 16, 13, fm); 
        
        for j = fi(1, 0, 1, 0, fm):x 
            delta_lambda(:) = delta_lambda + E(i,j)*Z(j);
        end 
        
        delta_lambda(:) = fi_div(W * (delta_lambda - e(i)), U); 
        L(i) = L(i) - delta_lambda; 
        
        
    end
   
    k(:) = k + fi(1, 0, 1, 0, fm); 
    
end 

end



function ntype = divideType(a,b)
    coder.inline( 'always' );
    nt1 = numerictype( a );
    nt2 = numerictype( b );
    maxFL = max( [ min( nt1.WordLength, nt1.FractionLength ), min( nt2.WordLength, nt2.FractionLength ) ] );
    FL = max( maxFL, 24 );
    extraBits = (FL - maxFL);
    WL = nt1.WordLength + nt2.WordLength;
    WL = min( WL, 124 );
    if (WL + extraBits)<64
        ntype = numerictype( nt1.Signed || nt2.Signed, WL + extraBits, FL );
    else
        ntype = numerictype( nt1.Signed || nt2.Signed, WL, FL );
    end
end


function c = fi_div(a,b)
    coder.inline( 'always' );
    if isfi( a ) && isfi( b ) && isscalar( b )
        a1 = fi( a, 'RoundMode', 'fix' );
        b1 = fi( b, 'RoundMode', 'fix' );
        c1 = divide( divideType( a1, b1 ), a1, b1 );
        c = fi( c1, numerictype( c1 ), fimath( a ) );
    else
        c = a / b;
    end
end


function y = fi_signed(a)
    coder.inline( 'always' );
    if isfi( a ) && ~(issigned( a ))
        nt = numerictype( a );
        new_nt = numerictype( 1, nt.WordLength + 1, nt.FractionLength );
        y = fi( a, new_nt, fimath( a ) );
    else
        y = a;
    end
end


function y = fi_toint(u)
    coder.inline( 'always' );
    if isfi( u )
        nt = numerictype( u );
        s = nt.SignednessBool;
        wl = nt.WordLength;
        y = int32( fi( u, s, wl, 0, hdlfimath ) );
    else
        y = int32( u );
    end
end


function y = fi_uminus(a)
    coder.inline( 'always' );
    if isfi( a )
        nt = numerictype( a );
        new_nt = numerictype( 1, nt.WordLength + 1, nt.FractionLength );
        y = -fi( a, new_nt, fimath( a ) );
    else
        y = -a;
    end
end

function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Floor',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode','FullPrecision',...
	     'MaxProductWordLength', 128,...
	     'SumMode','FullPrecision',...
	     'MaxSumWordLength', 128);
end