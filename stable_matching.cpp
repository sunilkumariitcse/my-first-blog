#include<bits/stdc++.h>

using namespace std;

/** stak for put the men */

struct Stack
{
	int top;
	unsigned capacity;
	int* array;	
};

struct Stack* createstack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

void expand_capacity(struct Stack* stack)
{
	
	int array1[stack->capacity];
	for(int i=0;i<stack->capacity;i++)
	{
		array1[i]=stack->array[i];
	}
	stack->capacity=2*(stack->capacity);
	stack->array = (int*) malloc(stack->capacity * sizeof(int));
	for(int i=0;i<stack->capacity;i++)
	{
		stack->array[i]=array1[i];
	}
}

int is_empty(struct Stack* stack)
{
	return stack->top == -1;
}
int is_full(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}
void push(struct Stack* stack, int item)
{
    if (is_full(stack))
    {
    		expand_capacity( stack);
     }
    stack->array[++stack->top] = item;
    //printf("%d pushed to stack\n", item);
}

int pop(struct Stack* stack)
{
    if (is_empty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int Top(struct Stack* stack)
{
    if (is_empty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
 
 /***** end stack ******************/
 

int main()
{
	int N;
	//cout<<"NO of men or women:";
	cin>>N;
	int men[N][N],women[N][N];
	/** taking prefrence of women for men ***/
	for(int i=0;i<N;i++)
	{
		//cout<<"Enter priority of "<<i+1<<" Men :";
		for(int j=0;j<N;j++)
		{
			cin>>men[i][j];
			men[i][j]--;
		}
	}
	/**** end taking prefrence of women for men ***/
	
	/** taking prefrence of men for women ***/
	for(int i=0;i<N;i++)
	{
		//cout<<"Enter priority of "<<i+1<<"Women :";
		for(int j=0;j<N;j++)
		{
			cin>>women[i][j];
			women[i][j]--;
		}
	}
	/**** end taking prefrence of men for women ***/
	
	
	struct Stack* men_stack = createstack(N);
	int pair[N];
	for(int i=0;i<N;i++)
	{
		pair[i]=-1;	//index of pair is women and valus is her preferd man
		push(men_stack,N-i-1);
	}	
		
	while(!is_empty(men_stack))
	{
		int current_men=pop(men_stack);
		for(int j=0;j<N;j++)
		{
			int crush=men[current_men][j];
			if(pair[crush]==-1)
			{
				// crush girl is not proposed yet
				pair[crush]=current_men;
				break;
			}	
			else
			{
				// crush girl has proposed
				int engaged_men=pair[crush],k;
				for(k=0;k<N;k++)
				{
					if(women[crush][k]==current_men || women[crush][k]==engaged_men)
						break;
				}
				if(women[crush][k]==current_men)
				{
					//engaged man is not is better preference of this woman
					pair[crush]=current_men;
					push(men_stack, engaged_men);
					break;
				}
			}	
		}
	}
	
	for(int i=0;i<N;i++)
	{
		// i+1 is women and pair[i]+1 is finaly engaged man for that (i+1)th women
		cout<<i+1<<" "<<pair[i]+1<<endl;
	}
	
	return 0;
}
