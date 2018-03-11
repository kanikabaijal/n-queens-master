 algorithm MIN-CONFLICTS
     input: csp, a constraint satisfaction problem
            max_steps,the number of steps allowed before giving up
            current_state, an initial assignment of values for the variables in the csp
     output: a solution set of values for the variable or failure
   for i=1 to max_steps do
       if current_state is a solution of csp then return current_state
       var <-- a randomly chosen variable from the set of conflicted variables CONFLICTED[csp]
       value <-- the value v for var that minimizes CONFLICTS(var,v,current_state,csp)
       set var = value in current_state
   return failure
   
   
Works all right, but need to optimize it further. Need to start from a good approximation of the solution - that'll be the best.

Also, for the presentation, let us try to show the polynomial complexity of the solution and say that it's way better than backtracking which is O(2^n )
