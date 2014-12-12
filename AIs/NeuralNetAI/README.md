NeuralNetAI
===========

NeuralNetAI is an evolving neural network inspired by Darwin's theory of evolution.

Let me summarize Darwin's theory of evolution for you:
- For some reason, short-necked girafes happen to die a lot.
- For some reason, long-necked girafes happen to reproduce a lot.
- Therefore, we have more long-necked girafes.

I think my point is the girafes didn't design their long neck, or think it was beautiful or elegant or useful. It just worked out really well for them because of the environment they live in. 

Your job is not to design the NeuralNetAI but to design an environment that will kill them if they don't evolve the traits you desire.

How to evolve:
--------------
- Generate an initial population
- Repeat until some condition is met (e.g. output is good enough, a number of generations have passed, time's up, etc.)
  - Evaluate the fitness of the population's individuals
  - Breed a new population with some mutations (make sure the fittest individuals have more chance to reproduce)
- Keep the fittest individual

Fitness Evaluation:
-------------------
- An AI with a higher fitness score should "roughly" mean that he's better
- You'll need to find the right balance between accuracy and resource usage (usually your CPU)
- Be lazy. Dont judge every single decision, judge the final outcome of the game.

Pros:
-----
- Doesn't need training data (input/output pairs unknown)
- Adapts evolving game rules
- Fast computing (once trained)
- Save/Load is fast (doesn't require much memory)

Cons:
-----
- Slow training
- Training might require some parameter tweaking

Thanks Wikipedia!
-----------------
Learn more about [Neuroevolution](http://en.wikipedia.org/wiki/Neuroevolution "Thanks Wikipedia!")
