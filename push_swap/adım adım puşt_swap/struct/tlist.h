typedef struct s_stack
{
	int					data;
	struct s_stack		*next;
}	t_stack;

typedef enum e_layout
{
	ASCENDING,
	DESCENDING,
}	t_layout;