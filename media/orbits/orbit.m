%% 
close all

x0 = [0; 100; 0.1; 0];

theta = 0;
Ft = 0;

h = 0.1;
T = 100;
N = T/h;

%[t, y] = ode45(@(t, x) f(x, theta, Ft), [0 h], x0);

x = zeros(4, N+1);
x(:, 1) = x0;

for k=1:N
    x(:, k+1) = RK4(x(:, k), h, @(x) f(x, theta, Ft));
end

t=0:h:T;

figure;
plot(t, x(1,:), '-');
title("rdot")
figure;
plot(t, x(2,:), '-');
title("r")
figure;
plot(t, x(3,:), '-');
title("phidot")
figure;
plot(t, x(4,:), '-');
title("phi")

px = x(2,:).*cos(x(4, :));
py = x(2,:).*sin(x(4, :));

figure;
plot(px, py);

%% 

% dynamics
function [dx] = f(x, theta, Ft)
    GM = 1;
    m = 1;
    dx = zeros(4, 1);
    dx(1) = -GM/((x(2))^2) + Ft/m*sin(theta) + x(1)*(x(3)^2);
    dx(2) = x(1);
    dx(3) = (Ft/m*cos(theta) - 2*x(1)*x(3))/x(2);
    dx(4) = x(3);
end