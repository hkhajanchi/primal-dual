function [val] = physics_lab_7(D)

L = 0.125; 
R = 0.065; 

val = (D/2) / ( (L - R) + sqrt( (R^2 - ( (D^2) /4) ) ) );

end 