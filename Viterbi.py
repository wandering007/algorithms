'''
The Viterbi algorithm is a dynamic programming algorithm for finding the most likely 
sequence of hidden states (the Viterbi path) that results in a sequence of observed events.
INPUT
- The observation space O = {o_1, o_2, ..., o_N}
- the state space S = {s_1, s_2, ..., s_K}
- an array of initial probabilities PI = (pi_1, pi_2, ..., pi_K) such that pi_i stores the probability that x_1 == s_i
- a sequence of observations Y = (y_1, y_2, ..., y_T) such that y_t == i if the observation at time t is o_i
- transition matrix A of size K * K such that A_{ij} stores the transition probability of transiting from state s_i to state s_j
- emission matrix B of size K * N such that B_{ij} stores the probability of observing o_j from state s_i
OUTPUT
- The most likely hidden state sequence X = (x_1, x_2, ..., x_T)
The complexity of this algorithm is O(T * |S| ^ 2)
'''
def viterbi(obs, states, start_p, trans_p, emit_p):
    V = [{}]
    for st in states:
        V[0][st] = {"prob": start_p[st] * emit_p[st][obs[0]], "prev": None}
    # Run Viterbi when t > 0
    for t in range(1, len(obs)):
        V.append({})
        for st in states:
            max_tr_prob = max(V[t - 1][prev_st]["prob"] * trans_p[prev_st][st] for prev_st in states)
            for prev_st in states:
                if V[t - 1][prev_st]["prob"] * trans_p[prev_st][st] == max_tr_prob:
                    max_prob = max_tr_prob * emit_p[st][obs[t]]
                    V[t][st] = {"prob": max_prob, "prev": prev_st}
                    break
    for line in dptable(V):
        print(line)
    opt = []
    # The highest probability
    max_prob = max( value["prob"] for value in V[-1].values() )
    previous = None
    # Get most probable state and its backtrack
    for st, data in V[-1].items():
        if data["prob"] == max_prob:
            opt.append(st)
            previous = st
            break
    # Follow the backtrack till the first observation
    for t in range(len(V) - 1, 0, -1):
        opt.insert(0, V[t][previous]["prev"])
        previous = V[t][previous]["prev"]

    print('The steps of states are {' + ' -> '.join(opt) + '} with highest probability of %s' % max_prob)

def dptable(V):
    # Print a table of steps from dictionary
    yield " ".join( ("%10d" % i) for i in range(len(V)) )
    for state in V[0]:
        yield "%-7s: " % state + " ".join("%-10s" % ("%f" % v[state]["prob"]) for v in V)