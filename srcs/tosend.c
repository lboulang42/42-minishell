
#include "minishell.h"

void	ft_err(char *err_msg)
{
	printf("%s", err_msg);
}

/*
Print full t_env
*/
void	print_t_env(t_env *env)
{
	t_env *tmp;
	tmp = env;
	while (tmp)
	{
		printf("\nVAR IN ENV:\n");
		printf("name:%s\n", tmp->name);
		printf("value:%s\n", tmp->value);
		printf("value:%s\n", tmp->display);
		tmp = tmp->next;
	}
}

t_env	*t_env_new(char	*name, char *value, int display)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		printf("malloc error t_env_new");//
		return (NULL);
	}
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->display = display;
	new->next = NULL;
	return (new);
}

t_env	*get_last_t_env(t_env *env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_t_env(t_env **env, char *name, char *value, int display)
{
	t_env	*temp;
	t_env	*new;
	
	new = t_env_new(name, value, display);
	if (!env || !*env)
	{
		*env = new;
		return ;
	}
	temp = get_last_t_env(*env);
	temp->next = new;
}

void	free_t_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		free((*env));
		*env = tmp;
	}
}

void	init_env(t_data *data, char **env)
{
	int	i;
	t_env   *tmp;
	char	**split_temp;
	char	*value;
	i = -1;
	if (!env || !*env)
	{
		add_t_env(&data->env, NULL, NULL, 0);
		printf("no env ????\n");//
		return ;
	}
	while (env[++i])
	{
		split_temp = ft_split(env[i], '=');
		if (!split_temp)
		{
			printf("split fail in init_env ? pas de = ?\n");//
			continue;
		}
		value = ft_substr(env[i], ft_strlen(split_temp[0])+1, ft_strlen(env[i]));
		if (!value)
		{
			printf("malloc error substr for env[i] = %s\n", env[i]);//
			ft_free_tab((void **)split_temp);
			continue;
		}
		if (!i)
			data->env = t_env_new(split_temp[0], value, 1);
		else
			add_t_env(&data->env, split_temp[0], value, 1);
		ft_free_tab((void **)split_temp);
		free(value);
	}
}