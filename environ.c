#include "shell.h"
/**
 * _shell_environment - Prints the environment variables.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int _shell_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _find_environment_variable - Find the value of an environment variable.
 * @info: Pointer to the info_t structure.
 * @name: The name of the environment variable.
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *_find_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->env;

	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _shell_set_environment_variable - Set an environment variable.
 * @info: Pointer to the info_t structure.
 * Return: 0 on success, 1 on failure.
 */
int _shell_set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_printErrorMessage("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnvironmentVariable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _shell_unset_environment_variable - Unset environment variables.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int _shell_unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_printErrorMessage("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnvironmentVariable(info, info->argv[i]);
	return (0);
}

/**
 * populate_environment_list - Populate environment list.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always 0.
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;

	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

