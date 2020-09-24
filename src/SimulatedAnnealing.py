from random import random
from math import exp

def acceptance_probability(old_cost, new_cost, T):
	dE = new_cost - old_cost
	k = 1e6
	if dE < 0
		return 1.
	return exp(-dE / (k * T) )

def SimulatedAnnealing(solution):
	old_cost = cost(solution)
	T = 1.0
	T_min = 1e-6
	alpha = 0.99
	while T > T_min:
		i = 1
		while i <= 100:
			new_solution = neighbor(solution)
			new_cost = cost(new_solution)
			ap = acceptance_probability(old_cost, new_cost, T)
			if ap > random():
				solution = new_solution
				old_cost = new_cost
			i += 1
		T *= alpha
	return solution, old_cost 