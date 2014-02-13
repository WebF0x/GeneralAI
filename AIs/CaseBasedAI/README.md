CaseBasedAI
===========

For every given input, this AI remembers multiple output-outcome pairs:

Dictionary
----------
+input_1
++output_a = outcome_a
++output_b = outcome_b
    output_c = outcome_c
input_2
    output_a = outcome_a
    output_b = outcome_b
    output_f = outcome_f

When faced with a new input, he will prioritize the outputs he thinks will have the greatest outcome.
He will sometimes try random new outputs. This is to try to find a better reaction (prevents getting stuck in a local maximum).
