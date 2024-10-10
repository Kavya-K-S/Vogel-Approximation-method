#include <stdio.h>
#include <limits.h>

struct transportationproblem {
    int cost[20][20];
    int supply[20];
    int demand[20];
    int n1; // Number of sources
    int n2; // Number of destinations
    
};

typedef struct transportationproblem tprblm;
tprblm tp;
void insertcost() {
    int i, j;
    // Input costs
    for (i = 0; i < tp.n1; i++) {
        for (j = 0; j < tp.n2; j++) {
            printf("Source %d to Destination %d: ", i + 1, j + 1);
            scanf("%d", &tp.cost[i][j]);
            if(tp.cost[i][j]<0)
			{ 
				printf("\nInvalid Entry!\n");
				main();
			}
            	
            
        }
    }
     printf("\n");
    // Input supply
    for (i = 0; i < tp.n1; i++) {
        printf("Enter the supply of Source %d: ", i + 1);
        scanf("%d", &tp.supply[i]);
        if(tp.supply[i]<0)
		{
        	printf("\nInvalid Entry. Enter the value again.\n\n");
        	i--;
		}
    }

    // Input demand
    for (j = 0; j < tp.n2; j++) {
        printf("Enter the demand of Destination %d: ", j + 1);
        scanf("%d", &tp.demand[j]);
        if(tp.demand[j]<0)
		{
        	printf("\nInvalid Entry. Enter the value again.\n\n");
        	j--;
        }
    }
}

void dispcost()
 {
    int i, j;
    printf("\n---------------COST MATRIX---------------\n\n");
    
    printf("\t\t");
    for (j = 0; j < tp.n2; j++) {
        printf("\tD%d\t", j + 1);
    }
    printf("\t  Supply\n");

    for (i = 0; i < tp.n1; i++)
	{
        printf("\tS%d\t", i + 1);
        for (j = 0; j < tp.n2; j++)
		{
            printf("\t%d\t", tp.cost[i][j]);
        }
        printf("\t  %d\n", tp.supply[i]);
    }

    printf("\tDemand\t");
    for (j = 0; j < tp.n2; j++)
	{
        printf("\t%d\t", tp.demand[j]);
    }
    printf("\n");
   
}

// Function to calculate penalties for rows and columns
void calcpenalty(int rowPenalty[20], int colPenalty[20])
{
    int i,j;
    int rows=tp.n1;
    int cols=tp.n2;
	for (i = 0; i < rows; i++)
	{
        if (tp.supply[i] == 0)
		{
            rowPenalty[i] = -1;  // Row exhausted
            continue;
        }
        int min1 = INT_MAX, min2 = INT_MAX;
        for (j = 0; j < cols; j++)
		{
            if (tp.demand[j] != 0)
			{ // Only consider unmet tp.demand
                if (tp.cost[i][j] < min1)
				{
                    min2 = min1;
                    min1 = tp.cost[i][j];
                }
				else if (tp.cost[i][j] < min2)
				{
                    min2 = tp.cost[i][j];
                }
            }
        }
        rowPenalty[i] = min2 - min1; // Penalty for rows
    }

    for (j = 0; j < cols; j++)
	{
        if (tp.demand[j] == 0)
		{
            colPenalty[j] = -1;  // Column satisfied
            continue;
        }
        int min1 = INT_MAX, min2 = INT_MAX;
        for (i = 0; i < rows; i++)
		{
            if (tp.supply[i] != 0)// Only consider available supply
			{ 
                if (tp.cost[i][j] < min1)
				{
                    min2 = min1;
                    min1 = tp.cost[i][j];
                } 
				else if (tp.cost[i][j] < min2)
				{
                    min2 = tp.cost[i][j];
                }
            }
        }
        colPenalty[j] = min2 - min1; // Penalty for columns
    }
}

// Function to solve the transportation problem using VAM
int vogelapprox(int rows, int cols,int allocation[20][20])
{
    int i,j,totsup=0,totdem=0;
	int rowPenalty[20], colPenalty[20], totalCost = 0;
	for (i = 0; i < tp.n1; i++)
	{
		totsup+=tp.supply[i];
	}
	 for (j = 0; j < tp.n2; j++) 
	 {
	 	totdem+=tp.demand[j];	
	 }
	 int m;
	 if(totsup!=totdem)
    {
        	printf("\n\nThis is an unbalanced transportation problem !!\n\n");
        	printf("\n1. New cost matrix \n2. Exit\n\nEnter your choice :");
        	scanf("%d",&m);
        	if(m!=1)
        	{
			   printf("\n*****************************************************************\n");
        	   return 0;
            }
        	else
        	  main();
    }
    while (1) {
        calcpenalty(rowPenalty, colPenalty);
        // Find the maximum penalty (row or column)
        int maxPenalty = -1, selectedRow = -1, selectedCol = -1;
        for (i = 0; i < rows; i++) {
            if (rowPenalty[i] > maxPenalty)
			{
                maxPenalty = rowPenalty[i];
                selectedRow = i;
                selectedCol = -1;
            }
        }
        for (j = 0; j < cols; j++)
		{
            if (colPenalty[j] > maxPenalty)
			{
                maxPenalty = colPenalty[j];
                selectedRow = -1;
                selectedCol = j;
            }
        }

        // If no penalty found, break the loop
        if (maxPenalty == -1) 
		    break;

        // If row penalty is maximum, choose the least tp.cost in that row
        if (selectedRow != -1)
		{
            int minCost = INT_MAX, col = -1;
            for (j = 0; j < cols; j++)
			{
                if (tp.demand[j] != 0 && tp.cost[selectedRow][j] < minCost)
				{
                    minCost = tp.cost[selectedRow][j];
                    col = j;
                }
            }
            int allocationAmount;
            if(tp.supply[selectedRow] < tp.demand[col])
            	allocationAmount=tp.supply[selectedRow] ;
            else
            	allocationAmount = tp.demand[col];
            //int allocationAmount = (tp.supply[selectedRow] < tp.demand[col]) ? tp.supply[selectedRow] : tp.demand[col];
            allocation[selectedRow][col] = allocationAmount;
            totalCost += allocationAmount * tp.cost[selectedRow][col];
            tp.supply[selectedRow] -= allocationAmount;
            tp.demand[col] -= allocationAmount;
        }

        // If column penalty is maximum, choose the least cost in that column
        if (selectedCol != -1) {
            int minCost = INT_MAX, row = -1;
            for (i = 0; i < rows; i++) {
                if (tp.supply[i] != 0 && tp.cost[i][selectedCol] < minCost) {
                    minCost = tp.cost[i][selectedCol];
                    row = i;
                }
            }
            int allocationAmount = (tp.supply[row] < tp.demand[selectedCol]) ? tp.supply[row] : tp.demand[selectedCol];
            allocation[row][selectedCol] = allocationAmount;
            totalCost += allocationAmount * tp.cost[row][selectedCol];
            tp.supply[row] -= allocationAmount;
            tp.demand[selectedCol] -= allocationAmount;
        }
    }
    
    return totalCost;
}

int main() {
    int allocation[20][20] = {0};
    int i,j,m;
    printf("\nEnter the number of suppliers: ");
    scanf("%d", &tp.n1);
    printf("\nEnter the number of consumers: ");
    scanf("%d", &tp.n2);
    printf("\nEnter the cost matrix\n\n");
    insertcost();
    dispcost();
    int totalCost = vogelapprox(tp.n1,tp.n2,allocation);
    if(totalCost!=0)
    {
	   
    	printf("\n\n---------OPTIMAL ALLOCATION MATRIX-----------\n\n");
    	printf("\t");
    	for (j = 0; j < tp.n2; j++) 
		{
        printf("\t\tD%d", j + 1);
    	}
        printf("\n");
    	for (i = 0; i <tp.n1; i++)
		{   
		    printf("\tS%d\t", i + 1);
        	for (j = 0; j <tp.n2; j++) {
            	printf("\t%d\t ", allocation[i][j]);
       	 }
        	printf("\n\n");
    	}
       
    printf("\nTotal transportation cost = %d Rupees\n", totalCost);
	
	printf("\n\n1. New cost matrix \n2. Exit\n\nEnter your choice :");
    scanf("%d",&m);
    if(m!=1)
    {
		printf("\n*****************************************************************\n");
        return 0;
    }
    else
        main();	
    }
    return 0;
}
