AIM

To provide an initial feasible solution to balanced transportation problems using Vogel's 
Approximation Method (VAM).

FUNCTIONALITIES
1. Input Handling:
• The program prompts the user to input the number of suppliers and consumers.
• It accepts a cost matrix representing transportation costs from each supplier to each
consumer.
• Users are prompted to enter the supply for each supplier and the demand for each
consumer.
• It checks for negative values in supply and demand inputs, ensuring valid entries.
2. Penalty Calculation:
• The program calculates penalties for each row and column based on the cost matrix to
determine the best allocation in the next step.
3. Vogel's Approximation Method:
• It iteratively allocates resources based on the maximum penalty, prioritizing
allocations that minimize costs.
• The method identifies the highest penalties and allocates accordingly, adjusting
supply and demand until all are satisfied.
4. Allocation Tracking:
• The program maintains a record of all allocations made, which can be printed for
review.
5. Output:
After completing the allocations, the program displays the final allocation matrix and
total transportation cost.
DESCRIPTION
The program aims to find an initial feasible solution to an unbalanced transportation problem, 
where the goal is to minimize the total transportation cost from multiple suppliers to multiple 
consumers. It employs Vogel's Approximation Method (VAM), which is known for its 
efficiency in generating a good starting solution.
