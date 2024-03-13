#ifndef rk4_hpp
#define rk4_hpp
/*
Algoritmo di Runge Kutta do ordine 4 per risolvere equazioni differenziali al
primo ordine. Le equazioni saranno del tipo $ x'= f(t, x) con x=x(t) $. Conosco
la f(t, x) ma non conosco la x(t).

Le equazioni del moto del doppio pendolo sono due ODE al secondo ordine,
accoppiate. Dovrò calcolare 16 coefficienti e sono:

$ t1" = f(t1, t2, t1', t2') $
$ t2" = g(t1, t2, t1', t2') $

( t1 e t2 sono theta1 e theta2 )
( t1d e t2d sono la derivata di di theta1 e di theta2 )
*/

#include <cmath>
#include <iostream>
#include <vector>

// t1 e t2 sono theta1 e theta2
// t1d e t2d sono la derivata di di theta1 e di theta2

constexpr double pi = 3.1415926535897932;

double const l = 100.;
// lunghezza dell'asta
double const w2 = 9.81 / l;
// omega al quadrato

double f(double, double, double, double);

double g(double, double, double, double);

// risolve l'ODE data la f(t, x), ossia calcola il punto successivo a quello
// dato. Restituisce l'insieme delle soluzioni: theta1, theta2, e le rispettive
// velocità
std::vector<double> ode_solver(std::vector<double>, double const);

double tot_energy(std::vector<double>) ;

#endif