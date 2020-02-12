%MATLAB to C Array Generator

function [] = c_array_gen(mat)

shape = size(mat); 

x = shape(1); 
y = shape(2); 

for i = 1:x
    
    fprintf('{');
    for j = 1:y-1
        fprintf('%f',mat(i,j));
        fprintf(',');
    end 
    
    fprintf('%d',mat(i,y)) 
    fprintf('},\n') 
    
    
end 





end