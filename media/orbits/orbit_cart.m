
%% 
close all

x0 = [1e3; 0; 0; 20];

theta = 0;
Ft = 1;

h = 0.05;
T = 100;
N = T/h;

N_sim = 1000;


x = zeros(4, N+1);
x(:, 1) = x0;


for i=1:N_sim
    


for k=1:N
    x(:, k+1) = RK4(x(:, k), h, @(x) f(x, 0, 0));
end

c_pos = RK4(x(:, k), h, @(x) f(x, theta, Ft));

x(:, 1) = c_pos;

t=0:h:T;

if i == 1

    figure;
    hold on
    orb = plot(x(1, :), x(3, :));
    sc = plot(c_pos(1), c_pos(3), '*');
    plot(0, 0, 'o');
    
    axis equal
    
else
    orb.XData = x(1, :);
    orb.YData = x(3, :);
    sc.XData = c_pos(1);
    sc.YData = c_pos(3);
end

pause(h);

end



function [dx] = f(x, theta, Ft)
    GM = 1e6;
    m = 1;
    dx = zeros(4, 1);
    
    
    phi = atan2(x(3), x(1));
    r = sqrt(x(3)^2 + x(1)^2);
    
    ag = -GM/(r^2);
    
    dx(1) = x(2);
    dx(3) = x(4);
    
    dx(2) = cos(phi)*ag + cos(theta)*Ft/m;
    dx(4) = sin(phi)*ag + sin(theta)*Ft/m;

end