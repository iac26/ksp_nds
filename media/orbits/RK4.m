function [x_next] = RK4(X,h,f)
%
% Inputs : 
%    X, U current state and input
%    h    sample period
%    f    continuous time dynamics f(x,u)
% Returns
%    State h seconds in the future
%

% Runge-Kutta 4 integration
% write your function here

k1 = f(X);
k2 = f(X + h/2 * k1);
k3 = f(X + h/2 * k2);
k4 = f(X + h * k3);
x_next = X + h/6*(k1 + 2*k2 + 2*k3 + k4);